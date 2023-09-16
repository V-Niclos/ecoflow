#ifndef WEB_HTML_CONFIGNET_H
#define WEB_HTML_CONFIGNET_H
const char g_Web_Html_ConfigNet[] PROGMEM = R"=====(
    <!DOCTYPE html><html><head> 
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
	<meta name=viewport content="width=device-width, initial-scale=1">
  <link rel="icon" href="favicon.svg" type=”image/svg+xml”>
  <link rel=”mask-icon” href=”mask-icon.svg” color=”#000000">
  <link rel="manifest" href="manifest.json">
<link rel="stylesheet" type="text/css" href="css.css">
<title>Config wifi</title> 
<style>
label {display: block; width: 130px; font-weight:bold; }
input[type=text] { padding: 12px 20px;  min-width: 20em;   box-sizing: border-box;   padding:3px;   font-size:1rem; }
input[type=password] { padding: 12px 20px;  min-width: 20em;   box-sizing: border-box;   padding:3px;   font-size:1rem; }
.slidecontainer {   width: 100%; } 
.slider {   -webkit-appearance: none;   width: 70%;   height: 25px;   background: #d3d3d3;   outline: none;   opacity: 0.7;  -webkit-transition: .2s;   transition: opacity .2s; }
.slider:hover {   opacity: 1; }
.slider::-webkit-slider-thumb { -webkit-appearance: none;  appearance: none;   width: 25px;   height: 25px;   background: #04AA6D;   cursor: pointer; }
.slider::-moz-range-thumb {   width: 25px;   height: 25px;   background: #04AA6D;   cursor: pointer; }
.divbuttons{
 border: 3px solid #666666;
  padding: 5px;
  text-align:right;
}
</style>
</head>
<body>
<div id="divbody">
<div class="row">
	<div class="column">
		<img style=" width:120px; " src="svg.svg" alt="Logo">
	</div>
	<div class="column">
			<spam class="title">Irrigation configuration
			<br><spam class="titlesub">wifi</spam></spam>
	 </div>
 
</div> 
<div class="row">
 <div class="row menu">
    <input type="button" Class="button orange" onClick="location.replace('/');" value ="Home" title="home read status"/>
    <input type="button" Class="button orange" onClick="location.replace('/relayirrigation.html'); return false" value ="Irrigation" title="relay 3 on off"/>
    <input type="button" Class="button orange" onClick="location.replace('/relayonof.html'); return false;" value ="Switch" title="relay 4 on off"/>
    <input type="button" disabled Class="button orange" onClick="location.replace('/confignet.html'); return false; " value ="Network & Time" title="config wifi, Ntp and gps location"/>
  </div>
  <hr/>
<div class="divbuttons">
<input type="button" Class="button" onClick="fncGetAjaxConfig('/netconfigget')" value ="get config"/>
<input type="button" Class="button" onClick="fncGetAjaxConfig('/netconfiggetdefault')" value ="get default"/>
<input type="button" Class="button" onClick="jsSetConfigSave()" value ="Save"/>
<input type="button" Class="button" onClick="fncSendGetHtml('scnMsgSend','/reset')" value ="reset"/>
<div id="scnMsgSend" style=" border: 1px solid gray;; background-color:#eeeeee;" margin:2px;"></div>
<div id="scnMsgReply" style="border: 1px solid gray; background-color:#eeeeee;" margin:2px;"></div>
</div>
</div>
<div class="row">
	<span id="scnMsg"></span>
	<fieldset>
<legend>General option</legend>
	<label for="scnHostName">Host name</label> 
	<input  type="text" id ="scnHostName" name="scnHostName" value="ecoflow" maxlength="25" placeholder="ecoflow">min length 5 max25 <span class="red" id="scnHostNameMsg"></span>
		<br/> Use DHCP		
  <input type="checkbox" id="scnDHCP" onclick="fncSwtichDHCP();">
  </fieldset>
<fieldset>
  <legend>For join to your net as ws:</legend>
 
  <label for="scnSsid">SSID</label>
  <input type="text" id ="scnSsid" name="scnSsid" placeholder="ecoflow"><span class="red" id="scnSsidMsg"></span><br>
  <label for="scnPwd">Password</label>
  <input  type="password" id ="scnPwd" name="scnPwd" placeholder="123456789">  <input type="checkbox" onclick="togglePwd('scnPwd')"><strong>Show Password</strong>
  <span class="red" id="scnPwdMsg"></span>
  <br>
  <label for="scnIp">IP Address</label>
  <input type="text" id ="scnIp" name="scnIp" value="" placeholder="192.168.2.254"> <span class="red" id="scnIpMsg"></span><br>
  <label for="scnMask">IP Mask</label>
  <input type="text" id ="scnMask" name="scnMask" value="" placeholder="255.255.255.0"><span class="red" id="scnMaskMsg"></span><br>
  <label for="scnGat">Gateway Address</label>
  <input type="text" id ="scnGat" name="scnGat" value="" placeholder="192.168.2.1"><span class="red" id="scnGatMsg"></span><br>
  <br/>
</fieldset>
<fieldset>
   <legend>For get local time from NTP server</legend>
   <div class="slidecontainer"><br/>
   <label for="scnTimeZone">Time zone [HH]</label>
   <input type="range" min="-11" max="12" value="1" class="slider" id="scnTimeZone" name="scnTimeZone"  oninput="fncShowValue('scnTimeZone','scnTimeZoneValue')" >
   <span id="scnTimeZoneValue"></span>
   </div>
   <div class="slidecontainer">
   	<label for="scnTimeZoneDay">Daylight [HH]</label>
   <input type="range" min="-2" max="+2" value="1" class="slider" id="scnTimeZoneDay" name="scnTimeZoneDay" oninput="fncShowValue('scnTimeZoneDay','scnTimeZoneDayValue')" >
    <span id="scnTimeZoneDayValue"></span>
   </div>
</fieldset>
<fieldset>
  <legend>GPS decimal cordinates</legend>
  <label for="scnGpsLat">Latitude:</label>
  <input type="number" id ="scnGpsLat" name="scnGpsLat" value="0" step="any" placeholder="40.4165000"><span>40.4167  (Madrid)</span><br>
  <label for="scnGpsLon">Longitude:</label>
  <input type="number" id ="scnGpsLon" name="scnGpsLon" value="0" step="any"  placeholder="-3.703228"><span id="scnGpsLongNote">-3.703228 (Madrid)</span><br>
</fieldset>




</div>
</body>

<script>

function fncSendGetHtml(pDivTarget, pURL) {
	 jsClearMsg();
 console.log("pDivTarget=" + pDivTarget + "\n pURL= " + pURL);
   document.getElementById("scnMsgSend").innerHTML = pURL;
 var xhttp;
 xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
  if (xhttp.readyState == 4 && xhttp.status == 200) {
  
     document.getElementById(pDivTarget).innerHTML = xhttp.responseText ;
  }
 };
 xhttp.open("GET", pURL, true);
 xhttp.send();
}

function jsValidateForm()
{		
	let bOk=true;
	jsClearMsg();
			document.getElementById("scnMsg").style.color="black";	
		let msg="";
	if(document.getElementById('scnHostName').value.length==0)
	{document.getElementById('scnHostName').value="ecoflow";}
	if( document.getElementById("scnHostName").value.length<5)
	{
		bOk=false;
    document.getElementById("scnHostNameMsg").innerHTML="*";
		msg+="Error: Host name to short <br/>";
	}
	
	let val=document.getElementById("scnSsid").value;
	if( val.length<5)
	{
		bOk=false;
		msg+="Error: Siid to short or empty <br/>";
		document.getElementById("scnSsidMsg").innerHTML="*";
	}
	
		 val= document.getElementById("scnPwd").value;
	if( val.length<5)
	{
		bOk=false;
		msg+="Error: password to short or empty <br/>";
			document.getElementById("scnPwdMsg").innerHTML="*";
	}
	if (!fncValidateIp("scnIp"))
	{
	
		bOk=false;
		msg+="Error: Ip Invalid IP4 format</br>";
				document.getElementById("scnIpMsg").innerHTML="*";
		}
		if (!fncValidateIp("scnMask"))
	{
		bOk=false;
		msg+="Error: Ip Invalid ip4 mask  format</br>";
		document.getElementById("scnMaskMsg").innerHTML="*";
		}
		
		if (!fncValidateIp("scnGat"))
	{
	
		bOk=false;
		msg+="Error: gatweqy Invalid IP4 format</br>";
		document.getElementById("scnGatMsg").innerHTML="*";
		}
	if(bOk==false)
	{	
	document.getElementById("scnMsg").style.color="red";	
	document.getElementById("scnMsg").innerHTML=msg;
}

	return bOk;
	}
	function jsClearMsg()
	{
  document.getElementById("scnGatMsg").innerHTML="";
  document.getElementById("scnMaskMsg").innerHTML="";
  document.getElementById("scnIpMsg").innerHTML="";
  document.getElementById("scnPwdMsg").innerHTML="";
  document.getElementById("scnSsidMsg").innerHTML="";
  document.getElementById("scnHostNameMsg").innerHTML="";
  document.getElementById("scnHostNameMsg").innerHTML="";
  document.getElementById("scnMsg").innerHTML="";
  
  
		}
function jsSetConfigSave()
{
		console.log("1");
	if(jsValidateForm()==false){return;}
	
  let sTemp="";
  let url="/netconfigsave?";
 
  
  url=url+"ssid="+document.getElementById('scnSsid').value.trim();
  url=url+"&pwd="+document.getElementById('scnPwd').value.trim();
  url=url+"&ip="+document.getElementById('scnIp').value.trim();
  url=url+"&mask="+document.getElementById('scnMask').value.trim();
  url=url+"&gat="+document.getElementById('scnGat').value.trim();
  url=url+"&TimeZone="+document.getElementById('scnTimeZone').value.trim();
  url=url+"&TimeDayLight="+document.getElementById('scnTimeZoneDay').value.trim();
  url=url+"&lat="+document.getElementById('scnGpsLat').value.trim();
  url=url+"&long="+document.getElementById('scnGpsLon').value.trim();
  url=url+"&host="+document.getElementById('scnHostName').value.trim();
  if(document.getElementById('scnDHCP').checked){sTemp="1";}else {sTemp="0";}
  url=url+"&dhcp="+sTemp;
   
  fncSendGetHtml('scnMsgReply', url);
}
function togglePwd(id) {
var temp = document.getElementById(id);
if (temp.type === "password") {temp.type = "text";}
else {temp.type = "password";}
}
function jsReset()
{
fncGetHtml('scnMsgReply', "/reset") ;
}
function fncShowValue(idRange, idRangeValue)
{
var slider = document.getElementById(idRange);
var output = document.getElementById(idRangeValue);
console.log(idRange); 
console.log(idRangeValue);
console.log(slider.value) ;
output.innerHTML = slider.value;
}

//---------------------------------------
function fncGetAjaxConfig(pURL) {
  // https://www.w3schools.com/js/js_ajax_http_send.asp
 console.log("fncGetAjax pURL= " + pURL);
 var xhttp;
 var reply = "";
 xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
  if (xhttp.readyState == 4 && xhttp.status == 200) 
  {
   reply = xhttp.responseText;
   document.getElementById("scnMsgReply").innerHTML = reply;
 fillFields(reply)
 }

 };
 xhttp.open("GET", pURL, true);
 xhttp.send();
}
function fillFields(stringValues)
{

   var aValues = stringValues.split("#");
 for (var i=0; i< aValues.length;i++) {console.log( i+" = "+ aValues[i]); }



 document.getElementById("scnSsid").value = aValues[0];
 document.getElementById("scnPwd").value = aValues[1];
 document.getElementById("scnIp").value = aValues[2];
 document.getElementById("scnMask").value = aValues[3];
 document.getElementById("scnGat").value = aValues[4];
 
 document.getElementById("scnTimeZone").value = aValues[5];
 document.getElementById("scnTimeZoneValue").value = aValues[5];

 document.getElementById("scnTimeZoneDay").value = aValues[6];
 document.getElementById("scnTimeZoneDayValue").value = aValues[6];
 
 aValues[7]=aValues[7].replace('.', ',').trim();;
 document.getElementById("scnGpsLat").value = aValues[7].trim();
 console.log(aValues[7]);

 aValues[8]=aValues[8].replace('.', ',').trim();;
 document.getElementById("scnGpsLon").value = aValues[8].trim();
 console.log(aValues[8]);

  document.getElementById("scnHostName").value = aValues[9];
  console.log("aValues[10]"+aValues[10])
  if(aValues[10]=="1")
  {
  document.getElementById("scnDHCP").checked  = true;
  }
  else
  {
document.getElementById("scnDHCP").checked  = false;
  }
}
function fncSwtichDHCP()
{
	let bEnable=false;
	if(document.getElementById("scnDHCP").checked){bEnable=true;}
	console.log(bEnable);
	document.getElementById("scnIp").disabled=bEnable;
	document.getElementById("scnGat").disabled=bEnable;
	document.getElementById("scnMask").disabled=bEnable;
	}
function fncValidateIp(elementId)
 {
 let IpText=	document.getElementById(elementId).value;
 var ipformat = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
 if(!IpText.match(ipformat))
 {
 return false;
 }
 return true;
 }
 //---------------------------------------
document.addEventListener("DOMContentLoaded", () => {
 
  //fncSendGetHtml('scnDebug', '/geconfig');
 jsClearMsg();
fncGetAjaxConfig('/netconfigget');



});
</script>
</html>



)=====";
#endif