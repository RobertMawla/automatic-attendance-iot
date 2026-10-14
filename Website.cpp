#include "App.h"

// ======================== Halaman website (HTML/CSS/JavaScript) ========================
// ======================== WEB UI ========================
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang="id">
<head>
<meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<meta name="theme-color" content="#101d32">
<title>Absensi Otomatis | Dashboard Perangkat</title>
<style>
:root{font-family:Inter,ui-sans-serif,system-ui,-apple-system,"Segoe UI",Arial,sans-serif;color:#182338;background:#f5f7fb;color-scheme:light}*{box-sizing:border-box}body{margin:0;font-size:14px;line-height:1.55}.top{background:linear-gradient(115deg,#111c34,#24395f);color:#fff;padding:25px 16px;box-shadow:0 6px 24px #17223512}.wrap{max-width:760px;margin:auto;padding:22px 16px 42px}.brand{font-size:1.2rem;font-weight:800;letter-spacing:-.025em}.sub{color:#c5d0e2;font-size:.84rem;margin-top:5px}.card{background:#fff;border:1px solid #e5eaf2;border-radius:16px;padding:22px;margin-bottom:16px;box-shadow:0 5px 20px #17223507}h2{font-size:1.08rem;letter-spacing:-.02em;margin:0 0 9px;font-weight:800}.muted{color:#738096;font-size:.87rem;line-height:1.7;margin:0}label{display:block;font-size:.82rem;font-weight:750;margin:17px 0 7px;color:#39465d}input,button{font:inherit;width:100%;padding:12px 13px;border-radius:10px}input{border:1px solid #d5dce8;outline:none;color:#182338}input::placeholder{color:#a1aabc}input:focus{border-color:#8295f3;box-shadow:0 0 0 3px #425fe81a}button{border:1px solid transparent;background:#425fe8;color:white;font-weight:750;cursor:pointer;margin-top:10px;transition:background .18s,box-shadow .18s}button:hover{background:#304bd0;box-shadow:0 4px 12px #425fe82b}button:disabled{opacity:.45;cursor:not-allowed;box-shadow:none}button.secondary{background:#eef2f8;color:#33415c;border-color:#e2e8f0}button.secondary:hover{background:#e2e9f4}button.danger{background:#fff1f2;color:#b72f43;border-color:#ffd8de}button.danger:hover{background:#ffe4e8}.steps{display:grid;gap:10px;margin:17px 0}.step{display:flex;gap:12px;padding:13px;border-radius:12px;background:#f8faff;border:1px solid #e7ecf5}.num{display:grid;place-items:center;width:29px;height:29px;border-radius:9px;background:#e9edff;color:#425fe8;font-weight:850;flex-shrink:0}.step strong{font-size:.87rem;color:#26334b}.step span{display:block;color:#738096;font-size:.81rem;line-height:1.55;margin-top:3px}.status{white-space:pre-wrap;line-height:1.65;background:#f5f8ff;border:1px solid #dce6ff;border-radius:11px;padding:14px;margin-top:13px;overflow-wrap:anywhere;font-size:.86rem}.devices{display:flex;flex-wrap:wrap;gap:7px;margin-top:13px}.pill{border:1px solid #e4e9f1;background:#f8fafc;border-radius:8px;padding:6px 10px;font-size:.77rem;font-weight:650;color:#536178}.pill.ok{color:#08775f;background:#effbf6;border-color:#ccefe1}.back{display:block;text-align:center;text-decoration:none;color:#425fe8;font-weight:750;padding:13px 10px;margin-top:5px}.back:hover{text-decoration:underline}.timer{font-size:.82rem;color:#738096;margin-top:9px}.foot{font-size:.77rem;color:#8792a5;text-align:center;margin-top:18px}@media(max-width:480px){.top{padding:21px 14px}.wrap{padding:16px 12px 30px}.card{padding:17px;border-radius:14px}}
</style></head>
<body>
<header class="top"><div class="topinner"><div class="topline"><div class="brand"><div class="logo">✓</div><div><h1>Absensi Otomatis</h1><p>ESP32 DevKit V1 · R558-S · MicroSD · RTC</p></div></div><div class="connection"><span class="dot" id="connectionDot"></span><span id="connectionText">Menghubungkan ke perangkat…</span></div></div></div></header>
<main class="wrap">
  <div class="sectionhead"><div><h2>Ringkasan perangkat</h2><p>Pantau kondisi perangkat dan aktivitas absensi.</p></div><button class="secondary" onclick="refreshAll()">↻ Muat ulang</button></div>
  <section class="grid">
    <div class="card"><div class="statlabel">Fingerprint R558-S</div><div class="statvalue" id="statFp">Memeriksa…</div><div class="statdetail">Pengenalan sidik jari</div></div>
    <div class="card"><div class="statlabel">Template sensor</div><div class="statvalue" id="statTemplates">—</div><div class="statdetail">Kapasitas sensor: 100 ID</div></div>
    <div class="card"><div class="statlabel">MicroSD</div><div class="statvalue" id="statSd">Memeriksa…</div><div class="statdetail">users.csv dan attendance.csv</div></div>
    <div class="card"><div class="statlabel">Waktu perangkat</div><div class="statvalue" id="statTime">—</div><div class="statdetail" id="statRtc">RTC DS1307</div></div>
  </section>
  <div class="layout">
    <section class="card"><h3 class="paneltitle">Status dan aktivitas</h3><div class="statuschips" id="chips"></div><div id="message" class="message" style="margin-top:14px">Menghubungkan…</div><p class="small" id="modeText" style="margin:12px 0 0">Mode: —</p><div class="actionrow"><button onclick="location.href='/pendaftaran'">＋ Daftarkan fingerprint</button></div><div class="field"><label for="datetime">Tanggal dan waktu RTC DS1307</label><input id="datetime" type="datetime-local"></div><div class="actionrow"><button class="secondary" onclick="setRTC()">Simpan waktu RTC</button></div><p class="modalnote">Halaman konfigurasi tersedia saat tombol GPIO14 ditahan selama 3 detik. Wi-Fi AP tidak aktif saat boot untuk menghemat daya.</p></section>
    <section class="card"><h3 class="paneltitle">Pengaturan Wi-Fi konfigurasi</h3><p class="small">Ubah nama dan kata sandi jaringan konfigurasi ESP32. Setelah disimpan, sambungkan ulang HP/laptop ke jaringan baru.</p><div class="field"><label for="wifiName">Nama jaringan (SSID)</label><input id="wifiName" maxlength="32" placeholder="Absensi-ESP32" autocomplete="off"></div><div class="field"><label for="wifiPassword">Kata sandi baru</label><input id="wifiPassword" type="password" maxlength="63" placeholder="Kosongkan untuk tetap memakai yang lama" autocomplete="new-password"></div><button id="saveWifiButton" onclick="saveWifi()">Simpan pengaturan</button><p class="modalnote">SSID 1–32 karakter. Kata sandi 8–63 karakter.</p></section>
  </div>
  <section class="card" style="margin-top:14px"><h3 class="paneltitle">Hubungkan template yang sudah tersimpan</h3><p class="small">Gunakan bagian ini jika sidik jari sudah tersimpan di sensor (misalnya ID 1 dari pengujian), tetapi belum memiliki nama di <code>users.csv</code>. Proses ini tidak memindai ulang atau mengubah template sensor.</p><div class="grid" style="grid-template-columns:minmax(100px,.35fr) minmax(180px,1fr);margin-top:12px"><div class="field" style="margin:0"><label for="storedId">ID template sensor</label><input id="storedId" type="number" min="1" max="100" placeholder="1"></div><div class="field" style="margin:0"><label for="storedName">Nama pengguna</label><input id="storedName" maxlength="32" placeholder="Nama pemilik sidik jari"></div></div><div class="actionrow"><button class="secondary" onclick="linkStoredUser()">Simpan pemetaan ID ke nama</button></div><p class="modalnote">Pilih hanya ID yang sidik jarinya memang sudah pernah didaftarkan. Program akan memeriksa apakah slot tersebut benar-benar berisi template.</p></section>
  <section class="card" style="margin-top:14px"><div class="sectionhead"><div><h2>Pengguna terdaftar</h2><p>Nama pada MicroSD harus memiliki ID yang sama dengan template di sensor. Tombol Hapus akan menghapus template dan data pengguna; riwayat absensi tetap disimpan.</p></div><span class="chip" id="userCount">0 pengguna</span></div><div class="tablewrap"><table><thead><tr><th>ID fingerprint</th><th>Nama pengguna</th><th>Aksi</th></tr></thead><tbody id="users"><tr><td colspan="3" class="empty">Memuat pengguna…</td></tr></tbody></table></div><div class="actionrow"><button class="secondary" onclick="refreshUsers()">Muat ulang pengguna</button></div></section>
  <section class="card" style="margin-top:14px"><div class="sectionhead"><div><h2>Riwayat absensi</h2><p>20 catatan terakhir dari attendance.csv.</p></div><button class="secondary" onclick="refreshLogs()">↻ Perbarui riwayat</button></div><div class="tablewrap"><table><thead><tr><th>Tanggal</th><th>Waktu</th><th>ID</th><th>Nama</th><th>Skor</th></tr></thead><tbody id="logs"><tr><td colspan="5" class="empty">Memuat riwayat…</td></tr></tbody></table></div></section>
  <footer class="foot">Absensi Otomatis · Akses lokal melalui <strong>http://192.168.4.1</strong> saat Wi-Fi konfigurasi aktif.</footer>
</main>
<script>
async function getJson(url){const r=await fetch(url,{cache:'no-store'});if(!r.ok)throw new Error(await r.text());return r.json()}
function cell(tr,value){const td=document.createElement('td');td.textContent=value??'';tr.appendChild(td)}
function setStatusMessage(text,type=''){const el=document.getElementById('message');el.textContent=text||'Tidak ada pesan.';el.className='message'+(type?' '+type:'')}
function setChip(label,value){const el=document.createElement('span');el.className='chip '+(value==='OK'||value==='SIAP'||value==='AKTIF'?'ok':(value==='GAGAL'||value==='TIDAK ADA'?'bad':''));el.textContent=label+': '+value;document.getElementById('chips').appendChild(el)}
async function refreshStatus(){try{const s=await getJson('/api/status');document.getElementById('connectionText').textContent='Terhubung ke ESP32';document.getElementById('connectionDot').style.background='#35c49a';document.getElementById('statFp').textContent=s.fingerprint;document.getElementById('statTemplates').textContent=s.templates+' / 100';document.getElementById('statSd').textContent=s.sd;document.getElementById('statTime').textContent=s.time;document.getElementById('statRtc').textContent='RTC DS1307: '+s.rtc;document.getElementById('modeText').textContent='Mode: '+s.mode+' · Wi-Fi: '+(s.wifi==='AKTIF'?'aktif':'nonaktif');document.getElementById('chips').textContent='';setChip('Fingerprint',s.fingerprint);setChip('MicroSD',s.sd);setChip('RTC',s.rtc);setChip('Audio',s.audio);setChip('Wi-Fi',s.wifi);const type=s.messageType||'';setStatusMessage(s.message,type);if(s.enrollBusy){setStatusMessage('Pendaftaran ID '+s.enrollId+' sedang berjalan.\n'+s.enrollment,'');}}catch(e){document.getElementById('connectionText').textContent='Perangkat tidak terhubung';document.getElementById('connectionDot').style.background='#e05260';setStatusMessage('Gagal mengambil status: '+e.message,'bad')}}
async function refreshUsers(){const b=document.getElementById('users');b.textContent='';try{const arr=await getJson('/api/users');document.getElementById('userCount').textContent=arr.length+' pengguna';if(!arr.length){const tr=document.createElement('tr');const td=document.createElement('td');td.colSpan=3;td.className='empty';td.textContent='Belum ada pengguna pada users.csv.';tr.appendChild(td);b.appendChild(tr);return}arr.forEach(u=>{const tr=document.createElement('tr');cell(tr,u.id);cell(tr,u.name);const td=document.createElement('td');const btn=document.createElement('button');btn.className='danger';btn.textContent='Hapus';btn.style.padding='8px 12px';btn.style.whiteSpace='nowrap';btn.onclick=()=>deleteUser(u.id,u.name);td.appendChild(btn);tr.appendChild(td);b.appendChild(tr)})}catch(e){const tr=document.createElement('tr');const td=document.createElement('td');td.colSpan=3;td.className='empty';td.textContent='MicroSD tidak tersedia atau users.csv gagal dibaca.';tr.appendChild(td);b.appendChild(tr)}}
async function deleteUser(id,name){const ok=confirm('Hapus pengguna '+name+' (ID '+id+')? Template sidik jari di sensor dan data pengguna di users.csv akan dihapus. Riwayat absensi di attendance.csv tetap tersimpan.');if(!ok)return;try{const r=await fetch('/api/delete-user?id='+encodeURIComponent(id),{method:'POST',cache:'no-store'});const t=await r.text();if(!r.ok)throw new Error(t);setStatusMessage(t,'ok');await Promise.all([refreshUsers(),refreshStatus()])}catch(e){setStatusMessage('Penghapusan gagal: '+e.message,'bad')}}
async function refreshLogs(){const b=document.getElementById('logs');b.textContent='';try{const arr=await getJson('/api/logs');if(!arr.length){const tr=document.createElement('tr');const td=document.createElement('td');td.colSpan=5;td.className='empty';td.textContent='Belum ada catatan absensi.';tr.appendChild(td);b.appendChild(tr);return}arr.forEach(x=>{const tr=document.createElement('tr');cell(tr,x.date);cell(tr,x.time);cell(tr,x.id);cell(tr,x.name);cell(tr,x.confidence);b.appendChild(tr)})}catch(e){const tr=document.createElement('tr');const td=document.createElement('td');td.colSpan=5;td.className='empty';td.textContent='Gagal membaca attendance.csv.';tr.appendChild(td);b.appendChild(tr)}}
async function loadWifi(){try{const s=await getJson('/api/wifi');document.getElementById('wifiName').value=s.ssid||''}catch(e){}}
async function linkStoredUser(){const id=document.getElementById('storedId').value;const name=document.getElementById('storedName').value.trim();if(!id||Number(id)<1||Number(id)>100){setStatusMessage('Masukkan ID template antara 1 sampai 100.','bad');return}if(!name){setStatusMessage('Masukkan nama pengguna.','bad');return}try{const r=await fetch('/api/link-user?id='+encodeURIComponent(id)+'&name='+encodeURIComponent(name),{method:'POST'});const t=await r.text();if(!r.ok)throw new Error(t);setStatusMessage(t,'ok');document.getElementById('storedName').value='';await Promise.all([refreshUsers(),refreshStatus()])}catch(e){setStatusMessage('Pemetaan gagal: '+e.message,'bad')}}
async function saveWifi(){const ssid=document.getElementById('wifiName').value.trim();const password=document.getElementById('wifiPassword').value;if(!ssid){setStatusMessage('Nama Wi-Fi wajib diisi.','bad');return}if(password&&password.length<8){setStatusMessage('Kata sandi minimal 8 karakter.','bad');return}const b=document.getElementById('saveWifiButton');b.disabled=true;b.textContent='Menyimpan…';try{const r=await fetch('/wifi?ssid='+encodeURIComponent(ssid)+'&password='+encodeURIComponent(password),{method:'POST'});const t=await r.text();if(!r.ok)throw new Error(t);document.getElementById('wifiPassword').value='';setStatusMessage(t+' Sambungkan ulang perangkat ke Wi-Fi yang baru jika diperlukan.','ok')}catch(e){setStatusMessage('Pengaturan Wi-Fi: '+e.message,'bad')}finally{b.disabled=false;b.textContent='Simpan pengaturan'}}
function initRTCInput(){const now=new Date();const local=new Date(now.getTime()-now.getTimezoneOffset()*60000).toISOString().slice(0,16);const el=document.getElementById('datetime');if(el&&!el.value)el.value=local}async function setRTC(){const value=document.getElementById('datetime').value;if(!value){setStatusMessage('Pilih tanggal dan waktu RTC terlebih dahulu.','bad');return}try{const r=await fetch('/rtc?datetime='+encodeURIComponent(value));const t=await r.text();if(!r.ok)throw new Error(t);setStatusMessage(t,'ok');refreshStatus()}catch(e){setStatusMessage('Gagal mengatur RTC: '+e.message,'bad')}}
async function refreshAll(){initRTCInput();await Promise.all([refreshStatus(),refreshUsers(),refreshLogs(),loadWifi()])}
refreshAll();setInterval(refreshStatus,1000);setInterval(refreshUsers,7000);setInterval(refreshLogs,5000);
</script></body></html>
)rawliteral";

const char REGISTRATION_HTML[] PROGMEM = R"rawliteral(
<!doctype html><html lang="id"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><meta name="theme-color" content="#101d32"><title>Pendaftaran Fingerprint | Absensi Otomatis</title>
<style>
:root{font-family:Inter,ui-sans-serif,system-ui,-apple-system,"Segoe UI",Arial,sans-serif;color:#172235;background:#f3f6fa}*{box-sizing:border-box}body{margin:0}.top{background:#101d32;color:#fff;padding:22px 16px}.wrap{max-width:720px;margin:auto;padding:18px 14px 40px}.brand{font-size:1.2rem;font-weight:800}.sub{color:#c3cfdf;font-size:.87rem;margin-top:5px}.card{background:#fff;border:1px solid #e2e8f0;border-radius:18px;padding:20px;margin-bottom:14px;box-shadow:0 3px 12px #17223508}h2{font-size:1.1rem;margin:0 0 8px}.muted{color:#718096;font-size:.9rem;line-height:1.55}label{display:block;font-size:.86rem;font-weight:750;margin:14px 0 7px}input,button{font:inherit;width:100%;padding:13px;border-radius:11px}input{border:1px solid #cbd5e1;outline:none}input:focus{border-color:#7093ef;box-shadow:0 0 0 3px #245bd61b}button{border:0;background:#245bd6;color:white;font-weight:750;cursor:pointer;margin-top:10px}button.secondary{background:#e9eef6;color:#26364f}button.danger{background:#fff0f1;color:#a92c3b;border:1px solid #ffd5d9}.steps{display:grid;gap:9px;margin:16px 0}.step{display:flex;gap:12px;padding:12px;border-radius:12px;background:#f7f9fc;border:1px solid #e5ebf4}.num{display:grid;place-items:center;width:27px;height:27px;border-radius:9px;background:#e5edff;color:#245bd6;font-weight:800;flex-shrink:0}.step strong{font-size:.9rem}.step span{display:block;color:#718096;font-size:.82rem;line-height:1.45;margin-top:3px}.status{white-space:pre-wrap;line-height:1.55;background:#f5f8ff;border:1px solid #dce7f8;border-radius:12px;padding:14px;margin-top:12px;overflow-wrap:anywhere}.devices{display:flex;flex-wrap:wrap;gap:7px;margin-top:12px}.pill{border:1px solid #e2e8f0;background:#f8fafc;border-radius:20px;padding:6px 10px;font-size:.8rem;color:#536178}.pill.ok{color:#08785f;background:#edfbf6;border-color:#c7f1e3}.back{display:block;text-align:center;text-decoration:none;color:#245bd6;font-weight:700;padding:12px}.timer{font-size:.85rem;color:#718096;margin-top:8px}.foot{font-size:.78rem;color:#718096;text-align:center;margin-top:16px}
</style></head><body><header class="top"><div class="wrap" style="padding-top:0;padding-bottom:0"><div class="brand">Pendaftaran pengguna</div><div class="sub">Absensi Otomatis · Fingerprint R558-S</div></div></header><main class="wrap">
<section class="card"><h2>Daftarkan sidik jari baru</h2><p class="muted">Masukkan nama pengguna. Sensor R558-S akan memandu pemindaian dan menyimpan template ke memori internal sensor. Nama dan ID akan dicatat pada MicroSD setelah penyimpanan berhasil.</p>
<label for="name">Nama pengguna</label><input id="name" maxlength="32" placeholder="Contoh: Robert" autocomplete="name"><button id="startButton" onclick="startEnroll()">Mulai pendaftaran</button><button class="danger" id="cancelButton" onclick="cancelEnroll()">Batalkan pendaftaran</button><div class="status" id="enrollResult">Siap. Isi nama pengguna, lalu mulai pendaftaran.</div><div class="timer" id="timer"></div></section>
<section class="card"><h2>Ikuti tiga langkah ini</h2><div class="steps"><div class="step"><div class="num">1</div><div><strong>Tempelkan jari</strong><span>Letakkan bagian tengah sidik jari dengan rata pada sensor hingga pembacaan pertama selesai.</span></div></div><div class="step"><div class="num">2</div><div><strong>Angkat sepenuhnya</strong><span>Jauhkan jari dari sensor saat diminta. Tunggu instruksi berikutnya.</span></div></div><div class="step"><div class="num">3</div><div><strong>Tempelkan jari yang sama</strong><span>Gunakan jari yang sama untuk pemindaian kedua. Jangan matikan ESP32 selama proses berlangsung.</span></div></div></div><div class="devices" id="devices"></div><div class="status" id="message">Menghubungkan ke perangkat…</div><a class="back" href="/">← Kembali ke dashboard</a></section><div class="foot">Jika pendaftaran gagal, ikuti pesan sensor dan ulangi dengan jari yang sama.</div></main>
<script>
async function status(){try{const r=await fetch('/api/status',{cache:'no-store'});if(!r.ok)throw new Error(await r.text());const s=await r.json();document.getElementById('message').textContent=s.message;document.getElementById('devices').innerHTML='';[['Fingerprint',s.fingerprint],['MicroSD',s.sd],['RTC',s.rtc]].forEach(([k,v])=>{const e=document.createElement('span');e.className='pill'+((v==='OK'||v==='SIAP')?' ok':'');e.textContent=k+': '+v;document.getElementById('devices').appendChild(e)});document.getElementById('enrollResult').textContent=s.enrollment;document.getElementById('startButton').disabled=s.enrollBusy;document.getElementById('cancelButton').disabled=!s.enrollBusy;document.getElementById('name').disabled=s.enrollBusy;document.getElementById('timer').textContent=s.enrollBusy?'Pendaftaran aktif untuk ID '+s.enrollId+'. Jangan menutup daya perangkat.':' '}catch(e){document.getElementById('message').textContent='Tidak dapat terhubung: '+e.message}}
async function startEnroll(){const name=document.getElementById('name').value.trim();if(!name){document.getElementById('enrollResult').textContent='Nama pengguna wajib diisi.';return}const b=document.getElementById('startButton');b.disabled=true;b.textContent='Memulai…';try{const r=await fetch('/enroll?name='+encodeURIComponent(name),{cache:'no-store'});const t=await r.text();document.getElementById('enrollResult').textContent=t;if(!r.ok)throw new Error(t);document.getElementById('name').disabled=true}catch(e){document.getElementById('enrollResult').textContent=e.message}finally{b.textContent='Mulai pendaftaran';await status()}}
async function cancelEnroll(){if(!confirm('Batalkan proses pendaftaran yang sedang berjalan?'))return;const b=document.getElementById('cancelButton');b.disabled=true;try{const r=await fetch('/enroll/cancel',{cache:'no-store'});document.getElementById('enrollResult').textContent=await r.text();document.getElementById('name').disabled=false}catch(e){document.getElementById('enrollResult').textContent='Gagal membatalkan: '+e.message}finally{await status()}}
status();setInterval(status,700);
</script></body></html>
)rawliteral";


// ======================== HTTP HELPERS ========================
void handleRoot() { server.send_P(200, "text/html; charset=utf-8", INDEX_HTML); }
void handleRegistrationPage() { server.send_P(200, "text/html; charset=utf-8", REGISTRATION_HTML); }

void handleStatus() {
  String payload = "{";
  payload += "\"fingerprint\":\"" + String(fingerprintReady ? "OK" : "GAGAL") + "\",";
  payload += "\"sd\":\"" + String(sdReady ? "OK" : "GAGAL") + "\",";
  payload += "\"rtc\":\"" + String(rtcReady ? "OK" : "GAGAL") + "\",";
  payload += "\"audio\":\"" + String(i2sReady ? "SIAP" : "GAGAL") + "\",";
  payload += "\"wifi\":\"" + String(configMode ? "AKTIF" : "NONAKTIF") + "\",";
  payload += "\"templates\":" + String(templateCountValue) + ",";
  payload += "\"enrollBusy\":" + String(enrollState == ENROLL_RUNNING ? "true" : "false") + ",";
  payload += "\"enrollId\":" + String(enrollId) + ",";
  payload += "\"mode\":\"" + jsonEscape(modeText()) + "\",";
  payload += "\"time\":\"" + jsonEscape(rtcDateString()) + "\",";
  payload += "\"message\":\"" + jsonEscape(systemMessage) + "\",";
  payload += "\"messageType\":\"" + String(systemMessage.indexOf("berhasil") >= 0 ? "ok" : (systemMessage.indexOf("gagal") >= 0 || systemMessage.indexOf("tidak dikenal") >= 0 ? "bad" : "")) + "\",";
  payload += "\"enrollment\":\"" + jsonEscape(enrollmentText()) + "\"}";
  server.send(200, "application/json; charset=utf-8", payload);
}

void handleWifiSettings() {
  server.send(200, "application/json; charset=utf-8", "{\"ssid\":\"" + jsonEscape(apSSID) + "\"}");
}

void handleWifiSave() {
  String newSsid = server.arg("ssid"); String newPassword = server.arg("password");
  newSsid.trim();
  if (newSsid.length() < 1 || newSsid.length() > 32) { server.send(400, "text/plain; charset=utf-8", "SSID harus 1 sampai 32 karakter."); return; }
  if (newPassword.length() == 0) newPassword = apPassword;
  if (newPassword.length() < 8 || newPassword.length() > 63) { server.send(400, "text/plain; charset=utf-8", "Password Wi-Fi harus 8 sampai 63 karakter."); return; }
  wifiPrefs.begin("absensi-wifi", false);
  wifiPrefs.putString("ssid", newSsid); wifiPrefs.putString("password", newPassword); wifiPrefs.end();
  apSSID = newSsid; apPassword = newPassword;
  server.send(200, "text/plain; charset=utf-8", "Pengaturan Wi-Fi tersimpan. ESP32 mengganti jaringan sekarang.");
  delay(500); server.stop(); WiFi.softAPdisconnect(true); WiFi.mode(WIFI_OFF); delay(250); startConfigWifi();
}

bool nameExistsInCsv(const String &name) {
  if (!sdReady) return false;
  File f = SD.open("/users.csv", FILE_READ); if (!f) return false;
  bool found = false; String target = name; target.toLowerCase();
  while (f.available()) {
    String line = f.readStringUntil('\n'); line.trim();
    if (!line.length() || line.startsWith("id,")) continue;
    int comma = line.indexOf(','); if (comma < 0) continue;
    String n = line.substring(comma + 1); n.toLowerCase();
    if (n == target) { found = true; break; }
  }
  f.close(); return found;
}

void handleStartEnroll() {
  if (!fingerprintReady) { systemMessage = "Pendaftaran gagal: sensor fingerprint tidak siap."; server.send(503, "text/plain; charset=utf-8", systemMessage); return; }
  if (!sdReady) { systemMessage = "Pendaftaran gagal: MicroSD tidak siap."; server.send(503, "text/plain; charset=utf-8", systemMessage); return; }
  if (enrollState != ENROLL_IDLE || fingerOperation == FOP_ENROLL) { systemMessage = "Pendaftaran masih berjalan. Tunggu sampai selesai atau batalkan pendaftaran."; server.send(409, "text/plain; charset=utf-8", systemMessage); return; }
  // Standby uses AutoIdentify continuously. Cancel that job before starting enrollment.
  if (fingerOperation == FOP_IDENTIFY) {
    cancelActiveFingerprintOperation();
    nextIdentifyAt = millis() + 1000;
  } else if (fingerOperation != FOP_NONE) {
    systemMessage = "Sensor sedang menjalankan operasi lain. Tunggu sebentar lalu coba lagi.";
    server.send(409, "text/plain; charset=utf-8", systemMessage);
    return;
  }
  String name = sanitizeName(server.arg("name"));
  if (!name.length()) { server.send(400, "text/plain; charset=utf-8", "Nama pengguna wajib diisi."); return; }
  if (nameExistsInCsv(name)) { server.send(409, "text/plain; charset=utf-8", "Nama tersebut sudah ada di users.csv. Gunakan nama berbeda atau periksa daftar pengguna."); return; }
  uint16_t freshCount = templateCountValue;
  if (readTemplateCount(freshCount)) templateCountValue = freshCount;
  uint16_t id = nextAvailableFingerprintId();
  if (!id || id > FP_CAPACITY) { systemMessage = "Tidak ditemukan slot ID kosong. Periksa kapasitas atau index table sensor."; server.send(507, "text/plain; charset=utf-8", systemMessage); return; }
  beginAutoEnroll(id, name);
  server.send(200, "text/plain; charset=utf-8", systemMessage);
}

void handleCancelEnroll() {
  if (enrollState == ENROLL_RUNNING) {
    cancelActiveFingerprintOperation(); enrollState = ENROLL_IDLE; enrollName = "";
    systemMessage = "Pendaftaran dibatalkan. Tidak ada nama pengguna baru yang ditulis ke users.csv.";
    startRemovalWait(); showFeedback(true, false, false, 1200);
  } else systemMessage = "Tidak ada pendaftaran yang sedang berjalan.";
  server.send(200, "text/plain; charset=utf-8", systemMessage);
}

void handleLinkStoredUser() {
  if (!fingerprintReady) { server.send(503, "text/plain; charset=utf-8", "Sensor fingerprint tidak siap."); return; }
  if (!sdReady) { server.send(503, "text/plain; charset=utf-8", "MicroSD tidak siap."); return; }
  if (enrollState == ENROLL_RUNNING || fingerOperation == FOP_ENROLL) { server.send(409, "text/plain; charset=utf-8", "Tunggu sampai pendaftaran selesai sebelum memetakan template."); return; }
  if (fingerOperation == FOP_IDENTIFY) cancelActiveFingerprintOperation();
  else if (fingerOperation != FOP_NONE) { server.send(409, "text/plain; charset=utf-8", "Sensor sedang menjalankan operasi lain. Coba lagi sebentar."); return; }
  long parsedId = server.arg("id").toInt();
  if (parsedId < 1 || parsedId > FP_CAPACITY) { server.send(400, "text/plain; charset=utf-8", "ID harus berada di antara 1 dan 100."); return; }
  uint16_t id = (uint16_t)parsedId;
  String name = sanitizeName(server.arg("name"));
  if (!name.length()) { server.send(400, "text/plain; charset=utf-8", "Nama pengguna wajib diisi."); return; }
  if (userIdExistsInCsv(id)) { server.send(409, "text/plain; charset=utf-8", "ID tersebut sudah memiliki pemetaan di users.csv."); return; }
  if (nameExistsInCsv(name)) { server.send(409, "text/plain; charset=utf-8", "Nama pengguna sudah digunakan di users.csv."); return; }
  bool known = false;
  bool occupied = templateStoredAtId(id, known);
  if (!known) { server.send(503, "text/plain; charset=utf-8", "Tidak dapat memeriksa slot template sensor. Coba lagi atau periksa komunikasi UART."); return; }
  if (!occupied) { server.send(404, "text/plain; charset=utf-8", "ID tersebut kosong di sensor. Daftarkan sidik jari melalui halaman pendaftaran."); return; }
  if (!saveUser(id, name)) { server.send(500, "text/plain; charset=utf-8", "Template ada di sensor, tetapi gagal menyimpan nama ke users.csv."); return; }
  systemMessage = "Template yang sudah ada berhasil dihubungkan ke " + name + " (ID " + String(id) + ").";
  Serial.println(systemMessage);
  server.send(200, "text/plain; charset=utf-8", systemMessage);
}

void handleRTCSet() {
  if (!rtcReady) { server.send(503, "text/plain; charset=utf-8", "RTC DS1307 tidak terdeteksi. Periksa wiring SDA/SCL dan daya."); return; }
  String value = server.arg("datetime"); int y=0, mo=0, d=0, hh=0, mm=0;
  if (sscanf(value.c_str(), "%d-%d-%dT%d:%d", &y, &mo, &d, &hh, &mm) != 5) { server.send(400, "text/plain; charset=utf-8", "Format tanggal/waktu tidak valid."); return; }
  DateTime dt(y, mo, d, hh, mm, 0);
  if (!dt.isValid()) { server.send(400, "text/plain; charset=utf-8", "Tanggal/waktu tidak valid."); return; }
  rtc.adjust(dt); systemMessage = "RTC berhasil diatur ke " + rtcDateString();
  server.send(200, "text/plain; charset=utf-8", systemMessage);
}

void handleDeleteUser() {
  if (!fingerprintReady) {
    server.send(503, "text/plain; charset=utf-8", "Sensor fingerprint tidak siap. Tidak ada data yang dihapus.");
    return;
  }
  if (!sdReady) {
    server.send(503, "text/plain; charset=utf-8", "MicroSD tidak siap. Tidak ada data yang dihapus.");
    return;
  }
  if (enrollState == ENROLL_RUNNING || fingerOperation == FOP_ENROLL) {
    server.send(409, "text/plain; charset=utf-8", "Batalkan atau tunggu pendaftaran selesai sebelum menghapus pengguna.");
    return;
  }
  if (audioPlaying) {
    server.send(409, "text/plain; charset=utf-8", "Tunggu audio selesai sebelum menghapus pengguna.");
    return;
  }

  long rawId = server.arg("id").toInt();
  if (rawId < 1 || rawId > FP_CAPACITY) {
    server.send(400, "text/plain; charset=utf-8", "ID fingerprint harus antara 1 sampai 100.");
    return;
  }
  uint16_t id = (uint16_t)rawId;

  bool hasMapping = false;
  if (!readUserMappingExists(id, hasMapping)) {
    server.send(500, "text/plain; charset=utf-8", "users.csv tidak dapat dibaca. Tidak ada data yang dihapus.");
    return;
  }

  // Standby normally runs AutoIdentify. Stop it before issuing DeleteChar.
  if (fingerOperation == FOP_IDENTIFY || fingerOperation == FOP_REMOVE_PROBE) {
    cancelActiveFingerprintOperation();
  } else if (fingerOperation != FOP_NONE) {
    server.send(409, "text/plain; charset=utf-8", "Sensor sedang menjalankan operasi lain. Coba lagi sebentar.");
    return;
  }

  bool occupancyKnown = false;
  bool templateExists = templateStoredAtId(id, occupancyKnown);
  if (!occupancyKnown) {
    server.send(503, "text/plain; charset=utf-8", "Tidak dapat memastikan apakah ID berisi template. Tidak ada data yang dihapus.");
    return;
  }
  if (!templateExists && !hasMapping) {
    server.send(404, "text/plain; charset=utf-8", "ID tersebut tidak memiliki template maupun data pengguna.");
    return;
  }

  if (templateExists) {
    // DeleteChar (0x0C): start PageID, then count to delete (0x0001 = one template).
    const uint8_t command[] = {0x0C, (uint8_t)(id >> 8), (uint8_t)id, 0x00, 0x01};
    uint8_t response[32]; uint16_t responseLen = 0;
    if (!fingerprintTransaction(command, sizeof(command), response, sizeof(response), responseLen, 5000)) {
      server.send(504, "text/plain; charset=utf-8", "Sensor tidak memberi respons DeleteChar. Data pengguna belum dihapus dari users.csv; periksa UART lalu coba lagi.");
      return;
    }
    if (responseLen < 1 || response[0] != 0x00) {
      String err = "Sensor menolak penghapusan template ID " + String(id) + ". Kode respons 0x" + String(responseLen ? response[0] : 0xFF, HEX) + ". Data users.csv tidak diubah.";
      server.send(502, "text/plain; charset=utf-8", err);
      return;
    }

    // Refresh count and, where the sensor supports it, confirm the selected ID is now empty.
    uint16_t freshCount = templateCountValue;
    if (readTemplateCount(freshCount)) templateCountValue = freshCount;
    bool afterKnown = false;
    bool stillPresent = templateStoredAtId(id, afterKnown);
    if (afterKnown && stillPresent) {
      server.send(500, "text/plain; charset=utf-8", "Sensor mengakui perintah hapus tetapi ID masih terdeteksi. users.csv tidak diubah.");
      return;
    }
  }

  bool mappingRemoved = false;
  if (hasMapping && !removeUserMappingFromCsv(id, mappingRemoved)) {
    systemMessage = "Template fingerprint ID " + String(id) + " sudah dihapus dari sensor, tetapi users.csv gagal diperbarui. Ulangi hapus ID ini setelah memeriksa MicroSD.";
    server.send(500, "text/plain; charset=utf-8", systemMessage);
    return;
  }

  uint16_t freshCount = templateCountValue;
  if (readTemplateCount(freshCount)) templateCountValue = freshCount;
  systemMessage = "Penghapusan selesai untuk ID " + String(id) + ": " +
                  String(templateExists ? "template fingerprint di sensor" : "template sensor sudah kosong") +
                  " dan " + String(mappingRemoved ? "data pengguna di users.csv sudah dihapus" : "tidak ada baris pengguna pada users.csv") +
                  ". Riwayat absensi tidak dihapus.";
  Serial.println(systemMessage);
  server.send(200, "text/plain; charset=utf-8", systemMessage);
}

void handleUsers() {
  if (!sdReady) { server.send(503, "application/json; charset=utf-8", "[]"); return; }
  String payload = "["; bool first = true;
  File f = SD.open("/users.csv", FILE_READ);
  if (f) {
    while (f.available()) {
      String line = f.readStringUntil('\n'); line.trim();
      if (!line.length() || line.startsWith("id,")) continue;
      int comma = line.indexOf(','); if (comma <= 0) continue;
      String id = line.substring(0, comma), name = line.substring(comma + 1);
      if (!first) payload += ','; first = false;
      payload += "{\"id\":" + String(id.toInt()) + ",\"name\":\"" + jsonEscape(name) + "\"}";
    }
    f.close();
  }
  payload += "]"; server.send(200, "application/json; charset=utf-8", payload);
}

void handleLogs() {
  if (!sdReady) { server.send(503, "application/json; charset=utf-8", "[]"); return; }
  String lines[20]; size_t total = 0;
  File f = SD.open("/attendance.csv", FILE_READ);
  if (f) {
    while (f.available()) {
      String line = f.readStringUntil('\n'); line.trim();
      if (!line.length() || line.startsWith("date,")) continue;
      lines[total % 20] = line; total++;
    }
    f.close();
  }
  size_t count = total < 20 ? total : 20; String payload = "[";
  for (size_t k = 0; k < count; k++) {
    size_t idx = (total - 1 - k) % 20; String line = lines[idx];
    if (k) payload += ',';
    payload += "{\"date\":\"" + jsonEscape(csvField(line, 0)) + "\",";
    payload += "\"time\":\"" + jsonEscape(csvField(line, 1)) + "\",";
    payload += "\"id\":" + String(csvField(line, 2).toInt()) + ",";
    payload += "\"name\":\"" + jsonEscape(csvField(line, 3)) + "\",";
    payload += "\"confidence\":" + String(csvField(line, 4).toInt()) + "}";
  }
  payload += "]"; server.send(200, "application/json; charset=utf-8", payload);
}

void setupWeb() {
  wifiPrefs.begin("absensi-wifi", true);
  apSSID = wifiPrefs.getString("ssid", DEFAULT_AP_SSID);
  apPassword = wifiPrefs.getString("password", DEFAULT_AP_PASSWORD);
  wifiPrefs.end();
  WiFi.mode(WIFI_OFF);
  server.on("/", HTTP_GET, handleRoot);
  server.on("/pendaftaran", HTTP_GET, handleRegistrationPage);
  server.on("/api/status", HTTP_GET, handleStatus);
  server.on("/api/wifi", HTTP_GET, handleWifiSettings);
  server.on("/wifi", HTTP_POST, handleWifiSave);
  server.on("/api/users", HTTP_GET, handleUsers);
  server.on("/api/delete-user", HTTP_POST, handleDeleteUser);
  server.on("/api/logs", HTTP_GET, handleLogs);
  server.on("/api/link-user", HTTP_POST, handleLinkStoredUser);
  server.on("/enroll", HTTP_GET, handleStartEnroll);
  server.on("/enroll/cancel", HTTP_GET, handleCancelEnroll);
  server.on("/rtc", HTTP_GET, handleRTCSet);
  server.onNotFound([]() { server.send(404, "text/plain; charset=utf-8", "404 - Endpoint tidak ditemukan"); });
  Serial.println("Web routes siap. Wi-Fi OFF sampai tombol GPIO14 ditahan 3 detik.");
}

