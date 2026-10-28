# Automatic Attendance IoT — ESP32 + Fingerprint R558-S

## Wiring

### 1. ESP32 DevKit V1 dan R558-S

| Komponen | Pin komponen | ESP32 DevKit V1 | Keterangan |
|---|---|---|---|
| R558-S | TX | GPIO32 | UART RX ESP32 |
| R558-S | RX | GPIO33 | UART TX ESP32 |
| R558-S | TOUCH_OUT | GPIO34 | Opsional, untuk pemantauan sentuhan |
| R558-S | VCC_3.3V | 3.3V | Periksa pinout modul |
| R558-S | VCC_MCU | 3.3V | Ikuti datasheet varian yang digunakan |
| R558-S | GND | GND | Ground bersama |

Baud rate sensor fingerprint: **57600**.

### 2. MicroSD Module

| Pin MicroSD | ESP32 DevKit V1 | Keterangan |
|---|---|---|
| SCK / CLK | GPIO18 | SPI clock |
| MISO / DO | GPIO19 | SPI data keluar dari MicroSD |
| MOSI / DI | GPIO23 | SPI data masuk ke MicroSD |
| CS | GPIO13 | Chip select |
| VCC | 5V | Sesuai modul MicroSD yang digunakan |
| GND | GND | Ground bersama |

Pastikan modul MicroSD mendukung suplai 5V pada pin VCC. Tegangan logika keluarannya harus sesuai dengan batas aman GPIO ESP32, yaitu 3,3V.

### 3. RTC DS1307

| Pin RTC | ESP32 DevKit V1 | Keterangan |
|---|---|---|
| SDA | GPIO21 melalui level shifter yang sesuai | Jalur I2C |
| SCL | GPIO22 melalui level shifter yang sesuai | Jalur I2C |
| VCC | 5V | Sesuai modul DS1307 |
| GND | GND | Ground bersama |

**Penting:** DS1307 umumnya menggunakan pull-up I2C ke tegangan 5V. Jangan menghubungkan SDA dan SCL langsung ke ESP32 apabila jalurnya ditarik ke 5V. Gunakan level shifter dua arah yang sesuai.

### 4. MAX98357A dan Speaker

| Pin MAX98357A | ESP32 DevKit V1 / Komponen | Keterangan |
|---|---|---|
| DIN | GPIO27 | I2S data |
| BCLK | GPIO26 | I2S bit clock |
| LRC / LRCLK | GPIO25 | I2S word select |
| VDD | 5V | Suplai amplifier |
| GND | GND | Ground bersama |
| OUT+ | Speaker + | Output audio |
| OUT- | Speaker - | Output audio |

Kedua terminal speaker harus terhubung ke OUT+ dan OUT-. **Jangan menghubungkan OUT+ atau OUT- ke GND**, karena output amplifier merupakan tipe bridge.

### 5. LED RGB Common Cathode

Gunakan resistor **330 Ω secara seri pada setiap kanal LED**.

| Pin LED RGB | ESP32 DevKit V1 | Keterangan |
|---|---|---|
| R | GPIO2 melalui resistor 330 Ω | Kanal merah |
| G | GPIO15 melalui resistor 330 Ω | Kanal hijau |
| B | GPIO4 melalui resistor 330 Ω | Kanal biru |
| Common cathode | GND | Katoda bersama |

Pinout ini berlaku untuk LED RGB tipe common cathode.

### 6. Tombol Konfigurasi Wi-Fi

| Koneksi | ESP32 DevKit V1 | Keterangan |
|---|---|---|
| Kaki pertama tombol | GPIO14 | Input tombol |
| Kaki kedua tombol | GND | Ground |

Program menggunakan `INPUT_PULLUP`. Tombol akan terbaca LOW ketika ditekan.

- Tahan tombol selama 3 detik untuk meminta aktivasi mode konfigurasi.
- Tahan kembali selama 3 detik untuk meminta keluar dari mode konfigurasi.

Aktivasi Wi-Fi harus diverifikasi melalui Serial Monitor. Jika ESP32 mengalami reset ketika Wi-Fi diaktifkan, periksa log sebelum menggunakan fitur web.

### 7. Ground dan Suplai Daya

- Semua modul yang terhubung ke ESP32 harus memiliki referensi GND bersama.
- Gunakan suplai yang sesuai dengan kebutuhan tegangan dan arus masing-masing modul.
- Jangan menghubungkan dua sumber tegangan ke jalur yang sama tanpa memastikan rangkaiannya memang mendukung konfigurasi tersebut.
- Pastikan level logika seluruh sinyal yang masuk ke GPIO ESP32 tidak melebihi 3,3V.
- Jika menggunakan USB komputer untuk ESP32 dan adaptor eksternal untuk modul lain, pastikan GND kedua sistem terhubung bersama.
- Jangan menganggap suplai daya pasti cukup hanya berdasarkan nilai arus pada label adaptor; kestabilan tegangan saat beban berubah juga perlu diperhatikan.

## Pengaturan Arduino IDE

1. Instal paket board **esp32 by Espressif Systems** melalui Boards Manager.
2. Pilih board **ESP32 Dev Module**.
3. Pilih port COM ESP32 yang benar.
4. Instal library berikut melalui Library Manager:
   - **Adafruit Fingerprint Sensor Library** oleh Adafruit.
   - **RTClib** oleh Adafruit.
5. Buka sketch `Absensi_R558S_ESP32.ino`.
6. Unggah program dan buka Serial Monitor pada **115200 baud**.

Library Wi-Fi, WebServer, SPI, SD, Wire, dan I2S berasal dari paket board ESP32 atau framework yang digunakan sketch.

## Web Lokal

Jika mode Access Point berhasil diaktifkan:

1. Sambungkan laptop atau ponsel ke jaringan `Absensi-ESP32`.
2. Password awal: `absensi123`.
3. Buka `http://192.168.4.1`.
4. Gunakan formulir web untuk mendaftarkan pengguna dan mengatur waktu RTC.

Alamat, SSID, dan password harus sesuai dengan konfigurasi pada sketch yang digunakan.

## Isi MicroSD

Sketch menggunakan file berikut:

- `users.csv` — pemetaan ID fingerprint dan nama pengguna.
- `attendance.csv` — catatan tanggal, waktu, ID, nama, dan confidence.

Jangan mengubah ID pada `users.csv` tanpa menyesuaikan template fingerprint yang tersimpan di sensor.

## Audio MAX98357A

Salin file WAV ke direktori root MicroSD:

- `/sukses.wav` — audio ketika sidik jari cocok.
- `/coba_lagi.wav` — audio ketika sidik jari tidak dikenal atau pendaftaran gagal.
- `/terima_kasih.wav` — audio setelah pendaftaran berhasil.

Format yang didukung sesuai implementasi sketch: **WAV PCM 16-bit**, mono atau stereo, dengan sample rate 8.000–48.000 Hz. Mengganti ekstensi MP3 menjadi WAV tidak mengubah format audio.

## Catatan Penggunaan

- GPIO34 merupakan input-only dan tidak memiliki internal pull-up/pull-down. Pastikan sinyal TOUCH_OUT sesuai dengan level logika ESP32.
- Pemindaian fingerprint dilakukan melalui komunikasi UART dengan sensor, bukan semata-mata berdasarkan sinyal TOUCH_OUT.
- Anti-log duplikat menggunakan jeda 30 detik untuk ID yang sama; ini bukan aturan satu kali per hari.
- Jika RTC tidak tersedia, catatan dapat menggunakan penanda `RTC_UNAVAILABLE`, sesuai implementasi sketch.
- Ganti password Wi-Fi contoh sebelum sistem digunakan.
- Fitur penghapusan pengguna melalui web, ekspor CSV melalui web, autentikasi admin tambahan, dan sinkronisasi server belum tersedia dalam versi ini.

## Troubleshooting Wi-Fi

Jika ESP32 berjalan normal tanpa Wi-Fi tetapi reset saat `WiFi.mode(WIFI_AP)` dipanggil:

1. Uji sketch Wi-Fi minimal tanpa perangkat eksternal.
2. Bandingkan hasilnya menggunakan board ESP32 lain dengan sketch dan konfigurasi yang sama.
3. Catat log Serial Monitor lengkap sebelum
