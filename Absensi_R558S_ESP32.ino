#include "App.h"

/*
  ABSENSI OTOMATIS ESP32 + FINGERPRINT R558-S
  File utama: state global, setup(), dan loop().
  Fungsi perangkat ada di Fungsi.cpp; UI dan HTTP endpoint ada di Website.cpp.
*/

// ======================== Wi-Fi ========================
const char *DEFAULT_AP_SSID = "Absensi-ESP32";
const char *DEFAULT_AP_PASSWORD = "absensi123";
String apSSID = DEFAULT_AP_SSID;
String apPassword = DEFAULT_AP_PASSWORD;
String internetSSID = "";
String internetPassword = "";
uint8_t audioVolume = 80;
Preferences wifiPrefs;

// ======================== Perangkat dan status ========================
HardwareSerial FingerSerial(2);
RTC_DS1307 rtc;
WebServer server(80);

bool fingerprintReady = false;
bool sdReady = false;
bool rtcReady = false;
bool i2sReady = false;
bool configMode = false;
uint16_t templateCountValue = 0;
String systemMessage = "Memulai sistem...";

// ======================== Status komunikasi R558-S ========================
FingerOperation fingerOperation = FOP_NONE;
bool identifyActive = false;
bool waitingFingerRemoval = false;
bool removeProbePending = false;
uint32_t removeProbeSentAt = 0;
uint32_t lastRemoveProbeAt = 0;
uint32_t nextIdentifyAt = 0;
uint32_t identifyStartedAt = 0;
const uint32_t IDENTIFY_RETRY_MS = 600;
const uint32_t REMOVE_PROBE_INTERVAL_MS = 250;
const uint32_t REMOVE_WAIT_MAX_MS = 20000;
uint32_t removeWaitStartedAt = 0;

// ======================== Pendaftaran ========================
EnrollState enrollState = ENROLL_IDLE;
String enrollName;
uint16_t enrollId = 0;
uint16_t enrollCountBefore = 0;
bool enrollFirstPromptPlayed = false;
bool enrollSecondPromptPlayed = false;
uint32_t enrollmentStartedAt = 0;
const uint32_t ENROLL_TIMEOUT_MS = 180000;

// ======================== Absensi ========================
uint32_t lastAttendanceAt = 0;
uint16_t lastAttendanceId = 0;
const uint32_t DUPLICATE_COOLDOWN_MS = 30000;

// ======================== Tombol dan LED ========================
bool buttonTiming = false;
bool buttonLongHandled = false;
uint32_t buttonPressedAt = 0;
uint32_t ledOverrideUntil = 0;
bool overrideR = false, overrideG = false, overrideB = false;

// ======================== Audio WAV ========================
File audioFile;
bool audioPlaying = false;
uint32_t audioBytesRemaining = 0;
uint32_t audioSampleRate = 16000;
uint16_t audioChannels = 1;


// ======================== SETUP ========================
void setup() {
  Serial.begin(115200); delay(900);
  Serial.println("\n==========================================");
  Serial.println(" ABSENSI OTOMATIS ESP32 + R558-S");
  Serial.println("==========================================");

  pinMode(LED_R, OUTPUT); pinMode(LED_G, OUTPUT); pinMode(LED_B, OUTPUT);
  setRgb(false, false, true);
  pinMode(CONFIG_BUTTON, INPUT_PULLUP);
  pinMode(FP_TOUCH, INPUT);

  FingerSerial.begin(FP_BAUD, SERIAL_8N1, FP_RX, FP_TX);
  delay(350);
  Serial.println("Memeriksa komunikasi R558-S...");
  fingerprintReady = verifyFingerprintSensor();
  if (fingerprintReady) {
    Serial.println("R558-S: BERHASIL");
    uint16_t count = 0;
    if (readTemplateCount(count)) { templateCountValue = count; Serial.printf("Template sensor: %u / %u\n", templateCountValue, FP_CAPACITY); }
    else Serial.println("Peringatan: jumlah template belum terbaca.");
  } else {
    Serial.println("R558-S: GAGAL. Periksa TX/RX, daya, baud rate 57600, dan GND bersama.");
  }

  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  sdReady = SD.begin(SD_CS, SPI, 4000000);
  Serial.printf("MicroSD: %s\n", sdReady ? "BERHASIL" : "GAGAL");
  if (sdReady) createCsvFilesIfNeeded();

  Wire.begin(RTC_SDA, RTC_SCL);
  rtcReady = rtc.begin();
  Serial.printf("RTC DS1307: %s\n", rtcReady ? "BERHASIL" : "GAGAL");
  if (rtcReady) {
    if (!rtc.isrunning()) {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      Serial.println("RTC belum berjalan; disetel ke waktu kompilasi. Atur waktu yang benar dari web.");
    }
    Serial.print("Waktu RTC: "); Serial.println(rtcDateString());
  }

  initI2S();
  setupWeb();
  systemMessage = fingerprintReady ? (templateCountValue ? "Sistem siap. Tempelkan sidik jari untuk absensi." : "Sistem siap, tetapi database fingerprint kosong. Aktifkan Wi-Fi konfigurasi dan daftarkan pengguna.") : "Sistem menyala, tetapi sensor fingerprint belum siap.";
  Serial.println(systemMessage);
}

// ======================== MAIN LOOP ========================
void loop() {
  if (configMode) server.handleClient();
  processConfigButton();
  processFingerprintSerial();
  processEnrollmentTimeout();
  processFingerprintScheduler();
  loopAudio();
  updateLed();
  delay(1);
}
