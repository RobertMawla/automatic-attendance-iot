# Absensi Otomatis ESP32 + Fingerprint R558-S

Sketch ini menggabungkan web lokal ESP32, pendaftaran fingerprint, absensi, pencatatan MicroSD, RTC DS1307, LED RGB, tombol konfigurasi, dan pemutaran WAV menggunakan MAX98357A.

## Library yang harus dipasang

Di Arduino IDE > Library Manager, pasang:

1. **Adafruit Fingerprint Sensor Library** (Adafruit)
2. **RTClib** (Adafruit)

Komponen Wi-Fi, WebServer, SPI, SD, Wire, dan I2S disediakan oleh paket board ESP32.

## Pengaturan board

1. Instal paket board **esp32 by Espressif Systems** melalui Boards Manager.
2. Pilih board **ESP32 Dev Module** (atau board DevKit V1 yang sesuai).
3. Pilih port COM yang benar.
4. Buka `Absensi_R558S_ESP32.ino`, lalu upload.
5. Buka Serial Monitor pada **115200 baud**.

## Wiring

| Komponen | Pin komponen | ESP32 DevKit V1 | Catatan |
|---|---|---|---|
| R558-S | TX | GPIO16 (RX2) | UART, silang TX/RX |
| R558-S | RX | GPIO17 (TX2) | UART, silang TX/RX |
| R558-S | TOUCH_OUT | GPIO34 | Opsional untuk pemantauan; bukan penentu utama scan |
| R558-S | VCC_3.3V | 3V3 sesuai spesifikasi modul | Jangan menebak tegangan modul |
| R558-S | VCC_MCU | 3V3 sesuai spesifikasi modul | Ikuti pinout/datasheet varian yang digunakan |
| R558-S | GND | GND | Ground bersama |
| MicroSD | SCK/CLK | GPIO18 | SPI |
| MicroSD | MISO/DO | GPIO19 | SPI |
| MicroSD | MOSI/DI | GPIO23 | SPI |
| MicroSD | CS | GPIO13 | SPI chip select |
| MicroSD | VCC | Sesuai modul | Modul berbeda bisa memerlukan 3.3 V atau 5 V |
| MicroSD | GND | GND | Ground bersama |
| DS1307 | SDA | GPIO21 melalui level shifter | DS1307 biasanya pull-up 5 V; jangan langsung ke ESP32 tanpa level shifting yang sesuai |
| DS1307 | SCL | GPIO22 melalui level shifter | I2C |
| DS1307 | VCC | 5V | Sesuai modul DS1307 |
| DS1307 | GND | GND | Ground bersama |
| MAX98357A | DIN | GPIO27 | I2S data |
| MAX98357A | BCLK | GPIO26 | I2S bit clock |
| MAX98357A | LRC/LRCLK | GPIO25 | I2S word select |
| MAX98357A | VDD | 5V | Pastikan suplai cukup dan stabil |
| MAX98357A | GND | GND | Ground bersama |
| MAX98357A | OUT+ | Speaker + | Jangan sambungkan salah satu terminal speaker ke GND |
| MAX98357A | OUT- | Speaker - | Output bridge amplifier |
| RGB common cathode | R | GPIO32 melalui resistor 330 Ω | Resistor seri tiap kanal |
| RGB common cathode | G | GPIO33 melalui resistor 330 Ω | Resistor seri tiap kanal |
| RGB common cathode | B | GPIO4 melalui resistor 330 Ω | Resistor seri tiap kanal |
| RGB common cathode | Common | GND | Berlaku untuk common cathode |
| Tombol | Satu kaki | GPIO14 | Kaki lain ke GND; pakai INPUT_PULLUP |

Semua modul harus memakai **GND bersama**. Periksa kembali label/pinout R558-S milikmu. Jangan menghubungkan VCC_3.3V dan VCC_MCU ke suplai yang sama jika datasheet varian modul tidak menyatakan demikian.

## Web lokal

1. Nyalakan ESP32.
2. Dari laptop/ponsel, sambungkan Wi-Fi ke `Absensi-ESP32`.
3. Kata sandi awal: `absensi123`.
4. Buka `http://192.168.4.1`.
5. Tahan tombol GPIO14 selama 3 detik untuk mengaktifkan mode konfigurasi. LED ungu menunjukkan konfigurasi/pendaftaran.
6. Daftarkan pengguna lewat formulir web. Tempelkan jari pertama kali, angkat saat diminta, lalu tempelkan jari yang sama untuk scan kedua.
7. Atur waktu RTC melalui formulir tanggal/waktu.
8. Tekan dan tahan GPIO14 selama 3 detik sekali lagi untuk keluar dari mode konfigurasi. Saat standby LED berwarna biru.
9. Pengguna melakukan absensi dengan menempelkan jari. Cocok: LED hijau dan log ke MicroSD. Tidak cocok: LED merah.

Alamat web tetap tersedia ketika mode konfigurasi nonaktif, tetapi pendaftaran dan pengaturan RTC ditolak sampai tombol konfigurasi diaktifkan.

## Isi MicroSD

Sketch membuat dua file CSV bila belum ada:

- `users.csv` — pemetaan ID fingerprint ke nama pengguna.
- `attendance.csv` — tanggal, waktu, ID, nama, dan nilai confidence.

Jangan menghapus atau mengubah ID di `users.csv` tanpa menyesuaikan template yang tersimpan di memori fingerprint.

## Audio MAX98357A

Salin WAV berikut ke root MicroSD (bukan ke folder):

- `/sukses.wav` — diputar saat sidik jari cocok.
- `/coba_lagi.wav` — diputar ketika sidik jari gagal/tidak dikenal atau pendaftaran gagal.
- `/terima_kasih.wav` — diputar setelah pendaftaran sukses.

File harus WAV **PCM 16-bit**, mono atau stereo, sample rate **8.000–48.000 Hz**. File MP3 yang hanya diganti namanya menjadi WAV tidak akan berfungsi. Jika file audio tidak ditemukan, fungsi fingerprint dan log tetap berjalan, tetapi audio tidak terdengar. Output speaker MAX98357A adalah output bridge; jangan sambungkan terminal speaker ke GND.

## Perilaku penting / batas versi ini

- GPIO34 TOUCH_OUT dipantau pada halaman web, tetapi scan fingerprint dilakukan lewat perintah sensor, bukan semata-mata berdasarkan HIGH/LOW TOUCH_OUT. Ini menghindari asumsi polaritas pin touch yang belum dipastikan.
- Anti-log duplikat dibuat sederhana: ID yang sama tidak dicatat ulang dalam 30 detik. Ini bukan aturan satu kali per hari.
- Saat RTC tidak tersedia, log tetap dapat ditulis dengan waktu `RTC_UNAVAILABLE`; periksa RTC sebelum dipakai nyata.
- Password Wi-Fi pada sketch adalah contoh. Ubah `AP_PASSWORD` sebelum penggunaan di lingkungan nyata.
- Versi ini belum menyediakan penghapusan pengguna dari web, ekspor CSV melalui web, otentikasi admin web tambahan, atau sinkronisasi ke server/internet.
# automatic-attendance-iot 
