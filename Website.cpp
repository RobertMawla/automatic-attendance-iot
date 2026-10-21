#include "App.h"
#include "LogoData.h"

// ======================== Halaman website (HTML/CSS/JavaScript) ========================
// ======================== WEB UI ========================
const char INDEX_HTML[] PROGMEM =
R"rawliteral(
<!doctype html>
<html lang="id">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta name="theme-color" content="#173f2d">
  <title>Absensi IoT — Dashboard ESP32</title>
  <style>
:root{--forest:#173f2d;--forest2:#28583c;--moss:#67865b;--leaf:#8ba778;--sage:#dce6d2;--sage2:#eef2e7;--cream:#f5f3e9;--paper:#fffef9;--ink:#21372a;--muted:#7b8779;--line:#e2e6da;--sand:#eee7d3;--rust:#a34335;--shadow:0 12px 34px rgba(28,59,38,.055);font-family:'DM Sans',Arial,sans-serif;color:var(--ink);background:var(--cream)}
*{box-sizing:border-box}html{scroll-behavior:smooth;scroll-padding-top:24px}body{margin:0;min-width:320px;background:var(--cream);font-size:14px;line-height:1.55}a{color:inherit}button,input{font:inherit}button{cursor:pointer}.app-shell{min-height:100vh;display:grid;grid-template-columns:252px minmax(0,1fr)}
.sidebar{position:sticky;top:0;height:100vh;background:var(--forest);color:#f8f6eb;padding:27px 17px 18px;display:flex;flex-direction:column;overflow-y:auto;z-index:10}.brand{display:flex;align-items:center;gap:11px;text-decoration:none;min-width:0}.sidebar .brand{padding:0 6px 27px;border-bottom:1px solid #ffffff20}.brand-logo{width:45px;height:45px;border-radius:14px;background:#fff;display:grid;place-items:center;overflow:hidden;flex:none}.brand-logo img{width:100%;height:100%;object-fit:contain;padding:3px}.brand-copy{min-width:0}.brand-copy strong{font:800 .84rem 'Manrope',sans-serif;letter-spacing:.02em;display:block;white-space:nowrap}.brand-copy small{display:block;color:#b8ceb5;font-size:.62rem;letter-spacing:.16em;margin-top:4px}.nav-label{font-size:.64rem;font-weight:700;letter-spacing:.16em;color:#92ae95;padding:25px 13px 9px}.side-nav{display:grid;gap:5px}.nav-link{display:flex;align-items:center;gap:11px;padding:11px 12px;color:#cadac8;text-decoration:none;border-radius:11px;font-size:.81rem;font-weight:600;transition:background .2s,color .2s}.nav-link:hover,.nav-link.active{background:#ffffff15;color:#fff}.nav-link.active{box-shadow:inset 3px 0 #b9d199}.nav-symbol{width:22px;text-align:center;font-size:1.08rem;color:#a9c49b}.sidebar-bottom{margin-top:auto}.local-mark{display:flex;align-items:center;gap:8px;color:#e1ebd7;font-size:.73rem;font-weight:700;background:#ffffff11;border:1px solid #ffffff12;border-radius:10px;padding:10px 11px}.local-pulse{width:7px;height:7px;background:#b9d19b;border-radius:50%;box-shadow:0 0 0 4px #b9d19b22}.sidebar-bottom p{color:#9eb6a0;font-size:.69rem;line-height:1.7;margin:10px 9px 0}
.workspace{min-width:0}.topbar{height:76px;display:flex;align-items:center;justify-content:space-between;gap:15px;padding:0 clamp(18px,3.1vw,45px);background:rgba(250,249,242,.86);border-bottom:1px solid var(--line)}.eyebrow,.section-overline{font-size:.64rem;font-weight:800;letter-spacing:.15em;color:#82977a}.topbar-title{font:800 .98rem 'Manrope',sans-serif;color:var(--forest);margin-top:3px}.topbar-right{display:flex;align-items:center;gap:13px}.demo-badge{display:flex;align-items:center;gap:7px;background:#eef3e7;border:1px solid #dbe5d2;color:#496848;border-radius:999px;padding:8px 12px;font-size:.66rem;font-weight:800;letter-spacing:.04em}.badge-dot{width:7px;height:7px;border-radius:50%;background:#7d9c6b}.avatar{width:34px;height:34px;display:grid;place-items:center;background:#e3ead8;border-radius:50%;color:var(--forest);font-weight:800;font-size:.8rem}.main-content{width:100%;max-width:1580px;padding:25px clamp(18px,3.1vw,45px) 36px;margin:0 auto}
.hero{position:relative;isolation:isolate;overflow:hidden;min-height:315px;border-radius:23px;background:linear-gradient(105deg,#173f2d 0%,#25563a 52%,#52744b 100%);color:#fff;padding:34px 36px 52px;box-shadow:0 17px 38px #173f2d18}.hero:before{content:"";position:absolute;z-index:-1;right:-7%;top:-55%;width:390px;height:390px;border-radius:50%;border:1px solid #ffffff15;box-shadow:0 0 0 27px #ffffff08,0 0 0 56px #ffffff05}.hero-copy{position:relative;z-index:2;max-width:610px}.hero-kicker{display:flex;align-items:center;gap:9px;color:#d9e6ca;font-size:.65rem;font-weight:800;letter-spacing:.13em}.kicker-leaf{display:grid;place-items:center;width:22px;height:22px;border-radius:8px;background:#ffffff17;color:#e2edc9;font-size:.95rem}.hero h1,.registration-hero h1{font:800 clamp(2.25rem,3.5vw,3.25rem)/1.08 'Manrope',sans-serif;letter-spacing:-.055em;margin:19px 0 12px;max-width:600px}.hero h1 em{font-style:normal;color:#c7d8a6}.hero p{font-size:.87rem;line-height:1.8;color:#d9e5d5;max-width:500px;margin:0}.hero-actions{display:flex;gap:10px;flex-wrap:wrap;margin-top:22px}.btn{display:inline-flex;align-items:center;justify-content:center;gap:9px;min-height:42px;border-radius:11px;padding:11px 15px;border:1px solid transparent;text-decoration:none;font-weight:750;font-size:.76rem;transition:transform .18s,background .18s,border-color .18s;white-space:normal}.btn:hover{transform:translateY(-1px)}.btn-cream{background:#f4f0df;color:var(--forest)}.btn-cream:hover{background:#fff9e8}.btn-outline{background:#ffffff0b;color:#fff;border-color:#ffffff49}.btn-outline:hover{background:#ffffff17}.btn-primary{background:var(--forest);color:#fff}.btn-primary:hover{background:#28583c}.btn-secondary{background:#f5f5ec;color:#476247;border-color:#e0e5d7}.btn-secondary:hover{background:#eaf0e1}.btn-danger{background:#fff0eb;color:var(--rust);border-color:#f0d8d0}.btn-danger:hover{background:#ffe3db}.btn-full{width:100%;margin-top:12px}.hero-art{position:absolute;z-index:1;right:0;top:0;width:44%;height:100%;pointer-events:none;overflow:hidden}.art-sun{position:absolute;right:23%;top:15%;width:135px;height:135px;border-radius:50%;background:#e5e9bd18}.art-hill{position:absolute;bottom:-7%;right:-3%;width:94%;height:45%;border-radius:70% 40% 0 0;transform:rotate(-10deg)}.hill-back{background:#b7c99828;right:-14%;bottom:7%;height:48%;transform:rotate(13deg)}.hill-front{background:#a5c08135}.art-plant{position:absolute;right:9%;bottom:-5%;width:280px;height:280px;filter:drop-shadow(0 8px 20px #102b1b30)}.art-grain{position:absolute;inset:0;background:radial-gradient(#ffffff18 .6px,transparent .6px);background-size:7px 7px;opacity:.18;mask-image:linear-gradient(90deg,transparent,black)}.hero-bottom{position:absolute;bottom:0;left:36px;right:36px;height:35px;border-top:1px solid #ffffff24;display:flex;align-items:center;justify-content:space-between;gap:10px;color:#abc5a8;font-size:.56rem;font-weight:700;letter-spacing:.12em}.hero-bottom span:last-child{text-align:right}
.section-block{margin-top:28px}.section-heading{display:flex;align-items:end;justify-content:space-between;gap:14px;margin-bottom:15px}.section-heading h2,.surface-heading h2{font:800 1.26rem 'Manrope',sans-serif;letter-spacing:-.04em;color:var(--forest);margin:5px 0 5px}.section-heading p,.surface-heading p{font-size:.78rem;color:var(--muted);margin:0;line-height:1.65}.date-pill{border:1px solid var(--line);background:#fcfbf5;color:#7c8978;padding:7px 11px;border-radius:999px;font-size:.69rem;white-space:nowrap}.stats-grid{display:grid;grid-template-columns:repeat(4,minmax(0,1fr));gap:12px}.stat-card{min-width:0;position:relative;overflow:hidden;background:var(--paper);border:1px solid var(--line);border-radius:17px;padding:17px 17px 19px;min-height:156px;box-shadow:var(--shadow)}.stat-card-top{display:flex;align-items:center;justify-content:space-between;gap:8px}.stat-icon{width:34px;height:34px;display:grid;place-items:center;border-radius:11px;font-size:1rem}.stat-icon.green{background:#e5eddd;color:#3f6844}.stat-icon.sand{background:#f0ead7;color:#8a7445}.stat-icon.sage{background:#e3ece5;color:#557b66}.stat-icon.cream{background:#f0eee3;color:#6d795f}.status-mini{font-size:.54rem;letter-spacing:.08em;font-weight:800}.status-mini.demo{color:#84937e}.stat-label{font-size:.72rem;font-weight:650;color:#7b8779;margin-top:14px}.stat-number{font:800 1.55rem 'Manrope',sans-serif;letter-spacing:-.045em;color:var(--forest);margin-top:3px;overflow-wrap:anywhere}.stat-number small{font:700 .82rem 'DM Sans',sans-serif;color:#8b9684;letter-spacing:0}.status-check{font-size:.75rem;color:#65946a}.stat-foot{font-size:.66rem;color:#9aa293;margin-top:5px}.time-number{font-size:1.65rem}.stat-accent{position:absolute;bottom:-28px;right:-20px;width:66px;height:66px;border-radius:50%;border:11px solid #e6eedf}.accent-sand{border-color:#f1ead9}.accent-sage{border-color:#e7eee6}.accent-cream{border-color:#eeece1}
.content-grid{display:grid;grid-template-columns:minmax(0,1.2fr) minmax(280px,.8fr);gap:14px;align-items:stretch}.surface-card{min-width:0;background:var(--paper);border:1px solid var(--line);border-radius:19px;padding:22px;box-shadow:var(--shadow)}.surface-heading{display:flex;align-items:flex-start;justify-content:space-between;gap:14px;margin-bottom:19px}.surface-heading h2{font-size:1.05rem;margin-top:5px}.surface-heading p{max-width:620px;font-size:.75rem}.heading-icon{width:38px;height:38px;border-radius:12px;background:#e7efdf;display:grid;place-items:center;color:#436746;font-size:1.08rem;flex:none}.sand-icon{background:#f0ead9;color:#8a7b52}.component-list{display:grid;gap:0}.component-row{display:flex;align-items:center;gap:10px;padding:11px 0;border-bottom:1px solid #edf0e8}.component-row:last-child{border-bottom:0}.component-icon{display:grid;place-items:center;width:31px;height:31px;border-radius:10px;background:#f0f3e9;color:#5d7956;flex:none}.component-name{flex:1;font-size:.77rem;font-weight:700;color:#465b45}.pill{display:inline-flex;align-items:center;border-radius:999px;padding:5px 8px;font-size:.62rem;font-weight:750;white-space:nowrap}.pill-demo{background:#edf2e6;color:#718766;border:1px solid #e0e8d5}.message-box{display:flex;align-items:flex-start;gap:10px;background:#f4f5eb;border:1px solid #e6e9dc;border-radius:12px;padding:12px;margin-top:14px}.message-mark{display:grid;place-items:center;width:21px;height:21px;border-radius:50%;background:#e0e8d5;color:#5d7956;font:800 .75rem Georgia;flex:none}.message-box strong{font-size:.74rem;color:#50684d}.message-box p{font-size:.7rem;line-height:1.65;color:#84907e;margin:3px 0 0}.panel-footer-line{display:flex;align-items:center;justify-content:space-between;gap:10px;border-top:1px solid #e8ece1;padding-top:13px;margin-top:14px}.muted-label{color:#909b8b;font-size:.68rem}.panel-footer-line strong{font-size:.67rem;color:#587650}.small-green-dot{width:6px;height:6px;display:inline-block;background:#7eaa72;border-radius:50%;margin-right:5px}.field-label{display:block;color:#526b4d;font-size:.74rem;font-weight:750;margin-bottom:7px}.field-label span{font-size:.66rem;font-weight:600;color:#9ca695;margin-left:3px}.input{display:block;width:100%;min-width:0;border:1px solid #dfe5d8;border-radius:10px;background:#fffef9;color:var(--ink);padding:12px 13px;font-size:.78rem;outline:none;transition:border .15s,box-shadow .15s}.input:focus{border-color:#88a477;box-shadow:0 0 0 3px #9cb88b2b}.input::placeholder{color:#a0a99a}.helper-text{color:#929b8b;font-size:.68rem;line-height:1.7;margin:11px 0 0}.time-card{background:linear-gradient(150deg,#fffef9,#f8f8ef)}.time-card .surface-heading{margin-bottom:23px}
.mapping-form{display:grid;grid-template-columns:minmax(110px,.36fr) minmax(190px,1fr) auto;gap:12px;align-items:end}.form-field{min-width:0}.map-button{white-space:nowrap}.inline-note{display:flex;align-items:center;gap:8px;margin-top:17px;padding-top:13px;border-top:1px solid #edf0e8;color:#8a9684;font-size:.69rem}.inline-note span{color:#7e9b6b}.count-box{min-width:66px;background:#edf2e5;border:1px solid #dfe8d4;border-radius:12px;padding:7px 10px;text-align:center;color:#607958}.count-box strong{display:block;font:800 1.05rem 'Manrope',sans-serif}.count-box span{font-size:.59rem}.table-toolbar{display:flex;align-items:center;justify-content:space-between;gap:12px;margin:-2px 0 13px}.search-box{display:flex;align-items:center;gap:8px;border:1px solid #e2e7db;border-radius:10px;background:#fffefb;padding:0 10px;max-width:310px;flex:1;color:#84937d}.search-box input{border:0;background:transparent;outline:0;min-width:0;width:100%;padding:10px 0;font-size:.75rem;color:var(--ink)}.search-box input:focus{box-shadow:none}.table-wrap{width:100%;overflow:auto;border:1px solid #e6eade;border-radius:12px;background:#fffefa}table{border-collapse:collapse;width:100%;font-size:.75rem}th,td{text-align:left;padding:13px 13px;border-bottom:1px solid #eef0e8;white-space:nowrap}th{background:#f4f5eb;color:#86917e;text-transform:uppercase;letter-spacing:.1em;font-size:.59rem;font-weight:800}tbody tr:last-child td{border-bottom:0}tbody tr:hover{background:#fafaf3}td{color:#586b55}.id-cell{display:inline-flex;align-items:center;justify-content:center;min-width:30px;padding:4px 7px;background:#edf2e6;color:#54714c;border-radius:7px;font-weight:800;font-size:.67rem}.person-cell{display:flex;align-items:center;gap:9px}.person-avatar{display:grid;place-items:center;width:29px;height:29px;background:#e3eadd;color:#55704f;border-radius:9px;font-weight:800;font-size:.68rem;flex:none}.person-name{font-weight:750;color:#3b533a}.person-sub{color:#9ba494;font-size:.62rem;margin-top:2px}.status-cell{color:#63855c;font-size:.68rem;font-weight:750}.align-right{text-align:right}.table-delete{border:1px solid #ecd9d1;background:#fff3ee;color:#a34b3f;border-radius:8px;padding:6px 9px;font-size:.66rem;font-weight:750}.table-delete:hover{background:#ffe4dc}.table-bottom{display:flex;align-items:center;justify-content:space-between;gap:10px;padding-top:12px;color:#9aa393;font-size:.63rem}.about-card{background:#edf1e5;position:relative;overflow:hidden}.about-leaf{font-size:1.8rem;color:#98ae7e;margin-bottom:9px}.about-card h2{font:800 1.12rem 'Manrope',sans-serif;letter-spacing:-.04em;margin:7px 0 9px;color:var(--forest);max-width:290px}.about-card p{font-size:.75rem;color:#71816b;line-height:1.8;margin:0;max-width:520px}.about-tags{display:flex;gap:7px;flex-wrap:wrap;margin-top:17px}.about-tags span{font-size:.62rem;font-weight:750;color:#58764f;background:#fbfcf5;border:1px solid #dae4d0;border-radius:7px;padding:5px 8px}.page-footer{display:flex;justify-content:space-between;gap:12px;flex-wrap:wrap;margin-top:26px;padding:16px 2px 0;border-top:1px solid #e0e5d9;color:#919b8b;font-size:.65rem}.page-footer strong{color:#58714f;font-size:.65rem;letter-spacing:.04em}.page-footer i{font-style:normal;color:#aabd93}.footer-leaf{color:#8ba876;margin-left:5px}.toast{position:fixed;z-index:99;right:22px;bottom:22px;max-width:min(420px,calc(100vw - 32px));padding:13px 16px;border-radius:12px;background:#1e4932;color:#fff;box-shadow:0 12px 35px #142c1c33;font-size:.78rem;line-height:1.55;opacity:0;transform:translateY(8px);pointer-events:none;transition:opacity .2s,transform .2s}.toast.show{opacity:1;transform:translateY(0)}
/* Registration prototype */
.registration-page{background:var(--cream)}.registration-header{height:77px;display:flex;align-items:center;justify-content:space-between;padding:0 clamp(17px,5vw,75px);background:var(--forest);color:#fff}.registration-header .brand-copy small{color:#bed0b5}.back-link{font-size:.75rem;color:#e6eddc;text-decoration:none;border:1px solid #ffffff42;padding:9px 12px;border-radius:10px}.back-link:hover{background:#ffffff13}.registration-hero{position:relative;overflow:hidden;background:linear-gradient(110deg,#1a442f,#426c42);padding:37px clamp(18px,7vw,100px) 42px;color:#fff}.reg-hero-copy{position:relative;z-index:2;max-width:760px}.registration-hero h1{margin:14px 0 10px;font-size:clamp(2.1rem,4vw,3.1rem)}.registration-hero p{max-width:630px;color:#d7e5cf;font-size:.85rem;line-height:1.8;margin:0}.reg-hero-leaf{position:absolute;right:10%;top:-62px;font:23rem/1 Georgia;color:#d0dfa519;transform:rotate(-20deg)}.registration-content{max-width:1240px;margin:auto;padding:27px 18px 45px}.registration-grid{display:grid;grid-template-columns:minmax(0,.95fr) minmax(0,1.05fr);gap:16px;align-items:start}.registration-form-card,.scan-steps-card{padding:24px}.registration-form-card form{margin-top:20px}.registration-form-card .field-label{margin-bottom:8px}.registration-form-card .btn-full{margin-top:11px}.enroll-result{display:flex;gap:10px;margin-top:16px;padding:13px;background:#f3f5e9;border:1px solid #e3e8d8;border-radius:12px}.result-icon{width:24px;height:24px;border-radius:50%;display:grid;place-items:center;background:#e0ead5;color:#587850;font-weight:800;flex:none}.enroll-result strong{font-size:.75rem;color:#4d6948}.enroll-result p{font-size:.7rem;color:#83907e;line-height:1.65;margin:3px 0 0}.scan-steps{display:grid;gap:10px}.scan-step{display:grid;grid-template-columns:35px minmax(0,1fr) auto;align-items:start;gap:11px;padding:14px 12px;border-radius:12px;background:#fafaf3;border:1px solid #e9ecdf}.step-number{width:32px;height:32px;border-radius:10px;display:grid;place-items:center;background:#e4ecd9;color:#55754d;font-size:.68rem;font-weight:800}.scan-step strong{font-size:.76rem;color:#496344}.scan-step p{font-size:.68rem;color:#84907e;line-height:1.65;margin:4px 0 0}.step-state{border-radius:999px;background:#eeefe6;color:#929988;padding:5px 7px;font-size:.56rem;white-space:nowrap}.step-state.active{background:#dfead3;color:#527747}.step-state.done{background:#e4efe1;color:#3c7548}.mock-device{display:flex;align-items:center;gap:10px;padding:13px;margin-top:15px;border:1px dashed #dce3d4;border-radius:13px}.mock-device-icon{width:36px;height:36px;background:#edf1e6;border-radius:11px;display:grid;place-items:center;color:#6a875d;font-size:1.1rem}.mock-device>div:nth-child(2){flex:1}.mock-device strong,.mock-device span{display:block}.mock-device strong{font-size:.73rem;color:#4b6346}.mock-device>div:nth-child(2) span{font-size:.64rem;color:#929a89;margin-top:3px}.device-offline{font-size:.61rem;color:#a07b63;white-space:nowrap}.device-offline i{width:6px;height:6px;border-radius:50%;background:#c5a083;display:inline-block;margin-right:4px}
@media(max-width:1200px){.app-shell{grid-template-columns:220px minmax(0,1fr)}.stats-grid{grid-template-columns:repeat(2,minmax(0,1fr))}.hero-art{width:38%;opacity:.82}.mapping-form{grid-template-columns:minmax(100px,.4fr) minmax(170px,1fr)}.map-button{grid-column:1/-1;justify-self:start}.map-button{min-width:180px}}
@media(max-width:900px){.app-shell{grid-template-columns:1fr}.sidebar{position:relative;height:auto;padding:14px 18px 12px;overflow:visible}.sidebar .brand{padding:0 2px 12px;border-bottom:0}.brand-logo{width:39px;height:39px;border-radius:12px}.nav-label,.sidebar-bottom{display:none}.side-nav{display:flex;overflow-x:auto;gap:4px;padding-bottom:2px}.nav-link{flex:0 0 auto;padding:9px 10px;font-size:.73rem}.nav-symbol{width:auto}.topbar{height:66px}.hero{min-height:300px}.content-grid{grid-template-columns:1fr}.registration-grid{grid-template-columns:1fr}}
@media(max-width:580px){.topbar{padding:0 14px}.topbar-title{font-size:.86rem}.eyebrow{font-size:.57rem}.topbar-right{gap:7px}.demo-badge{padding:7px 9px;font-size:.56rem}.avatar{width:30px;height:30px}.main-content{padding:16px 12px 28px}.hero{padding:25px 19px 51px;min-height:325px;border-radius:18px}.hero-copy{max-width:100%}.hero h1{font-size:2.08rem}.hero p{font-size:.79rem;max-width:390px}.hero-art{width:75%;right:-10%;opacity:.34}.hero-actions{display:grid;grid-template-columns:1fr;max-width:260px}.hero-actions .btn{width:100%}.hero-bottom{left:19px;right:19px;font-size:.49rem}.hero-bottom span:last-child{display:none}.section-block{margin-top:23px}.section-heading{align-items:flex-start}.section-heading h2{font-size:1.15rem}.section-heading p{font-size:.72rem}.date-pill{font-size:.6rem}.stats-grid{gap:8px}.stat-card{padding:13px;min-height:146px;border-radius:14px}.stat-icon{width:30px;height:30px}.status-mini{font-size:.46rem}.stat-label{font-size:.65rem;margin-top:11px}.stat-number{font-size:1.25rem}.stat-foot{font-size:.6rem}.time-number{font-size:1.4rem}.surface-card{padding:16px;border-radius:16px}.surface-heading h2{font-size:.98rem}.surface-heading p{font-size:.69rem}.heading-icon{width:33px;height:33px}.component-row{gap:7px}.component-name{font-size:.68rem}.pill{font-size:.56rem;padding:4px 6px}.mapping-form{grid-template-columns:1fr;gap:11px}.map-button{grid-column:auto;width:100%}.table-toolbar{align-items:stretch;flex-direction:column}.search-box{max-width:none}.table-toolbar .btn{align-self:flex-start}.table-bottom{font-size:.58rem}.page-footer{font-size:.6rem}.registration-header{height:66px;padding:0 13px;gap:10px}.registration-header .brand-copy strong{font-size:.7rem}.registration-header .brand-copy small{font-size:.53rem}.back-link{font-size:.65rem;padding:8px}.registration-hero{padding:28px 17px 32px}.registration-hero h1{font-size:2.15rem}.registration-hero p{font-size:.78rem}.reg-hero-leaf{right:-5%;opacity:.6}.registration-content{padding:15px 12px 30px}.registration-form-card,.scan-steps-card{padding:16px}.scan-step{grid-template-columns:31px minmax(0,1fr);gap:8px}.step-state{grid-column:2;justify-self:start}.mock-device{flex-wrap:wrap}.device-offline{margin-left:46px}}
@media(prefers-reduced-motion:reduce){html{scroll-behavior:auto}*,*::before,*::after{transition:none!important;animation:none!important}}

/* ===== Dashboard redesign: clean attendance app with a subtle nature palette ===== */
.dashboard-page{
  --forest:#214d35;--forest2:#326b45;--moss:#73956a;--leaf:#a9c78b;--sage:#e5eddf;--sage2:#f2f6ee;--cream:#f5f7f2;--paper:#ffffff;--ink:#24372a;--muted:#829084;--line:#e5ebe2;--sand:#f0f2e9;--rust:#a34335;--shadow:0 8px 26px rgba(28,59,38,.045);
  background:#f5f7f3;color:var(--ink);font-family:Inter,"Segoe UI",Arial,sans-serif
}
.dashboard-page body{background:#f5f7f3}
.dashboard-page .app-shell{grid-template-columns:232px minmax(0,1fr);gap:0}
.dashboard-page .sidebar{background:#eef3e9;color:#284331;border-right:1px solid #e0e8dc;padding:24px 15px 18px}
.dashboard-page .sidebar .brand{padding:0 6px 23px;border-bottom:1px solid #dce6d7}
.dashboard-page .brand-logo{width:42px;height:42px;border-radius:12px;background:#fff;border:1px solid #e2e9dd}
.dashboard-page .brand-copy strong{font-family:Inter,"Segoe UI",Arial,sans-serif;font-size:.82rem;letter-spacing:.035em;color:#234731}
.dashboard-page .brand-copy small{font-size:.58rem;letter-spacing:.12em;color:#7b9276}
.dashboard-page .nav-label{font-size:.6rem;letter-spacing:.13em;color:#90a38a;padding:23px 13px 9px}
.dashboard-page .side-nav{gap:4px}
.dashboard-page .nav-link{color:#627866;border-radius:9px;font-size:.78rem;padding:11px 12px;font-weight:650;transition:background .18s,color .18s}
.dashboard-page .nav-link:hover{background:#e2ebdd;color:#315b3b}
.dashboard-page .nav-link.active{background:#dce9d6;color:#285337;box-shadow:inset 3px 0 #56875a}
.dashboard-page .nav-symbol{font-size:1rem;color:#7b9a70;width:20px}
.dashboard-page .sidebar-device{margin:30px 3px 18px;padding:13px 12px 12px;border:1px solid #dae5d5;background:linear-gradient(145deg,#f9fbf6,#e8f0e3);border-radius:13px}
.dashboard-page .device-top{display:flex;align-items:center;gap:7px;color:#416448;font-size:.65rem;font-weight:800;letter-spacing:.05em}
.dashboard-page .device-led{width:7px;height:7px;background:#d0a76b;border-radius:50%;box-shadow:0 0 0 4px #d0a76b20}
.dashboard-page .device-state{margin-left:auto;font-size:.53rem;letter-spacing:.08em;color:#81927b}
.dashboard-page .device-name{margin-top:13px;font-size:.77rem;font-weight:800;color:#2e4d34}
.dashboard-page .device-caption{margin-top:2px;font-size:.63rem;color:#879787}
.dashboard-page .device-line{height:4px;background:#dce7d7;border-radius:20px;margin:12px 0 9px;overflow:hidden}
.dashboard-page .device-line span{display:block;width:39%;height:100%;background:#88a77b;border-radius:20px}
.dashboard-page .device-foot{display:flex;justify-content:space-between;gap:7px;color:#8a9888;font-size:.54rem}
.dashboard-page .sidebar-bottom{margin-top:auto}
.dashboard-page .local-mark{display:flex;align-items:center;gap:7px;color:#486849;font-size:.66rem;font-weight:750;background:#e0ea)rawliteral"
R"rawliteral(db;border:1px solid #d7e4d1;border-radius:9px;padding:9px 10px}
.dashboard-page .local-pulse{width:7px;height:7px;background:#8ba878;border-radius:50%;box-shadow:0 0 0 4px #8ba87822}
.dashboard-page .sidebar-bottom p{color:#96a395;font-size:.63rem;margin:8px 9px 0;line-height:1.55}
.dashboard-page .workspace{min-width:0}
.dashboard-page .topbar{height:74px;padding:0 clamp(20px,3vw,42px);background:#fff;border-bottom:1px solid #e8ede5}
.dashboard-page .eyebrow,.dashboard-page .section-overline{font-size:.6rem;font-weight:800;letter-spacing:.14em;color:#8b9c87}
.dashboard-page .topbar-title{font:750 1.02rem/1.25 Inter,"Segoe UI",Arial,sans-serif;color:#234731;margin-top:4px;letter-spacing:-.025em}
.dashboard-page .topbar-right{gap:12px}
.dashboard-page .connection-pill{display:flex;align-items:center;gap:7px;border:1px solid #e1e9dc;background:#f5f8f1;color:#6a8266;border-radius:8px;padding:8px 10px;font-size:.64rem;font-weight:750}
.dashboard-page .badge-dot{width:6px;height:6px;background:#a4b98b;border-radius:50%}
.dashboard-page .avatar{width:33px;height:33px;border-radius:10px;background:#dfead8;color:#335d3d;font-size:.72rem}
.dashboard-page .main-content{max-width:1640px;padding:25px clamp(20px,3vw,42px) 34px}
.dashboard-page .hero{min-height:246px;border-radius:17px;padding:29px 31px 43px;background:linear-gradient(112deg,#234e35 0%,#2c633e 65%,#427649 100%);box-shadow:0 12px 28px rgba(28,68,40,.11)}
.dashboard-page .hero:before{content:"";position:absolute;z-index:-1;right:-90px;top:-230px;width:470px;height:470px;border:1px solid #ffffff1e;border-radius:50%;box-shadow:0 0 0 35px #ffffff08,0 0 0 75px #ffffff06}
.dashboard-page .hero-copy{max-width:540px}
.dashboard-page .hero-kicker{gap:8px;font-size:.58rem;letter-spacing:.15em;color:#d6e5cf}
.dashboard-page .kicker-leaf{width:20px;height:20px;border-radius:6px;background:#ffffff15;font-size:.82rem}
.dashboard-page .hero h1{font:750 clamp(2rem,3.1vw,2.8rem)/1.08 Inter,"Segoe UI",Arial,sans-serif;letter-spacing:-.06em;margin:15px 0 10px;max-width:510px}
.dashboard-page .hero h1 em{font-style:normal;color:#c6dca8}
.dashboard-page .hero p{font-size:.8rem;line-height:1.65;color:#dbe8d6;max-width:440px;margin:0}
.dashboard-page .hero-actions{gap:9px;margin-top:18px}
.dashboard-page .btn{min-height:38px;border-radius:9px;padding:9px 13px;font-size:.7rem;font-weight:750;transition:transform .16s,background .16s}
.dashboard-page .btn-cream{background:#f4f6e9;color:#2b5035}
.dashboard-page .btn-cream:hover{background:#fff}
.dashboard-page .btn-outline{background:#ffffff0b;color:#f5f8f0;border-color:#ffffff40}
.dashboard-page .btn-outline:hover{background:#ffffff19}
.dashboard-page .btn-primary{background:#2c5b39;color:#fff;border-color:#2c5b39}
.dashboard-page .btn-primary:hover{background:#3c754a}
.dashboard-page .btn-secondary{background:#f7f9f4;color:#567153;border-color:#e0e8dc}
.dashboard-page .btn-secondary:hover{background:#edf4e8}
.dashboard-page .btn-danger{background:#fff0eb;color:var(--rust);border-color:#f0d8d0}
.dashboard-page .btn-full{width:100%;margin-top:11px}
.dashboard-page .hero-botanical{position:absolute;inset:0 0 0 auto;width:43%;pointer-events:none;overflow:hidden;opacity:.95}
.dashboard-page .botanical-orb{position:absolute;width:195px;height:195px;right:20%;top:20px;border-radius:50%;background:#c0d7a018;border:1px solid #cbd9b326}
.dashboard-page .botanical-ring{position:absolute;width:285px;height:285px;right:7%;top:-25px;border:1px solid #ffffff18;border-radius:50%;box-shadow:0 0 0 23px #ffffff05}
.dashboard-page .botanical-stem{position:absolute;height:255px;width:2px;background:#d7e6c178;right:38%;bottom:-37px;transform:rotate(23deg);border-radius:5px}
.dashboard-page .hero-botanical .leaf{position:absolute;display:block;width:86px;height:42px;background:linear-gradient(120deg,#c5d99a,#719a69);border-radius:95% 4% 90% 5%;opacity:.7;transform-origin:right bottom;box-shadow:inset 0 0 0 1px #e2e9c32a}
.dashboard-page .hero-botanical .leaf-one{right:38%;top:63px;transform:rotate(-25deg)}
.dashboard-page .hero-botanical .leaf-two{right:17%;top:108px;transform:rotate(42deg) scale(.85);background:linear-gradient(120deg,#a9cb8a,#648b58)}
.dashboard-page .hero-botanical .leaf-three{right:37%;top:150px;transform:rotate(14deg) scale(1.05);background:linear-gradient(120deg,#9cbe7d,#5c8755)}
.dashboard-page .hero-botanical .leaf-four{right:17%;top:194px;transform:rotate(53deg) scale(.75);background:linear-gradient(120deg,#d3e1a9,#7ca16a)}
.dashboard-page .hero-bottom{left:31px;right:31px;height:30px;border-top:1px solid #ffffff23;color:#c2d7bd;font-size:.52rem;letter-spacing:.12em}
.dashboard-page .hero-bottom span:last-child{letter-spacing:.03em;text-transform:none;font-size:.62rem}
.dashboard-page .metric-grid{display:grid;grid-template-columns:repeat(4,minmax(0,1fr));gap:13px;margin-top:19px}
.dashboard-page .metric-card{min-width:0;position:relative;overflow:hidden;background:#fff;border:1px solid #e5ebe2;border-radius:14px;padding:15px 16px 14px;min-height:143px;box-shadow:0 4px 14px #183a2005}
.dashboard-page .metric-card:after{content:"";position:absolute;right:-27px;bottom:-39px;width:87px;height:87px;border-radius:50%;border:12px solid #eff4eb}
.dashboard-page .metric-featured{background:#fbfdf9}
.dashboard-page .metric-featured:before{content:"";position:absolute;top:0;left:0;right:0;height:3px;background:#719b68}
.dashboard-page .metric-top{display:flex;align-items:center;justify-content:space-between;gap:8px}
.dashboard-page .metric-icon{width:32px;height:32px;border-radius:9px;background:#e4eedf;color:#4b7549;display:grid;place-items:center;font-size:1rem}
.dashboard-page .metric-icon.icon-light{background:#f0f4ed;color:#75916c}
.dashboard-page .metric-tag{font-size:.5rem;letter-spacing:.1em;color:#9aaa96;font-weight:850}
.dashboard-page .metric-label{margin-top:13px;font-size:.67rem;font-weight:650;color:#78897a}
.dashboard-page .metric-value{font:750 1.38rem/1.2 Inter,"Segoe UI",Arial,sans-serif;letter-spacing:-.045em;color:#284d32;margin-top:3px;overflow-wrap:anywhere}
.dashboard-page .metric-value small{font:650 .74rem Inter,"Segoe UI",Arial,sans-serif;color:#98a597;letter-spacing:0}
.dashboard-page .metric-check{font-size:.7rem;color:#689466}
.dashboard-page .metric-bottom{position:relative;z-index:1;display:flex;align-items:center;gap:6px;margin-top:7px;color:#98a394;font-size:.59rem}
.dashboard-page .metric-dot{width:6px;height:6px;border-radius:50%;background:#91b482}
.dashboard-page .section-block{margin-top:20px}
.dashboard-page .dashboard-grid{display:grid;grid-template-columns:minmax(0,1.3fr) minmax(270px,.7fr);gap:14px;align-items:stretch}
.dashboard-page .surface-card{min-width:0;background:#fff;border:1px solid #e4ebe1;border-radius:15px;padding:20px;box-shadow:0 4px 18px rgba(35,66,38,.025)}
.dashboard-page .surface-heading{display:flex;align-items:flex-start;justify-content:space-between;gap:13px;margin-bottom:16px}
.dashboard-page .surface-heading h2,.dashboard-page .section-heading h2{font:750 1.05rem/1.3 Inter,"Segoe UI",Arial,sans-serif;letter-spacing:-.035em;color:#2c4d33;margin:5px 0 0}
.dashboard-page .surface-heading p{font-size:.7rem;color:#89978a;margin:6px 0 0;line-height:1.5}
.dashboard-page .section-chip{display:flex;align-items:center;gap:6px;padding:6px 8px;border-radius:7px;background:#f1f6ed;color:#7c9475;font-size:.58rem;font-weight:750;white-space:nowrap}
.dashboard-page .heading-icon{width:34px;height:34px;border-radius:10px;background:#e8f0e2;display:grid;place-items:center;color:#547e4d;font-size:1rem;flex:none}
.dashboard-page .component-list{display:grid;gap:0}
.dashboard-page .component-row{display:flex;align-items:center;gap:10px;padding:11px 0;border-bottom:1px solid #edf1ea}
.dashboard-page .component-row:last-child{border-bottom:0}
.dashboard-page .component-icon{display:grid;place-items:center;width:30px;height:30px;border-radius:9px;background:#f0f5ed;color:#66875e;flex:none;font-size:.9rem}
.dashboard-page .component-name{flex:1;font-size:.73rem;font-weight:680;color:#4e6650}
.dashboard-page .pill{display:inline-flex;align-items:center;border-radius:6px;padding:5px 8px;font-size:.57rem;font-weight:750;white-space:nowrap}
.dashboard-page .pill-demo{background:#eff5ea;color:#77916c;border:1px solid #e5eee0}
.dashboard-page .message-box{display:flex;align-items:flex-start;gap:9px;background:#f7f9f4;border:1px solid #e9eee5;border-radius:10px;padding:10px;margin-top:12px}
.dashboard-page .message-mark{display:grid;place-items:center;width:19px;height:19px;border-radius:6px;background:#e6eee0;color:#6e8a64;font:800 .7rem Georgia;flex:none}
.dashboard-page .message-box strong{font-size:.68rem;color:#5b7556}
.dashboard-page .message-box p{font-size:.64rem;line-height:1.5;color:#8e9b8a;margin:2px 0 0}
.dashboard-page .clock-panel{background:linear-gradient(160deg,#fff 65%,#f5f8f0);position:relative;overflow:hidden}
.dashboard-page .clock-panel:after{content:"";position:absolute;width:150px;height:150px;border-radius:50%;border:1px solid #e7eee2;right:-70px;top:30px;box-shadow:0 0 0 17px #f6f9f3,0 0 0 35px #fbfcf9;pointer-events:none}
.dashboard-page .clock-panel-head{display:flex;justify-content:space-between;position:relative;z-index:1;margin-bottom:24px}
.dashboard-page .clock-panel h2{font:750 1.05rem Inter,"Segoe UI",Arial,sans-serif;color:#2c4d33;letter-spacing:-.035em;margin:5px 0 0}
.dashboard-page .clock-decor{display:grid;place-items:center;width:34px;height:34px;border-radius:10px;background:#e8f0e2;color:#66885b;font-size:1.1rem}
.dashboard-page .clock-panel .field-label,.dashboard-page .settings-panel .field-label{display:block;position:relative;z-index:1;margin-bottom:7px}
.dashboard-page .field-label{display:block;font-size:.68rem;color:#627661;font-weight:750;margin-bottom:7px}
.dashboard-page .field-label span{font-weight:600;color:#9ba697;margin-left:4px;font-size:.61rem}
.dashboard-page .input{width:100%;min-width:0;border:1px solid #e1e9dd;background:#fcfdfb;color:#3d5540;border-radius:9px;padding:11px 12px;outline:0;font-size:.73rem;transition:border-color .18s,box-shadow .18s}
.dashboard-page .input:focus{border-color:#9ab98d;box-shadow:0 0 0 3px #9ab98d20}
.dashboard-page .helper-text{font-size:.62rem;color:#9aa697;line-height:1.55;margin:9px 0 0;position:relative;z-index:1}
.dashboard-page .mapping-panel .surface-heading{margin-bottom:15px}
.dashboard-page .mapping-form{display:grid;grid-template-columns:minmax(135px,.38fr) minmax(190px,1fr) auto;gap:12px;align-items:end}
.dashboard-page .form-field{min-width:0}
.dashboard-page .map-button{white-space:nowrap}
.dashboard-page .inline-note{display:flex;align-items:center;gap:7px;margin-top:14px;padding-top:11px;border-top:1px solid #edf1e9;color:#94a091;font-size:.63rem}
.dashboard-page .inline-note span{display:grid;place-items:center;background:#edf3e8;color:#77966d;width:17px;height:17px;border-radius:5px;font-size:.62rem}
.dashboard-page .count-box{min-width:60px;background:#edf4e8;border:1px solid #e0ebd9;border-radius:9px;padding:6px 9px;text-align:center;color:#58764e}
.dashboard-page .count-box strong{display:block;font:750 1rem Inter,"Segoe UI",Arial,sans-serif}
.dashboard-page .count-box span{font-size:.54rem}
.dashboard-page .table-toolbar{display:flex;align-items:center;justify-content:space-between;gap:12px;margin:-1px 0 12px}
.dashboard-page .search-box{display:flex;align-items:center;gap:8px;border:1px solid #e3eade;border-radius:9px;background:#fbfcfa;padding:0 10px;max-width:310px;flex:1;color:#869884}
.dashboard-page .search-box input{border:0;background:transparent;outline:0;min-width:0;width:100%;padding:9px 0;font-size:.7rem;color:#314a35}
.dashboard-page .table-wrap{width:100%;overflow:auto;border:1px solid #e8eee5;border-radius:10px;background:#fff}
.dashboard-page table{border-collapse:collapse;width:100%;font-size:.71rem}
.dashboard-page th,.dashboard-page td{text-align:left;padding:11px 12px;border-bottom:1px solid #eef2eb;white-space:nowrap}
.dashboard-page th{background:#f6f8f4;color:#92a08e;text-transform:uppercase;letter-spacing:.09em;font-size:.54rem;font-weight:850}
.dashboard-page tbody tr:last-child td{border-bottom:0}
.dashboard-page tbody tr:hover{background:#fbfcfa}
.dashboard-page td{color:#5f735f}
.dashboard-page .id-cell{display:inline-flex;align-items:center;justify-content:center;min-width:29px;padding:4px 6px;background:#edf4e9;color:#55764e;border-radius:6px;font-weight:800;font-size:.63rem}
.dashboard-page .person-cell{display:flex;align-items:center;gap:8px}
.dashboard-page .person-avatar{display:grid;place-items:center;width:28px;height:28px;background:#e7efe2;color:#54764f;border-radius:8px;font-weight:800;font-size:.62rem;flex:none}
.dashboard-page .person-name{font-weight:700;color:#3f5941}
.dashboard-page .person-sub{color:#a0aa9b;font-size:.58rem;margin-top:2px}
.dashboard-page .status-cell{color:#719167;font-size:.63rem;font-weight:750}
.dashboard-page .align-right{text-align:right}
.dashboard-page .table-delete{border:1px solid #f0ded7;background:#fff7f3;color:#a56c5c;border-radius:7px;padding:5px 8px;font-size:.62rem;font-weight:750}
.dashboard-page .table-delete:hover{background:#ffebe5}
.dashboard-page .table-bottom{display:flex;align-items:center;justify-content:space-between;gap:10px;padding-top:10px;color:#9ca797;font-size:.59rem}
.dashboard-page .settings-grid{display:grid;grid-template-columns:minmax(0,1fr) minmax(0,1fr);gap:14px;align-items:stretch}
.dashboard-page .settings-panel form{display:grid;grid-template-columns:1fr 1fr;gap:10px 12px}
.dashboard-page .settings-panel form .btn-full{grid-column:1/-1;margin-top:0}
.dashboard-page .settings-panel .helper-text{margin-top:10px}
.dashboard-page .about-card{position:relative;overflow:hidden;background:#eef4e9;border-color:#e2eadc;padding:22px}
.dashboard-page .about-card h2{font:750 1.13rem Inter,"Segoe UI",Arial,sans-serif;letter-spacing:-.04em;margin:6px 0 7px;color:#2c4d33;max-width:290px}
.dashboard-page .about-card p{font-size:.72rem;color:#7c9079;line-height:1.65;margin:0;max-width:400px;position:relative;z-index:1}
.dashboard-page .about-graphic{position:absolute;right:15px;top:5px;width:120px;height:120px;opacity:.5}
.dashboard-page .about-graphic:before{content:"";position:absolute;right:33px;top:22px;width:2px;height:100px;background:#a2bd91;transform:rotate(30deg)}
.dashboard-page .about-graphic span{position:absolute;display:block;width:45px;height:25px;background:#adc99b;border-radius:100% 0 100% 0}
.dashboard-page .about-graphic span:nth-child(1){right:40px;top:25px;transform:rotate(-25deg)}
.dashboard-page .about-graphic span:nth-child(2){right:5px;top:52px;transform:rotate(35deg)}
.dashboard-page .about-graphic span:nth-child(3){right:40px;top:77px;transform:rotate(-7deg)}
.dashboard-page .about-tags{display:flex;gap:6px;flex-wrap:wrap;margin-top:14px;position:relative;z-index:1}
.dashboard-page .about-tags span{font-size:.57rem;font-weight:750;color:#62805b;background:#fbfdf8;border:1px solid #dfe9d9;border-radius:6px;padding:4px 7px}
.dashboard-page .page-footer{display:flex;justify-content:space-between;gap:12px;flex-wrap:wrap;margin-top:23px;padding:14px 2px 0;border-top:1px solid #e1e9de;color:#9ba697;font-size:.6rem}
.dashboard-page .page-footer strong{color:#688262;font-size:.61rem;letter-spacing:.05em}
.dashboard-page .page-footer i{font-style:normal;color:#acbea0}
.dashboard-page .toast{background:#244e34;font-size:.73rem}

/* Keep the registration screen consistent and concise. */
.registration-page{background:#f5f7f3}
.registration-page .registration-header{background:#eef3e9;color:#284331;border-bottom:1px solid #e0e8dc}
.registration-page .registration-header .brand-copy strong{color:#234731}
.registration-page .registration-header .brand-copy small{color:#7b9276}
.registration-page .back-link{color:#517151;border-color:#d8e4d2;border-radius:8px}
.registration-page .back-link:hover{background:#e2ebdd}
.registration-page .registration-hero{background:linear-gradient(112deg,#234e35 0%,#2c633e 65%,#427649 100%);padding-top:29px;padding-bottom:31px}
.registration-page .registration-hero h1{font-size:clamp(1.9rem,3.2vw,2.55rem);margin:12px 0 8px}
.registration-page .registration-hero p{font-size:.78rem;line-height:1.6;max-width:530px}
.registration-page .reg-hero-leaf{font-size:19rem;color:#d0dfa512}
.registration-page .registration-content{max-width:1250px;padding-top:22px}
.registration-page .surface-card{border-radius:15px;border-color:#e4ebe1;box-shadow:0 4px 18px rgba(35,66,38,.025)}
.registration-page .surface-heading h2{font-size:1.03rem}
.registration-page .surface-heading p{font-size:.7rem}
.registration-page .registration-form-card,.registration-page .scan-steps-card{padding:21px}
.registration-page .registration-form-card .btn-full{margin-top:10px}
.registration-page .scan-step{background:#f8faf6;border-color:#e7eee3;border-radius:10px}
.registration-page .mock-device{border-color:#dce7d7;border-radius:10px}
.registration-page .page-footer{border-color:#e1e9de}

@media(max-width:1150px){
 .dashboard-page .app-shell{grid-template-columns:212px minmax(0,1fr)}
 .dashboard-page .metric-grid{grid-template-columns:repeat(2,minmax(0,1fr))}
 .dashboard-page .hero-botanical{width:39%;opacity:.7}
 .dashboard-page .mapping-form{grid-template-columns:minmax(110px,.42fr) minmax(160px,1fr)}
 .dashboard-page .map-button{grid-column:1/-1;justify-self:start}
}
@media(max-width:900px){
 .dashboard-page .app-shell{grid-template-columns:minmax(0,1fr)}
 .dashboard-page .sidebar{position:relative;height:auto;padding:13px 17px 10px;overflow:visible}
 .dashboard-page .sidebar .brand{padding:0 3px 10px;border-bottom:0}
 .dashboard-page .nav-label,.dashboard-page .sidebar-bottom,.dashboard-page .sidebar-device{display:none}
 .dashboard-page .side-nav{display:flex;overflow-x:auto;gap:4px;padding:0 0 2px}
 .dashboard-page .nav-link{flex:0 0 auto;padding:8px 10px;font-size:.7rem}
 .dashboard-page .nav-symbol{width:auto}
 .dashboard-page .topbar{height:64px}
 .dashboard-page .dashboard-grid{grid-template-columns:minmax(0,1fr)}
 .dashboard-page .settings-grid{grid-template-columns:1fr 1fr}
 .registration-page .registration-grid{grid-template-columns:1fr}
}
@media(max-width:600px){
 .dashboard-page .topbar{padding:0 14px}
 .dashboard-page .topbar-title{font-size:.9rem}
 .dashboard-page .eyebrow{font-size:.53rem}
 .dashboard-page .connection-pill{font-size:.57rem;padding:7px 8px}
 .dashboard-page .avatar{width:29px;height:29px}
 .dashboard-page .main-content{padding:15px 12px 26px}
 .dashboard-page .hero{padding:23px 18px 44px;min-height:276px;border-radius:14px}
 .dashboard-page .hero h1{font-size:2rem;max-width:100%}
 .dashboard-page .hero p{font-size:.74rem;max-width:300px}
 .dashboard-page .hero-botanical{width:64%;right:-16%;opacity:.42}
 .dashboard-page .hero-actions{display:flex;gap:7px;max-width:100%}
 .dashboard-page .hero-actions .btn{font-size:.65rem;padding:9px 10px}
 .dashboard-page .hero-bottom{left:18px;right:18px;font-size:.47rem}
 .dashboard-page .hero-bottom span:last-child{font-size:.56rem}
 .dashboard-page .metric-grid{gap:8px;margin-top:12px}
 .dashboard-page .metric-card{padding:12px;min-height:132px;border-radius:11px}
 .dashboard-page .metric-icon{width:29px;height:29px}
 .dashboard-page .metric-tag{font-size:.45rem}
 .dashboard-page .metric-label{font-size:.62rem;margin-top:10px}
 .dashboard-page .metric-value{font-size:1.18rem}
 .dashboard-page .metric-value small{font-size:.68rem}
 .dashboard-page .metric-bottom{font-size:.54rem}
 .dashboard-page .section-block{margin-top:14px}
 .dashboard-page .surface-card{padding:15px;border-radius:12px}
 .dashboard-page .surface-heading h2{font-size:.96rem}
 .dashboard-page .surface-heading p{font-size:.65rem}
 .dashboard-page .component-name{font-size:.67rem}
 .dashboard-page .mapping-form{grid-template-columns:1fr;gap:10px}
 .dashboard-page .map-button{grid-column:auto;width:100%}
 .dashboard-page .table-toolbar{align-items:stretch;flex-direction:column}
 .dashboard-page .search-box{max-width:none}
 .dashboard-page .table-toolbar .btn{align-self:flex-start}
 .dashboard-page .table-bottom{font-size:.55rem}
 .dashboard-page .settings-grid{grid-template-columns:1fr}
 .dashboard-page .settings-panel form{grid-template-columns:1fr}
 .dashboard-page .settings-panel form .btn-full{grid-column:auto}
 .dashboard-page .page-footer{font-size:.55rem}
 .registration-page .registration-header{height:65px;padding:0 13px;gap:10px}
 .registration-page .registration-header .brand-copy strong{font-size:.7rem}
 .registration-page .registration-header .brand-copy small{font-size:.53rem}
 .registration-page .back-link{font-size:.62rem;padding:8px}
 .registration-page .registration-hero{padding:25px 17px 28px}
 .registration-page .registration-hero h1{font-size:2rem}
 .registration-page .registration-content{padding:14px 12px 28px}
 .registration-page .registration-form-card,.registration-page .scan-steps-card{padding:15px}
}

/* State styles for live ESP32 data */
.dashboard-page .badge-dot.is-online,.dashboard-page .device-led.is-online{background:#5b9e61;box-shadow:0 0 0 4px #5b9e6122}
.dashboard-page .badge-dot.is-offline,.dashboard-page .device-led.is-offline{background:#cf6656;box-shadow:0 0 0 4px #cf665622}
.dashboard-page .pill-live-ok{background:#e8f4e3;color:#397346;border:1px solid #d3e6c9}
.dashboard-page .pill-live-bad{background:#fff0ec;color:#a84336;border:1px solid #efd5ce}
.dashboard-page .pill-live-neutral{background:#f0f1e9;color:#7c8677;border:1px solid #e3e6da}
.dashboard-page .message-box.is-ok{background:#edf6e8;border-color:#d6e8cc}
.dashboard-page .message-box.is-bad{background:#fff0ec;border-color:#efd5ce}
.dashboard-page .message-box.is-bad .message-mark{background:#f6dcd5;color:#a84336}
.dashboard-page .message-box.is-ok .message-mark{background:#dcebd3;color:#397346}
.dashboard-page .component-row .pill{max-width:135px;overflow:hidden;text-overflow:ellipsis}
.registration-page .step-state.active{background:#dfead3;color:#527747}
.registration-page .step-state.done{background:#e4efe1;color:#3c7548}
.registration-page .enroll-result.is-bad{background:#fff0ec;border-color:#efd5ce}
.registration-page .enroll-result.is-ok{background:#edf6e8;border-color:#d6e8cc}
.registration-page .device-online{color:#397346}
.registration-device-pills{display:flex;flex-wrap:wrap;gap:7px;margin-top:13px}
.registration-device-pills .pill{border-radius:999px;padding:6px 9px;font-size:.62rem;font-weight:750;background:#f0f1e9;color:#7c8677;border:1px solid #e3e6da}
.registration-device-pills .pill-live-ok{background:#e8f4e3;color:#397346;border-color:#d3e6c9}
.registration-device-pills .pill-live-bad{background:#fff0ec;color:#a84336;border-color:#efd5ce}
.registration-page .reg-status-message{margin-top:12px}

</style>
</head>
<body data-page="dashboard" class="dashboard-page">
  <div class="app-shell">
    <aside class="sidebar">
      <a class="brand" href="/" aria-label="Dashboard Absensi IoT">
        <span class="brand-logo"><img src="/logo.png" alt="Logo perusahaan"></span>
        <span class="brand-copy"><strong>ABSENSI IOT</strong><small>SMART ATTENDANCE</small></span>
      </a>
      <div class="nav-label">MENU</div>
      <nav class="side-nav" aria-label="Navigasi utama">
        <a class="nav-link active" href="#overview"><span class="nav-symbol">▦</span><span>Dashboard</span></a>
        <a class="nav-link" href="#monitoring"><span class="nav-symbol">◉</span><span>Perangkat</span></a>
        <a class="nav-link" href="#users"><span class="nav-symbol">♙</span><span>Pengguna</span></a>
        <a class="nav-link" href="#history"><span class="nav-symbol">◷</span><span>Riwayat absensi</span></a>
        <a class="nav-link" href="#settings"><span class="nav-symbol">⚙</span><span>Pengaturan</span></a>
      </nav>
      <div class="sidebar-device">
        <div class="device-top"><span class="device-led"></span><span>ESP32</span><span class="device-state" id="deviceState">MEM)rawliteral"
R"rawliteral(ERIKSA</span></div>
        <div class="device-name">Absensi otomatis</div>
        <div class="device-caption">ESP32 · akses lokal</div>
        <div class="device-line"><span></span></div>
        <div class="device-foot"><span id="sidebarMode">Mode: —</span><span id="sidebarWifi">Wi-Fi —</span></div>
      </div>
      <div class="sidebar-bottom">
        <div class="local-mark"><span class="local-pulse"></span><span id="liveLabel">Mengecek ESP32</span></div>
        <p id="sidebarInfo">Menghubungkan ke perangkat.</p>
      </div>
    </aside>

    <div class="workspace">
      <header class="topbar">
        <div class="topbar-heading"><div class="eyebrow">RUANG KENDALI</div><div class="topbar-title">Dashboard absensi</div></div>
        <div class="topbar-right"><span class="connection-pill"><span class="badge-dot" id="connectionDot"></span><span id="connectionText">Memeriksa ESP32…</span></span><span class="avatar">IOT</span></div>
      </header>

      <main class="main-content">
        <section class="hero" id="overview">
          <div class="hero-copy">
            <div class="hero-kicker"><span class="kicker-leaf">✳</span> SISTEM ABSENSI IOT</div>
            <h1>Absensi, lebih<br><em>praktis dan teratur.</em></h1>
            <p>Pantau perangkat dan kelola data kehadiran dari satu dashboard.</p>
            <div class="hero-actions"><a class="btn btn-cream" href="/pendaftaran">＋ Daftarkan sidik jari</a><button class="btn btn-outline" id="refreshAll">↻ Segarkan</button></div>
          </div>
          <div class="hero-botanical" aria-hidden="true"><div class="botanical-orb"></div><div class="botanical-stem"></div><i class="leaf leaf-one"></i><i class="leaf leaf-two"></i><i class="leaf leaf-three"></i><i class="leaf leaf-four"></i><div class="botanical-ring"></div></div>
          <div class="hero-bottom"><span>ABSENSI OTOMATIS</span><span id="todayLabel">Hari ini</span></div>
        </section>

        <section class="metric-grid" aria-label="Ringkasan sistem">
          <article class="metric-card metric-featured"><div class="metric-top"><span class="metric-icon">◎</span><span class="metric-tag" id="fpTag">MEMERIKSA</span></div><div class="metric-label">Fingerprint R558-S</div><div class="metric-value" id="statFp">—</div><div class="metric-bottom" id="fpMeta"><span class="metric-dot"></span> Menunggu status sensor</div></article>
          <article class="metric-card"><div class="metric-top"><span class="metric-icon icon-light">♙</span><span class="metric-tag">DATA</span></div><div class="metric-label">Template sensor tersimpan</div><div class="metric-value" id="templateCount">— <small>/ 100</small></div><div class="metric-bottom">Kapasitas template sensor</div></article>
          <article class="metric-card"><div class="metric-top"><span class="metric-icon icon-light">▤</span><span class="metric-tag" id="sdTag">MEMERIKSA</span></div><div class="metric-label">MicroSD</div><div class="metric-value" id="statSd">—</div><div class="metric-bottom" id="sdMeta">Memeriksa penyimpanan</div></article>
          <article class="metric-card metric-clock"><div class="metric-top"><span class="metric-icon icon-light">◷</span><span class="metric-tag" id="rtcTag">RTC</span></div><div class="metric-label">Jam sistem</div><div class="metric-value" id="clockValue">--:--</div><div class="metric-bottom" id="clockDate">Menunggu RTC DS1307</div><span id="statRtcTag" hidden></span></article>
        </section>

        <section class="dashboard-grid section-block" id="monitoring">
          <article class="surface-card device-panel">
            <div class="surface-heading"><div><div class="section-overline">STATUS PERANGKAT</div><h2>Monitoring</h2></div><span class="section-chip"><span class="small-green-dot"></span> Simulasi</span></div>
            <div class="component-list" id="componentList">
              <div class="component-row"><span class="component-icon">◎</span><span class="component-name">Fingerprint R558-S</span><span class="pill pill-demo">Siap</span></div>
              <div class="component-row"><span class="component-icon">▤</span><span class="component-name">MicroSD</span><span class="pill pill-demo">Siap</span></div>
              <div class="component-row"><span class="component-icon">◷</span><span class="component-name">RTC DS1307</span><span class="pill pill-demo">Browser</span></div>
              <div class="component-row"><span class="component-icon">♫</span><span class="component-name">Audio MAX98357A</span><span class="pill pill-demo">Siap</span></div>
            </div>
            <div class="message-box" id="statusMessage"><span class="message-mark">i</span><div><strong>Status perangkat</strong><p>Menghubungkan ke ESP32…</p></div></div>
          </article>
          <article class="surface-card clock-panel">
            <div class="clock-panel-head"><div><div class="section-overline">PENGATURAN RTC</div><h2>Atur waktu</h2></div><span class="clock-decor">◷</span></div>
            <label class="field-label" for="rtcInput">Tanggal dan waktu</label><input class="input" id="rtcInput" type="datetime-local">
            <button class="btn btn-primary btn-full" id="saveRtc">Simpan waktu</button>
            <p class="helper-text">Hanya mengubah tampilan demo.</p>
          </article>
        </section>

        <section class="surface-card section-block mapping-panel" id="mapping">
          <div class="surface-heading"><div><div class="section-overline">MANAJEMEN DATA</div><h2>Pemetaan fingerprint</h2><p>Hubungkan ID template dengan nama pengguna.</p></div><span class="heading-icon">＋</span></div>
          <form id="mappingForm" class="mapping-form">
            <div class="form-field"><label class="field-label" for="storedId">ID template <span>01–100</span></label><input class="input" id="storedId" type="number" min="1" max="100" placeholder="ID fingerprint" required></div>
            <div class="form-field name-field"><label class="field-label" for="storedName">Nama pengguna</label><input class="input" id="storedName" maxlength="32" placeholder="Nama lengkap" required></div>
            <button class="btn btn-primary map-button" type="submit">Simpan pemetaan <span>→</span></button>
          </form>
          <div class="inline-note" id="mappingHint"><span>i</span> Pemetaan disimpan ke users.csv pada MicroSD melalui ESP32.</div>
        </section>

        <section class="surface-card section-block" id="users">
          <div class="surface-heading"><div><div class="section-overline">DIREKTORI</div><h2>Pengguna</h2></div><div class="count-box"><strong id="userCount">03</strong><span>pengguna</span></div></div>
          <div class="table-toolbar"><label class="search-box"><span>⌕</span><input id="userSearch" type="search" placeholder="Cari nama atau ID..."></label><button class="btn btn-secondary" id="refreshUsers" type="button">Muat ulang data</button></div>
          <div class="table-wrap"><table><thead><tr><th>ID</th><th>Nama pengguna</th><th>Status</th><th class="align-right">Aksi</th></tr></thead><tbody id="usersBody"></tbody></table></div>
          <div class="table-bottom"><span id="tableSummary">Menampilkan data contoh</span><span>users.csv · MicroSD</span></div>
        </section>

        <section class="surface-card section-block" id="history">
          <div class="surface-heading"><div><div class="section-overline">LOG KEHADIRAN</div><h2>Riwayat absensi</h2></div><button class="btn btn-secondary" id="refreshLogs">↻ Muat ulang</button></div>
          <div class="table-wrap"><table><thead><tr><th>Tanggal</th><th>Waktu</th><th>ID</th><th>Nama</th><th>Skor</th><th>Status</th></tr></thead><tbody id="logsBody"></tbody></table></div>
          <div class="table-bottom"><span>Maks. 20 catatan</span><span>Data contoh</span></div>
        </section>

        <section class="settings-grid section-block" id="settings">
          <article class="surface-card settings-panel">
            <div class="surface-heading"><div><div class="section-overline">KONEKSI</div><h2>Pengaturan Wi-Fi</h2></div><span class="heading-icon">⌁</span></div>
            <form id="wifiForm"><div class="form-field"><label class="field-label" for="wifiName">Nama jaringan (SSID)</label><input class="input" id="wifiName" maxlength="32" value="Absensi-ESP32" required></div><div class="form-field"><label class="field-label" for="wifiPassword">Kata sandi</label><input class="input" id="wifiPassword" type="password" maxlength="63" placeholder="Minimal 8 karakter"></div><button class="btn btn-primary btn-full" type="submit">Simpan pengaturan</button></form><p class="helper-text">Perubahan diterapkan pada Wi-Fi konfigurasi ESP32. Setelah tersimpan, sambungkan ulang bila jaringan berubah.</p>
          </article>
          <article class="surface-card about-card"><div class="about-graphic" aria-hidden="true"><span></span><span></span><span></span></div><div class="section-overline">TENTANG</div><h2>Absensi IoT</h2><p>Panel administrasi untuk sensor R558-S, MicroSD, RTC DS1307, dan audio MAX98357A.</p><div class="about-tags"><span>HTML</span><span>CSS</span><span>JavaScript</span></div></article>
        </section>

        <footer class="page-footer"><span><strong>ABSENSI IOT</strong> <i>·</i> Dashboard lokal</span><span>Data langsung dari ESP32 saat perangkat terhubung</span></footer>
      </main>
    </div>
  </div>
  <div class="toast" id="toast" role="status" aria-live="polite"></div>
  <script>
(() => {
  'use strict';
  const $ = (id) => document.getElementById(id);
  let toastTimer = null;
  let rtcInputTouched = false;
  let cachedUsers = [];
  const esc = (value) => String(value ?? '').replace(/[&<>\"']/g, ch => ({'&':'&amp;','<':'&lt;','>':'&gt;','\"':'&quot;',"'":'&#39;'}[ch]));

  function toast(message) {
    const el = $('toast'); if (!el) return;
    el.textContent = message; el.classList.add('show');
    clearTimeout(toastTimer); toastTimer = setTimeout(() => el.classList.remove('show'), 3400);
  }
  async function getJson(url) {
    const response = await fetch(url, {cache:'no-store'});
    if (!response.ok) throw new Error((await response.text()) || `HTTP ${response.status}`);
    return response.json();
  }
  async function getText(url, options = {}) {
    const response = await fetch(url, {...options, cache:'no-store'});
    const body = await response.text();
    if (!response.ok) throw new Error(body || `HTTP ${response.status}`);
    return body;
  }
  function initialLetters(name) {
    return String(name || '').trim().split(/\s+/).slice(0,2).map(s => s[0] || '').join('').toUpperCase() || 'U';
  }
  function setConnection(connected, label) {
    const text = $('connectionText'); if (text) text.textContent = label;
    const dot = $('connectionDot'); if (dot) dot.classList.toggle('is-online', connected), dot.classList.toggle('is-offline', !connected);
    const state = $('deviceState'); if (state) state.textContent = connected ? 'TERHUBUNG' : 'OFFLINE';
    const led = document.querySelector('.device-led'); if (led) { led.classList.toggle('is-online', connected); led.classList.toggle('is-offline', !connected); }
    const info = $('sidebarInfo'); if (info) info.textContent = connected ? 'Data perangkat diterima dari ESP32.' : 'ESP32 belum dapat dijangkau dari browser.';
    const live = $('liveLabel'); if (live) live.textContent = connected ? 'Koneksi perangkat aktif' : 'Menunggu koneksi perangkat';
  }
  function setMessageBox(title, detail, type = '') {
    const box = $('statusMessage'); if (!box) return;
    box.className = 'message-box' + (type ? ' is-' + type : '');
    box.replaceChildren();
    const icon = document.createElement('span'); icon.className = 'message-mark'; icon.textContent = type === 'bad' ? '!' : (type === 'ok' ? '✓' : 'i');
    const content = document.createElement('div');
    const strong = document.createElement('strong'); strong.textContent = title || 'Status perangkat';
    const p = document.createElement('p'); p.textContent = detail || 'Tidak ada pesan tambahan.';
    content.append(strong, p); box.append(icon, content);
  }
  function stateClass(value) {
    if (['OK','SIAP','AKTIF'].includes(String(value).toUpperCase())) return 'pill-live-ok';
    if (['GAGAL','TIDAK ADA'].includes(String(value).toUpperCase())) return 'pill-live-bad';
    return 'pill-live-neutral';
  }
  function renderComponents(s) {
    const host = $('componentList'); if (!host) return;
    const items = [
      ['◎','Fingerprint R558-S',s.fingerprint],
      ['▤','MicroSD',s.sd],
      ['◷','RTC DS1307',s.rtc],
      ['♫','Audio MAX98357A',s.audio],
      ['⌁','Wi-Fi konfigurasi',s.wifi]
    ];
    host.replaceChildren();
    items.forEach(([iconText, label, value]) => {
      const row = document.createElement('div'); row.className = 'component-row';
      const icon = document.createElement('span'); icon.className = 'component-icon'; icon.textContent = iconText;
      const name = document.createElement('span'); name.className = 'component-name'; name.textContent = label;
      const pill = document.createElement('span'); pill.className = 'pill ' + stateClass(value); pill.textContent = value ?? '—';
      row.append(icon, name, pill); host.appendChild(row);
    });
  }
  function parseRtc(value) {
    if (!value || value === 'Tidak tersedia') return null;
    const match = String(value).match(/^(\d{4})-(\d{2})-(\d{2})[ T](\d{2}):(\d{2})(?::(\d{2}))?/);
    return match ? {date:`${match[1]}-${match[2]}-${match[3]}`, time:`${match[4]}:${match[5]}`, input:`${match[1]}-${match[2]}-${match[3]}T${match[4]}:${match[5]}`} : null;
  }
  function initRtcInput() {
    const input = $('rtcInput'); if (!input || input.dataset.ready === '1') return;
    const now = new Date(); input.value = new Date(now.getTime() - now.getTimezoneOffset()*60000).toISOString().slice(0,16);
    input.dataset.ready = '1';
    input.addEventListener('input', () => { rtcInputTouched = true; });
  }
  async function refreshStatus() {
    try {
      const s = await getJson('/api/status');
      setConnection(true, 'ESP32 terhubung');
      if ($('statFp')) $('statFp').textContent = s.fingerprint || '—';
      if ($('fpTag')) $('fpTag').textContent = s.fingerprint === 'OK' ? 'SIAP' : 'PERIKSA';
      if ($('fpMeta')) $('fpMeta').textContent = s.fingerprint === 'OK' ? 'Sensor merespons' : 'Periksa koneksi R558-S';
      if ($('templateCount')) $('templateCount').innerHTML = `${String(s.templates ?? 0).padStart(2,'0')} <small>/ 100</small>`;
      if ($('statSd')) $('statSd').textContent = s.sd || '—';
      if ($('sdMeta')) $('sdMeta').textContent = s.sd === 'OK' ? 'Penyimpanan tersedia' : 'Periksa MicroSD';
      if ($('sdTag')) $('sdTag').textContent = s.sd === 'OK' ? 'TERSEDIA' : 'PERIKSA';
      if ($('statRtcTag')) $('statRtcTag').textContent = s.rtc || '—';
      const rtc = parseRtc(s.time);
      if ($('clockValue')) $('clockValue').textContent = rtc ? rtc.time : '--:--';
      if ($('clockDate')) $('clockDate').textContent = rtc ? `RTC DS1307 · ${rtc.date}` : 'RTC DS1307 tidak tersedia';
      if ($('rtcTag')) $('rtcTag').textContent = s.rtc === 'OK' ? 'AKTIF' : 'PERIKSA';
      if (rtc && $('rtcInput') && !rtcInputTouched) $('rtcInput').value = rtc.input;
      if ($('todayLabel')) $('todayLabel').textContent = rtc ? rtc.date : new Intl.DateTimeFormat('id-ID',{day:'numeric',month:'short',year:'numeric'}).format(new Date());
      if ($('sidebarMode')) $('sidebarMode').textContent = s.mode || '—';
      if ($('sidebarWifi')) $('sidebarWifi').textContent = 'Wi-Fi ' + (s.wifi || '—');
      renderComponents(s);
      const type = s.messageType === 'ok' ? 'ok' : (s.messageType === 'bad' ? 'bad' : '');
      const title = s.enrollBusy ? `Pendaftaran ID ${s.enrollId} berjalan` : (s.mode || 'Status perangkat');
      setMessageBox(title, s.enrollBusy ? `${s.enrollment || s.message || 'Ikuti instruksi sensor.'}` : (s.message || 'Status diterima dari perangkat.'), type);
    } catch (error) {
      setConnection(false, 'ESP32 tidak terjangkau');
      setMessageBox('Tidak dapat membaca perangkat', error.message + '. Pastikan browser dibuka melalui alamat ESP32 saat Wi-Fi konfigurasi aktif.', 'bad');
      if ($('statFp')) $('statFp').textContent = '—';
      if ($('statSd')) $('statSd').textContent = '—';
    }
  }
  function renderUsers() {
    const body = $('usersBody'); if (!body) return;
    const query = ($('userSearch')?.value || '').trim().toLowerCase();
    const users = cachedUsers.filter(u => String(u.name || '').toLowerCase().includes(query) || String(u.id).includes(query));
    body.replaceChildren();
    if (!users.length) {
      const row = document.createElement('tr'); const cell = document.createElement('td'); cell.colSpan = 4; cell.className = 'empty-cell';
      cell.textContent = query ? 'Tidak ada pengguna yang cocok.' : 'Belum ada pengguna pada users.csv.'; row.appendChild(cell); body.appendChild(row);
    } else users.forEach(user => {
      const tr = document.createElement('tr');
      const idCell = document.createElement('td'); idCell.innerHTML = `<span class="id-cell">${String(Number(user.id)).padStart(2,'0')}</span>`;
      const nameCell = document.createElement('td');
      nameCell.innerHTML = `<div class="person-cell"><span class="person-avatar">${esc(initialLetters(user.name))}</span><div><div class="person-name">${esc(user.name)}</div><div class="person-sub">users.csv • MicroSD</div></div></div>`;
      const statusCell = document.createElement('td'); statusCell.innerHTML = '<span class="status-cell">● Terdaftar</span>';
      const actionCell = document.createElement('td'); actionCell.className = 'align-right';
      const button = document.createElement('button'); button.type = 'button'; button.className = 'table-delete'; button.textContent = 'Hapus'; button.dataset.deleteId = String(user.id); button.dataset.deleteName = String(user.name || '');
      actionCell.appendChild(button); tr.append(idCell, nameCell, statusCell, actionCell); body.appendChild(tr);
    });
    if ($('userCount')) $('userCount').textContent = String(cachedUsers.length).padStart(2,'0');
    if ($('tableSummary')) $('tableSummary').textContent = `Menampilkan ${users.length} dari ${cachedUsers.length} pengguna pada MicroSD`;
  }
  async function refreshUsers() {
    try { const result = await getJson('/api/users'); cachedUsers = Array.isArray(result) ? result : []; renderUsers(); }
    catch (error) { const body = $('usersBody'); if (body) body.innerHTML = `<tr><td colspan="4" class="empty-cell">Gagal membaca users.csv: ${esc(error.message)}</td></tr>`; if ($('tableSummary')) $('tableSummary').textContent = 'Data pengguna tidak tersedia'; }
  }
  async function refreshLogs() {
    const body = $('logsBody'); if (!body) return;
    try {
      const logs = await getJson('/api/logs'); body.replaceChildren();
      if (!Array.isArray(logs) || !logs.length) { body.innerHTML = '<tr><td colspan="6" class="empty-cell">Belum ada catatan pada attendance.csv.</td></tr>'; return; }
      logs.forEach(log => {
        const tr = document.createElement('tr');
        const fields = [log.date, log.time, String(log.id ?? ''), log.name, Number.isFinite(Number(log.confidence)) ? `${Number(log.confidence)}%` : '—'];
        fields.forEach((value, idx) => { const td = document.createElement('td'); td.textContent = value ?? ''; if (idx === 2) td.innerHTML = `<span class="id-cell">${esc(value)}</span>`; tr.appendChild(td); });
        const status = document.createElement('td'); status.innerHTML = '<span class="pill pill-live-ok">Tercatat</span>'; tr.appendChild(status); body.appendChild(tr);
      });
    } catch (error) { body.innerHTML = `<tr><td colspan="6" class="empty-cell">Gagal membaca attendance.csv: ${esc(error.message)}</td></tr>`; }
  }
  async function handleMapping(event) {
    event.preventDefault();
    const id = Number($('storedId').value), name = $('storedName').value.trim();
    if (!Number.isInteger(id) || id < 1 || id > 100) return toast('Masukkan ID template 1–100.');
    if (!name) return toast('Nama pengguna wajib diisi.');
    try {
      const result = await getText(`/api/link-user?id=${encodeURIComponent(id)}&name=${encodeURIComponent(name)}`, {method:'POST'});
      toast(result); $('storedId').value = ''; $('storedName').value = '';
      await Promise.all([refreshUsers(), refreshStatus()]);
    } catch (error) { toast('Pemetaan gagal: ' + error.message); }
  }
  async function handleDelete(id, name) {
    if (!confirm(`Hapus ${name} (ID ${id})? Template sensor dan pemetaan pada users.csv akan dihapus. Riwayat absensi tetap disimpan.`)) return;
    try { const result = await getText(`/api/delete-user?id=${encodeURIComponent(id)}`, {method:'POST'}); toast(result); await Promise.all([refreshUsers(), refreshLogs(), refreshStatus()]); }
    catch (error) { toast('Penghapusan gagal: ' + error.message); }
  }
  async function handleRtc() {
    const value = $('rtcInput')?.value; if (!value) return toast('Pilih tanggal dan waktu RTC.');
    try { const result = await getText(`/rtc?datetime=${encodeURIComponent(value)}`); rtcInputTouched = false; toast(result); await refreshStatus(); }
    catch (error) { toast('Gagal mengatur RTC: ' + error.message); }
  }
  async function handleWifi(event) {
    event.preventDefault(); const ssid = $('wifiName').value.trim(), password = $('wifiPassword').value;
    if (!ssid || ssid.length > 32) return toast('SSID harus 1–32 karakter.');
    if (password && (password.length < 8 || password.length > 63)) return toast('Kata sandi harus 8–63 karakter.');
    const button = $('wifiForm')?.querySelector('button[type="submit"]'); if (button) { button.disabled = true; button.dataset.originalText = button.textContent; button.textContent = 'Menyimpan…'; }
    try { const result = await getText(`/wifi?ssid=${encodeURIComponent(ssid)}&password=${encodeURIComponent(password)}`, {method:'POST'}); $('wifiPassword').value = ''; toast(result + ' Sambungkan ulang ke jaringan jika diminta.'); }
    catch (error) { toast('Gagal menyimpan Wi-Fi: ' + error.message); }
    finally { if (button) { button.disabled = false; button.textContent = button.dataset.originalText || 'Simpan pengaturan'; } }
  }
  async function refreshAll() { initRtcInput(); await Promise.all([refreshStatus(), refreshUsers(), refreshLogs(), loadWifi()]); }
  async function loadWifi() { try { const data = await getJson('/api/wifi'); if ($('wifiName') && !$('wifiName').dataset.touched) $('wifiName').value = data.ssid || ''; } catch (_) {} }
  function init() {
    initRtcInput(); $('mappingForm')?.addEventListener('submit', handleMapping); $('wifiForm')?.addEventListener('submit', handleWifi);
    $('saveRtc')?.addEventListener('click', handleRtc); $('refreshAll')?.addEventListener('click', () => refreshAll().then(() => toast('Data dashboard diperbarui dari ESP32.')));
    $('refreshLogs')?.addEventListener('click', refreshLogs); $('refreshUsers')?.addEventListener('click', refreshUsers);
    $('userSearch')?.addEventListener('input', renderUsers); $('wifiName')?.addEventListener('input', () => { $('wifiName').dataset.touched = '1'; });
    $('usersBody')?.addEventListener('click', event => { const button = event.target.closest('[data-delete-id]'); if (button) handleDelete(button.dataset.deleteId, button.dataset.deleteName); });
    document.querySelectorAll('.side-nav .nav-link').forEach(link => link.addEventListener('click', () => { document.querySelectorAll('.side-nav .nav-link').forEach(item => item.classList.remove('active')); link.classList.add('active'); }));
    refreshAll(); setInterval(refreshStatus, 1200); setInterval(refreshUsers, 7000); setInterval(refreshLogs, 5000);
  }
  init();
})();
</script>
</body>
</html>
)rawliteral";

const char REGISTRATION_HTML[] PROGMEM =
R"rawliteral(
<!doctype html>
<html lang="id">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta name="theme-color" content="#173f2d">
  <title>Pendaftaran Fingerprint — ESP32</title>
  <style>
:root{--forest:#173f2d;--forest2:#28583c;--moss:#67865b;--leaf:#8ba778;--sage:#dce6d2;--sage2:#eef2e7;--cream:#f5f3e9;--paper:#fffef9;--ink:#21372a;--muted:#7b8779;--line:#e2e6da;--sand:#eee7d3;--rust:#a34335;--shadow:0 12px 34px rgba(28,59,38,.055);font-family:'DM Sans',Arial,sans-serif;color:var(--ink);background:var(--cream)}
*{box-sizing:border-box}html{scroll-behavior:smooth;scroll-padding-top:24px}body{margin:0;min-width:320px;background:var(--cream);font-size:14px;line-height:1.55}a{color:inherit}button,input{font:inherit}button{cursor:pointer}.app-shell{min-height:100vh;display:grid;grid-template-columns:252px minmax(0,1fr)}
.sidebar{position:sticky;top:0;height:100vh;background:var(--forest);color:#f8f6eb;padding:27px 17px 18px;display:flex;flex-direction:column;overflow-y:auto;z-index:10}.brand{display:flex;align-items:center;gap:11px;text-decoration:none;min-width:0}.sidebar .brand{padding:0 6px 27px;border-bottom:1px solid #ffffff20}.brand-logo{width:45px;height:45px;border-radius:14px;background:#fff;display:grid;place-items:center;overflow:hidden;flex:none}.brand-logo img{width:100%;height:100%;object-fit:contain;padding:3px}.brand-copy{min-width:0}.brand-copy strong{font:800 .84rem 'Manrope',sans-serif;letter-spacing:.02em;display:block;white-space:nowrap}.brand-copy small{display:block;color:#b8ceb5;font-size:.62rem;letter-spacing:.16em;margin-top:4px}.nav-label{font-size:.64rem;font-weight:700;letter-spacing:.16em;color:#92ae95;padding:25px 13px 9px}.side-nav{display:grid;gap:5px}.nav-link{display:flex;align-items:center;gap:11px;padding:11px 12px;color:#cadac8;text-decoration:none;border-radius:11px;font-size:.81rem;font-weight:600;transition:background .2s,color .2s}.nav-link:hover,.nav-link.active{background:#ffffff15;color:#fff}.nav-link.active{box-shadow:inset 3px 0 #b9d199}.nav-symbol{width:22px;text-align:center;font-size:1.08rem;color:#a9c49b}.sidebar-bottom{margin-top:auto}.local-mark{display:flex;align-items:center;gap:8px;color:#e1ebd7;font-size:.73rem;font-weight:700;background:#ffffff11;border:1px solid #ffffff12;border-radius:10px;padding:10px 11px}.local-pulse{width:7px;height:7px;background:#b9d19b;border-radius:50%;box-shadow:0 0 0 4px #b9d19b22}.sidebar-bottom p{color:#9eb6a0;font-size:.69rem;line-height:1.7;margin:10px 9px 0}
.workspace{min-width:0}.topbar{height:76px;display:flex;align-items:center;justify-content:space-between;gap:15px;padding:0 clamp(18px,3.1vw,45px);background:rgba(250,249,242,.86);border-bottom:1px solid var(--line)}.eyebrow,.section-overline{font-size:.64rem;font-weight:800;letter-spacing:.15em;color:#82977a}.topbar-title{font:800 .98rem 'Manrope',sans-serif;color:var(--forest);margin-top:3px}.topbar-right{display:flex;align-items:center;gap:13px}.demo-badge{display:flex;align-items:center;gap:7px;background:#eef3e7;border:1px solid #dbe5d2;color:#496848;border-radius:999px;padding:8px 12px;font-size:.66rem;font-weight:800;letter-spacing:.04em}.badge-dot{width:7px;height:7px;border-radius:50%;background:#7d9c6b}.avatar{width:34px;height:34px;display:grid;place-items:center;background:#e3ead8;border-radius:50%;color:var(--forest);font-weight:800;font-size:.8rem}.main-content{width:100%;max-width:1580px;padding:25px clamp(18px,3.1vw,45px) 36px;margin:0 auto}
.hero{position:relative;isolation:isolate;overflow:hidden;min-height:315px;border-radius:23px;background:linear-gradient(105deg,#173f2d 0%,#25563a 52%,#52744b 100%);color:#fff;padding:34px 36px 52px;box-shadow:0 17px 38px #173f2d18}.hero:before{content:"";position:absolute;z-index:-1;right:-7%;top:-55%;width:390px;height:390px;border-radius:50%;border:1px solid #ffffff15;box-shadow:0 0 0 27px #ffffff08,0 0 0 56px #ffffff05}.hero-copy{position:relative;z-index:2;max-width:610px}.hero-kicker{display:flex;align-items:center;gap:9px;color:#d9e6ca;font-size:.65rem;font-weight:800;letter-spacing:.13em}.kicker-leaf{display:grid;place-items:center;width:22px;height:22px;border-radius:8px;background:#ffffff17;color:#e2edc9;font-size:.95rem}.hero h1,.registration-hero h1{font:800 clamp(2.25rem,3.5vw,3.25rem)/1.08 'Manrope',sans-serif;letter-spacing:-.055em;margin:19px 0 12px;max-width:600px}.hero h1 em{font-style:normal;color:#c7d8a6}.hero p{font-size:.87rem;line-height:1.8;color:#d9e5d5;max-width:500px;margin:0}.hero-actions{display:flex;gap:10px;flex-wrap:wrap;margin-top:22px}.btn{display:inline-flex;align-items:center;justify-content:center;gap:9px;min-height:42px;border-radius:11px;padding:11px 15px;border:1px solid transparent;text-decoration:none;font-weight:750;font-size:.76rem;transition:transform .18s,background .18s,border-color .18s;white-space:normal}.btn:hover{transform:translateY(-1px)}.btn-cream{background:#f4f0df;color:var(--forest)}.btn-cream:hover{background:#fff9e8}.btn-outline{background:#ffffff0b;color:#fff;border-color:#ffffff49}.btn-outline:hover{background:#ffffff17}.btn-primary{background:var(--forest);color:#fff}.btn-primary:hover{background:#28583c}.btn-secondary{background:#f5f5ec;color:#476247;border-color:#e0e5d7}.btn-secondary:hover{background:#eaf0e1}.btn-danger{background:#fff0eb;color:var(--rust);border-color:#f0d8d0}.btn-danger:hover{background:#ffe3db}.btn-full{width:100%;margin-top:12px}.hero-art{position:absolute;z-index:1;right:0;top:0;width:44%;height:100%;pointer-events:none;overflow:hidden}.art-sun{position:absolute;right:23%;top:15%;width:135px;height:135px;border-radius:50%;background:#e5e9bd18}.art-hill{position:absolute;bottom:-7%;right:-3%;width:94%;height:45%;border-radius:70% 40% 0 0;transform:rotate(-10deg)}.hill-back{background:#b7c99828;right:-14%;bottom:7%;height:48%;transform:rotate(13deg)}.hill-front{background:#a5c08135}.art-plant{position:absolute;right:9%;bottom:-5%;width:280px;height:280px;filter:drop-shadow(0 8px 20px #102b1b30)}.art-grain{position:absolute;inset:0;background:radial-gradient(#ffffff18 .6px,transparent .6px);background-size:7px 7px;opacity:.18;mask-image:linear-gradient(90deg,transparent,black)}.hero-bottom{position:absolute;bottom:0;left:36px;right:36px;height:35px;border-top:1px solid #ffffff24;display:flex;align-items:center;justify-content:space-between;gap:10px;color:#abc5a8;font-size:.56rem;font-weight:700;letter-spacing:.12em}.hero-bottom span:last-child{text-align:right}
.section-block{margin-top:28px}.section-heading{display:flex;align-items:end;justify-content:space-between;gap:14px;margin-bottom:15px}.section-heading h2,.surface-heading h2{font:800 1.26rem 'Manrope',sans-serif;letter-spacing:-.04em;color:var(--forest);margin:5px 0 5px}.section-heading p,.surface-heading p{font-size:.78rem;color:var(--muted);margin:0;line-height:1.65}.date-pill{border:1px solid var(--line);background:#fcfbf5;color:#7c8978;padding:7px 11px;border-radius:999px;font-size:.69rem;white-space:nowrap}.stats-grid{display:grid;grid-template-columns:repeat(4,minmax(0,1fr));gap:12px}.stat-card{min-width:0;position:relative;overflow:hidden;background:var(--paper);border:1px solid var(--line);border-radius:17px;padding:17px 17px 19px;min-height:156px;box-shadow:var(--shadow)}.stat-card-top{display:flex;align-items:center;justify-content:space-between;gap:8px}.stat-icon{width:34px;height:34px;display:grid;place-items:center;border-radius:11px;font-size:1rem}.stat-icon.green{background:#e5eddd;color:#3f6844}.stat-icon.sand{background:#f0ead7;color:#8a7445}.stat-icon.sage{background:#e3ece5;color:#557b66}.stat-icon.cream{background:#f0eee3;color:#6d795f}.status-mini{font-size:.54rem;letter-spacing:.08em;font-weight:800}.status-mini.demo{color:#84937e}.stat-label{font-size:.72rem;font-weight:650;color:#7b8779;margin-top:14px}.stat-number{font:800 1.55rem 'Manrope',sans-serif;letter-spacing:-.045em;color:var(--forest);margin-top:3px;overflow-wrap:anywhere}.stat-number small{font:700 .82rem 'DM Sans',sans-serif;color:#8b9684;letter-spacing:0}.status-check{font-size:.75rem;color:#65946a}.stat-foot{font-size:.66rem;color:#9aa293;margin-top:5px}.time-number{font-size:1.65rem}.stat-accent{position:absolute;bottom:-28px;right:-20px;width:66px;height:66px;border-radius:50%;border:11px solid #e6eedf}.accent-sand{border-color:#f1ead9}.accent-sage{border-color:#e7eee6}.accent-cream{border-color:#eeece1}
.content-grid{display:grid;grid-template-columns:minmax(0,1.2fr) minmax(280px,.8fr);gap:14px;align-items:stretch}.surface-card{min-width:0;background:var(--paper);border:1px solid var(--line);border-radius:19px;padding:22px;box-shadow:var(--shadow)}.surface-heading{display:flex;align-items:flex-start;justify-content:space-between;gap:14px;margin-bottom:19px}.surface-heading h2{font-size:1.05rem;margin-top:5px}.surface-heading p{max-width:620px;font-size:.75rem}.heading-icon{width:38px;height:38px;border-radius:12px;background:#e7efdf;display:grid;place-items:center;color:#436746;font-size:1.08rem;flex:none}.sand-icon{background:#f0ead9;color:#8a7b52}.component-list{display:grid;gap:0}.component-row{display:flex;align-items:center;gap:10px;padding:11px 0;border-bottom:1px solid #edf0e8}.component-row:last-child{border-bottom:0}.component-icon{display:grid;place-items:center;width:31px;height:31px;border-radius:10px;background:#f0f3e9;color:#5d7956;flex:none}.component-name{flex:1;font-size:.77rem;font-weight:700;color:#465b45}.pill{display:inline-flex;align-items:center;border-radius:999px;padding:5px 8px;font-size:.62rem;font-weight:750;white-space:nowrap}.pill-demo{background:#edf2e6;color:#718766;border:1px solid #e0e8d5}.message-box{display:flex;align-items:flex-start;gap:10px;background:#f4f5eb;border:1px solid #e6e9dc;border-radius:12px;padding:12px;margin-top:14px}.message-mark{display:grid;place-items:center;width:21px;height:21px;border-radius:50%;background:#e0e8d5;color:#5d7956;font:800 .75rem Georgia;flex:none}.message-box strong{font-size:.74rem;color:#50684d}.message-box p{font-size:.7rem;line-height:1.65;color:#84907e;margin:3px 0 0}.panel-footer-line{display:flex;align-items:center;justify-content:space-between;gap:10px;border-top:1px solid #e8ece1;padding-top:13px;margin-top:14px}.muted-label{color:#909b8b;font-size:.68rem}.panel-footer-line strong{font-size:.67rem;color:#587650}.small-green-dot{width:6px;height:6px;display:inline-block;background:#7eaa72;border-radius:50%;margin-right:5px}.field-label{display:block;color:#526b4d;font-size:.74rem;font-weight:750;margin-bottom:7px}.field-label span{font-size:.66rem;font-weight:600;color:#9ca695;margin-left:3px}.input{display:block;width:100%;min-width:0;border:1px solid #dfe5d8;border-radius:10px;background:#fffef9;color:var(--ink);padding:12px 13px;font-size:.78rem;outline:none;transition:border .15s,box-shadow .15s}.input:focus{border-color:#88a477;box-shadow:0 0 0 3px #9cb88b2b}.input::placeholder{color:#a0a99a}.helper-text{color:#929b8b;font-size:.68rem;line-height:1.7;margin:11px 0 0}.time-card{background:linear-gradient(150deg,#fffef9,#f8f8ef)}.time-card .surface-heading{margin-bottom:23px}
.mapping-form{display:grid;grid-template-columns:minmax(110px,.36fr) minmax(190px,1fr) auto;gap:12px;align-items:end}.form-field{min-width:0}.map-button{white-space:nowrap}.inline-note{display:flex;align-items:center;gap:8px;margin-top:17px;padding-top:13px;border-top:1px solid #edf0e8;color:#8a9684;font-size:.69rem}.inline-note span{color:#7e9b6b}.count-box{min-width:66px;background:#edf2e5;border:1px solid #dfe8d4;border-radius:12px;padding:7px 10px;text-align:center;color:#607958}.count-box strong{display:block;font:800 1.05rem 'Manrope',sans-serif}.count-box span{font-size:.59rem}.table-toolbar{display:flex;align-items:center;justify-content:space-between;gap:12px;margin:-2px 0 13px}.search-box{display:flex;align-items:center;gap:8px;border:1px solid #e2e7db;border-radius:10px;background:#fffefb;padding:0 10px;max-width:310px;flex:1;color:#84937d}.search-box input{border:0;background:transparent;outline:0;min-width:0;width:100%;padding:10px 0;font-size:.75rem;color:var(--ink)}.search-box input:focus{box-shadow:none}.table-wrap{width:100%;overflow:auto;border:1px solid #e6eade;border-radius:12px;background:#fffefa}table{border-collapse:collapse;width:100%;font-size:.75rem}th,td{text-align:left;padding:13px 13px;border-bottom:1px solid #eef0e8;white-space:nowrap}th{background:#f4f5eb;color:#86917e;text-transform:uppercase;letter-spacing:.1em;font-size:.59rem;font-weight:800}tbody tr:last-child td{border-bottom:0}tbody tr:hover{background:#fafaf3}td{color:#586b55}.id-cell{display:inline-flex;align-items:center;justify-content:center;min-width:30px;padding:4px 7px;background:#edf2e6;color:#54714c;border-radius:7px;font-weight:800;font-size:.67rem}.person-cell{display:flex;align-items:center;gap:9px}.person-avatar{display:grid;place-items:center;width:29px;height:29px;background:#e3eadd;color:#55704f;border-radius:9px;font-weight:800;font-size:.68rem;flex:none}.person-name{font-weight:750;color:#3b533a}.person-sub{color:#9ba494;font-size:.62rem;margin-top:2px}.status-cell{color:#63855c;font-size:.68rem;font-weight:750}.align-right{text-align:right}.table-delete{border:1px solid #ecd9d1;background:#fff3ee;color:#a34b3f;border-radius:8px;padding:6px 9px;font-size:.66rem;font-weight:750}.table-delete:hover{background:#ffe4dc}.table-bottom{display:flex;align-items:center;justify-content:space-between;gap:10px;padding-top:12px;color:#9aa393;font-size:.63rem}.about-card{background:#edf1e5;position:relative;overflow:hidden}.about-leaf{font-size:1.8rem;color:#98ae7e;margin-bottom:9px}.about-card h2{font:800 1.12rem 'Manrope',sans-serif;letter-spacing:-.04em;margin:7px 0 9px;color:var(--forest);max-width:290px}.about-card p{font-size:.75rem;color:#71816b;line-height:1.8;margin:0;max-width:520px}.about-tags{display:flex;gap:7px;flex-wrap:wrap;margin-top:17px}.about-tags span{font-size:.62rem;font-weight:750;color:#58764f;background:#fbfcf5;border:1px solid #dae4d0;border-radius:7px;padding:5px 8px}.page-footer{display:flex;justify-content:space-between;gap:12px;flex-wrap:wrap;margin-top:26px;padding:16px 2px 0;border-top:1px solid #e0e5d9;color:#919b8b;font-size:.65rem}.page-footer strong{color:#58714f;font-size:.65rem;letter-spacing:.04em}.page-footer i{font-style:normal;color:#aabd93}.footer-leaf{color:#8ba876;margin-left:5px}.toast{position:fixed;z-index:99;right:22px;bottom:22px;max-width:min(420px,calc(100vw - 32px));padding:13px 16px;border-radius:12px;background:#1e4932;color:#fff;box-shadow:0 12px 35px #142c1c33;font-size:.78rem;line-height:1.55;opacity:0;transform:translateY(8px);pointer-events:none;transition:opacity .2s,transform .2s}.toast.show{opacity:1;transform:translateY(0)}
/* Registration prototype */
.registration-page{background:var(--cream)}.registration-header{height:77px;display:flex;align-items:center;justify-content:space-between;padding:0 clamp(17px,5vw,75px);background:var(--forest);color:#fff}.registration-header .brand-copy small{color:#bed0b5}.back-link{font-size:.75rem;color:#e6eddc;text-decoration:none;border:1px solid #ffffff42;padding:9px 12px;border-radius:10px}.back-link:hover{background:#ffffff13}.registration-hero{position:relative;overflow:hidden;background:linear-gradient(110deg,#1a442f,#426c42);padding:37px clamp(18px,7vw,100px) 42px;color:#fff}.reg-hero-copy{position:relative;z-index:2;max-width:760px}.registration-hero h1{margin:14px 0 10px;font-size:clamp(2.1rem,4vw,3.1rem)}.registration-hero p{max-width:630px;color:#d7e5cf;font-size:.85rem;line-height:1.8;margin:0}.reg-hero-leaf{position:absolute;right:10%;top:-62px;font:23rem/1 Georgia;color:#d0dfa519;transform:rotate(-20deg)}.registration-content{max-width:1240px;margin:auto;padding:27px 18px 45px}.registration-grid{display:grid;grid-template-columns:minmax(0,.95fr) minmax(0,1.05fr);gap:16px;align-items:start}.registration-form-card,.scan-steps-card{padding:24px}.registration-form-card form{margin-top:20px}.registration-form-card .field-label{margin-bottom:8px}.registration-form-card .btn-full{margin-top:11px}.enroll-result{display:flex;gap:10px;margin-top:16px;padding:13px;background:#f3f5e9;border:1px solid #e3e8d8;border-radius:12px}.result-icon{width:24px;height:24px;border-radius:50%;display:grid;place-items:center;background:#e0ead5;color:#587850;font-weight:800;flex:none}.enroll-result strong{font-size:.75rem;color:#4d6948}.enroll-result p{font-size:.7rem;color:#83907e;line-height:1.65;margin:3px 0 0}.scan-steps{display:grid;gap:10px}.scan-step{display:grid;grid-template-columns:35px minmax(0,1fr) auto;align-items:start;gap:11px;padding:14px 12px;border-radius:12px;background:#fafaf3;border:1px solid #e9ecdf}.step-number{width:32px;height:32px;border-radius:10px;display:grid;place-items:center;background:#e4ecd9;color:#55754d;font-size:.68rem;font-weight:800}.scan-step strong{font-size:.76rem;color:#496344}.scan-step p{font-size:.68rem;color:#84907e;line-height:1.65;margin:4px 0 0}.step-state{border-radius:999px;background:#eeefe6;color:#929988;padding:5px 7px;font-size:.56rem;white-space:nowrap}.step-state.active{background:#dfead3;color:#527747}.step-state.done{background:#e4efe1;color:#3c7548}.mock-device{display:flex;align-items:center;gap:10px;padding:13px;margin-top:15px;border:1px dashed #dce3d4;border-radius:13px}.mock-device-icon{width:36px;height:36px;background:#edf1e6;border-radius:11px;display:grid;place-items:center;color:#6a875d;font-size:1.1rem}.mock-device>div:nth-child(2){flex:1}.mock-device strong,.mock-device span{display:block}.mock-device strong{font-size:.73rem;color:#4b6346}.mock-device>div:nth-child(2) span{font-size:.64rem;color:#929a89;margin-top:3px}.device-offline{font-size:.61rem;color:#a07b63;white-space:nowrap}.device-offline i{width:6px;height:6px;border-radius:50%;background:#c5a083;display:inline-block;margin-right:4px}
@media(max-width:1200px){.app-shell{grid-template-columns:220px minmax(0,1fr)}.stats-grid{grid-template-columns:repeat(2,minmax(0,1fr))}.hero-art{width:38%;opacity:.82}.mapping-form{grid-template-columns:minmax(100px,.4fr) minmax(170px,1fr)}.map-button{grid-column:1/-1;justify-self:start}.map-button{min-width:180px}}
@media(max-width:900px){.app-shell{grid-template-columns:1fr}.sidebar{position:relative;height:auto;padding:14px 18px 12px;overflow:visible}.sidebar .brand{padding:0 2px 12px;border-bottom:0}.brand-logo{width:39px;height:39px;border-radius:12px}.nav-label,.sidebar-bottom{display:none}.side-nav{display:flex;overflow-x:auto;gap:4px;padding-bottom:2px}.nav-link{flex:0 0 auto;padding:9px 10px;font-size:.73rem}.nav-symbol{width:auto}.topbar{height:66px}.hero{min-height:300px}.content-grid{grid-template-columns:1fr}.registration-grid{grid-template-columns:1fr}}
@media(max-width:580px){.topbar{padding:0 14px}.topbar-title{font-size:.86rem}.eyebrow{font-size:.57rem}.topbar-right{gap:7px}.demo-badge{padding:7px 9px;font-size:.56rem}.avatar{width:30px;height:30px}.main-content{padding:16px 12px 28px}.hero{padding:25px 19px 51px;min-height:325px;border-radius:18px}.hero-copy{max-width:100%}.hero h1{font-size:2.08rem}.hero p{font-size:.79rem;max-width:390px}.hero-art{width:75%;right:-10%;opacity:.34}.hero-actions{display:grid;grid-template-columns:1fr;max-width:260px}.hero-actions .btn{width:100%}.hero-bottom{left:19px;right:19px;font-size:.49rem}.hero-bottom span:last-child{display:none}.section-block{margin-top:23px}.section-heading{align-items:flex-start}.section-heading h2{font-size:1.15rem}.section-heading p{font-size:.72rem}.date-pill{font-size:.6rem}.stats-grid{gap:8px}.stat-card{padding:13px;min-height:146px;border-radius:14px}.stat-icon{width:30px;height:30px}.status-mini{font-size:.46rem}.stat-label{font-size:.65rem;margin-top:11px}.stat-number{font-size:1.25rem}.stat-foot{font-size:.6rem}.time-number{font-size:1.4rem}.surface-card{padding:16px;border-radius:16px}.surface-heading h2{font-size:.98rem}.surface-heading p{font-size:.69rem}.heading-icon{width:33px;height:33px}.component-row{gap:7px}.component-name{font-size:.68rem}.pill{font-size:.56rem;padding:4px 6px}.mapping-form{grid-template-columns:1fr;gap:11px}.map-button{grid-column:auto;width:100%}.table-toolbar{align-items:stretch;flex-direction:column}.search-box{max-width:none}.table-toolbar .btn{align-self:flex-start}.table-bottom{font-size:.58rem}.page-footer{font-size:.6rem}.registration-header{height:66px;padding:0 13px;gap:10px}.registration-header .brand-copy strong{font-size:.7rem}.registration-header .brand-copy small{font-size:.53rem}.back-link{font-size:.65rem;padding:8px}.registration-hero{padding:28px 17px 32px}.registration-hero h1{font-size:2.15rem}.registration-hero p{font-size:.78rem}.reg-hero-leaf{right:-5%;opacity:.6}.registration-content{padding:15px 12px 30px}.registration-form-card,.scan-steps-card{padding:16px}.scan-step{grid-template-columns:31px minmax(0,1fr);gap:8px}.step-state{grid-column:2;justify-self:start}.mock-device{flex-wrap:wrap}.device-offline{margin-left:46px}}
@media(prefers-reduced-motion:reduce){html{scroll-behavior:auto}*,*::before,*::after{transition:none!important;animation:none!important}}

/* ===== Dashboard redesign: clean attendance app with a subtle nature palette ===== */
.dashboard-page{
  --forest:#214d35;--forest2:#326b45;--moss:#73956a;--leaf:#a9c78b;--sage:#e5eddf;--sage2:#f2f6ee;--cream:#f5f7f2;--paper:#ffffff;--ink:#24372a;--muted:#829084;--line:#e5ebe2;--sand:#f0f2e9;--rust:#a34335;--shadow:0 8px 26px rgba(28,59,38,.045);
  background:#f5f7f3;color:var(--ink);font-family:Inter,"Segoe UI",Arial,sans-serif
}
.dashboard-page body{background:#f5f7f3}
.dashboard-page .app-shell{grid-template-columns:232px minmax(0,1fr);gap:0}
.dashboard-page .sidebar{background:#eef3e9;color:#284331;border-right:1px solid #e0e8dc;padding:24px 15px 18px}
.dashboard-page .sidebar .brand{padding:0 6px 23px;border-bottom:1px solid #dce6d7}
.dashboard-page .brand-logo{width:42px;height:42px;border-radius:12px;background:#fff;border:1px solid #e2e9dd}
.dashboard-page .brand-copy strong{font-family:Inter,"Segoe UI",Arial,sans-serif;font-size:.82rem;letter-spacing:.035em;color:#234731}
.dashboard-page .brand-copy small{font-size:.58rem;letter-spacing:.12em;color:#7b9276}
.dashboard-page .nav-label{font-size:.6rem;letter-spacing:.13em;color:#90a38a;padding:23px 13px 9px}
.dashboard-page .side-nav{gap:4px}
.dashboard-page .nav-link{color:#627866;border-radius:9px;font-size:.78rem;padding:11px 12px;font-weight:650;transition:background .18s,color .18s}
.dashboard-page .nav-link:hover{background:#e2ebdd;color:#315b3b}
.dashboard-page .nav-link.active{background:#dce9d6;color:#285337;box-shadow:inset 3px 0 #56875a}
.dashboard-page .nav-symbol{font-size:1rem;color:#7b9a70;width:20px}
.dashboard-page .sidebar-device{margin:30px 3px 18px;padding:13px 12px 12px;border:1px solid #dae5d5;background:linear-gradient(145deg,#f9fbf6,#e8f0e3);border-radius:13px}
.dashboard-page .device-top{display:flex;align-items:center;gap:7px;color:#416448;font-size:.65rem;font-weight:800;letter-spacing:.05em}
.dashboard-page .device-led{width:7px;height:7px;background:#d0a76b;border-radius:50%;box-shadow:0 0 0 4px #d0a76b20}
.dashboard-page .device-state{margin-left:auto;font-size:.53rem;letter-spacing:.08em;color:#81927b}
.dashboard-page .device-name{margin-top:13px;font-size:.77rem;font-weight:800;color:#2e4d34}
.dashboard-page .device-caption{margin-top:2px;font-size:.63rem;color:#879787}
.dashboard-page .device-line{height:4px;background:#dce7d7;border-radius:20px;margin:12px 0 9px;overflow:hidden}
.dashboard-page .device-line span{display:block;width:39%;height:100%;background:#88a77b;border-radius:20px}
.dashboard-page .device-foot{display:flex;justify-content:space-between;gap:7px;color:#8a9888;font-size:.54rem}
.dashboard-page .sidebar-bottom{margin-top:auto}
.dashboard-page .local-mark{display:flex;align-items:center;gap:7px;color:#486849;font-size:.66rem;font-weight:750;background:#e0)rawliteral"
R"rawliteral(eadb;border:1px solid #d7e4d1;border-radius:9px;padding:9px 10px}
.dashboard-page .local-pulse{width:7px;height:7px;background:#8ba878;border-radius:50%;box-shadow:0 0 0 4px #8ba87822}
.dashboard-page .sidebar-bottom p{color:#96a395;font-size:.63rem;margin:8px 9px 0;line-height:1.55}
.dashboard-page .workspace{min-width:0}
.dashboard-page .topbar{height:74px;padding:0 clamp(20px,3vw,42px);background:#fff;border-bottom:1px solid #e8ede5}
.dashboard-page .eyebrow,.dashboard-page .section-overline{font-size:.6rem;font-weight:800;letter-spacing:.14em;color:#8b9c87}
.dashboard-page .topbar-title{font:750 1.02rem/1.25 Inter,"Segoe UI",Arial,sans-serif;color:#234731;margin-top:4px;letter-spacing:-.025em}
.dashboard-page .topbar-right{gap:12px}
.dashboard-page .connection-pill{display:flex;align-items:center;gap:7px;border:1px solid #e1e9dc;background:#f5f8f1;color:#6a8266;border-radius:8px;padding:8px 10px;font-size:.64rem;font-weight:750}
.dashboard-page .badge-dot{width:6px;height:6px;background:#a4b98b;border-radius:50%}
.dashboard-page .avatar{width:33px;height:33px;border-radius:10px;background:#dfead8;color:#335d3d;font-size:.72rem}
.dashboard-page .main-content{max-width:1640px;padding:25px clamp(20px,3vw,42px) 34px}
.dashboard-page .hero{min-height:246px;border-radius:17px;padding:29px 31px 43px;background:linear-gradient(112deg,#234e35 0%,#2c633e 65%,#427649 100%);box-shadow:0 12px 28px rgba(28,68,40,.11)}
.dashboard-page .hero:before{content:"";position:absolute;z-index:-1;right:-90px;top:-230px;width:470px;height:470px;border:1px solid #ffffff1e;border-radius:50%;box-shadow:0 0 0 35px #ffffff08,0 0 0 75px #ffffff06}
.dashboard-page .hero-copy{max-width:540px}
.dashboard-page .hero-kicker{gap:8px;font-size:.58rem;letter-spacing:.15em;color:#d6e5cf}
.dashboard-page .kicker-leaf{width:20px;height:20px;border-radius:6px;background:#ffffff15;font-size:.82rem}
.dashboard-page .hero h1{font:750 clamp(2rem,3.1vw,2.8rem)/1.08 Inter,"Segoe UI",Arial,sans-serif;letter-spacing:-.06em;margin:15px 0 10px;max-width:510px}
.dashboard-page .hero h1 em{font-style:normal;color:#c6dca8}
.dashboard-page .hero p{font-size:.8rem;line-height:1.65;color:#dbe8d6;max-width:440px;margin:0}
.dashboard-page .hero-actions{gap:9px;margin-top:18px}
.dashboard-page .btn{min-height:38px;border-radius:9px;padding:9px 13px;font-size:.7rem;font-weight:750;transition:transform .16s,background .16s}
.dashboard-page .btn-cream{background:#f4f6e9;color:#2b5035}
.dashboard-page .btn-cream:hover{background:#fff}
.dashboard-page .btn-outline{background:#ffffff0b;color:#f5f8f0;border-color:#ffffff40}
.dashboard-page .btn-outline:hover{background:#ffffff19}
.dashboard-page .btn-primary{background:#2c5b39;color:#fff;border-color:#2c5b39}
.dashboard-page .btn-primary:hover{background:#3c754a}
.dashboard-page .btn-secondary{background:#f7f9f4;color:#567153;border-color:#e0e8dc}
.dashboard-page .btn-secondary:hover{background:#edf4e8}
.dashboard-page .btn-danger{background:#fff0eb;color:var(--rust);border-color:#f0d8d0}
.dashboard-page .btn-full{width:100%;margin-top:11px}
.dashboard-page .hero-botanical{position:absolute;inset:0 0 0 auto;width:43%;pointer-events:none;overflow:hidden;opacity:.95}
.dashboard-page .botanical-orb{position:absolute;width:195px;height:195px;right:20%;top:20px;border-radius:50%;background:#c0d7a018;border:1px solid #cbd9b326}
.dashboard-page .botanical-ring{position:absolute;width:285px;height:285px;right:7%;top:-25px;border:1px solid #ffffff18;border-radius:50%;box-shadow:0 0 0 23px #ffffff05}
.dashboard-page .botanical-stem{position:absolute;height:255px;width:2px;background:#d7e6c178;right:38%;bottom:-37px;transform:rotate(23deg);border-radius:5px}
.dashboard-page .hero-botanical .leaf{position:absolute;display:block;width:86px;height:42px;background:linear-gradient(120deg,#c5d99a,#719a69);border-radius:95% 4% 90% 5%;opacity:.7;transform-origin:right bottom;box-shadow:inset 0 0 0 1px #e2e9c32a}
.dashboard-page .hero-botanical .leaf-one{right:38%;top:63px;transform:rotate(-25deg)}
.dashboard-page .hero-botanical .leaf-two{right:17%;top:108px;transform:rotate(42deg) scale(.85);background:linear-gradient(120deg,#a9cb8a,#648b58)}
.dashboard-page .hero-botanical .leaf-three{right:37%;top:150px;transform:rotate(14deg) scale(1.05);background:linear-gradient(120deg,#9cbe7d,#5c8755)}
.dashboard-page .hero-botanical .leaf-four{right:17%;top:194px;transform:rotate(53deg) scale(.75);background:linear-gradient(120deg,#d3e1a9,#7ca16a)}
.dashboard-page .hero-bottom{left:31px;right:31px;height:30px;border-top:1px solid #ffffff23;color:#c2d7bd;font-size:.52rem;letter-spacing:.12em}
.dashboard-page .hero-bottom span:last-child{letter-spacing:.03em;text-transform:none;font-size:.62rem}
.dashboard-page .metric-grid{display:grid;grid-template-columns:repeat(4,minmax(0,1fr));gap:13px;margin-top:19px}
.dashboard-page .metric-card{min-width:0;position:relative;overflow:hidden;background:#fff;border:1px solid #e5ebe2;border-radius:14px;padding:15px 16px 14px;min-height:143px;box-shadow:0 4px 14px #183a2005}
.dashboard-page .metric-card:after{content:"";position:absolute;right:-27px;bottom:-39px;width:87px;height:87px;border-radius:50%;border:12px solid #eff4eb}
.dashboard-page .metric-featured{background:#fbfdf9}
.dashboard-page .metric-featured:before{content:"";position:absolute;top:0;left:0;right:0;height:3px;background:#719b68}
.dashboard-page .metric-top{display:flex;align-items:center;justify-content:space-between;gap:8px}
.dashboard-page .metric-icon{width:32px;height:32px;border-radius:9px;background:#e4eedf;color:#4b7549;display:grid;place-items:center;font-size:1rem}
.dashboard-page .metric-icon.icon-light{background:#f0f4ed;color:#75916c}
.dashboard-page .metric-tag{font-size:.5rem;letter-spacing:.1em;color:#9aaa96;font-weight:850}
.dashboard-page .metric-label{margin-top:13px;font-size:.67rem;font-weight:650;color:#78897a}
.dashboard-page .metric-value{font:750 1.38rem/1.2 Inter,"Segoe UI",Arial,sans-serif;letter-spacing:-.045em;color:#284d32;margin-top:3px;overflow-wrap:anywhere}
.dashboard-page .metric-value small{font:650 .74rem Inter,"Segoe UI",Arial,sans-serif;color:#98a597;letter-spacing:0}
.dashboard-page .metric-check{font-size:.7rem;color:#689466}
.dashboard-page .metric-bottom{position:relative;z-index:1;display:flex;align-items:center;gap:6px;margin-top:7px;color:#98a394;font-size:.59rem}
.dashboard-page .metric-dot{width:6px;height:6px;border-radius:50%;background:#91b482}
.dashboard-page .section-block{margin-top:20px}
.dashboard-page .dashboard-grid{display:grid;grid-template-columns:minmax(0,1.3fr) minmax(270px,.7fr);gap:14px;align-items:stretch}
.dashboard-page .surface-card{min-width:0;background:#fff;border:1px solid #e4ebe1;border-radius:15px;padding:20px;box-shadow:0 4px 18px rgba(35,66,38,.025)}
.dashboard-page .surface-heading{display:flex;align-items:flex-start;justify-content:space-between;gap:13px;margin-bottom:16px}
.dashboard-page .surface-heading h2,.dashboard-page .section-heading h2{font:750 1.05rem/1.3 Inter,"Segoe UI",Arial,sans-serif;letter-spacing:-.035em;color:#2c4d33;margin:5px 0 0}
.dashboard-page .surface-heading p{font-size:.7rem;color:#89978a;margin:6px 0 0;line-height:1.5}
.dashboard-page .section-chip{display:flex;align-items:center;gap:6px;padding:6px 8px;border-radius:7px;background:#f1f6ed;color:#7c9475;font-size:.58rem;font-weight:750;white-space:nowrap}
.dashboard-page .heading-icon{width:34px;height:34px;border-radius:10px;background:#e8f0e2;display:grid;place-items:center;color:#547e4d;font-size:1rem;flex:none}
.dashboard-page .component-list{display:grid;gap:0}
.dashboard-page .component-row{display:flex;align-items:center;gap:10px;padding:11px 0;border-bottom:1px solid #edf1ea}
.dashboard-page .component-row:last-child{border-bottom:0}
.dashboard-page .component-icon{display:grid;place-items:center;width:30px;height:30px;border-radius:9px;background:#f0f5ed;color:#66875e;flex:none;font-size:.9rem}
.dashboard-page .component-name{flex:1;font-size:.73rem;font-weight:680;color:#4e6650}
.dashboard-page .pill{display:inline-flex;align-items:center;border-radius:6px;padding:5px 8px;font-size:.57rem;font-weight:750;white-space:nowrap}
.dashboard-page .pill-demo{background:#eff5ea;color:#77916c;border:1px solid #e5eee0}
.dashboard-page .message-box{display:flex;align-items:flex-start;gap:9px;background:#f7f9f4;border:1px solid #e9eee5;border-radius:10px;padding:10px;margin-top:12px}
.dashboard-page .message-mark{display:grid;place-items:center;width:19px;height:19px;border-radius:6px;background:#e6eee0;color:#6e8a64;font:800 .7rem Georgia;flex:none}
.dashboard-page .message-box strong{font-size:.68rem;color:#5b7556}
.dashboard-page .message-box p{font-size:.64rem;line-height:1.5;color:#8e9b8a;margin:2px 0 0}
.dashboard-page .clock-panel{background:linear-gradient(160deg,#fff 65%,#f5f8f0);position:relative;overflow:hidden}
.dashboard-page .clock-panel:after{content:"";position:absolute;width:150px;height:150px;border-radius:50%;border:1px solid #e7eee2;right:-70px;top:30px;box-shadow:0 0 0 17px #f6f9f3,0 0 0 35px #fbfcf9;pointer-events:none}
.dashboard-page .clock-panel-head{display:flex;justify-content:space-between;position:relative;z-index:1;margin-bottom:24px}
.dashboard-page .clock-panel h2{font:750 1.05rem Inter,"Segoe UI",Arial,sans-serif;color:#2c4d33;letter-spacing:-.035em;margin:5px 0 0}
.dashboard-page .clock-decor{display:grid;place-items:center;width:34px;height:34px;border-radius:10px;background:#e8f0e2;color:#66885b;font-size:1.1rem}
.dashboard-page .clock-panel .field-label,.dashboard-page .settings-panel .field-label{display:block;position:relative;z-index:1;margin-bottom:7px}
.dashboard-page .field-label{display:block;font-size:.68rem;color:#627661;font-weight:750;margin-bottom:7px}
.dashboard-page .field-label span{font-weight:600;color:#9ba697;margin-left:4px;font-size:.61rem}
.dashboard-page .input{width:100%;min-width:0;border:1px solid #e1e9dd;background:#fcfdfb;color:#3d5540;border-radius:9px;padding:11px 12px;outline:0;font-size:.73rem;transition:border-color .18s,box-shadow .18s}
.dashboard-page .input:focus{border-color:#9ab98d;box-shadow:0 0 0 3px #9ab98d20}
.dashboard-page .helper-text{font-size:.62rem;color:#9aa697;line-height:1.55;margin:9px 0 0;position:relative;z-index:1}
.dashboard-page .mapping-panel .surface-heading{margin-bottom:15px}
.dashboard-page .mapping-form{display:grid;grid-template-columns:minmax(135px,.38fr) minmax(190px,1fr) auto;gap:12px;align-items:end}
.dashboard-page .form-field{min-width:0}
.dashboard-page .map-button{white-space:nowrap}
.dashboard-page .inline-note{display:flex;align-items:center;gap:7px;margin-top:14px;padding-top:11px;border-top:1px solid #edf1e9;color:#94a091;font-size:.63rem}
.dashboard-page .inline-note span{display:grid;place-items:center;background:#edf3e8;color:#77966d;width:17px;height:17px;border-radius:5px;font-size:.62rem}
.dashboard-page .count-box{min-width:60px;background:#edf4e8;border:1px solid #e0ebd9;border-radius:9px;padding:6px 9px;text-align:center;color:#58764e}
.dashboard-page .count-box strong{display:block;font:750 1rem Inter,"Segoe UI",Arial,sans-serif}
.dashboard-page .count-box span{font-size:.54rem}
.dashboard-page .table-toolbar{display:flex;align-items:center;justify-content:space-between;gap:12px;margin:-1px 0 12px}
.dashboard-page .search-box{display:flex;align-items:center;gap:8px;border:1px solid #e3eade;border-radius:9px;background:#fbfcfa;padding:0 10px;max-width:310px;flex:1;color:#869884}
.dashboard-page .search-box input{border:0;background:transparent;outline:0;min-width:0;width:100%;padding:9px 0;font-size:.7rem;color:#314a35}
.dashboard-page .table-wrap{width:100%;overflow:auto;border:1px solid #e8eee5;border-radius:10px;background:#fff}
.dashboard-page table{border-collapse:collapse;width:100%;font-size:.71rem}
.dashboard-page th,.dashboard-page td{text-align:left;padding:11px 12px;border-bottom:1px solid #eef2eb;white-space:nowrap}
.dashboard-page th{background:#f6f8f4;color:#92a08e;text-transform:uppercase;letter-spacing:.09em;font-size:.54rem;font-weight:850}
.dashboard-page tbody tr:last-child td{border-bottom:0}
.dashboard-page tbody tr:hover{background:#fbfcfa}
.dashboard-page td{color:#5f735f}
.dashboard-page .id-cell{display:inline-flex;align-items:center;justify-content:center;min-width:29px;padding:4px 6px;background:#edf4e9;color:#55764e;border-radius:6px;font-weight:800;font-size:.63rem}
.dashboard-page .person-cell{display:flex;align-items:center;gap:8px}
.dashboard-page .person-avatar{display:grid;place-items:center;width:28px;height:28px;background:#e7efe2;color:#54764f;border-radius:8px;font-weight:800;font-size:.62rem;flex:none}
.dashboard-page .person-name{font-weight:700;color:#3f5941}
.dashboard-page .person-sub{color:#a0aa9b;font-size:.58rem;margin-top:2px}
.dashboard-page .status-cell{color:#719167;font-size:.63rem;font-weight:750}
.dashboard-page .align-right{text-align:right}
.dashboard-page .table-delete{border:1px solid #f0ded7;background:#fff7f3;color:#a56c5c;border-radius:7px;padding:5px 8px;font-size:.62rem;font-weight:750}
.dashboard-page .table-delete:hover{background:#ffebe5}
.dashboard-page .table-bottom{display:flex;align-items:center;justify-content:space-between;gap:10px;padding-top:10px;color:#9ca797;font-size:.59rem}
.dashboard-page .settings-grid{display:grid;grid-template-columns:minmax(0,1fr) minmax(0,1fr);gap:14px;align-items:stretch}
.dashboard-page .settings-panel form{display:grid;grid-template-columns:1fr 1fr;gap:10px 12px}
.dashboard-page .settings-panel form .btn-full{grid-column:1/-1;margin-top:0}
.dashboard-page .settings-panel .helper-text{margin-top:10px}
.dashboard-page .about-card{position:relative;overflow:hidden;background:#eef4e9;border-color:#e2eadc;padding:22px}
.dashboard-page .about-card h2{font:750 1.13rem Inter,"Segoe UI",Arial,sans-serif;letter-spacing:-.04em;margin:6px 0 7px;color:#2c4d33;max-width:290px}
.dashboard-page .about-card p{font-size:.72rem;color:#7c9079;line-height:1.65;margin:0;max-width:400px;position:relative;z-index:1}
.dashboard-page .about-graphic{position:absolute;right:15px;top:5px;width:120px;height:120px;opacity:.5}
.dashboard-page .about-graphic:before{content:"";position:absolute;right:33px;top:22px;width:2px;height:100px;background:#a2bd91;transform:rotate(30deg)}
.dashboard-page .about-graphic span{position:absolute;display:block;width:45px;height:25px;background:#adc99b;border-radius:100% 0 100% 0}
.dashboard-page .about-graphic span:nth-child(1){right:40px;top:25px;transform:rotate(-25deg)}
.dashboard-page .about-graphic span:nth-child(2){right:5px;top:52px;transform:rotate(35deg)}
.dashboard-page .about-graphic span:nth-child(3){right:40px;top:77px;transform:rotate(-7deg)}
.dashboard-page .about-tags{display:flex;gap:6px;flex-wrap:wrap;margin-top:14px;position:relative;z-index:1}
.dashboard-page .about-tags span{font-size:.57rem;font-weight:750;color:#62805b;background:#fbfdf8;border:1px solid #dfe9d9;border-radius:6px;padding:4px 7px}
.dashboard-page .page-footer{display:flex;justify-content:space-between;gap:12px;flex-wrap:wrap;margin-top:23px;padding:14px 2px 0;border-top:1px solid #e1e9de;color:#9ba697;font-size:.6rem}
.dashboard-page .page-footer strong{color:#688262;font-size:.61rem;letter-spacing:.05em}
.dashboard-page .page-footer i{font-style:normal;color:#acbea0}
.dashboard-page .toast{background:#244e34;font-size:.73rem}

/* Keep the registration screen consistent and concise. */
.registration-page{background:#f5f7f3}
.registration-page .registration-header{background:#eef3e9;color:#284331;border-bottom:1px solid #e0e8dc}
.registration-page .registration-header .brand-copy strong{color:#234731}
.registration-page .registration-header .brand-copy small{color:#7b9276}
.registration-page .back-link{color:#517151;border-color:#d8e4d2;border-radius:8px}
.registration-page .back-link:hover{background:#e2ebdd}
.registration-page .registration-hero{background:linear-gradient(112deg,#234e35 0%,#2c633e 65%,#427649 100%);padding-top:29px;padding-bottom:31px}
.registration-page .registration-hero h1{font-size:clamp(1.9rem,3.2vw,2.55rem);margin:12px 0 8px}
.registration-page .registration-hero p{font-size:.78rem;line-height:1.6;max-width:530px}
.registration-page .reg-hero-leaf{font-size:19rem;color:#d0dfa512}
.registration-page .registration-content{max-width:1250px;padding-top:22px}
.registration-page .surface-card{border-radius:15px;border-color:#e4ebe1;box-shadow:0 4px 18px rgba(35,66,38,.025)}
.registration-page .surface-heading h2{font-size:1.03rem}
.registration-page .surface-heading p{font-size:.7rem}
.registration-page .registration-form-card,.registration-page .scan-steps-card{padding:21px}
.registration-page .registration-form-card .btn-full{margin-top:10px}
.registration-page .scan-step{background:#f8faf6;border-color:#e7eee3;border-radius:10px}
.registration-page .mock-device{border-color:#dce7d7;border-radius:10px}
.registration-page .page-footer{border-color:#e1e9de}

@media(max-width:1150px){
 .dashboard-page .app-shell{grid-template-columns:212px minmax(0,1fr)}
 .dashboard-page .metric-grid{grid-template-columns:repeat(2,minmax(0,1fr))}
 .dashboard-page .hero-botanical{width:39%;opacity:.7}
 .dashboard-page .mapping-form{grid-template-columns:minmax(110px,.42fr) minmax(160px,1fr)}
 .dashboard-page .map-button{grid-column:1/-1;justify-self:start}
}
@media(max-width:900px){
 .dashboard-page .app-shell{grid-template-columns:minmax(0,1fr)}
 .dashboard-page .sidebar{position:relative;height:auto;padding:13px 17px 10px;overflow:visible}
 .dashboard-page .sidebar .brand{padding:0 3px 10px;border-bottom:0}
 .dashboard-page .nav-label,.dashboard-page .sidebar-bottom,.dashboard-page .sidebar-device{display:none}
 .dashboard-page .side-nav{display:flex;overflow-x:auto;gap:4px;padding:0 0 2px}
 .dashboard-page .nav-link{flex:0 0 auto;padding:8px 10px;font-size:.7rem}
 .dashboard-page .nav-symbol{width:auto}
 .dashboard-page .topbar{height:64px}
 .dashboard-page .dashboard-grid{grid-template-columns:minmax(0,1fr)}
 .dashboard-page .settings-grid{grid-template-columns:1fr 1fr}
 .registration-page .registration-grid{grid-template-columns:1fr}
}
@media(max-width:600px){
 .dashboard-page .topbar{padding:0 14px}
 .dashboard-page .topbar-title{font-size:.9rem}
 .dashboard-page .eyebrow{font-size:.53rem}
 .dashboard-page .connection-pill{font-size:.57rem;padding:7px 8px}
 .dashboard-page .avatar{width:29px;height:29px}
 .dashboard-page .main-content{padding:15px 12px 26px}
 .dashboard-page .hero{padding:23px 18px 44px;min-height:276px;border-radius:14px}
 .dashboard-page .hero h1{font-size:2rem;max-width:100%}
 .dashboard-page .hero p{font-size:.74rem;max-width:300px}
 .dashboard-page .hero-botanical{width:64%;right:-16%;opacity:.42}
 .dashboard-page .hero-actions{display:flex;gap:7px;max-width:100%}
 .dashboard-page .hero-actions .btn{font-size:.65rem;padding:9px 10px}
 .dashboard-page .hero-bottom{left:18px;right:18px;font-size:.47rem}
 .dashboard-page .hero-bottom span:last-child{font-size:.56rem}
 .dashboard-page .metric-grid{gap:8px;margin-top:12px}
 .dashboard-page .metric-card{padding:12px;min-height:132px;border-radius:11px}
 .dashboard-page .metric-icon{width:29px;height:29px}
 .dashboard-page .metric-tag{font-size:.45rem}
 .dashboard-page .metric-label{font-size:.62rem;margin-top:10px}
 .dashboard-page .metric-value{font-size:1.18rem}
 .dashboard-page .metric-value small{font-size:.68rem}
 .dashboard-page .metric-bottom{font-size:.54rem}
 .dashboard-page .section-block{margin-top:14px}
 .dashboard-page .surface-card{padding:15px;border-radius:12px}
 .dashboard-page .surface-heading h2{font-size:.96rem}
 .dashboard-page .surface-heading p{font-size:.65rem}
 .dashboard-page .component-name{font-size:.67rem}
 .dashboard-page .mapping-form{grid-template-columns:1fr;gap:10px}
 .dashboard-page .map-button{grid-column:auto;width:100%}
 .dashboard-page .table-toolbar{align-items:stretch;flex-direction:column}
 .dashboard-page .search-box{max-width:none}
 .dashboard-page .table-toolbar .btn{align-self:flex-start}
 .dashboard-page .table-bottom{font-size:.55rem}
 .dashboard-page .settings-grid{grid-template-columns:1fr}
 .dashboard-page .settings-panel form{grid-template-columns:1fr}
 .dashboard-page .settings-panel form .btn-full{grid-column:auto}
 .dashboard-page .page-footer{font-size:.55rem}
 .registration-page .registration-header{height:65px;padding:0 13px;gap:10px}
 .registration-page .registration-header .brand-copy strong{font-size:.7rem}
 .registration-page .registration-header .brand-copy small{font-size:.53rem}
 .registration-page .back-link{font-size:.62rem;padding:8px}
 .registration-page .registration-hero{padding:25px 17px 28px}
 .registration-page .registration-hero h1{font-size:2rem}
 .registration-page .registration-content{padding:14px 12px 28px}
 .registration-page .registration-form-card,.registration-page .scan-steps-card{padding:15px}
}

/* State styles for live ESP32 data */
.dashboard-page .badge-dot.is-online,.dashboard-page .device-led.is-online{background:#5b9e61;box-shadow:0 0 0 4px #5b9e6122}
.dashboard-page .badge-dot.is-offline,.dashboard-page .device-led.is-offline{background:#cf6656;box-shadow:0 0 0 4px #cf665622}
.dashboard-page .pill-live-ok{background:#e8f4e3;color:#397346;border:1px solid #d3e6c9}
.dashboard-page .pill-live-bad{background:#fff0ec;color:#a84336;border:1px solid #efd5ce}
.dashboard-page .pill-live-neutral{background:#f0f1e9;color:#7c8677;border:1px solid #e3e6da}
.dashboard-page .message-box.is-ok{background:#edf6e8;border-color:#d6e8cc}
.dashboard-page .message-box.is-bad{background:#fff0ec;border-color:#efd5ce}
.dashboard-page .message-box.is-bad .message-mark{background:#f6dcd5;color:#a84336}
.dashboard-page .message-box.is-ok .message-mark{background:#dcebd3;color:#397346}
.dashboard-page .component-row .pill{max-width:135px;overflow:hidden;text-overflow:ellipsis}
.registration-page .step-state.active{background:#dfead3;color:#527747}
.registration-page .step-state.done{background:#e4efe1;color:#3c7548}
.registration-page .enroll-result.is-bad{background:#fff0ec;border-color:#efd5ce}
.registration-page .enroll-result.is-ok{background:#edf6e8;border-color:#d6e8cc}
.registration-page .device-online{color:#397346}
.registration-device-pills{display:flex;flex-wrap:wrap;gap:7px;margin-top:13px}
.registration-device-pills .pill{border-radius:999px;padding:6px 9px;font-size:.62rem;font-weight:750;background:#f0f1e9;color:#7c8677;border:1px solid #e3e6da}
.registration-device-pills .pill-live-ok{background:#e8f4e3;color:#397346;border-color:#d3e6c9}
.registration-device-pills .pill-live-bad{background:#fff0ec;color:#a84336;border-color:#efd5ce}
.registration-page .reg-status-message{margin-top:12px}

</style>
</head>
<body data-page="registration" class="registration-page">
  <header class="registration-header">
    <a class="brand" href="/"><span class="brand-logo"><img src="/logo.png" alt="Logo perusahaan"></span><span class="brand-copy"><strong>ABSENSI IOT</strong><small>SMART ATTENDANCE</small></span></a>
    <a class="back-link" href="/">← Dashboard</a>
  </header>
  <section class="registration-hero">
    <div class="reg-hero-copy"><div class="hero-kicker"><span class="kicker-leaf">✳</span> MANAJEMEN PENGGUNA</div><h1>Pendaftaran fingerprint</h1><p>Daftarkan pengguna ke sensor R558-S. Ikuti instruksi sensor hingga template berhasil tersimpan dan nama tercatat pada MicroSD.</p></div>
    <div class="reg-hero-leaf" aria-hidden="true">❧</div>
  </section>
  <main class="registration-content">
    <div class="registration-grid">
      <section class="surface-card registration-form-card">
        <div class="surface-heading"><div><div class="section-overline">DATA PENGGUNA</div><h2>Pengguna baru</h2></div><div class="heading-icon">♙</div></div>
        <form id="enrollForm"><label class="field-label" for="enrollName">Nama lengkap</label><input class="input" id="enrollNam)rawliteral"
R"rawliteral(e" maxlength="32" placeholder="Masukkan nama" autocomplete="name" required><button class="btn btn-primary btn-full" id="startEnroll" type="submit">Mulai pendaftaran <span>→</span></button><button class="btn btn-danger btn-full" id="cancelEnroll" type="button" disabled>Batalkan</button></form>
        <p class="helper-text" id="timer"></p>
        <div class="enroll-result" id="enrollResult"><span class="result-icon">i</span><div><strong>Menunggu input</strong><p>Isi nama untuk memulai.</p></div></div>
        <p class="helper-text">Halaman ini mengirim perintah pendaftaran ke ESP32 saat tombol konfigurasi dan Wi-Fi aktif.</p>
      </section>
      <section class="surface-card scan-steps-card">
        <div class="surface-heading"><div><div class="section-overline">PROSES SENSOR</div><h2>Alur pemindaian</h2></div><div class="heading-icon sand-icon">◎</div></div>
        <div class="scan-steps">
          <div class="scan-step"><span class="step-number">01</span><div><strong>Tempelkan jari</strong><p>Pemindaian pertama.</p></div><span class="step-state" id="step1">Menunggu</span></div>
          <div class="scan-step"><span class="step-number">02</span><div><strong>Angkat jari</strong><p>Ikuti instruksi sensor.</p></div><span class="step-state" id="step2">Menunggu</span></div>
          <div class="scan-step"><span class="step-number">03</span><div><strong>Ulangi pemindaian</strong><p>Gunakan jari yang sama.</p></div><span class="step-state" id="step3">Menunggu</span></div>
        </div>
        <div class="mock-device"><div class="mock-device-icon">◎</div><div><strong>Fingerprint R558-S</strong><span>Sensor yang terpasang pada ESP32</span></div><span class="device-offline" id="enrollmentDeviceState"><i></i> Memeriksa</span></div>
        <div class="registration-device-pills" id="devicePills"></div>
        <div class="enroll-result reg-status-message" id="message"><span class="result-icon">i</span><div><strong>Status perangkat</strong><p>Menghubungkan ke ESP32…</p></div></div>
      </section>
    </div>
    <footer class="page-footer"><span><strong>ABSENSI IOT</strong> <i>·</i> Pendaftaran perangkat</span><span>Terhubung melalui ESP32 saat Wi-Fi konfigurasi aktif</span></footer>
  </main>
  <div class="toast" id="toast" role="status" aria-live="polite"></div>
  <script>
(() => {
  'use strict';
  const $ = id => document.getElementById(id);
  let previousBusy = false;
  let toastTimer = null;
  function toast(message) { const el = $('toast'); if (!el) return; el.textContent = message; el.classList.add('show'); clearTimeout(toastTimer); toastTimer = setTimeout(() => el.classList.remove('show'), 3300); }
  async function request(url, options = {}) { const response = await fetch(url, {...options, cache:'no-store'}); const text = await response.text(); if (!response.ok) throw new Error(text || `HTTP ${response.status}`); return text; }
  async function getStatus() { const response = await fetch('/api/status', {cache:'no-store'}); if (!response.ok) throw new Error(await response.text() || `HTTP ${response.status}`); return response.json(); }
  function setResult(title, detail, state = '') {
    const box = $('enrollResult'); if (!box) return; box.className = 'enroll-result' + (state ? ' is-' + state : ''); box.replaceChildren();
    const icon = document.createElement('span'); icon.className = 'result-icon'; icon.textContent = state === 'ok' ? '✓' : state === 'bad' ? '!' : 'i';
    const wrap = document.createElement('div'); const strong = document.createElement('strong'); strong.textContent = title; const p = document.createElement('p'); p.textContent = detail; wrap.append(strong, p); box.append(icon, wrap);
  }
  function setStep(index, state) {
    const el = $(`step${index}`); if (!el) return; el.textContent = state === 'done' ? 'Selesai' : state === 'active' ? 'Berlangsung' : 'Menunggu';
    el.classList.toggle('active', state === 'active'); el.classList.toggle('done', state === 'done');
  }
  function updateProgress(message, busy) {
    [1,2,3].forEach(i => setStep(i, 'waiting'));
    if (!busy) return;
    const text = String(message || '').toLowerCase();
    if (text.includes('angkat jari')) { setStep(1,'done'); setStep(2,'done'); setStep(3,'active'); }
    else if (text.includes('pemindaian pertama')) { setStep(1,'done'); setStep(2,'active'); }
    else if (text.includes('pemindaian kedua') || text.includes('menggabungkan') || text.includes('template terbentuk')) { [1,2,3].forEach(i => setStep(i,'done')); }
    else setStep(1,'active');
  }
  function renderDevicePills(s) {
    const host = $('devicePills'); if (!host) return; host.replaceChildren();
    [['Fingerprint',s.fingerprint],['MicroSD',s.sd],['RTC',s.rtc],['Audio',s.audio],['Wi-Fi',s.wifi]].forEach(([label,value]) => {
      const pill = document.createElement('span');
      const normalized = String(value || '').toUpperCase();
      pill.className = 'pill ' + (['OK','SIAP','AKTIF'].includes(normalized) ? 'pill-live-ok' : (['GAGAL','TIDAK ADA'].includes(normalized) ? 'pill-live-bad' : 'pill-demo'));
      pill.textContent = `${label}: ${value || '—'}`; host.appendChild(pill);
    });
    const online = $('enrollmentDeviceState'); if (online) { online.textContent = 'Terhubung'; online.classList.add('device-online'); }
  }
  async function pollStatus() {
    try {
      const s = await getStatus();
      const message = s.enrollBusy ? (s.enrollment || s.message || 'Ikuti instruksi sensor.') : (s.message || 'Status diterima dari ESP32.');
      if (s.enrollBusy) setResult(`Pendaftaran ID ${s.enrollId} berjalan`, message, '');
      else if (previousBusy || !$('enrollResult').dataset.initialized) {
        const success = /berhasil|selesai/i.test(message) && !/gagal|dibatalkan|habis waktu/i.test(message);
        setResult(s.enrollBusy ? 'Pendaftaran berlangsung' : (success ? 'Status perangkat' : 'Pesan perangkat'), message, success ? 'ok' : (/gagal|dibatalkan|habis waktu|tidak dikenal/i.test(message) ? 'bad' : ''));
        $('enrollResult').dataset.initialized = '1';
      } else if (message && $('enrollResult').dataset.lastDeviceMessage !== message) {
        if (!previousBusy) setResult('Pesan perangkat', message, /gagal|tidak dikenal/i.test(message) ? 'bad' : '');
      }
      $('enrollResult').dataset.lastDeviceMessage = message;
      $('message') && ($('message').textContent = s.message || 'Tidak ada pesan dari perangkat.');
      $('startEnroll').disabled = !!s.enrollBusy; $('cancelEnroll').disabled = !s.enrollBusy; $('enrollName').disabled = !!s.enrollBusy;
      $('startEnroll').innerHTML = s.enrollBusy ? 'Pendaftaran berjalan…' : 'Mulai pendaftaran <span>→</span>';
      $('timer').textContent = s.enrollBusy ? `ID template: ${s.enrollId}. Jangan mematikan ESP32.` : '';
      updateProgress(message, !!s.enrollBusy); renderDevicePills(s); previousBusy = !!s.enrollBusy;
    } catch (error) {
      $('message').textContent = 'ESP32 belum terjangkau: ' + error.message + '. Buka halaman ini melalui alamat perangkat saat Wi-Fi konfigurasi aktif.';
      const state = $('enrollmentDeviceState'); if (state) { state.textContent = 'Offline'; state.classList.remove('device-online'); }
    }
  }
  async function startEnrollment(event) {
    event.preventDefault(); const name = $('enrollName').value.trim();
    if (!name) { setResult('Nama diperlukan','Isi nama pengguna sebelum memulai.','bad'); return; }
    $('startEnroll').disabled = true;
    try { const result = await request('/enroll?name=' + encodeURIComponent(name)); setResult('Permintaan pendaftaran dikirim', result, ''); toast(result); await pollStatus(); }
    catch (error) { $('startEnroll').disabled = false; setResult('Pendaftaran gagal dimulai', error.message, 'bad'); toast('Gagal memulai: ' + error.message); }
  }
  async function cancelEnrollment() {
    if (!confirm('Batalkan pendaftaran fingerprint yang sedang berlangsung?')) return;
    $('cancelEnroll').disabled = true;
    try { const result = await request('/enroll/cancel'); setResult('Pendaftaran dibatalkan', result, 'bad'); $('enrollName').disabled = false; toast(result); await pollStatus(); }
    catch (error) { setResult('Gagal membatalkan', error.message, 'bad'); toast(error.message); await pollStatus(); }
  }
  $('enrollForm')?.addEventListener('submit', startEnrollment);
  $('cancelEnroll')?.addEventListener('click', cancelEnrollment);
  pollStatus(); setInterval(pollStatus, 700);
})();
</script>
</body>
</html>
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
  server.on("/logo.png", HTTP_GET, []() { server.send_P(200, "image/png", (PGM_P)LOGO_PNG, sizeof(LOGO_PNG)); });
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

