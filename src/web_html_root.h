#ifndef WEB_HTML_ROOT_H
#define WEB_HTML_ROOT_H
	const char g_Web_Htlm_Root[] PROGMEM = R"=====(
<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Irrigation</title>

<link rel="stylesheet" type="text/css" href="css.css">
<meta http-equiv='cache-control' content='no-cache'/>
<meta http-equiv='expires' content='0'/>
<meta http-equiv='pragma' content='no-cache'/>
<script src="js.js"></script>
</head>
<body>
<div id="divbody">
  <div class="row">
    <div class="column">
          <img style=" width:120px; " src="svg.svg" alt="Logo"/>
   </div>
      <div class="column">
        <span class="title">riego (EcoFlow)</span> <br/>
        <span class="titlesub">IOT Irrigation system EcoFlow (ESP32)</span><br/>
      </div>
 </div>
     
  <div class="row menu">
    <input type="button" disabled Class="button orange" onClick="location.replace('/');" value ="Home" title="home read status"/>
    <input type="button" Class="button orange" onClick="location.replace('/irrigationauto.html'); return false" value ="Automatic" title="Irrigation automatic"/>
    <input type="button" Class="button orange" onClick="location.replace('/irrigationmanual.html'); return false;" value ="Manual" title="Irrigation manual"/>
    <input type="button" Class="button orange" onClick="location.replace('/confignet.html'); return false; " value ="Network & Time" title="config wifi, Ntp and gps location"/>
  </div>
   <p>
   <input type="button" class="button orange" onclick="getRelay(0);" value="Pipe 1" >
   <input type="button" class="button orange" onclick="getRelay(1);" value="Pipe 2">
 
  </p><hr>
  <div class="row">
    <div id="divContent">
      Please wait, loading page...
    </div>
  </div>
</div>
<script>
 document.addEventListener("DOMContentLoaded", (event) => { getRelay(0); });
 function getRelay(idRelay)
  {
  url="/getstatus?idRelay="+idRelay;
  fncGetHtml("divContent",url);
  } 
</script>

</body>
</html>
)=====";
#endif