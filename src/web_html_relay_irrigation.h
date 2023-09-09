
#ifndef WEB_HTML_RELAY_IRRIGATION_H
#define WEB_HTML_RELAY_IRRIGATION_H
	const char g_Web_Htlm_Relay_Irrigation[] PROGMEM = R"=====(
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
<input type="button" disabled Class="button orange" onClick="location.replace('/relayirrigation.html'); return false" value ="Irrigation" title="relay 3 on off"/>
<input type="button" Class="button orange" onClick="location.replace('/relayonof.html'); return false;" value ="Switch" title="relay 4 on off"/>
<input type="button" Class="button orange" onClick="location.replace('/confignet.html'); return false; " value ="Network & Time" title="config wifi, Ntp and gps location"/>
</div>

<div class="row">
<div id="scnMsgDebug" class="row" style="line-height:1.4em; border: 1px solid gray; background-color:#eeeeee; margin:2px; height:auto;"></div>


 <fieldset>
 <legend><span id="scn_relayName" >Wait data</span> <span id="scn_relayIsOpen" class="led"></span><span id="scn_relayId" style="visibility: visible;"> relay -1</span>
</legend>
<p>
<input type="button" Class="button orange" onClick="fncJsonToScreenTest();" value ="Test to screen" title="save"/>
<input type="button" Class="button orange" onClick="fncJsonFromScreenTest();" value ="Test from screen" title="save"/>
<input type="button" Class="button orange" onClick="fncRelayAjaxSave('save');" value ="Save" title="save this"/>
<input type="button" Class="button orange" onClick="fncRelayAjaxGet("get",0);" value ="1 Irrigation" title="go irrigation 1, don't save this"/>
<input type="button" Class="button orange" onClick="fncRelayAjaxGet("get",1);" value ="2 Irrigatin " title="go irrigation 2, don't save this"/>

<hr/></p>
<p>

	
 <b>Programation <span id="scn_id0"></span> Mode: <span id="scn_mode0" >1</span> <span id="scn_mode0Txt"></span></b><span id="scn_isOpen0" class="led"></span>
 <br/>
 <label class="labelfrm" for="scn_name0"> Name:</label>
 <input type="text" id="scn_name0" name="scn_name0"  minlength="4" maxlength="15" size="15" /> 10-15 Chararcters
 <br/>
 
 <label class="labelfrm" for="scn_onOff0"> Switich:</label>
 <input type="radio" id="scn_onOff00" name="scn_onOff0" value="0" checked>
 <label for="scn_onOff00">Off</label>
 <input type="radio" id="scn_onOff01" name="scn_onOff0" value="1">
 <label for="scn_onOff01">On</label>
 <br/>
 <label class="labelfrm" for="scn_startHHMM0">Start Time:</label> 
 <input type="time" id="scn_startHHMM0" value="00;00" > 
 <br/>
  <label class="labelfrm" for="scn_minutes0"> minutes:</label> 
 <input type="range" name="scn_minutes0" id="scn_minutes0" value="1" min="1" max="59" 
 oninput="scn_minutes0Value.value = scn_minutes0.value">
 <output name="scn_minutes0Value" id="scn_minutes0Value">1</output><span class="soft"> Minutes</span>
 <br/>
 <label class="labelfrm" for="scn_intervalDays0">Interval days:</label> 
 <input type="range" name="scn_intervalDays0" id="scn_intervalDays0"   value="0" min="0" max="10" oninput="scn_intervalDays0Value.value = scn_intervalDays0.value">
 <output name="scn_intervalDays0Value" id="scn_intervalDays0Value">0</output><span class="soft"> Between days</span>
 <div id="scn_msg0" class="msg">.</div>
 <hr/></p>
 
<p>
 <b>Programation <span id="scn_id1"></span> Mode: <span id="scn_mode1" >1</span><span id="scn_mode1Txt"></b><span id="scn_isOpen1" class="led"></span>
 <br/>
 <label class="labelfrm" for="scn_name1"> Name:</label>
 <input type="text" id="scn_name1" name="scn_name1"  minlength="4" maxlength="15" size="15" /> 10-15 Chararcters
 <br/>
  <label class="labelfrm" for="scn_onOff1"> Switich:</label>
 <input type="radio" id="scn_onOff10" name="scn_onOff1" value="1" checked>
 <label for="scn_onOff10">Off</label>
 <input type="radio" id="scn_onOff11" name="scn_onOff1" value="1">
 <label for="scn_onOff11">On</label>
 <br/>
 <label class="labelfrm" for="scn_startHHMM1">Start Time:</label>
 <input type="time" id="scn_startHHMM1" value="00;01" > 
 <br/>
 <label class="labelfrm" for="scn_minutes1"> minutes:</label> 
 <input type="range" name="scn_minutes1" id="scn_minutes1" value="1" min="1" max="59"  oninput="scn_minutes1Value.value = scn_minutes1.value">
 <output name="scn_minutes1Value" id="scn_minutes1Value">1</output><span class="soft"> Minutes</span>
 <br/>
 <label class="labelfrm" for="scn_intervalDays1">Interval days:</label> 
 <input type="range" name="scn_intervalDays1" id="scn_intervalDays1"   value="1" min="1" max="11" oninput="scn_intervalDays1Value.value = scn_intervalDays1.value">
 <output name="scn_intervalDays1Value" id="scn_intervalDays1Value">0</output><span class="soft"> Between days</span>
 <div id="scn_msg1" class="msg">.</div>
  <hr/>
 </p>
 <p>
 <b>Programation <span id="scn_id2"></span> Mode: <span id="scn_mode2" >2</span><span id="scn_mode2Txt"></b><span id="scn_isOpen2" class="led"></span>
 <br/>
 <label class="labelfrm" for="scn_name2"> Name:</label>
 <input type="text" id="scn_name2" name="scn_name2"  minlength="4" maxlength="15" size="15" /> 10-15 Chararcters
 <br/>
   <label class="labelfrm" for="scn_minutes2"> minutes:</label> 
 <input type="range" name="scn_minutes2" id="scn_minutes2" value="2" min="1" max="10 
 oninput="scn_minutes2Value.value = scn_minutes2.value">
 <output name="scn_minutes2Value" id="scn_minutes2Value">1</output><span class="soft"> [1-10]Minutes</span>
  <input type="button" Class="button orange" onClick="fncJsonSendManualStart();" value ="Start" title="Manual start"/>
<input type="button" Class="button orange" onClick="fncJsonSendManualStop();" value ="Stop" title="manual stop"/>

   <div id="scn_msg2" class="msg">.</div>
 </p>
 </fieldset>

</div>


</div>

<script>
 const fncIsNull = (value) => typeof value === "object" && !value;
   let g_fldRelayId= "relayId";
  let g_fldRelayName= "relayName";
  let g_fldRelayIsOpen="relayIsOpen";
  let g_fldId="id";
  let g_fldName="name";
  let g_fldMode="mode"
  let g_fldOnOff="onOff";
  let g_fldStartHHMM="startHHMM";
  let g_fldIntervalDays="intervalDays";
  let g_fldMinutes="minutes";
  let g_fldIsOpen="isOpen";
  let g_fldMsg="msg";
  let g_scnPrefix="scn_";
  let msg="";
let obj ;

//===============================================
//===============================================
//===============================================
function fncRelayAjaxJson(option, idRelay)
{
	let aJson="";
	let pUrl="";
	if (option="set")
	{
			pUrl="/relayjson?set="+idRelay+"&json="+fncGetRelayJsonFromScreen();
	}
	if (option="get"){
		pUrl="/relayjson?get="+idRelay;
	}
 console.log("Enviado");
 console.log("fncRelayJsonGet pURL= " + pURL);

 var xhttp;
 var reply = "";
 xhttp = new XMLHttpRequest();
  
 xhttp.onreadystatechange = function() {
 if (xhttp.readyState == 4 && xhttp.status == 200) {
 message="";
 arrJson = xhttp.responseText;
 console.log("recibido");
 console.log(arrJson);
 fncFillJsonToScreen(arrJson);
 var now = new Date();
 now.setMinutes(now.getMinutes() - now.getTimezoneOffset());
 elem = document.getElementsByName("scnMessageDate");
 if(elem !== null && elem !== 'undefined' )
 {
  elem.innerHTML=now.toISOString().slice(0,16); }
}
 };

 console.log("xhttp.open(GET, pURL, true)");
 xhttp.open("GET", pURL, true);
 xhttp.send();

}

//================================================
 //-----------------------------------------------------------------------
 //-----------------------------------------------------------------------
 //-----------------------------------------------------------------------

function fncJsonFromScreenTest()
{
	fncGetRelayJsonFromScreen();
}
function fncGetRelayJsonFromScreen()
{
	
 /*
{
	"relayIrrigation": [{
		"relayId": "0",
		"relayName": "Irrigation 1"

	}],
	"prg": [{
		"id": "0",
		"name": "prg 0",
		"mode": "1",
		"onOff": "1",
		"startHHMM": "12:34",
		"minutes": "5",
		"intervalDays": "4"

	}, {
		"id": "1",
		"name": "prg 1",
		"mode": "1",
		"onOff": "0",
		"startHHMM": "14:34",
		"minutes": "2",
		"intervalDays": "1"

	}, {
		"id": "2",
		"name": "prg 2",
		"mode": "2"
	}] 
 */
 let isFisrtRow=true;
let isFirstValue=true;
let temp="";
let docId="";
let mode="";
let id="";

 console.clear();

 
  docId=g_scnPrefix+g_fldRelayId;
   console.log(g_fldRelayId+" "+docId);
   temp=document.getElementById(docId).innerHTML;
	let arrJson="{\"relayIrrigation\": [{";
	arrJson+=fncFillJsonPair(true,g_fldRelayId,temp)

	arrJson+="}], \"prg\": [";



for ( idPrg=0;idPrg<3;idPrg++) {
	if(isFisrtRow){	arrJson+="{";}else{arrJson+=", {";}
	isFisrtRow=false;
	isFirstValue=true;

	console.log(g_fldId);
	arrJson+=fncFillJsonPair(isFirstValue,g_fldId,document.getElementById(g_scnPrefix+g_fldId+idPrg).innerHTML) ;
	isFirstValue=false;
 	
  docId=g_scnPrefix+g_fldName+idPrg;
  console.log(g_fldRelayId+" "+docId);
  temp=document.getElementById(docId).value;
  arrJson+=fncFillJsonPair(isFirstValue,g_fldName,temp) ;
  	 
   docId=g_scnPrefix+g_fldMode+idPrg;
  console.log(g_fldRelayId+" "+docId);
  mode=document.getElementById(docId).innerHTML;
  arrJson+=fncFillJsonPair(isFirstValue,g_fldMode,mode) ;
   
  console.log("Mode="+mode);
   // aoutomatic mode only.
   if(mode!="2")
   {
   docId=g_scnPrefix+g_fldOnOff+idPrg;
  console.log(g_fldRelayId+" "+docId);;
   temp=fncGetRadioSelected(  g_scnPrefix+g_fldOnOff+idPrg);
   arrJson+=fncFillJsonPair(isFirstValue,g_fldOnOff,temp) ;
   
    docId=g_scnPrefix+g_fldStartHHMM+idPrg;
  console.log(g_fldStartHHMM+" "+docId);;
   temp=document.getElementById(docId).value;
    arrJson+=fncFillJsonPair(isFirstValue,g_fldStartHHMM,temp) ;
  
   console.log (g_fldMinutes);
   temp=document.getElementById(g_scnPrefix+g_fldMinutes+idPrg).value;
   arrJson+=fncFillJsonPair(isFirstValue,g_fldMinutes,temp) ;
   
   temp     =document.getElementById(g_scnPrefix+g_fldIntervalDays+idPrg);
   arrJson+=fncFillJsonPair(isFirstValue,g_fldIntervalDays,temp) ;
   arrJson+="}"
   }
  
}
arrJson+="}]}";
document.getElementById("scnMsgDebug").innerHTML=arrJson;
console.log(arrJson);
return arrJson;
 }
function fncFillJsonPair(isFirstValue,keyName, keyValue)
{
	let result="";
	if (isFirstValue==false) {result=", ";}
	 result+="\""+keyName+"\":\""+keyValue+"\"";
	
	return result;
	}
function fncGetRadioSelected(pNameRadio){
let result='';
let ele = document.getElementsByName(pNameRadio);
for(i = 0; i < ele.length; i++){
 if(ele[i].checked)
 {
 result = ele[i].value;
 }
}
return result;
}
<!-- -------------------- TEST -------------- -->


function fncJsonToScreenTest() {
var sJsonStringTest = '{\"relayIrrigation\": [{	\"relayId\": \"0\", \"relayName\": \"Irrigation 1\", \"relayIsOpen\": \"1\"	}],	\"prg\": [{\"id\": \"0\", \"name\": \"prg 0\", \"mode\": \"1\", \"onOff\": \"1\", \"startHHMM\": \"12:34\", \"startDate\": \"12/1/2023\", \"stopHHMM\": \"12:34\", \"stopDate\": \"12/2/2023\", \"minutes\": \"5\", \"intervalDays\": \"4\", \"isOpen\": \"1\", \"msg\": \"msg 1\"}, {\"id\": \"1\", \"name\": \"prg 1\", \"mode\": \"1\", \"onOff\": \"0\", \"startHHMM\": \"14:34\", \"startDate\": \"12/1/23\", \"stopHHMM\": \"12:34\", \"stopDate\": \"12/2/23\", \"minutes\": \"2\", \"intervalDays\": \"1\", \"isOpen\": \"1\", \"msg\": \"msg 1\"}, {\"id\": \"2\", \"name\": \"prg 2\", \"mode\": \"2\", \"onOff\": \"0\", \"startHHMM\": \"16:00\", \"startDate\": \"12/1/23\", \"stopHHMM\": \"12:34\", \"stopDate\": \"12/2/23\", \"minutes\": \"15\", \"intervalDays\": \"2\", \"isOpen\": \"0\", \"msg\": \"msg 1\"}]}';
fncFillJsonToScreen(sJsonStringTest);
}
//===============================================
//===============================================
//===============================================

function fncFillJsonToScreen(arrJson){
let scnFld="";
console.log("---------------------aqui reply from  esp32");
console.log(arrJson);

document.getElementById("scnMsgDebug").innerHTML=arrJson;
scnFld=g_scnPrefix+ g_fldRelayName;
console.log(scnFld);
document.getElementById(scnFld).innerHTML="";
scnFld=g_scnPrefix+ g_fldRelayId;
console.log(scnFld);
document.getElementById(scnFld).innerHTML="";

scnFld=g_scnPrefix+g_fldRelayIsOpen;

LineIsOpen=false;

//document.getElementById(g_scnLineIsOpen).background-color="#666666";

/*
{
	"relayIrrigation": [{
		"relayId": "0",
		"relayName": "Irrigation 1",
		"relayIsOpen":"1"
	}],
	"prg": [{
		"id": "0",
		"name": "prg  0",
		"mode": "1",
		"onOff": "0",
		"startHHMM": "12:34",
		"startDate": "12/1/23",
		"stopHHMM": "12:34",
		"stopDate": "12/2/23",
		"minutes": "5",
		"intervalDays": "1",
		"isOpen": "1",
		"msg": "msg 1"
	},
*/
let mode="";
let msg="";
obj = JSON.parse(arrJson);

scnFld=g_scnPrefix+ g_fldRelayId;
console.log(scnFld);
document.getElementById(scnFld).innerHTML=obj.relayIrrigation[0].relayId;


scnFld=g_scnPrefix+ g_fldRelayName;
console.log(scnFld);
document.getElementById(scnFld).innerHTML=obj.relayIrrigation[0].relayName 

scnFld=g_scnPrefix+ g_fldRelayIsOpen;
console.log(scnFld);
if(obj.relayIrrigation[0].relayIsOpen =="1")
{
	document.getElementById(scnFld).style.backgroundColor="#009900";
	document.getElementById(scnFld).style.backgroundColor="#009900";
}
else
{
 	document.getElementById(scnFld).style.backgroundColor="#990000";
}

//------------------------------------------------
for (let k = 0; k < obj.prg.length; k++)
{
scnFld=g_scnPrefix+ g_fldId+k;
console.log(scnFld);
document.getElementById(scnFld).innerHTML=parseInt(obj.prg[k].id)+1;

scnFld=g_scnPrefix+ g_fldName+k;
console.log(scnFld);
document.getElementById(scnFld).value=obj.prg[k].name;




scnFld=g_scnPrefix+ g_fldMode+k;
let scnFldTxt=scnFld+"Txt";
let modeTxt="";
console.log(scnFld+" =" +mode);
mode=obj.prg[k].mode;
if(obj.prg[k].mode=="1"){modeTxt=" Automatic";}else{modeTxt=" manual";}
document.getElementById(scnFld).innerHTML=mode;
document.getElementById(scnFldTxt).innerHTML=modeTxt;


//------------------------------------------- only automatic start
	if(obj.prg[k].mode=="1")
	{
		
scnFld=g_scnPrefix+g_fldOnOff+k+obj.prg[k].onOff;
console.log(scnFld);
document.getElementById(scnFld).checked=true;
scnFld=g_scnPrefix+ g_fldStartHHMM+k;
console.log(scnFld);
document.getElementById(scnFld).value=obj.prg[k].startHHMM;

	
scnFld=g_scnPrefix+ g_fldIntervalDays+k;
console.log(scnFld);
document.getElementById(scnFld).value=obj.prg[k].intervalDays;	
scnFld+="Value";
console.log(scnFld);
document.getElementById(scnFld).value=obj.prg[k].intervalDays;
	
}
//------------------------------------------- only automatic end
scnFld=g_scnPrefix+ g_fldMinutes+k;
console.log(scnFld);
document.getElementById(scnFld).value=obj.prg[k].minutes;
scnFld+="Value";
console.log(scnFld);
document.getElementById(scnFld).value=obj.prg[k].minutes;

scnFld=g_scnPrefix+ g_fldIsOpen+k;
console.log(scnFld);
if(obj.prg[k].isOpen=="1")
{
	document.getElementById(scnFld).style.backgroundColor="#009900";
	document.getElementById(scnFld).style.backgroundColor="#009900";
}
else
{
 	document.getElementById(scnFld).style.backgroundColor="#990000";
}

msg="";
msg+="Start "+ obj.prg[k].startDate+" at "+obj.prg[k].startHHMM;
msg+=", Stop " +obj.prg[k].stopDate +" at "+ obj.prg[k].stopHHMM;
if(obj.prg[k].msg!="") {msg+="<br/> "+obj.prg[k].msg;}
scnFld=g_scnPrefix+ g_fldMsg+k;
console.log(scnFld);
document.getElementById(scnFld).innerHTML=msg;

 }

}
document.addEventListener("DOMContentLoaded", () => {fncRelayAjaxJson("get", 0);});
</script>
</div></body></html>
)=====";
#endif
