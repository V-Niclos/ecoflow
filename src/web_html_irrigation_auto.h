
#ifndef WEB_HTML_IRRIGATION_AUTO_H
#define WEB_HTML_IRRIGATION_AUTO_H
const char g_Web_Htlm_Irrigation_Auto[] PROGMEM = R"=====(
<!doctype html>
<html lang="en"><head>
<meta http-equiv="content-type" content="text/html; charset=UTF-8"><meta charset="utf-8">
  <meta name="viewport" content="width=device-width">
  <title>Irrigation</title>

   <link rel="stylesheet" type="text/css" href="/css.css">
  <script src="/js.js"></script>

  </head>
  <body>
    <div id="divbody">
      <div class="row">
        <div class="column">
          <img style=" width:120px; " src="/svg.svg" alt="Logo">
        </div>
        <div class="column">
          <span class="title">riego</span>
          <br>
          <span class="titlesub">IOT Irrigation system (ESP32)</span>
        </div>
      </div>
      <div class="row menu">
        <input type="button"  class="button orange" onclick="location.replace('/');" value="Home" title="home read status">
        <input type="button" disabled="disabled" class="button orange" onclick="location.replace('/irrigationauto.html'); return false" value="Automatic" title="Irrigation automatic">
        <input type="button" class="button orange" onclick="location.replace('/irrigationmanual.html'); return false;" value="Manual" title="Irrigation manual">
        <input type="button" class="button orange" onclick="location.replace('/confignet.html'); return false; " value="Network &amp; Time" title="config wifi, Ntp and gps location">
      </div>
      <div class="row">
        <fieldset>
          <legend> Id Relay: <span id="m_RelayId">0</span>
            <span id="m_PrgAuto_IsActiveLED" class="led gray"></span>g_fldPrgAuto_IsActive
          </legend>
          <p>
            <input type="button" class="button orange" onclick="fncRelayAjaxJson_GET(0);" value="Pipe 1" title="go irrigation 1">
            <input type="button" class="button orange" onclick="fncRelayAjaxJson_GET(1);" value="Pipe 2" title="go irrigation 2">
            <input type="button" class="button orange" onclick="fncRelayAjaxJson_GET(2);" value="Pipe 3" title="go irrigation 3">
            <input type="button" class="button orange" onclick="fncRelayAjaxJson_GET(3);" value="Pipe 4" title="go irrigation 4">
            <input type="button" class="button orange" onclick="fncRelayAjaxJson_GET(4);" value="Pipe 5" title="go irrigation 5">
            </p><hr>
        
          <span id="scnMessageDate"></span>
          <label class="labelfrm" for="m_RelayName"> Relay Name:</label>
          <input type="text" id="m_RelayName" name="m_RelayName" minlength="4" maxlength="15" size="15"> 10-15 Chararcters <br>
          <p>
            <label class="labelfrm" for="m_PrgAuto_Description"> Description:</label>
            <input type="text" id="m_PrgAuto_Description" name="m_PrgAuto_Description" minlength="4" maxlength="15" size="15"> 10-15 Chararcters <br>
           
           <label class="labelfrm" > Switch:</label>
            <input type="radio" id="m_PrgAuto_IsActive0" name="m_PrgAuto_IsActive" value="0" checked="checked">
            <label for="m_PrgAuto_IsActive0">Off</label>

            <input type="radio" id="m_PrgAuto_IsActive1" name="m_PrgAuto_IsActive" value="1">
            <label for="m_PrgAuto_IsActive1">On</label>
            <br>
            <label class="labelfrm" for="m_PrgAuto_StartHHMM">Start Time:</label>
            <input type="time" id="m_PrgAuto_StartHHMM" value="00:00">
            <br>
            <label class="labelfrm" for="m_PrgAuto_Minutes"> minutes:</label>
            <input type="range" name="m_PrgAuto_Minutes" id="m_PrgAuto_Minutes" value="1" min="1" max="15" oninput="m_PrgAuto_MinutesValue.value = m_PrgAuto_Minutes.value">
            <output name="m_PrgAuto_MinutesValue" id="m_PrgAuto_MinutesValue">1</output>
            <span class="soft"> Minutes</span>
            <br>
            <label class="labelfrm" for="m_PrgAuto_IntervalDays">Interval days:</label>
            <input type="range" name="m_PrgAuto_IntervalDays" id="m_PrgAuto_IntervalDays" value="0" min="0" max="10" oninput="m_PrgAuto_IntervalDaysValue.value = m_PrgAuto_IntervalDays.value">
            <output name="m_PrgAuto_IntervalDaysValue" id="m_PrgAuto_IntervalDaysValue">0</output>
            <span class="soft"> Between days</span>
            <br>
            <span id="m_RelayMessage" class="msg">.</span>
          </p>
          <input type="button" class="button orange" onclick="fncRelayAjaxJson_POST();" value="Save" title="save this">
        </fieldset>
      </div>
    </div>
 
<script>
g_fldRelayId = "m_RelayId";
g_fldRelayName = "m_RelayName";
g_fldRelayMessage = "m_RelayMessage";
g_fldPrgAuto_Description = "m_PrgAuto_Description";
g_fldPrgAuto_IsActive = "m_PrgAuto_IsActive";
g_PrgAuto_IsActiveLED = "m_PrgAuto_IsActiveLED";
g_fldPrgAuto_StartHHMM = "m_PrgAuto_StartHHMM";
g_fldPrgAuto_IntervalDays ="m_PrgAuto_IntervalDays";
g_fldPrgAuto_IntervalDaysValue = "m_PrgAuto_IntervalDaysValue";
g_fldPrgAuto_Minutes = "m_PrgAuto_Minutes";
g_fldPrgAuto_MinutesValue = "m_PrgAuto_MinutesValue" ;
msg = "";
function fncRelayAjaxJson_POST() {
var xhttp_Post = new XMLHttpRequest();
var url = "/relayirrigationset";
xhttp_Post.open('POST', 'relayirrigationset', true);
xhttp_Post.setRequestHeader('Content-Type', 'application/json');
xhttp_Post.addEventListener('load', function(event) {
console.log('OK', xhttp_Post);
});
xhttp_Post.addEventListener('error', function(event) {
console.log('error', xhttp_Post);
});
xhttp_Post.xhttp_Post = function() {
if(xhttp_Post.readyState === 4 && xhttp_Post.status === 200) {
dataResponse = (xhr.responseText);
console.log("Respuesta del servidor " + dataResponse);
}
};
var data = "";
data = fncGetRelayJsonFromScreen();
console.log("send json data="+data);
xhttp_Post.send(data);
}
function fncRelayAjaxJson_GET(pRelayId) {
console.log("Start fncRelayAjaxJson_GET()");
relayId = pRelayId; //document.getElementById("scn_relayId").innerHTML;
aJson = "";
pUrl = "";
pUrl = "/irrigationautoget?idRelay=" + relayId;
console.log("Enviado");
console.log("fncRelayAjaxJson_GET pUrl= " + pUrl);
var xhttp;
var reply = "";
xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if(xhttp.readyState == 4 && xhttp.status == 200) {
message = "";
arrJson = xhttp.responseText;
console.log(arrJson);
fncFillJsonToScreen(arrJson);
var now = new Date();
now.setMinutes(now.getMinutes() - now.getTimezoneOffset());
elem = document.getElementsByName("scnMessageDate");
if(elem !== null && elem !== 'undefined') {
elem.innerHTML = now.toISOString().slice(0, 16);
}}};
xhttp.open("GET", pUrl, true);
xhttp.send();
}
function fncIsEmpty(value) {
return (value == null || (typeof value === "string" && value.trim()
.length === 0));
}
const fncRegex_Valid_HMMM = (str) => /^([01]?[0-9]|2[0-3]):[0-5][0-9]$/.test(str);
function fncValidateHHMMString(scnFieldId) {
value = document.getElementById(scnFieldId).value;
if(fncIsEmpty(value)) {
value = "00:00";
}
if(!fncRegex_Valid_HMMM(value)) {
value = "00:00";
}
document.getElementById(scnFieldId).value = value;
return value;
}
function fncValidFieldString(scnFieldId) {
value = document.getElementById(scnFieldId).value;
if(fncIsEmpty(value)) {
value = "";
}
value = value.trim();
document.getElementById(scnFieldId).value = value;
return value;
}
function fncValidFieldNumber(scnFieldId) {
sVal = 0;
var objScreen=document.getElementById(scnFieldId);
val =objScreen.value;
iVal=Number(val);
if(typeof iVal == 'number')
{	console.log(iVal + " is a number");
}else{  iVal=0; }
objScreen.value = iVal;
return iVal;
}
function fncGetRelayJsonFromScreen() {
arrJson ="{";
arrJson += fncFillJsonPair(true, g_fldRelayId, document.getElementById(g_fldRelayId).innerHTML);
arrJson += fncFillJsonPair(false, g_fldRelayName, fncValidFieldString(g_fldRelayName));
arrJson += fncFillJsonPair(false, g_fldPrgAuto_Description, fncValidFieldString(g_fldPrgAuto_Description));
arrJson += fncFillJsonPair(false, g_fldPrgAuto_Minutes, fncValidFieldNumber(g_fldPrgAuto_Minutes));
arrJson += fncFillJsonPair(false, g_fldPrgAuto_IntervalDays, fncValidFieldNumber(g_fldPrgAuto_IntervalDays));
arrJson += fncFillJsonPair(false, g_fldPrgAuto_IsActive, fncGetRadioSelected(g_fldPrgAuto_IsActive));
arrJson += fncFillJsonPair(false, g_fldPrgAuto_StartHHMM, fncValidateHHMMString(g_fldPrgAuto_StartHHMM));
arrJson += "}";
return arrJson;
}
function fncFillJsonPair(isFirstValue, keyName, keyValue) {
result = "";
if(isFirstValue == false) {
result = ", ";
}
result += "\"" + keyName + "\":\"" + keyValue + "\"";
return result;
}
function fncGetRadioSelected(pNameRadio) {
result = '';
ele = document.getElementsByName(pNameRadio);
for(i = 0; i < ele.length; i++) {
if(ele[i].checked) {
result = ele[i].value;
}
}
return result;
}
function fncFillJsonToScreen(arrJson) {
scnFld = "";
document.getElementById(g_fldRelayId).innerHTML = "";
document.getElementById(g_fldRelayName).value = "";
document.getElementById(g_fldPrgAuto_Description).value = "No se rellena";
document.getElementById(g_fldRelayMessage).innerHTML = "";
document.getElementById(g_fldPrgAuto_StartHHMM).value = "00:00";
document.getElementById(g_fldPrgAuto_IntervalDays).value = 0;
document.getElementById(g_fldPrgAuto_Minutes).value = 0;
obj = JSON.parse(arrJson);
document.getElementById(g_fldRelayId).innerHTML = obj.m_RelayId;
document.getElementById(g_fldRelayName).value = obj.m_RelayName;

temp = obj.m_PrgAuto_Description;
document.getElementById(g_fldPrgAuto_Description).value = temp;
document.getElementById(g_fldPrgAuto_Minutes).value = obj.m_PrgAuto_Minutes;
document.getElementById(g_fldPrgAuto_MinutesValue).value = obj.m_PrgAuto_Minutes;
document.getElementById(g_fldPrgAuto_IntervalDays).value = obj.m_PrgAuto_IntervalDays;
document.getElementById(g_fldPrgAuto_IntervalDaysValue).innerHTML = obj.m_PrgAuto_IntervalDays;
if(obj.m_PrgAuto_IsActive == "1") {
document.getElementById(g_PrgAuto_IsActiveLED).className = "led green ";
document.getElementById("m_PrgAuto_IsActive1").checked = true;
} else {
document.getElementById(g_PrgAuto_IsActiveLED).className = "led red";
document.getElementById("m_PrgAuto_IsActive0").checked = true;
}
temp = obj.m_PrgAuto_StartHHMM;
document.getElementById(g_fldPrgAuto_StartHHMM).value = temp;
temp = obj.m_RelayMessage;
if(temp == "null") {
temp = "";
}
document.getElementById(g_fldRelayMessage).innerHTML = temp;
}
window.onload = function() {fncRelayAjaxJson_GET(0);};
</script>
</body></html>
)=====";
#endif
