
#ifndef WEB_HTML_WATER_MANUAL_H
#define WEB_HTML_WATER_MANUAL_H
const char g_Web_Htlm_Water_Manual[] PROGMEM = R"=====(
<!doctype html>
<html lang="en">
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0">
<title>Irrigation</title>
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
        
          <span class="title">riego</span> <br>
           <span class="titlesub">IOT Irrigation system EcoFlow (ESP32)</span>
        </div>
      </div>
  <div class="row menu">
    <input type="button"  Class="button orange" onClick="location.replace('/');" value ="Home" title="home read status"/>
    <input type="button" Class="button orange" onClick="location.replace('/irrigationauto.html'); return false" value ="Automatic" title="Irrigation automatic"/>
    <input type="button"disabled="disabled" Class="button orange" onClick="location.replace('/irrigationmanual.html'); return false;" value ="Manual" title="Irrigation manual"/>
    <input type="button" Class="button orange" onClick="location.replace('/confignet.html'); return false; " value ="Network & Time" title="config wifi, Ntp and gps location"/>
  <hr>
  </div>
  <div id="divBody">
  <h4>Manual irrigation, unscheduled, with immediate effect</h4>
 
    <p>
    <b>Pipe 1</b>
    <input type="button" Class="button" onClick="fncManualSet(0,0);" value ="OFF"/>
    <input type="button" Class="button" onClick="fncManualSet(0,1);" value ="1 min."/>
    <input type="button" Class="button" onClick="fncManualSet(0,5);" value ="5 min."/>
    <input type="button" Class="button" onClick="fncManualSet(0,10);" value ="10 min."/>
        <input type="button" Class="button" onClick="fncManualSet(0,15);" value ="15 min."/>
   </p>
    <p>
    <b>Pipe 2</b>
         <input type="button" Class="button" onClick="fncManualSet(1,0);" value ="OFF"/>
    <input type="button" Class="button" onClick="fncManualSet(1,1);" value ="1 min."/>
    <input type="button" Class="button" onClick="fncManualSet(1,5);" value ="5 min."/>
    <input type="button" Class="button" onClick="fncManualSet(1,10);" value ="10 min."/>
    <input type="button" Class="button" onClick="fncManualSet(1,15);" value ="15 min."/>
   </p>
    <p>
    <b>Pipe 3</b>
    <input type="button" Class="button" onClick="fncManualSet(2,0);" value ="OFF"/>
    <input type="button" Class="button" onClick="fncManualSet(2,1);" value ="1 min."/>
    <input type="button" Class="button" onClick="fncManualSet(2,5);" value ="5 min."/>
    <input type="button" Class="button" onClick="fncManualSet(2,10);" value ="10 min."/>
    <input type="button" Class="button" onClick="fncManualSet(2,15);" value ="15 min."/>
   </p>
   <p>
    <b>Pipe 4</b>
    <input type="button" Class="button" onClick="fncManualSet(3,0);" value ="OFF"/>
    <input type="button" Class="button" onClick="fncManualSet(3,1);" value ="1 min."/>
    <input type="button" Class="button" onClick="fncManualSet(3,5);" value ="5 min."/>
    <input type="button" Class="button" onClick="fncManualSet(3,10);" value ="10 min."/>
    <input type="button" Class="button" onClick="fncManualSet(3,15);" value ="15 min."/>
   </p>
   <p>
    <b>Pipe 5</b>
    <input type="button" Class="button" onClick="fncManualSet(4,0);" value ="OFF"/>
    <input type="button" Class="button" onClick="fncManualSet(4,1);" value ="1 min."/>
    <input type="button" Class="button" onClick="fncManualSet(4,5);" value ="5 min."/>
    <input type="button" Class="button" onClick="fncManualSet(4,10);" value ="10 min."/>
    <input type="button" Class="button" onClick="fncManualSet(4,15);" value ="15 min."/>
   </p>
  <p id="msg"></p>  

 </div>
</div>
<script>
function fncManualSet(idRrelay,minutes)
{
  let pURL="/irrigationmanualset?idrelay="+idRrelay+"&minutes="+minutes;
  console.log(pURL);
  fncGetHtml("msg", pURL);
}
</script>
</body></html>

)=====";
#endif