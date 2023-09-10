
#ifndef WEB_HTML_RELAY_ONOFF_H
#define WEB_HTML_RELAY_ONOFF_H
	const char g_Web_Htlm_Relay_OnOff[] PROGMEM = R"=====(
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
    <input type="button" Class="button orange" onClick="location.replace('/');" value ="Home" title="home read status"/>
    <input type="button" Class="button orange" onClick="location.replace('/relayirrigation.html'); return false" value ="Irrigation" title="relay 3 on off"/>
    <input type="button" disabled Class="button orange" onClick="location.replace('/relayonof.html'); return false;" value ="Switch" title="relay 4 on off"/>
    <input type="button" Class="button orange" onClick="location.replace('/confignet.html'); return false; " value ="Network & Time" title="config wifi, Ntp and gps location"/>
  </div>
  <div id="divBody">
  <h4>TODO functionality</h4>
  <p id="msg"></p>
  <p>Relays 3,4,5 on board, not for irrigation.<br/>Pending functionality analysis. For now only on/off </p>
    <p>
    <b>Rele on off O</b>
     <input type="button" Class="button" onClick="fncOnOff(0,1);" value ="On"/>
     <input type="button" Class="button" onClick="fncOnOff(0,0);" value ="Off"/>
   </p>
    <p>
    <b>Rele on off 1</b>
     <input type="button" Class="button" onClick="fncOnOff(1,1);" value ="On"/>
     <input type="button" Class="button" onClick="fncOnOff(1,0);" value ="Off"/>
   </p>
    <p>
    <b>Rele on off 2</b>
     <input type="button" Class="button" onClick="fncOnOff(2,1);" value ="On"/>
     <input type="button" Class="button" onClick="fncOnOff(2,0);" value ="Off"/>
   </p>
   

 </div>
</div>
<script>
function fncOnOff(idRrelay,onOff)
{
  let pURL="/relayonoffset?idrelay="+idRrelay+"&onoff="+onOff;
  console.log(pURL);
  fncGetHtml("msg", pURL);
}</script>
</body></html>

)=====";
#endif