/*
  ABSENSI OTOMATIS ESP32 + FINGERPRINT R558-S

  Fitur:
  - Web lokal melalui Access Point ESP32
  - Pendaftaran sidik jari (dua kali scan) melalui halaman web
  - Pencocokan sidik jari dan pencatatan ke MicroSD
  - RTC DS1307 untuk tanggal/waktu
  - LED RGB common cathode
  - Tombol GPIO14 ditahan 3 detik untuk mengaktifkan/nonaktifkan mode konfigurasi
  - Pemutaran WAV PCM 16-bit melalui MAX98357A

  Library Arduino IDE yang diperlukan:
  - Adafruit Fingerprint Sensor Library
  - RTClib by Adafruit

  Target: ESP32 DevKit V1. UART R558-S teruji sebelumnya pada 57600 baud.

  File MicroSD yang digunakan:
  /users.csv
  /attendance.csv
  /sukses.wav
  /coba_lagi.wav
  /terima_kasih.wav

  Format WAV: PCM (format 1), 16-bit, mono atau stereo, 8 kHz sampai 48 kHz.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_Fingerprint.h>
#include "driver/i2s.h"

// ======================== PIN ========================
#define FP_RX       16     // ESP32 RX2 <- TX R558-S
#define FP_TX       17     // ESP32 TX2 -> RX R558-S
#define FP_TOUCH    34     // TOUCH_OUT (opsional; hanya dipantau)
#define FP_BAUD     57600

#define SD_SCK      18
#define SD_MISO     19
#define SD_MOSI     23
#define SD_CS       13

#define RTC_SDA     21
#define RTC_SCL     22

#define I2S_DOUT    27
#define I2S_BCLK    26
#define I2S_LRC     25

#define LED_R       32
#define LED_G       33
#define LED_B        4     // LED RGB common cathode; tiap warna pakai resistor 330 ohm

#define CONFIG_BUTTON 14   // tombol ke GND, menggunakan INPUT_PULLUP

// ======================== WIFI LOKAL ========================
const char *AP_SSID = "Absensi-ESP32";
const char *AP_PASSWORD = "absensi123"; // Ubah untuk keamanan; minimal 8 karakter

// ======================== OBJEK ========================
HardwareSerial FingerSerial(2);
Adafruit_Fingerprint finger(&FingerSerial);
RTC_DS1307 rtc;
WebServer server(80);

// ======================== STATUS PERANGKAT ========================
bool fingerprintReady = false;
bool sdReady = false;
bool rtcReady = false;
bool i2sReady = false;
bool configMode = false;
String systemMessage = "Memulai sistem...";

// ======================== PENDAFTARAN ========================
enum EnrollStep : uint8_t {
  ENROLL_IDLE,
  ENROLL_WAIT_FIRST,
  ENROLL_WAIT_REMOVE,
  ENROLL_WAIT_SECOND
};

EnrollStep enrollStep = ENROLL_IDLE;
String enrollName = "";
uint16_t enrollId = 0;
unsigned long enrollmentStartedAt = 0;
unsigned long lastEnrollmentPoll = 0;
const unsigned long ENROLL_TIMEOUT_MS = 90000;

// ======================== ABSENSI ========================
bool waitForFingerRemoval = false;
unsigned long lastFingerprintPoll = 0;
unsigned long lastAttendanceAt = 0;
uint16_t lastAttendanceId = 0;
const unsigned long FINGER_POLL_INTERVAL_MS = 120;
const unsigned long DUPLICATE_COOLDOWN_MS = 30000; // cegah log berulang dalam 30 detik

// ======================== TOMBOL ========================
bool buttonTiming = false;
bool buttonLongHandled = false;
unsigned long buttonPressedAt = 0;

// ======================== LED FEEDBACK ========================
unsigned long ledOverrideUntil = 0;
bool overrideR = false, overrideG = false, overrideB = false;

// ======================== AUDIO WAV ========================
File audioFile;
bool audioPlaying = false;
uint32_t audioBytesRemaining = 0;
uint32_t audioSampleRate = 16000;
uint16_t audioChannels = 1;

// ======================== HALAMAN WEB ========================
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang="id">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Absensi Otomatis ESP32</title>
<style>
:root{font-family:system-ui,-apple-system,Segoe UI,Roboto,Arial,sans-serif;color:#18212f;background:#f3f5f8}
body{margin:0;padding:16px}.wrap{max-width:920px;margin:auto}.hero{background:#172b4d;color:#fff;padding:22px;border-radius:16px;margin-bottom:14px}
h1{font-size:1.45rem;margin:0 0 6px}.muted{color:#687386;font-size:.92rem}.hero .muted{color:#d8e1ef}
.card{background:#fff;border:1px solid #e0e5ec;border-radius:14px;padding:16px;margin:12px 0;box-shadow:0 2px 6px #14233b0b}
h2{font-size:1.1rem;margin:0 0 12px}label{display:block;font-weight:600;margin:9px 0 5px}
input,button{font:inherit;padding:10px;border-radius:9px;border:1px solid #ccd3de;box-sizing:border-box}input{width:100%}
button{cursor:pointer;background:#1f5aa6;color:white;border:0;font-weight:650;margin-top:10px}button.secondary{background:#5c6778}button.danger{background:#a52d36}
.row{display:grid;grid-template-columns:repeat(auto-fit,minmax(190px,1fr));gap:10px}.pill{display:inline-block;border-radius:20px;background:#e9eef5;padding:5px 10px;font-size:.85rem;margin:2px}.message{background:#f4f7fb;border-left:4px solid #3672b8;padding:12px;border-radius:7px;white-space:pre-wrap}
.tablewrap{overflow:auto}table{width:100%;border-collapse:collapse;font-size:.92rem}th,td{text-align:left;padding:9px;border-bottom:1px solid #e7ebf0;white-space:nowrap}th{background:#f7f9fc}
.note{font-size:.9rem;line-height:1.5}.ok{color:#167847}.bad{color:#b4232c}
</style>
</head>
<body><div class="wrap">
<div class="hero"><h1>Absensi Otomatis</h1><div class="muted">ESP32 DevKit V1 · Fingerprint R558-S · MicroSD · RTC DS1307</div><p class="muted">Web lokal untuk pendaftaran sidik jari, pengaturan waktu, dan melihat log.</p></div>
<div class="card"><h2>Status perangkat</h2><div id="devices">Memuat status...</div><p id="mode" class="muted"></p><div id="message" class="message">Menghubungkan ke ESP32...</div><p class="note">Untuk mengaktifkan pendaftaran dan pengaturan RTC, tahan tombol fisik GPIO14 selama 3 detik. Tekan dan tahan lagi 3 detik untuk keluar dari mode konfigurasi.</p></div>
<div class="card"><h2>1. Daftarkan pengguna</h2><label for="name">Nama pengguna</label><input id="name" maxlength="32" placeholder="Contoh: Robert"><button onclick="startEnroll()">Mulai pendaftaran fingerprint</button><button class="secondary" onclick="cancelEnroll()">Batalkan pendaftaran</button><p class="note">Setelah menekan mulai, tempelkan jari. Angkat jari ketika diminta, lalu tempelkan jari yang sama sekali lagi.</p><div id="enrollResult" class="muted"></div></div>
<div class="card"><h2>2. Atur waktu RTC</h2><label for="datetime">Tanggal dan waktu perangkat</label><input type="datetime-local" id="datetime"><button onclick="setRTC()">Simpan tanggal dan waktu</button><p class="note">Waktu diambil dari komputer/ponsel yang membuka halaman. Pastikan perangkat tersebut menggunakan zona waktu yang benar.</p></div>
<div class="card"><h2>3. Pengguna terdaftar</h2><button class="secondary" onclick="refreshUsers()">Muat ulang daftar pengguna</button><div class="tablewrap"><table><thead><tr><th>ID Fingerprint</th><th>Nama</th></tr></thead><tbody id="users"><tr><td colspan="2">Memuat...</td></tr></tbody></table></div></div>
<div class="card"><h2>4. Log absensi terakhir</h2><button class="secondary" onclick="refreshLogs()">Muat ulang log</button><div class="tablewrap"><table><thead><tr><th>Tanggal</th><th>Waktu</th><th>ID</th><th>Nama</th><th>Confidence</th></tr></thead><tbody id="logs"><tr><td colspan="5">Memuat...</td></tr></tbody></table></div></div>
<div class="card note"><b>Alamat web:</b> http://192.168.4.1<br><b>Wi-Fi:</b> Absensi-ESP32<br><b>Password awal:</b> absensi123 (ubah di kode sebelum digunakan secara nyata).</div>
</div>
<script>
async function getJson(url){const r=await fetch(url,{cache:'no-store'});if(!r.ok)throw new Error(await r.text());return await r.json();}
function addCell(tr,value){const td=document.createElement('td');td.textContent=value;tr.appendChild(td);}
async function refreshStatus(){try{const s=await getJson('/api/status');document.getElementById('devices').innerHTML='';const d=document.getElementById('devices');[['Fingerprint',s.fingerprint],['MicroSD',s.sd],['RTC DS1307',s.rtc],['Audio I2S',s.audio],['TOUCH_OUT',s.touch]].forEach(([k,v])=>{const x=document.createElement('span');x.className='pill';x.textContent=k+': '+v;d.appendChild(x)});document.getElementById('mode').textContent='Mode: '+s.mode+' · Waktu RTC: '+s.time;document.getElementById('message').textContent=s.message;document.getElementById('enrollResult').textContent=s.enrollment;}catch(e){document.getElementById('message').textContent='Gagal terhubung ke ESP32: '+e.message;}}
async function startEnroll(){const n=document.getElementById('name').value.trim();if(!n){alert('Masukkan nama pengguna.');return;}try{const r=await fetch('/enroll?name='+encodeURIComponent(n));document.getElementById('enrollResult').textContent=await r.text();await refreshStatus();}catch(e){alert('Permintaan gagal: '+e.message)}}
async function cancelEnroll(){try{const r=await fetch('/enroll/cancel');document.getElementById('enrollResult').textContent=await r.text();await refreshStatus();}catch(e){alert(e.message)}}
async function setRTC(){const dt=document.getElementById('datetime').value;if(!dt){alert('Pilih tanggal dan waktu.');return;}try{const r=await fetch('/rtc?datetime='+encodeURIComponent(dt));alert(await r.text());await refreshStatus();}catch(e){alert('Gagal mengatur RTC: '+e.message)}}
async function refreshUsers(){const b=document.getElementById('users');b.textContent='';try{const arr=await getJson('/api/users');if(!arr.length){const tr=document.createElement('tr');addCell(tr,'Belum ada pengguna');tr.children[0].colSpan=2;b.appendChild(tr);return;}arr.forEach(u=>{const tr=document.createElement('tr');addCell(tr,u.id);addCell(tr,u.name);b.appendChild(tr)});}catch(e){b.textContent='Gagal membaca daftar pengguna';}}
async function refreshLogs(){const b=document.getElementById('logs');b.textContent='';try{const arr=await getJson('/api/logs');if(!arr.length){const tr=document.createElement('tr');addCell(tr,'Belum ada log absensi');tr.children[0].colSpan=5;b.appendChild(tr);return;}arr.forEach(x=>{const tr=document.createElement('tr');addCell(tr,x.date);addCell(tr,x.time);addCell(tr,x.id);addCell(tr,x.name);addCell(tr,x.confidence);b.appendChild(tr)});}catch(e){b.textContent='MicroSD tidak tersedia atau log gagal dibaca';}}
refreshStatus();refreshUsers();refreshLogs();setInterval(refreshStatus,1500);setInterval(refreshLogs,8000);
</script></body></html>
)rawliteral";

// ======================== UTILITAS STRING/JSON ========================
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
  if (enrollStep != ENROLL_IDLE) return "pendaftaran";
  return configMode ? "konfigurasi" : "absensi/standby";
}

String enrollmentText() {
  switch (enrollStep) {
    case ENROLL_WAIT_FIRST: return "Menunggu pemindaian sidik jari pertama.";
    case ENROLL_WAIT_REMOVE: return "Angkat jari dari sensor.";
    case ENROLL_WAIT_SECOND: return "Tempelkan jari yang sama untuk pemindaian kedua.";
    default: return "Tidak ada pendaftaran yang berjalan.";
  }
}

String rtcDateString() {
  if (!rtcReady) return "RTC tidak tersedia";
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

void showFeedback(bool r, bool g, bool b, unsigned long durationMs = 1800) {
  overrideR = r; overrideG = g; overrideB = b;
  ledOverrideUntil = millis() + durationMs;
}

void updateLed() {
  if ((int32_t)(millis() - ledOverrideUntil) < 0) {
    setRgb(overrideR, overrideG, overrideB);
    return;
  }
  if (enrollStep != ENROLL_IDLE || configMode) {
    setRgb(true, false, true);   // ungu: konfigurasi/pendaftaran
  } else {
    setRgb(false, false, true);  // biru: standby
  }
}

// ======================== FILE MICROSD ========================
void createCsvFilesIfNeeded() {
  if (!sdReady) return;
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
  String found = "";
  while (f.available()) {
    String line = f.readStringUntil('\n');
    line.trim();
    if (!line.length() || line.startsWith("id,")) continue;
    int comma = line.indexOf(',');
    if (comma < 0) continue;
    long rowId = line.substring(0, comma).toInt();
    if (rowId == id) { found = line.substring(comma + 1); break; }
  }
  f.close();
  return found;
}

uint16_t nextUserId() {
  if (!sdReady) return 0;
  uint16_t maxId = 0;
  File f = SD.open("/users.csv", FILE_READ);
  if (f) {
    while (f.available()) {
      String line = f.readStringUntil('\n');
      line.trim();
      if (!line.length() || line.startsWith("id,")) continue;
      int comma = line.indexOf(',');
      if (comma <= 0) continue;
      uint16_t id = (uint16_t)line.substring(0, comma).toInt();
      if (id > maxId) maxId = id;
    }
    f.close();
  }
  if (maxId >= finger.capacity) return 0;
  return maxId + 1;
}

bool saveUser(uint16_t id, const String &name) {
  if (!sdReady) return false;
  File f = SD.open("/users.csv", FILE_APPEND);
  if (!f) return false;
  f.print(id);
  f.print(',');
  f.println(name);
  f.flush();
  bool okay = !f.getWriteError();
  f.close();
  return okay;
}

bool appendAttendance(uint16_t id, const String &name, uint16_t confidence) {
  if (!sdReady) return false;
  File f = SD.open("/attendance.csv", FILE_APPEND);
  if (!f) return false;

  String datePart = "RTC_UNAVAILABLE";
  String timePart = "--:--:--";
  if (rtcReady) {
    DateTime now = rtc.now();
    char d[12], t[10];
    snprintf(d, sizeof(d), "%04u-%02u-%02u", now.year(), now.month(), now.day());
    snprintf(t, sizeof(t), "%02u:%02u:%02u", now.hour(), now.minute(), now.second());
    datePart = d;
    timePart = t;
  }

  f.print(datePart); f.print(',');
  f.print(timePart); f.print(',');
  f.print(id); f.print(',');
  f.print(name); f.print(',');
  f.println(confidence);
  f.flush();
  bool okay = !f.getWriteError();
  f.close();
  return okay;
}

String csvField(const String &line, uint8_t wanted) {
  int start = 0;
  for (uint8_t field = 0; field < wanted; field++) {
    int comma = line.indexOf(',', start);
    if (comma < 0) return "";
    start = comma + 1;
  }
  int end = line.indexOf(',', start);
  if (end < 0) end = line.length();
  return line.substring(start, end);
}

// ======================== AUDIO I2S / WAV ========================
uint16_t readLE16(File &f) {
  int a = f.read(); int b = f.read();
  if (a < 0 || b < 0) return 0;
  return (uint16_t)((uint16_t)b << 8) | (uint16_t)a;
}

uint32_t readLE32(File &f) {
  int a = f.read(); int b = f.read(); int c = f.read(); int d = f.read();
  if (a < 0 || b < 0 || c < 0 || d < 0) return 0;
  return ((uint32_t)d << 24) | ((uint32_t)c << 16) | ((uint32_t)b << 8) | (uint32_t)a;
}

bool readFourCC(File &f, char *out) {
  if (f.read((uint8_t *)out, 4) != 4) return false;
  out[4] = '\0';
  return true;
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
  if (err != ESP_OK) {
    Serial.printf("I2S driver install gagal: %d\n", (int)err);
    i2sReady = false;
    return;
  }

  i2s_pin_config_t pins = {};
  pins.bck_io_num = I2S_BCLK;
  pins.ws_io_num = I2S_LRC;
  pins.data_out_num = I2S_DOUT;
  pins.data_in_num = I2S_PIN_NO_CHANGE;
  pins.mck_io_num = I2S_PIN_NO_CHANGE;
  err = i2s_set_pin(I2S_NUM_0, &pins);
  if (err != ESP_OK) {
    Serial.printf("Konfigurasi pin I2S gagal: %d\n", (int)err);
    i2sReady = false;
    return;
  }
  i2s_zero_dma_buffer(I2S_NUM_0);
  i2sReady = true;
  Serial.println("I2S MAX98357A siap.");
}

bool startAudio(const char *path) {
  if (!sdReady || !i2sReady) return false;
  if (audioFile) audioFile.close();
  audioPlaying = false;
  audioBytesRemaining = 0;

  audioFile = SD.open(path, FILE_READ);
  if (!audioFile) {
    Serial.printf("Audio tidak ditemukan: %s\n", path);
    return false;
  }

  char id[5];
  if (!readFourCC(audioFile, id) || strcmp(id, "RIFF") != 0) {
    Serial.printf("File bukan RIFF/WAV: %s\n", path);
    audioFile.close();
    return false;
  }
  (void)readLE32(audioFile); // ukuran RIFF
  if (!readFourCC(audioFile, id) || strcmp(id, "WAVE") != 0) {
    Serial.printf("Header WAVE tidak valid: %s\n", path);
    audioFile.close();
    return false;
  }

  uint16_t format = 0, channels = 0, bits = 0;
  uint32_t sampleRate = 0, dataSize = 0;
  bool haveFmt = false, haveData = false;
  uint32_t dataStart = 0;

  while (audioFile.available()) {
    if (!readFourCC(audioFile, id)) break;
    uint32_t chunkSize = readLE32(audioFile);
    uint32_t chunkStart = audioFile.position();

    if (strcmp(id, "fmt ") == 0) {
      if (chunkSize < 16) { audioFile.close(); return false; }
      format = readLE16(audioFile);
      channels = readLE16(audioFile);
      sampleRate = readLE32(audioFile);
      (void)readLE32(audioFile); // byte rate
      (void)readLE16(audioFile); // block align
      bits = readLE16(audioFile);
      haveFmt = true;
      uint32_t endPos = chunkStart + chunkSize + (chunkSize & 1U);
      if (endPos <= audioFile.size()) audioFile.seek(endPos);
    } else if (strcmp(id, "data") == 0) {
      dataStart = chunkStart;
      dataSize = chunkSize;
      haveData = true;
      break;
    } else {
      uint32_t endPos = chunkStart + chunkSize + (chunkSize & 1U);
      if (endPos > audioFile.size()) break;
      audioFile.seek(endPos);
    }
  }

  if (!haveFmt || !haveData || format != 1 || bits != 16 ||
      (channels != 1 && channels != 2) || sampleRate < 8000 || sampleRate > 48000 ||
      dataStart >= audioFile.size()) {
    Serial.printf("Format WAV tidak didukung: %s (harus PCM 16-bit mono/stereo, 8-48 kHz)\n", path);
    audioFile.close();
    return false;
  }

  uint32_t availableData = (uint32_t)(audioFile.size() - dataStart);
  if (dataSize > availableData) dataSize = availableData;
  dataSize &= ~1U;
  if (!audioFile.seek(dataStart)) {
    audioFile.close();
    return false;
  }

  audioChannels = channels;
  audioSampleRate = sampleRate;
  audioBytesRemaining = dataSize;
  if (i2s_set_clk(I2S_NUM_0, audioSampleRate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO) != ESP_OK) {
    Serial.println("Gagal mengatur sample rate I2S.");
    audioFile.close();
    return false;
  }
  i2s_zero_dma_buffer(I2S_NUM_0);
  audioPlaying = true;
  Serial.printf("Memutar %s (%lu Hz, %u channel)\n", path, (unsigned long)audioSampleRate, audioChannels);
  return true;
}

void loopAudio() {
  if (!audioPlaying) return;
  if (!audioFile || audioBytesRemaining == 0) {
    if (audioFile) audioFile.close();
    audioPlaying = false;
    i2s_zero_dma_buffer(I2S_NUM_0);
    return;
  }

  uint8_t inputBuffer[512];
  uint8_t outputBuffer[1024];
  size_t bytesToRead = audioBytesRemaining > sizeof(inputBuffer) ? sizeof(inputBuffer) : audioBytesRemaining;
  bytesToRead &= ~((size_t)1);
  size_t got = audioFile.read(inputBuffer, bytesToRead);
  got &= ~((size_t)1);
  if (got == 0) {
    audioFile.close();
    audioPlaying = false;
    i2s_zero_dma_buffer(I2S_NUM_0);
    return;
  }

  size_t outputBytes = got;
  if (audioChannels == 1) {
    size_t samples = got / 2;
    for (size_t i = 0; i < samples; i++) {
      uint8_t lo = inputBuffer[i * 2];
      uint8_t hi = inputBuffer[i * 2 + 1];
      outputBuffer[i * 4] = lo;
      outputBuffer[i * 4 + 1] = hi;
      outputBuffer[i * 4 + 2] = lo;
      outputBuffer[i * 4 + 3] = hi;
    }
    outputBytes = samples * 4;
  } else {
    memcpy(outputBuffer, inputBuffer, got);
  }

  size_t written = 0;
  i2s_write(I2S_NUM_0, outputBuffer, outputBytes, &written, pdMS_TO_TICKS(30));
  audioBytesRemaining -= got;
}

// ======================== LOGIKA PENDAFTARAN ========================
void finishEnrollment(bool success, const String &message) {
  // Jangan langsung memproses jari yang masih menempel sebagai absensi setelah pendaftaran berakhir.
  waitForFingerRemoval = true;
  enrollStep = ENROLL_IDLE;
  enrollName = "";
  enrollmentStartedAt = 0;
  systemMessage = message;
  if (success) {
    showFeedback(false, true, false, 2500);
    startAudio("/terima_kasih.wav");
  } else {
    showFeedback(true, false, false, 2000);
    startAudio("/coba_lagi.wav");
  }
}

void processEnrollment() {
  if (enrollStep == ENROLL_IDLE || !fingerprintReady) return;
  if (millis() - enrollmentStartedAt > ENROLL_TIMEOUT_MS) {
    finishEnrollment(false, "Pendaftaran dibatalkan karena waktu habis.");
    return;
  }
  if (millis() - lastEnrollmentPoll < 120) return;
  lastEnrollmentPoll = millis();

  uint8_t p;
  switch (enrollStep) {
    case ENROLL_WAIT_FIRST:
      p = finger.getImage();
      if (p == FINGERPRINT_NOFINGER) return;
      if (p != FINGERPRINT_OK) {
        systemMessage = "Gagal mengambil gambar pertama. Lepaskan jari lalu coba lagi.";
        return;
      }
      p = finger.image2Tz(1);
      if (p != FINGERPRINT_OK) {
        systemMessage = "Gambar pertama kurang jelas. Coba tempelkan jari dengan rata.";
        showFeedback(true, false, false, 700);
        return;
      }
      p = finger.fingerFastSearch(); // cek apakah jari sudah terdaftar
      if (p == FINGERPRINT_OK) {
        String existingName = findUserName(finger.fingerID);
        String msg = "Sidik jari sudah terdaftar pada ID " + String(finger.fingerID);
        if (existingName.length()) msg += " (" + existingName + ")";
        finishEnrollment(false, msg + ". Gunakan jari lain atau batalkan.");
        return;
      }
      if (p != FINGERPRINT_NOTFOUND) {
        finishEnrollment(false, "Gagal memeriksa duplikasi sidik jari. Periksa koneksi sensor.");
        return;
      }
      enrollStep = ENROLL_WAIT_REMOVE;
      systemMessage = "Pemindaian pertama berhasil. Angkat jari dari sensor.";
      showFeedback(false, false, true, 700);
      Serial.println(systemMessage);
      return;

    case ENROLL_WAIT_REMOVE:
      p = finger.getImage();
      if (p == FINGERPRINT_NOFINGER) {
        enrollStep = ENROLL_WAIT_SECOND;
        systemMessage = "Sekarang tempelkan jari yang sama untuk kedua kali.";
        Serial.println(systemMessage);
      }
      return;

    case ENROLL_WAIT_SECOND:
      p = finger.getImage();
      if (p == FINGERPRINT_NOFINGER) return;
      if (p != FINGERPRINT_OK) {
        systemMessage = "Gagal mengambil gambar kedua. Angkat jari dan coba lagi.";
        return;
      }
      p = finger.image2Tz(2);
      if (p != FINGERPRINT_OK) {
        finishEnrollment(false, "Gambar kedua kurang jelas. Silakan mulai pendaftaran lagi.");
        return;
      }
      p = finger.createModel();
      if (p != FINGERPRINT_OK) {
        finishEnrollment(false, "Sidik jari tidak cocok antara pemindaian pertama dan kedua. Ulangi pendaftaran.");
        return;
      }
      p = finger.storeModel(enrollId);
      if (p != FINGERPRINT_OK) {
        finishEnrollment(false, "Gagal menyimpan template ke memori sensor.");
        return;
      }
      if (!saveUser(enrollId, enrollName)) {
        finger.deleteModel(enrollId); // rollback bila metadata MicroSD gagal disimpan
        finishEnrollment(false, "Template gagal dicatat di MicroSD. Template pada sensor dibatalkan.");
        return;
      }
      {
        String successMessage = "Pendaftaran berhasil. ID " + String(enrollId) + " — " + enrollName + ". Terima kasih.";
        Serial.println(successMessage);
        finishEnrollment(true, successMessage);
      }
      return;

    default:
      return;
  }
}

// ======================== LOGIKA ABSENSI ========================
void processAttendance() {
  if (!fingerprintReady || enrollStep != ENROLL_IDLE || audioPlaying) return;
  if (millis() - lastFingerprintPoll < FINGER_POLL_INTERVAL_MS) return;
  lastFingerprintPoll = millis();

  uint8_t p;
  if (waitForFingerRemoval) {
    p = finger.getImage();
    if (p == FINGERPRINT_NOFINGER) {
      waitForFingerRemoval = false;
      systemMessage = "Siap menerima sidik jari berikutnya.";
    }
    return;
  }

  p = finger.getImage();
  if (p == FINGERPRINT_NOFINGER) return;
  if (p != FINGERPRINT_OK) return;

  waitForFingerRemoval = true;
  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK) {
    systemMessage = "Sidik jari tidak terbaca jelas. Coba lagi.";
    showFeedback(true, false, false, 1500);
    startAudio("/coba_lagi.wav");
    return;
  }

  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    uint16_t foundId = finger.fingerID;
    uint16_t confidence = finger.confidence;
    String name = findUserName(foundId);
    if (!name.length()) {
      systemMessage = "Template ID " + String(foundId) + " ada di sensor, tetapi namanya tidak ditemukan di users.csv.";
      showFeedback(true, false, false, 1800);
      startAudio("/coba_lagi.wav");
      return;
    }

    if (foundId == lastAttendanceId && (millis() - lastAttendanceAt) < DUPLICATE_COOLDOWN_MS) {
      systemMessage = "Absensi " + name + " baru saja tercatat. Tunggu 30 detik sebelum mencoba lagi.";
      showFeedback(false, false, true, 1000);
      return;
    }

    bool logged = appendAttendance(foundId, name, confidence);
    lastAttendanceId = foundId;
    lastAttendanceAt = millis();
    if (logged) {
      systemMessage = "Absensi berhasil: " + name + " (ID " + String(foundId) + "). Data tersimpan di MicroSD.";
    } else {
      systemMessage = "Sidik jari cocok: " + name + ", tetapi log gagal disimpan ke MicroSD.";
    }
    showFeedback(false, true, false, 2200);
    startAudio("/sukses.wav");
    Serial.println(systemMessage);
  } else if (p == FINGERPRINT_NOTFOUND) {
    systemMessage = "Sidik jari tidak terdaftar. Silakan coba lagi.";
    showFeedback(true, false, false, 1800);
    startAudio("/coba_lagi.wav");
    Serial.println(systemMessage);
  } else {
    systemMessage = "Terjadi kesalahan pencarian sidik jari. Coba lagi.";
    showFeedback(true, false, false, 1500);
    startAudio("/coba_lagi.wav");
  }
}

// ======================== TOMBOL KONFIGURASI ========================
void processConfigButton() {
  bool pressed = digitalRead(CONFIG_BUTTON) == LOW;
  if (pressed) {
    if (!buttonTiming) {
      buttonTiming = true;
      buttonPressedAt = millis();
      buttonLongHandled = false;
    } else if (!buttonLongHandled && millis() - buttonPressedAt >= 3000) {
      buttonLongHandled = true;
      configMode = !configMode;
      if (configMode) {
        systemMessage = "Mode konfigurasi aktif. Buka http://192.168.4.1 untuk mengelola sistem.";
        showFeedback(true, false, true, 1800);
      } else {
        if (enrollStep != ENROLL_IDLE) {
          enrollStep = ENROLL_IDLE;
          enrollName = "";
          waitForFingerRemoval = true;
        }
        systemMessage = "Mode konfigurasi nonaktif. Sistem kembali ke mode absensi.";
        showFeedback(false, false, true, 1800);
      }
      Serial.println(systemMessage);
    }
  } else {
    buttonTiming = false;
    buttonLongHandled = false;
  }
}

// ======================== WEB API ========================
void handleRoot() {
  server.send_P(200, "text/html; charset=utf-8", INDEX_HTML);
}

void handleStatus() {
  String payload = "{";
  payload += "\"fingerprint\":\"" + String(fingerprintReady ? "OK" : "GAGAL") + "\",";
  payload += "\"sd\":\"" + String(sdReady ? "OK" : "GAGAL") + "\",";
  payload += "\"rtc\":\"" + String(rtcReady ? "OK" : "GAGAL") + "\",";
  payload += "\"audio\":\"" + String(i2sReady ? "SIAP" : "GAGAL") + "\",";
  payload += "\"touch\":\"" + String(digitalRead(FP_TOUCH) == HIGH ? "HIGH" : "LOW") + "\",";
  payload += "\"mode\":\"" + jsonEscape(modeText()) + "\",";
  payload += "\"time\":\"" + jsonEscape(rtcDateString()) + "\",";
  payload += "\"message\":\"" + jsonEscape(systemMessage) + "\",";
  payload += "\"enrollment\":\"" + jsonEscape(enrollmentText()) + "\"}";
  server.send(200, "application/json; charset=utf-8", payload);
}

void handleStartEnroll() {
  if (!configMode) {
    server.send(403, "text/plain; charset=utf-8", "Mode konfigurasi belum aktif. Tahan tombol GPIO14 selama 3 detik.");
    return;
  }
  if (!fingerprintReady) {
    server.send(503, "text/plain; charset=utf-8", "Sensor fingerprint tidak siap.");
    return;
  }
  if (!sdReady) {
    server.send(503, "text/plain; charset=utf-8", "MicroSD tidak siap; pendaftaran tidak bisa menyimpan nama pengguna.");
    return;
  }
  if (enrollStep != ENROLL_IDLE) {
    server.send(409, "text/plain; charset=utf-8", "Pendaftaran sedang berjalan. Selesaikan atau batalkan terlebih dahulu.");
    return;
  }
  String name = sanitizeName(server.arg("name"));
  if (!name.length()) {
    server.send(400, "text/plain; charset=utf-8", "Nama pengguna wajib diisi.");
    return;
  }
  uint16_t id = nextUserId();
  if (!id || id > finger.capacity) {
    server.send(507, "text/plain; charset=utf-8", "Kapasitas ID terpakai atau penuh. Periksa users.csv dan kapasitas sensor.");
    return;
  }

  enrollName = name;
  enrollId = id;
  enrollmentStartedAt = millis();
  lastEnrollmentPoll = 0;
  enrollStep = ENROLL_WAIT_FIRST;
  systemMessage = "Pendaftaran ID " + String(enrollId) + " dimulai. Tempelkan jari pada sensor.";
  showFeedback(true, false, true, 1200);
  Serial.println(systemMessage);
  server.send(200, "text/plain; charset=utf-8", systemMessage);
}

void handleCancelEnroll() {
  if (enrollStep != ENROLL_IDLE) {
    waitForFingerRemoval = true;
    enrollStep = ENROLL_IDLE;
    enrollName = "";
    enrollId = 0;
    systemMessage = "Pendaftaran dibatalkan.";
    showFeedback(true, false, false, 1200);
  } else {
    systemMessage = "Tidak ada pendaftaran yang sedang berjalan.";
  }
  server.send(200, "text/plain; charset=utf-8", systemMessage);
}

void handleRTCSet() {
  if (!configMode) {
    server.send(403, "text/plain; charset=utf-8", "Mode konfigurasi belum aktif. Tahan tombol GPIO14 selama 3 detik.");
    return;
  }
  if (!rtcReady) {
    server.send(503, "text/plain; charset=utf-8", "RTC DS1307 tidak terdeteksi. Periksa wiring SDA/SCL, level shifter, daya, dan baterai.");
    return;
  }
  String value = server.arg("datetime");
  int y = 0, mo = 0, d = 0, hh = 0, mm = 0;
  if (sscanf(value.c_str(), "%d-%d-%dT%d:%d", &y, &mo, &d, &hh, &mm) != 5) {
    server.send(400, "text/plain; charset=utf-8", "Format tanggal/waktu tidak valid.");
    return;
  }
  DateTime dt(y, mo, d, hh, mm, 0);
  if (!dt.isValid()) {
    server.send(400, "text/plain; charset=utf-8", "Tanggal/waktu di luar rentang yang valid.");
    return;
  }
  rtc.adjust(dt);
  systemMessage = "RTC berhasil diatur ke " + rtcDateString();
  server.send(200, "text/plain; charset=utf-8", systemMessage);
}

void handleUsers() {
  if (!sdReady) {
    server.send(503, "application/json; charset=utf-8", "[]");
    return;
  }
  String payload = "[";
  bool first = true;
  File f = SD.open("/users.csv", FILE_READ);
  if (f) {
    while (f.available()) {
      String line = f.readStringUntil('\n');
      line.trim();
      if (!line.length() || line.startsWith("id,")) continue;
      int comma = line.indexOf(',');
      if (comma <= 0) continue;
      String id = line.substring(0, comma);
      String name = line.substring(comma + 1);
      if (!first) payload += ',';
      first = false;
      payload += "{\"id\":" + String(id.toInt()) + ",\"name\":\"" + jsonEscape(name) + "\"}";
    }
    f.close();
  }
  payload += "]";
  server.send(200, "application/json; charset=utf-8", payload);
}

void handleLogs() {
  if (!sdReady) {
    server.send(503, "application/json; charset=utf-8", "[]");
    return;
  }
  String lines[20];
  size_t total = 0;
  File f = SD.open("/attendance.csv", FILE_READ);
  if (f) {
    while (f.available()) {
      String line = f.readStringUntil('\n');
      line.trim();
      if (!line.length() || line.startsWith("date,")) continue;
      lines[total % 20] = line;
      total++;
    }
    f.close();
  }
  size_t count = total < 20 ? total : 20;
  String payload = "[";
  for (size_t k = 0; k < count; k++) {
    size_t idx = (total - 1 - k) % 20;
    String line = lines[idx];
    if (k) payload += ',';
    payload += "{\"date\":\"" + jsonEscape(csvField(line, 0)) + "\",";
    payload += "\"time\":\"" + jsonEscape(csvField(line, 1)) + "\",";
    payload += "\"id\":" + String(csvField(line, 2).toInt()) + ",";
    payload += "\"name\":\"" + jsonEscape(csvField(line, 3)) + "\",";
    payload += "\"confidence\":" + String(csvField(line, 4).toInt()) + "}";
  }
  payload += "]";
  server.send(200, "application/json; charset=utf-8", payload);
}

void setupWeb() {
  WiFi.mode(WIFI_AP);
  bool apStarted = WiFi.softAP(AP_SSID, AP_PASSWORD);
  Serial.printf("Wi-Fi AP: %s\n", apStarted ? "OK" : "GAGAL");
  Serial.print("SSID: "); Serial.println(AP_SSID);
  Serial.print("IP: "); Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/api/status", HTTP_GET, handleStatus);
  server.on("/api/users", HTTP_GET, handleUsers);
  server.on("/api/logs", HTTP_GET, handleLogs);
  server.on("/enroll", HTTP_GET, handleStartEnroll);
  server.on("/enroll/cancel", HTTP_GET, handleCancelEnroll);
  server.on("/rtc", HTTP_GET, handleRTCSet);
  server.onNotFound([]() { server.send(404, "text/plain; charset=utf-8", "404 - Endpoint tidak ditemukan"); });
  server.begin();
  Serial.println("Web server berjalan pada http://192.168.4.1");
}

// ======================== SETUP ========================
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n==========================================");
  Serial.println(" ABSENSI OTOMATIS ESP32 + R558-S");
  Serial.println("==========================================");

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  setRgb(false, false, true);

  pinMode(CONFIG_BUTTON, INPUT_PULLUP);
  pinMode(FP_TOUCH, INPUT); // GPIO34 tidak memiliki internal pull-up/pull-down

  // Fingerprint R558-S
  FingerSerial.begin(FP_BAUD, SERIAL_8N1, FP_RX, FP_TX);
  delay(300);
  Serial.println("Memeriksa R558-S...");
  fingerprintReady = finger.verifyPassword();
  if (fingerprintReady) {
    Serial.println("R558-S: BERHASIL");
    if (finger.getParameters() == FINGERPRINT_OK) {
      Serial.printf("Kapasitas: %u | Security: %u | Baud: %u\n", finger.capacity, finger.security_level, finger.baud_rate);
    }
  } else {
    Serial.println("R558-S: GAGAL; periksa TX/RX, suplai, dan baud rate.");
  }

  // MicroSD SPI
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  sdReady = SD.begin(SD_CS, SPI, 4000000);
  Serial.printf("MicroSD: %s\n", sdReady ? "BERHASIL" : "GAGAL");
  if (sdReady) createCsvFilesIfNeeded();

  // RTC DS1307 pada I2C melalui level shifter
  Wire.begin(RTC_SDA, RTC_SCL);
  rtcReady = rtc.begin();
  Serial.printf("RTC DS1307: %s\n", rtcReady ? "BERHASIL" : "GAGAL");
  if (rtcReady) {
    if (!rtc.isrunning()) {
      // Waktu awal dari waktu kompilasi; atur waktu yang benar lagi lewat web lokal.
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      Serial.println("RTC belum berjalan; diatur ke waktu kompilasi. Atur ulang dari web.");
    }
    Serial.print("Waktu RTC: "); Serial.println(rtcDateString());
  }

  initI2S();
  setupWeb();
  systemMessage = "Sistem siap. Tahan tombol GPIO14 selama 3 detik untuk mode konfigurasi.";
  Serial.println(systemMessage);
}

// ======================== LOOP ========================
void loop() {
  server.handleClient();
  processConfigButton();
  processEnrollment();
  processAttendance();
  loopAudio();
  updateLed();
  delay(1);
}
