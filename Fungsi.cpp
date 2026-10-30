#include "App.h"

// ======================== Fungsi perangkat dan logika aplikasi ========================
// Internal receive buffer for the R558-S UART protocol.
static uint8_t fpRxBuffer[320];
static size_t fpRxLength = 0;
static const uint8_t FP_ADDR[4] = {0xFF, 0xFF, 0xFF, 0xFF};

// ======================== UTILITIES ========================
String jsonEscape(const String &in) {
  String out;
  out.reserve(in.length() + 8);
  for (size_t i = 0; i < in.length(); i++) {
    char c = in[i];
    if (c == '"') out += "\\\"";
    else if (c == '\\') out += "\\\\";
    else if (c == '\n') out += "\\n";
    else if (c == '\r') out += "\\r";
    else if ((uint8_t)c < 0x20) out += ' ';
    else out += c;
  }
  return out;
}

String sanitizeName(String name) {
  name.trim();
  name.replace(",", " ");
  name.replace("\r", " ");
  name.replace("\n", " ");
  while (name.indexOf("  ") >= 0) name.replace("  ", " ");
  if (name.length() > 32) name = name.substring(0, 32);
  name.trim();
  return name;
}

String modeText() {
  if (enrollState == ENROLL_RUNNING) return "pendaftaran fingerprint";
  if (configMode) return "Wi-Fi konfigurasi aktif";
  return "absensi standby (Wi-Fi nonaktif)";
}

String enrollmentText() {
  if (enrollState != ENROLL_RUNNING) return systemMessage;
  return systemMessage;
}

String rtcDateString() {
  if (!rtcReady) return "Tidak tersedia";
  DateTime now = rtc.now();
  char b[24];
  snprintf(b, sizeof(b), "%04u-%02u-%02u %02u:%02u:%02u",
           now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  return String(b);
}

void setRgb(bool r, bool g, bool b) {
  digitalWrite(LED_R, r ? HIGH : LOW);
  digitalWrite(LED_G, g ? HIGH : LOW);
  digitalWrite(LED_B, b ? HIGH : LOW);
}

void showFeedback(bool r, bool g, bool b, uint32_t durationMs) {
  overrideR = r; overrideG = g; overrideB = b;
  ledOverrideUntil = millis() + durationMs;
}

void updateLed() {
  if ((int32_t)(millis() - ledOverrideUntil) < 0) {
    setRgb(overrideR, overrideG, overrideB);
    return;
  }
  if (enrollState == ENROLL_RUNNING || configMode) setRgb(true, false, true);
  else setRgb(false, false, true);
}

// ======================== R558-S PACKET FUNCTIONS ========================
void resetFingerprintRx() {
  fpRxLength = 0;
  while (FingerSerial.available()) FingerSerial.read();
}

bool sendFingerprintCommand(const uint8_t *payload, uint16_t payloadLength, bool debug) {
  uint8_t packet[64];
  if (payloadLength + 11 > sizeof(packet)) return false;
  packet[0] = 0xEF; packet[1] = 0x01;
  memcpy(packet + 2, FP_ADDR, sizeof(FP_ADDR));
  packet[6] = 0x01; // command packet
  uint16_t len = payloadLength + 2;
  packet[7] = (uint8_t)(len >> 8);
  packet[8] = (uint8_t)(len & 0xFF);
  memcpy(packet + 9, payload, payloadLength);
  uint32_t sum = packet[6] + packet[7] + packet[8];
  for (uint16_t i = 0; i < payloadLength; i++) sum += payload[i];
  uint16_t checksum = sum & 0xFFFF;
  packet[9 + payloadLength] = checksum >> 8;
  packet[10 + payloadLength] = checksum & 0xFF;
  FingerSerial.write(packet, payloadLength + 11);
  FingerSerial.flush();
  return true;
}

// Non-blocking packet reader. Keeps partial UART packets between loop iterations.
bool readFingerprintPacket(uint8_t *out, uint16_t outCapacity, uint16_t &outLength, bool debug) {
  while (FingerSerial.available() && fpRxLength < sizeof(fpRxBuffer)) {
    fpRxBuffer[fpRxLength++] = (uint8_t)FingerSerial.read();
  }
  for (;;) {
    if (fpRxLength < 2) return false;
    size_t headerAt = 0;
    while (headerAt + 1 < fpRxLength && !(fpRxBuffer[headerAt] == 0xEF && fpRxBuffer[headerAt + 1] == 0x01)) headerAt++;
    if (headerAt + 1 >= fpRxLength) {
      bool keepEF = fpRxBuffer[fpRxLength - 1] == 0xEF;
      fpRxLength = keepEF ? 1 : 0;
      if (keepEF) fpRxBuffer[0] = 0xEF;
      return false;
    }
    if (headerAt > 0) {
      memmove(fpRxBuffer, fpRxBuffer + headerAt, fpRxLength - headerAt);
      fpRxLength -= headerAt;
    }
    if (fpRxLength < 9) return false;
    uint16_t packetLen = ((uint16_t)fpRxBuffer[7] << 8) | fpRxBuffer[8];
    if (packetLen < 2 || packetLen > 260) {
      memmove(fpRxBuffer, fpRxBuffer + 1, --fpRxLength);
      continue;
    }
    size_t total = 9 + packetLen;
    if (fpRxLength < total) return false;
    if (fpRxBuffer[6] != 0x07) {
      memmove(fpRxBuffer, fpRxBuffer + total, fpRxLength - total);
      fpRxLength -= total;
      continue;
    }
    uint16_t payloadLen = packetLen - 2;
    uint32_t sum = fpRxBuffer[6] + fpRxBuffer[7] + fpRxBuffer[8];
    for (uint16_t i = 0; i < payloadLen; i++) sum += fpRxBuffer[9 + i];
    uint16_t expected = sum & 0xFFFF;
    uint16_t received = ((uint16_t)fpRxBuffer[9 + payloadLen] << 8) | fpRxBuffer[10 + payloadLen];
    if (expected != received) {
      memmove(fpRxBuffer, fpRxBuffer + 1, --fpRxLength);
      continue;
    }
    if (payloadLen > outCapacity) {
      memmove(fpRxBuffer, fpRxBuffer + total, fpRxLength - total);
      fpRxLength -= total;
      return false;
    }
    memcpy(out, fpRxBuffer + 9, payloadLen);
    outLength = payloadLen;
    memmove(fpRxBuffer, fpRxBuffer + total, fpRxLength - total);
    fpRxLength -= total;
    return true;
  }
}

bool readFingerprintPacketBlocking(uint8_t *out, uint16_t outCapacity, uint16_t &outLength, uint32_t timeoutMs) {
  uint32_t start = millis();
  while (millis() - start < timeoutMs) {
    if (readFingerprintPacket(out, outCapacity, outLength, true)) return true;
    delay(1);
  }
  return false;
}

bool fingerprintTransaction(const uint8_t *command, uint16_t commandLength,
                            uint8_t *response, uint16_t responseCapacity,
                            uint16_t &responseLength, uint32_t timeoutMs) {
  if (fingerOperation != FOP_NONE) return false;
  resetFingerprintRx();
  if (!sendFingerprintCommand(command, commandLength, true)) return false;
  return readFingerprintPacketBlocking(response, responseCapacity, responseLength, timeoutMs);
}

bool verifyFingerprintSensor() {
  // R558-S previously worked with TemplateNum (0x1D), AutoEnroll (0x31),
  // and AutoIdentify (0x32). Do not gate readiness on VfyPwd (0x13): a
  // module with a non-default password can reject that command even though
  // fingerprint operations work. Confirm readiness using the known-good
  // TemplateNum command and validate its three-byte ACK payload.
  const uint8_t command[] = {0x1D};
  uint8_t response[16];
  uint16_t len = 0;

  if (!fingerprintTransaction(command, sizeof(command), response,
                              sizeof(response), len, 3000)) {
    return false;
  }

  if (len < 3 || response[0] != 0x00) {
    return false;
  }

  uint16_t count = ((uint16_t)response[1] << 8) | response[2];
  return true;
}

bool readTemplateCount(uint16_t &count) {
  const uint8_t command[] = {0x1D};
  uint8_t response[40]; uint16_t len = 0;
  if (!fingerprintTransaction(command, sizeof(command), response, sizeof(response), len, 3000)) return false;
  if (len < 3 || response[0] != 0x00) return false;
  count = ((uint16_t)response[1] << 8) | response[2];
  return true;
}

bool readTemplateIndexPage(uint8_t page, uint8_t *bitmap, size_t bitmapCapacity, size_t &bitmapLength) {
  const uint8_t command[] = {0x1F, page};
  uint8_t response[64]; uint16_t len = 0;
  if (!fingerprintTransaction(command, sizeof(command), response, sizeof(response), len, 3000)) return false;
  if (len < 2 || response[0] != 0x00) return false;
  bitmapLength = len - 1;
  if (bitmapLength > bitmapCapacity) bitmapLength = bitmapCapacity;
  memcpy(bitmap, response + 1, bitmapLength);
  return bitmapLength > 0;
}

bool templateIdOccupied(uint16_t id, bool &known) {
  known = false;
  if (id > 255) {
    uint8_t map[40]; size_t n = 0;
    if (!readTemplateIndexPage(1, map, sizeof(map), n)) return false;
    uint16_t bit = id - 256;
    if ((bit / 8) >= n) return false;
    known = true;
    return (map[bit / 8] & (1U << (bit % 8))) != 0;
  }
  uint8_t map[40]; size_t n = 0;
  if (!readTemplateIndexPage(0, map, sizeof(map), n)) return false;
  if ((id / 8) >= n) return false;
  known = true;
  return (map[id / 8] & (1U << (id % 8))) != 0;
}

String findUserName(uint16_t id);
bool saveUser(uint16_t id, const String &name);

uint16_t maxUserIdInCsv() {
  if (!sdReady) return 0;
  File f = SD.open("/users.csv", FILE_READ);
  if (!f) return 0;
  uint16_t highest = 0;
  while (f.available()) {
    String line = f.readStringUntil('\n'); line.trim();
    if (!line.length() || line.startsWith("id,")) continue;
    int comma = line.indexOf(','); if (comma <= 0) continue;
    long parsed = line.substring(0, comma).toInt();
    if (parsed > highest && parsed <= 65535) highest = (uint16_t)parsed;
  }
  f.close();
  return highest;
}

bool userIdExistsInCsv(uint16_t id) {
  if (!sdReady) return true;
  File f = SD.open("/users.csv", FILE_READ);
  if (!f) return true;
  bool exists = false;
  while (f.available()) {
    String line = f.readStringUntil('\n'); line.trim();
    if (!line.length() || line.startsWith("id,")) continue;
    int comma = line.indexOf(','); if (comma <= 0) continue;
    if ((uint16_t)line.substring(0, comma).toInt() == id) { exists = true; break; }
  }
  f.close(); return exists;
}

bool templateStoredAtId(uint16_t id, bool &known) {
  bool occupied = templateIdOccupied(id, known);
  if (known) return occupied;
  const uint8_t loadCommand[] = {0x07, 0x01, (uint8_t)(id >> 8), (uint8_t)id};
  uint8_t response[16]; uint16_t responseLen = 0;
  if (fingerprintTransaction(loadCommand, sizeof(loadCommand), response, sizeof(response), responseLen, 2000) && responseLen >= 1) {
    if (response[0] == 0x00) { known = true; return true; }
    if (response[0] == 0x23) { known = true; return false; }
  }
  known = false;
  return false;
}

uint16_t nextAvailableFingerprintId() {
  if (!sdReady || !fingerprintReady) return 0;
  uint8_t bitmap0[40]; size_t bytes0 = 0;
  bool hasBitmap = readTemplateIndexPage(0, bitmap0, sizeof(bitmap0), bytes0);
  uint8_t bitmap1[40]; size_t bytes1 = 0;
  bool hasBitmap1 = false;
  if (FP_CAPACITY > 256) hasBitmap1 = readTemplateIndexPage(1, bitmap1, sizeof(bitmap1), bytes1);
  uint16_t csvMax = maxUserIdInCsv();
  for (uint16_t id = 1; id <= FP_CAPACITY; id++) {
    if (userIdExistsInCsv(id)) continue;
    bool known = false;
    bool occupied = false;
    if (hasBitmap && id <= 255 && (id / 8) < bytes0) {
      occupied = (bitmap0[id / 8] & (1U << (id % 8))) != 0;
      known = true;
    } else if (hasBitmap1 && id > 255 && ((id - 256) / 8) < bytes1) {
      uint16_t bit = id - 256;
      occupied = (bitmap1[bit / 8] & (1U << (bit % 8))) != 0;
      known = true;
    }
    // If index-table access is unavailable, use the next sequential CSV ID.
    // AutoEnroll refuses an occupied ID (0x22); it does not overwrite a template.
    if (!hasBitmap || !known) {
      // Fallback: probe this slot directly through LoadChar (0x07).
      // R558-S returns 0x23 for an empty slot and 0x00 for an occupied slot.
      const uint8_t loadCommand[] = {0x07, 0x01, (uint8_t)(id >> 8), (uint8_t)id};
      uint8_t response[16]; uint16_t responseLen = 0;
      if (fingerprintTransaction(loadCommand, sizeof(loadCommand), response, sizeof(response), responseLen, 2000) && responseLen >= 1) {
        if (response[0] == 0x23) return id;
        if (response[0] == 0x00) continue;
      }
      if (id <= csvMax) continue;
      // Last-resort candidate; AutoEnroll rejects occupied IDs and will not overwrite them.
      return id;
    }
    if (!occupied) return id;
  }
  return 0;
}

const char *fingerErrorText(uint8_t code) {
  switch (code) {
    case 0x00: return "Berhasil";
    case 0x01: return "Kesalahan menerima paket";
    case 0x07: return "Fitur sidik jari gagal dibuat";
    case 0x08: return "Sidik jari tidak cocok";
    case 0x09: return "Sidik jari tidak ditemukan";
    case 0x0A: return "Penggabungan template gagal";
    case 0x0B: return "ID di luar rentang";
    case 0x18: return "Gagal membaca/menulis Flash";
    case 0x1E: return "Pendaftaran otomatis gagal";
    case 0x1F: return "Database fingerprint penuh";
    case 0x22: return "ID sudah memiliki template";
    case 0x23: return "Template ID kosong";
    case 0x24: return "Database fingerprint kosong";
    case 0x25: return "Jumlah pemindaian tidak valid";
    case 0x26: return "Waktu tunggu habis";
    case 0x27: return "Sidik jari sudah terdaftar";
    case 0x28: return "Area sidik jari tidak sesuai";
    case 0x31: return "Perintah tidak cocok dengan tingkat keamanan";
    case 0x35: return "Data tidak valid";
    case 0x3B: return "Kualitas template buruk";
    default: return "Kode respons belum dikenali";
  }
}

// ======================== CSV / MICROSD ========================
void createCsvFilesIfNeeded() {
  if (!sdReady) return;
  // Recover an interrupted users.csv swap after a power loss during deletion.
  if (!SD.exists("/users.csv") && SD.exists("/users.bak")) {
    SD.rename("/users.bak", "/users.csv");
  }
  if (SD.exists("/users.csv") && SD.exists("/users.bak")) SD.remove("/users.bak");
  if (SD.exists("/users.tmp")) SD.remove("/users.tmp");
  if (!SD.exists("/users.csv")) {
    File f = SD.open("/users.csv", FILE_WRITE);
    if (f) { f.println("id,name"); f.close(); }
  }
  if (!SD.exists("/attendance.csv")) {
    File f = SD.open("/attendance.csv", FILE_WRITE);
    if (f) { f.println("date,time,id,name,confidence"); f.close(); }
  }
}

String findUserName(uint16_t id) {
  if (!sdReady) return "";
  File f = SD.open("/users.csv", FILE_READ);
  if (!f) return "";
  String found;
  while (f.available()) {
    String line = f.readStringUntil('\n'); line.trim();
    if (!line.length() || line.startsWith("id,")) continue;
    int comma = line.indexOf(','); if (comma < 0) continue;
    if ((uint16_t)line.substring(0, comma).toInt() == id) { found = line.substring(comma + 1); break; }
  }
  f.close(); return found;
}

bool saveUser(uint16_t id, const String &name) {
  if (!sdReady || userIdExistsInCsv(id)) return false;
  File f = SD.open("/users.csv", FILE_APPEND);
  if (!f) return false;
  f.print((int)id); f.print(','); f.println(name); f.flush();
  bool okay = !f.getWriteError(); f.close(); return okay;
}

// Read users.csv with an explicit I/O-success flag (separate from "not found").
bool readUserMappingExists(uint16_t wantedId, bool &exists) {
  exists = false;
  if (!sdReady) return false;
  File f = SD.open("/users.csv", FILE_READ);
  if (!f) return false;
  while (f.available()) {
    String line = f.readStringUntil('\n'); line.trim();
    if (!line.length() || line.startsWith("id,")) continue;
    int comma = line.indexOf(',');
    if (comma <= 0) continue;
    if ((uint16_t)line.substring(0, comma).toInt() == wantedId) {
      exists = true;
      break;
    }
  }
  f.close();
  return true;
}

// Remove a single ID from users.csv via a temporary file and rollback backup.
// The fingerprint template is handled separately by DeleteChar (0x0C).
bool removeUserMappingFromCsv(uint16_t wantedId, bool &removed) {
  removed = false;
  if (!sdReady) return false;
  File in = SD.open("/users.csv", FILE_READ);
  if (!in) return false;

  SD.remove("/users.tmp");
  File out = SD.open("/users.tmp", FILE_WRITE);
  if (!out) { in.close(); return false; }

  bool found = false;
  bool writeOk = true;
  while (in.available()) {
    String line = in.readStringUntil('\n');
    String check = line; check.trim();
    bool matches = false;
    if (check.length() && !check.startsWith("id,")) {
      int comma = check.indexOf(',');
      if (comma > 0 && (uint16_t)check.substring(0, comma).toInt() == wantedId) matches = true;
    }
    if (matches) { found = true; continue; }
    out.println(check);
    if (out.getWriteError()) { writeOk = false; break; }
  }
  in.close();
  out.flush();
  if (out.getWriteError()) writeOk = false;
  out.close();

  if (!writeOk) { SD.remove("/users.tmp"); return false; }
  if (!found) { SD.remove("/users.tmp"); return true; }

  // Validate the temporary file before swapping it with the original.
  bool tempHasId = false;
  File verify = SD.open("/users.tmp", FILE_READ);
  if (!verify) { SD.remove("/users.tmp"); return false; }
  while (verify.available()) {
    String line = verify.readStringUntil('\n'); line.trim();
    if (!line.length() || line.startsWith("id,")) continue;
    int comma = line.indexOf(',');
    if (comma > 0 && (uint16_t)line.substring(0, comma).toInt() == wantedId) { tempHasId = true; break; }
  }
  verify.close();
  if (tempHasId) { SD.remove("/users.tmp"); return false; }

  SD.remove("/users.bak");
  if (!SD.rename("/users.csv", "/users.bak")) { SD.remove("/users.tmp"); return false; }
  if (!SD.rename("/users.tmp", "/users.csv")) {
    SD.rename("/users.bak", "/users.csv");
    SD.remove("/users.tmp");
    return false;
  }
  SD.remove("/users.bak");
  removed = true;
  return true;
}

bool appendAttendance(uint16_t id, const String &name, uint16_t confidence) {
  if (!sdReady) return false;
  File f = SD.open("/attendance.csv", FILE_APPEND);
  if (!f) return false;
  String datePart = "RTC_UNAVAILABLE", timePart = "--:--:--";
  if (rtcReady) {
    DateTime now = rtc.now(); char d[12], t[10];
    snprintf(d, sizeof(d), "%04u-%02u-%02u", now.year(), now.month(), now.day());
    snprintf(t, sizeof(t), "%02u:%02u:%02u", now.hour(), now.minute(), now.second());
    datePart = d; timePart = t;
  }
  f.print(datePart); f.print(','); f.print(timePart); f.print(',');
  f.print(id); f.print(','); f.print(name); f.print(','); f.println(confidence);
  f.flush(); bool okay = !f.getWriteError(); f.close(); return okay;
}

String csvField(const String &line, uint8_t wanted) {
  int start = 0;
  for (uint8_t field = 0; field < wanted; field++) {
    int comma = line.indexOf(',', start); if (comma < 0) return ""; start = comma + 1;
  }
  int end = line.indexOf(',', start); if (end < 0) end = line.length();
  return line.substring(start, end);
}

// ======================== AUDIO / I2S ========================
uint16_t readLE16(File &f) {
  int a = f.read(), b = f.read();
  if (a < 0 || b < 0) return 0;
  return (uint16_t)(((uint16_t)b << 8) | (uint16_t)a);
}
uint32_t readLE32(File &f) {
  int a=f.read(), b=f.read(), c=f.read(), d=f.read();
  if (a<0||b<0||c<0||d<0) return 0;
  return ((uint32_t)d<<24)|((uint32_t)c<<16)|((uint32_t)b<<8)|(uint32_t)a;
}
bool readFourCC(File &f, char *out) {
  if (f.read((uint8_t *)out, 4) != 4) return false;
  out[4] = '\0'; return true;
}

void initI2S() {
  i2s_config_t cfg = {};
  cfg.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
  cfg.sample_rate = 16000;
  cfg.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;
  cfg.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;
  cfg.communication_format = I2S_COMM_FORMAT_I2S_MSB;
  cfg.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;
  cfg.dma_buf_count = 8;
  cfg.dma_buf_len = 256;
  cfg.use_apll = false;
  cfg.tx_desc_auto_clear = true;
  cfg.fixed_mclk = 0;
  esp_err_t err = i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL);
  if (err != ESP_OK) { Serial.printf("I2S install gagal: %d\n", (int)err); i2sReady = false; return; }
  i2s_pin_config_t pins = {};
  pins.bck_io_num = I2S_BCLK; pins.ws_io_num = I2S_LRC;
  pins.data_out_num = I2S_DOUT; pins.data_in_num = I2S_PIN_NO_CHANGE;
  pins.mck_io_num = I2S_PIN_NO_CHANGE;
  err = i2s_set_pin(I2S_NUM_0, &pins);
  if (err != ESP_OK) { Serial.printf("I2S pin gagal: %d\n", (int)err); i2sReady = false; return; }
  i2s_zero_dma_buffer(I2S_NUM_0);
  i2sReady = true;
  Serial.println("I2S MAX98357A siap.");
}

bool startAudio(const char *path) {
  if (!sdReady || !i2sReady) return false;
  if (audioFile) audioFile.close();
  audioPlaying = false; audioBytesRemaining = 0;
  audioFile = SD.open(path, FILE_READ);
  if (!audioFile) { Serial.printf("Audio tidak ditemukan: %s\n", path); return false; }
  char id[5];
  if (!readFourCC(audioFile, id) || strcmp(id, "RIFF") != 0) { audioFile.close(); return false; }
  (void)readLE32(audioFile);
  if (!readFourCC(audioFile, id) || strcmp(id, "WAVE") != 0) { audioFile.close(); return false; }
  uint16_t format=0, channels=0, bits=0; uint32_t sampleRate=0, dataSize=0, dataStart=0;
  bool haveFmt=false, haveData=false;
  while (audioFile.available()) {
    if (!readFourCC(audioFile, id)) break;
    uint32_t chunkSize = readLE32(audioFile);
    uint32_t chunkStart = audioFile.position();
    if (strcmp(id, "fmt ") == 0) {
      if (chunkSize < 16) { audioFile.close(); return false; }
      format = readLE16(audioFile); channels = readLE16(audioFile); sampleRate = readLE32(audioFile);
      (void)readLE32(audioFile); (void)readLE16(audioFile); bits = readLE16(audioFile); haveFmt = true;
      uint32_t endPos = chunkStart + chunkSize + (chunkSize & 1U);
      if (endPos <= audioFile.size()) audioFile.seek(endPos);
    } else if (strcmp(id, "data") == 0) {
      dataStart = chunkStart; dataSize = chunkSize; haveData = true; break;
    } else {
      uint32_t endPos = chunkStart + chunkSize + (chunkSize & 1U);
      if (endPos > audioFile.size()) break;
      audioFile.seek(endPos);
    }
  }
  if (!haveFmt || !haveData || format != 1 || bits != 16 || (channels != 1 && channels != 2) || sampleRate < 8000 || sampleRate > 48000 || dataStart >= audioFile.size()) {
    Serial.printf("Format WAV tidak didukung: %s (PCM 16-bit mono/stereo, 8-48 kHz)\n", path); audioFile.close(); return false;
  }
  uint32_t availableData = (uint32_t)(audioFile.size() - dataStart);
  if (dataSize > availableData) dataSize = availableData;
  dataSize &= ~1U;
  if (!audioFile.seek(dataStart)) { audioFile.close(); return false; }
  audioChannels = channels; audioSampleRate = sampleRate; audioBytesRemaining = dataSize;
  if (i2s_set_clk(I2S_NUM_0, audioSampleRate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO) != ESP_OK) { audioFile.close(); return false; }
  i2s_zero_dma_buffer(I2S_NUM_0); audioPlaying = true;
  return true;
}

void loopAudio() {
  if (!audioPlaying) return;
  if (!audioFile || audioBytesRemaining == 0) {
    if (audioFile) audioFile.close(); audioPlaying = false; i2s_zero_dma_buffer(I2S_NUM_0); return;
  }
  uint8_t inputBuffer[512]; uint8_t outputBuffer[1024];
  size_t toRead = audioBytesRemaining > sizeof(inputBuffer) ? sizeof(inputBuffer) : (size_t)audioBytesRemaining;
  toRead &= ~((size_t)1);
  size_t got = audioFile.read(inputBuffer, toRead); got &= ~((size_t)1);
  if (got == 0) { audioFile.close(); audioPlaying = false; audioBytesRemaining = 0; i2s_zero_dma_buffer(I2S_NUM_0); return; }
  // Terapkan volume digital ke sampel PCM signed 16-bit sebelum dikirim ke I2S.
  // Volume disimpan di Preferences dan nilainya 0–100 persen.
  for (size_t i = 0; i + 1 < got; i += 2) {
    int16_t sample = (int16_t)((uint16_t)inputBuffer[i] | ((uint16_t)inputBuffer[i + 1] << 8));
    int32_t scaled = ((int32_t)sample * (int32_t)audioVolume) / 100;
    if (scaled > 32767) scaled = 32767;
    if (scaled < -32768) scaled = -32768;
    inputBuffer[i] = (uint8_t)(scaled & 0xFF);
    inputBuffer[i + 1] = (uint8_t)((scaled >> 8) & 0xFF);
  }
  size_t outputBytes = got;
  if (audioChannels == 1) {
    size_t samples = got / 2;
    for (size_t i = 0; i < samples; i++) {
      uint8_t lo=inputBuffer[i*2], hi=inputBuffer[i*2+1];
      outputBuffer[i*4]=lo; outputBuffer[i*4+1]=hi; outputBuffer[i*4+2]=lo; outputBuffer[i*4+3]=hi;
    }
    outputBytes = samples * 4;
  } else memcpy(outputBuffer, inputBuffer, got);
  size_t writtenTotal = 0; uint32_t writeStarted = millis();
  while (writtenTotal < outputBytes) {
    size_t written = 0;
    esp_err_t err = i2s_write(I2S_NUM_0, outputBuffer + writtenTotal, outputBytes - writtenTotal, &written, pdMS_TO_TICKS(100));
    if (err == ESP_OK && written > 0) { writtenTotal += written; writeStarted = millis(); }
    else if (millis() - writeStarted > 1000) { Serial.println("Audio dihentikan: I2S tidak menerima data."); audioFile.close(); audioPlaying=false; audioBytesRemaining=0; i2s_zero_dma_buffer(I2S_NUM_0); return; }
    else delay(1);
  }
  audioBytesRemaining -= got;
}

// ======================== FINGERPRINT JOB HANDLERS ========================
void startRemovalWait() {
  waitingFingerRemoval = true;
  removeProbePending = false;
  removeWaitStartedAt = millis();
  lastRemoveProbeAt = 0;
}

void finishEnrollment(bool success, const String &message) {
  fingerOperation = FOP_NONE;
  identifyActive = false;
  enrollState = ENROLL_IDLE;
  enrollName = "";
  enrollmentStartedAt = 0;
  systemMessage = message;
  startRemovalWait();
  if (success) {
    showFeedback(false, true, false, 2500);
    startAudio("/daftar_berhasil.wav");
  } else {
    showFeedback(true, false, false, 2000);
  }
  Serial.println(systemMessage);
}

void completeEnrollmentFromSensor() {
  fingerOperation = FOP_NONE;
  uint16_t newCount = templateCountValue;
  bool countOk = readTemplateCount(newCount);
  if (countOk) templateCountValue = newCount;
  if (!countOk || newCount <= enrollCountBefore) {
    finishEnrollment(false, "Sensor menyelesaikan tahap pendaftaran, tetapi perubahan jumlah template tidak dapat diverifikasi. Periksa database sensor sebelum mengulang.");
    return;
  }
  uint16_t completedId = enrollId;
  String completedName = enrollName;
  if (!saveUser(completedId, completedName)) {
    finishEnrollment(false, "Template berhasil disimpan ke sensor pada ID " + String(completedId) + ", tetapi metadata gagal ditulis ke users.csv. Jangan ulangi ID ini; periksa MicroSD lalu tambahkan pasangan ID,nama secara manual.");
    return;
  }
  finishEnrollment(true, "Pendaftaran berhasil: " + completedName + " (ID " + String(completedId) + "). Template sensor dan users.csv sudah diperbarui.");
}

void handleEnrollmentPacket(const uint8_t *data, uint16_t len) {
  if (len < 2) return;
  uint8_t code = data[0];
  uint8_t stage = data[1];
  uint8_t detail = len >= 3 ? data[2] : 0;
  if (code != 0x00) {
    fingerOperation = FOP_NONE;
    String message = "Pendaftaran gagal: " + String(fingerErrorText(code)) + " (0x" + String(code, HEX) + ").";
    if (code == 0x22) message += " ID tujuan sudah berisi template; tidak ada data yang ditimpa. Silakan mulai ulang agar ID kosong dipilih.";
    if (code == 0x27) message += " Sensor mendeteksi sidik jari duplikat.";
    finishEnrollment(false, message);
    return;
  }
  switch (stage) {
    case 0:
      systemMessage = "Silakan tempelkan jari Anda untuk pemindaian pertama.";
      // Play once even if firmware repeats this progress event.
      if (!enrollFirstPromptPlayed) {
        enrollFirstPromptPlayed = true;
        startAudio("/silahkan_tempelkan_jari.wav");
      }
      break;
    case 1:
      systemMessage = detail == 2 ? "Pemindaian pertama selesai. Tempelkan jari yang sama untuk pemindaian kedua." : "Jari terdeteksi. Tahan posisi hingga pemindaian pertama selesai.";
      break;
    case 2:
      systemMessage = detail == 2 ? "Pemindaian kedua terbaca. Sensor sedang memproses fitur sidik jari." : "Pemindaian pertama terbaca. Sensor sedang memproses fitur sidik jari.";
      break;
    case 3:
      systemMessage = "Angkat jari Anda lalu tempelkan kembali jari yang sama.";
      // Combined lift-and-repeat prompt for the second capture.
      if (!enrollSecondPromptPlayed) {
        enrollSecondPromptPlayed = true;
        startAudio("/angkat_tempelkan_kembali.wav");
      }
      break;
    case 4:
      systemMessage = "Sensor sedang menggabungkan dan memeriksa template sidik jari. Tunggu sebentar.";
      break;
    case 5:
      if (code == 0x27) {
        fingerOperation = FOP_NONE;
        finishEnrollment(false, "Sidik jari ini sudah terdaftar di sensor. Gunakan jari lain atau pastikan database pengguna cocok.");
        return;
      }
      systemMessage = "Template terbentuk. Sensor sedang memvalidasi hasil pendaftaran.";
      break;
    case 6:
      completeEnrollmentFromSensor();
      return;
    default:
      systemMessage = "Pendaftaran sedang diproses oleh sensor (tahap " + String(stage) + ").";
      break;
  }
}

void handleIdentificationPacket(const uint8_t *data, uint16_t len) {
  if (len < 2) return;
  uint8_t code = data[0], stage = data[1];
  if (stage == 0 && code == 0x00) {
    systemMessage = "Siap absensi. Tempelkan sidik jari pada sensor.";
    return;
  }
  if (stage == 1 && code == 0x00) {
    systemMessage = "Sidik jari terbaca. Sedang mencocokkan dengan database.";
    return;
  }
  if (stage == 5) {
    fingerOperation = FOP_NONE;
    identifyActive = false;
    if (code == 0x00 && len >= 6) {
      uint16_t foundId = ((uint16_t)data[2] << 8) | data[3];
      uint16_t score = ((uint16_t)data[4] << 8) | data[5];
      String name = findUserName(foundId);
      if (!name.length()) {
        systemMessage = "Sidik jari cocok pada ID " + String(foundId) + ", tetapi nama tidak ditemukan di users.csv. Periksa pemetaan ID di MicroSD.";
        showFeedback(true, false, false, 2200);
        startAudio("/absen_tidak_dikenal.wav");
        startRemovalWait();
        return;
      }
      if (foundId == lastAttendanceId && millis() - lastAttendanceAt < DUPLICATE_COOLDOWN_MS) {
        systemMessage = "Sidik jari dikenali: " + name + ". Absensi untuk pengguna ini sudah tercatat dalam 30 detik terakhir.";
        showFeedback(false, false, true, 1200);
        startRemovalWait();
        return;
      }
      if (appendAttendance(foundId, name, score)) {
        systemMessage = "Absensi berhasil: " + name + " (ID " + String(foundId) + "). Tersimpan di attendance.csv.";
        lastAttendanceId = foundId; lastAttendanceAt = millis();
        showFeedback(false, true, false, 2200);
        startAudio("/absensi_berhasil.wav");
      } else {
        systemMessage = "Sidik jari cocok: " + name + ", tetapi gagal menulis attendance.csv. Periksa MicroSD.";
        showFeedback(true, false, false, 2200);
      }
      startRemovalWait();
      Serial.println(systemMessage);
      return;
    }
    if (code == 0x08 || code == 0x09 || code == 0x07) {
      systemMessage = (code == 0x07) ? "Gambar sidik jari kurang jelas. Tempelkan jari dengan rata dan coba lagi." : "Sidik jari tidak dikenal. Tidak ada absensi yang dicatat.";
      showFeedback(true, false, false, 1700);
      if (code != 0x07) startAudio("/absen_tidak_dikenal.wav");
      startRemovalWait();
      return;
    }
  }
  if (code == 0x24 || code == 0x23) {
    fingerOperation = FOP_NONE; identifyActive = false;
    templateCountValue = 0;
    systemMessage = "Database fingerprint kosong. Daftarkan pengguna melalui halaman konfigurasi.";
    nextIdentifyAt = millis() + 3000;
    return;
  }
  if (code == 0x26) {
    fingerOperation = FOP_NONE; identifyActive = false;
    nextIdentifyAt = millis() + IDENTIFY_RETRY_MS;
    return;
  }
  if (code != 0x00) {
    fingerOperation = FOP_NONE; identifyActive = false;
    systemMessage = "AutoIdentify gagal: " + String(fingerErrorText(code)) + " (0x" + String(code, HEX) + ").";
    nextIdentifyAt = millis() + 1500;
  }
}

void handleRemoveProbePacket(const uint8_t *data, uint16_t len) {
  removeProbePending = false;
  fingerOperation = FOP_NONE;
  if (len >= 1 && data[0] == 0x02) {
    waitingFingerRemoval = false;
    systemMessage = "Sensor siap menerima sidik jari berikutnya.";
    nextIdentifyAt = millis() + 250;
    return;
  }
  if (millis() - removeWaitStartedAt > REMOVE_WAIT_MAX_MS) {
    waitingFingerRemoval = false;
    systemMessage = "Batas tunggu pengangkatan jari tercapai. Sistem kembali siaga.";
    nextIdentifyAt = millis() + 700;
    return;
  }
  // code 00 means a finger is still on the sensor; retry a probe shortly.
  lastRemoveProbeAt = millis();
}

void processFingerprintSerial() {
  uint8_t payload[270]; uint16_t len = 0;
  if (!readFingerprintPacket(payload, sizeof(payload), len, true)) return;
  switch (fingerOperation) {
    case FOP_ENROLL: handleEnrollmentPacket(payload, len); break;
    case FOP_IDENTIFY: handleIdentificationPacket(payload, len); break;
    case FOP_REMOVE_PROBE: handleRemoveProbePacket(payload, len); break;
    default:
      // Abaikan respons di luar operasi aktif agar Serial Monitor tetap ringkas.
      break;
  }
}

void processEnrollmentTimeout() {
  if (enrollState != ENROLL_RUNNING || fingerOperation != FOP_ENROLL) return;
  if (millis() - enrollmentStartedAt <= ENROLL_TIMEOUT_MS) return;
  Serial.println("Waktu pendaftaran habis; mengirim Cancel 0x30.");
  const uint8_t cancelCommand[] = {0x30};
  sendFingerprintCommand(cancelCommand, sizeof(cancelCommand), true);
  fingerOperation = FOP_NONE;
  enrollState = ENROLL_IDLE;
  enrollName = "";
  systemMessage = "Pendaftaran habis waktu dan dibatalkan. Silakan mulai lagi.";
  startRemovalWait();
  showFeedback(true, false, false, 1800);
}

void beginAutoEnroll(uint16_t id, const String &name) {
  // AutoEnroll packet: 0x31, ID(2 bytes), capture count, parameter(2 bytes).
  const uint8_t command[] = {0x31, (uint8_t)(id >> 8), (uint8_t)id, 0x02, 0x00, 0x00};
  enrollName = name;
  enrollId = id;
  enrollCountBefore = templateCountValue;
  enrollFirstPromptPlayed = false;
  enrollSecondPromptPlayed = false;
  enrollmentStartedAt = millis();
  enrollState = ENROLL_RUNNING;
  waitingFingerRemoval = false;
  identifyActive = false;
  fingerOperation = FOP_ENROLL;
  systemMessage = "Pendaftaran ID " + String(id) + " dimulai. Tempelkan jari pada sensor.";
  showFeedback(true, false, true, 1200);
  Serial.println(systemMessage);
  if (!sendFingerprintCommand(command, sizeof(command), true)) {
    finishEnrollment(false, "Gagal mengirim perintah AutoEnroll ke sensor.");
  }
}

void beginAutoIdentify() {
  // ID 0xFFFF requests one-to-many search across the entire fingerprint database.
  // parameters=0 asks the sensor to report progress/status steps.
  const uint8_t command[] = {0x32, 0x03, 0xFF, 0xFF, 0x00, 0x00};
  if (!sendFingerprintCommand(command, sizeof(command), false)) {
    nextIdentifyAt = millis() + 1500; return;
  }
  fingerOperation = FOP_IDENTIFY;
  identifyActive = true;
  identifyStartedAt = millis();
}

void processFingerprintScheduler() {
  if (fingerOperation == FOP_IDENTIFY && millis() - identifyStartedAt > 20000UL) {
    const uint8_t cancelCommand[] = {0x30};
    sendFingerprintCommand(cancelCommand, sizeof(cancelCommand), false);
    fingerOperation = FOP_NONE; identifyActive = false;
    resetFingerprintRx(); nextIdentifyAt = millis() + 700;
  }
  if (fingerOperation == FOP_REMOVE_PROBE) {
    if (removeProbePending && millis() - removeProbeSentAt > 1200) {
      removeProbePending = false;
      fingerOperation = FOP_NONE;
      lastRemoveProbeAt = millis();
    }
    return;
  }
  if (!fingerprintReady || enrollState != ENROLL_IDLE || audioPlaying) return;
  if (waitingFingerRemoval) {
    if (fingerOperation == FOP_NONE && !removeProbePending && millis() - lastRemoveProbeAt >= REMOVE_PROBE_INTERVAL_MS) {
      const uint8_t getImage[] = {0x01};
      if (sendFingerprintCommand(getImage, sizeof(getImage), false)) {
        fingerOperation = FOP_REMOVE_PROBE;
        removeProbePending = true;
        removeProbeSentAt = millis();
        lastRemoveProbeAt = millis();
      }
    } else if (removeProbePending && millis() - removeProbeSentAt > 1200) {
      removeProbePending = false; fingerOperation = FOP_NONE; lastRemoveProbeAt = millis();
    }
    return;
  }
  if (fingerOperation == FOP_NONE && templateCountValue > 0 && millis() >= nextIdentifyAt) beginAutoIdentify();
}

// ======================== WIFI CONFIGURATION ========================
bool startConfigWifi() {
  WiFi.mode(internetSSID.length() ? WIFI_AP_STA : WIFI_AP);
  delay(100);
  bool ok = WiFi.softAP(apSSID.c_str(), apPassword.c_str());
  if (ok) {
    if (internetSSID.length()) {
      WiFi.begin(internetSSID.c_str(), internetPassword.c_str());
      Serial.printf("Menghubungkan Wi-Fi internet: %s\n", internetSSID.c_str());
    }
    server.begin(); configMode = true;
    systemMessage = "Wi-Fi konfigurasi aktif. Sambungkan ke " + apSSID + " lalu buka http://192.168.4.1.";
    Serial.println(systemMessage);
  } else {
    configMode = false; WiFi.softAPdisconnect(true); WiFi.mode(WIFI_OFF);
    systemMessage = "Gagal mengaktifkan Wi-Fi konfigurasi.";
  }
  return ok;
}

void cancelActiveFingerprintOperation() {
  if (fingerOperation == FOP_ENROLL || fingerOperation == FOP_IDENTIFY) {
    const uint8_t cancelCommand[] = {0x30};
    sendFingerprintCommand(cancelCommand, sizeof(cancelCommand), true);
    uint8_t response[16]; uint16_t len = 0;
    (void)readFingerprintPacketBlocking(response, sizeof(response), len, 1000);
  }
  fingerOperation = FOP_NONE; identifyActive = false; removeProbePending = false;
  resetFingerprintRx();
}

void stopConfigWifi() {
  if (enrollState == ENROLL_RUNNING) {
    cancelActiveFingerprintOperation();
    enrollState = ENROLL_IDLE; enrollName = "";
    systemMessage = "Wi-Fi konfigurasi dimatikan; pendaftaran dibatalkan.";
    startRemovalWait();
  }
  configMode = false;
  server.stop(); WiFi.softAPdisconnect(true); WiFi.mode(WIFI_OFF);
  if (systemMessage.indexOf("pendaftaran dibatalkan") < 0) systemMessage = "Wi-Fi konfigurasi dimatikan. Absensi tetap berjalan.";
  Serial.println(systemMessage);
}


// ======================== CONFIG BUTTON ========================
void processConfigButton() {
  bool pressed = digitalRead(CONFIG_BUTTON) == LOW;
  if (pressed) {
    if (!buttonTiming) { buttonTiming = true; buttonPressedAt = millis(); buttonLongHandled = false; }
    else if (!buttonLongHandled && millis() - buttonPressedAt >= 3000) {
      buttonLongHandled = true;
      if (!configMode) { if (startConfigWifi()) showFeedback(true, false, true, 1800); else showFeedback(true, false, false, 1800); }
      else { stopConfigWifi(); showFeedback(false, false, true, 1800); }
      Serial.println(systemMessage);
    }
  } else { buttonTiming = false; buttonLongHandled = false; }
}

