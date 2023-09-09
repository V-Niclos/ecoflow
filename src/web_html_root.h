#ifndef WEB_HTML_ROOT_H
#define WEB_HTML_ROOT_H
	const char g_Web_Htlm_Root[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0">
<title>Irrigation</title>
<link rel="shortcut icon" href="favicon.ico" type="image/x-icon">
<link rel="icon" href="favicon.ico">
<link rel="icon" href="favicon.svg" type="image/svg+xml">
<link rel="apple-touch-icon" href="apple-touch-icon.png">
<link rel="stylesheet" type="text/css" href="css.css">
<meta http-equiv='cache-control' content='no-cache'>
<meta http-equiv='expires' content='0'>
<meta http-equiv='pragma' content='no-cache'>

<script src="js.js"></script></head>
<body>
<div id="divbody">
  <div class="row">
    <div class="column">
      <img style=" width:120px; " src="svg.svg" alt="Logo">
    </div>
    <div class="column">
      <spam class="title">Irrigation
      <br><spam class="titlesub">Alexa and web managging five relays</spam></spam>
    </div>
  </div>
  <div class="row menu">
    <input type="button" disabled Class="button orange" onClick="location.replace('/');" value ="Home" title="home read status"/>
    <input type="button" Class="button orange" onClick="location.replace('/relayirrigation.html'); return false" value ="Irrigation" title="relay 3 on off"/>
    <input type="button" Class="button orange" onClick="location.replace('/relayonof.html'); return false;" value ="Switch" title="relay 4 on off"/>
    <input type="button" Class="button orange" onClick="location.replace('/confignet.html'); return false; " value ="Network & Time" title="config wifi, Ntp and gps location"/>
  </div>
  <div id="divContent">
    Please wait, loading page...
  </div>
</div>
<script>
 document.addEventListener("DOMContentLoaded", (event) => {
    console.log("DOM fully loaded and parsed");
   // fncGetHtml("divContent","/getstatus.html");
  });

</script>
</body></html>

)=====";
#endif