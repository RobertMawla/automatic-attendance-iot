#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include <WebServer.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <RTClib.h>
#include "driver/i2s.h"

// ======================== Pin configuration ========================
#define FP_RX          32
#define FP_TX          33
#define FP_TOUCH       34
#define FP_BAUD        57600
#define FP_CAPACITY    100
#define SD_SCK         18
#define SD_MISO        19
#define SD_MOSI        23
#define SD_CS          13
#define RTC_SDA        21
#define RTC_SCL        22
#define I2S_DOUT       27
#define I2S_BCLK       26
#define I2S_LRC        25
#define LED_R          2
#define LED_G          15
#define LED_B          4
#define CONFIG_BUTTON  14

// ======================== Shared state types ========================
enum FingerOperation : uint8_t {
  FOP_NONE,
  FOP_ENROLL,
  FOP_IDENTIFY,
  FOP_REMOVE_PROBE
};

enum EnrollState : uint8_t {
  ENROLL_IDLE,
  ENROLL_RUNNING
};

// ======================== Global state owned by the main .ino ========================
extern const char *DEFAULT_AP_SSID;
extern const char *DEFAULT_AP_PASSWORD;
extern String apSSID;
extern String apPassword;
extern String internetSSID;
extern String internetPassword;
extern uint8_t audioVolume;
extern Preferences wifiPrefs;
extern HardwareSerial FingerSerial;
extern RTC_DS1307 rtc;
extern WebServer server;

extern bool fingerprintReady;
extern bool sdReady;
extern bool rtcReady;
extern bool i2sReady;
extern bool configMode;
extern uint16_t templateCountValue;
extern String systemMessage;

extern FingerOperation fingerOperation;
extern bool identifyActive;
extern bool waitingFingerRemoval;
extern bool removeProbePending;
extern uint32_t removeProbeSentAt;
extern uint32_t lastRemoveProbeAt;
extern uint32_t nextIdentifyAt;
extern uint32_t identifyStartedAt;
extern uint32_t removeWaitStartedAt;
extern const uint32_t IDENTIFY_RETRY_MS;
extern const uint32_t REMOVE_PROBE_INTERVAL_MS;
extern const uint32_t REMOVE_WAIT_MAX_MS;

extern EnrollState enrollState;
extern String enrollName;
extern uint16_t enrollId;
extern uint16_t enrollCountBefore;
extern bool enrollFirstPromptPlayed;
extern bool enrollSecondPromptPlayed;
extern uint32_t enrollmentStartedAt;
extern const uint32_t ENROLL_TIMEOUT_MS;

extern uint32_t lastAttendanceAt;
extern uint16_t lastAttendanceId;
extern const uint32_t DUPLICATE_COOLDOWN_MS;

extern bool buttonTiming;
extern bool buttonLongHandled;
extern uint32_t buttonPressedAt;
extern uint32_t ledOverrideUntil;
extern bool overrideR;
extern bool overrideG;
extern bool overrideB;

extern File audioFile;
extern bool audioPlaying;
extern uint32_t audioBytesRemaining;
extern uint32_t audioSampleRate;
extern uint16_t audioChannels;

extern const char INDEX_HTML[] PROGMEM;
extern const char REGISTRATION_HTML[] PROGMEM;

// ======================== Function module declarations ========================
String jsonEscape(const String &in);
String sanitizeName(String name);
String modeText();
String enrollmentText();
String rtcDateString();
void setRgb(bool r, bool g, bool b);
void showFeedback(bool r, bool g, bool b, uint32_t durationMs = 1800);
void updateLed();

void resetFingerprintRx();
bool sendFingerprintCommand(const uint8_t *payload, uint16_t payloadLength, bool debug = true);
bool readFingerprintPacket(uint8_t *out, uint16_t outCapacity, uint16_t &outLength, bool debug = true);
bool readFingerprintPacketBlocking(uint8_t *out, uint16_t outCapacity, uint16_t &outLength, uint32_t timeoutMs);
bool fingerprintTransaction(const uint8_t *command, uint16_t commandLength,
                            uint8_t *response, uint16_t responseCapacity,
                            uint16_t &responseLength, uint32_t timeoutMs = 3000);
bool verifyFingerprintSensor();
bool readTemplateCount(uint16_t &count);
bool readTemplateIndexPage(uint8_t page, uint8_t *bitmap, size_t bitmapCapacity, size_t &bitmapLength);
bool templateIdOccupied(uint16_t id, bool &known);
uint16_t maxUserIdInCsv();
bool userIdExistsInCsv(uint16_t id);
bool templateStoredAtId(uint16_t id, bool &known);
uint16_t nextAvailableFingerprintId();
const char *fingerErrorText(uint8_t code);

void createCsvFilesIfNeeded();
String findUserName(uint16_t id);
bool saveUser(uint16_t id, const String &name);
bool readUserMappingExists(uint16_t wantedId, bool &exists);
bool removeUserMappingFromCsv(uint16_t wantedId, bool &removed);
bool appendAttendance(uint16_t id, const String &name, uint16_t confidence);
String csvField(const String &line, uint8_t wanted);

uint16_t readLE16(File &f);
uint32_t readLE32(File &f);
bool readFourCC(File &f, char *out);
void initI2S();
bool startAudio(const char *path);
void loopAudio();

void startRemovalWait();
void finishEnrollment(bool success, const String &message);
void completeEnrollmentFromSensor();
void handleEnrollmentPacket(const uint8_t *data, uint16_t len);
void handleIdentificationPacket(const uint8_t *data, uint16_t len);
void handleRemoveProbePacket(const uint8_t *data, uint16_t len);
void processFingerprintSerial();
void processEnrollmentTimeout();
void beginAutoEnroll(uint16_t id, const String &name);
void beginAutoIdentify();
void processFingerprintScheduler();

bool startConfigWifi();
void cancelActiveFingerprintOperation();
void stopConfigWifi();
void processConfigButton();

// ======================== Website module declarations ========================
void handleRoot();
void handleRegistrationPage();
void handleStatus();
void handleWifiSettings();
void handleWifiSave();
void handleStopConfigMode();
bool nameExistsInCsv(const String &name);
void handleStartEnroll();
void handleCancelEnroll();
void handleLinkStoredUser();
void handleRTCSet();
void handleDeleteUser();
void handleUsers();
void handleLogs();
void setupWeb();
