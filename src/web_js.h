//javascripts
// validator https://jshint.com/
//https://codebeautify.org/jsviewer
#ifndef WEB_JS_H
#define WEB_JS_H
const char g_HTML_Web_JS[] PROGMEM = R"=====(
//..................
var g_Ajax_XHR;

function fncCfggetConfig() {
 g_Ajax_XHR = fncBuildXMLHttpRequest();
 g_Ajax_XHR.onreadystatechange = fncAjax_ConfigFill;
 g_Ajax_XHR.open("GET", "configget");
 g_Ajax_XHR.send(null);
 return false;
}
//..................
function fncBuildXMLHttpRequest() {
 g_Ajax_XHR = new XMLHttpRequest();
 return g_Ajax_XHR;
}


//..................
function fncGetAjax(pURL) {
 console.log("fncGetAjax pURL= " + pURL);
 var xhttp;
 var reply = "";
 xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
  if (xhttp.readyState == 4 && xhttp.status == 200) {
   reply = xhttp.responseText;
   console.log(reply);
   return "reply";
  }
 };
 xhttp.open("GET", pURL, true);
 xhttp.send();
}

function fncGetHtml(pDivTarget, pURL) {
 console.log("pDivTarget=" + pDivTarget + "\n pURL= " + pURL);

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

function fncMsg(pDivTarget, msg) {
 document.getElementById(pDivTarget).innerHTML = msg;
 return false;
}


function fncStrContainsStr(strMain, strFind) {
 return (strMain.indexOf(strFind) != -1 ? true : false);
}


function fncCfgTogglePwds(fieldid, oFrom) {
 var temp = document.getElementById(fieldid);
 if (temp.type === "password") {
  temp.type = "text";
  oFrom.innerHTML = "hide";
 } else {
  temp.type = "password";
  oFrom.innerHTML = "show";
 }
}

function fncCfgMsgCfg(scnFieldId, Msg) {
 document.getElementById(scnFieldId).innerHTML = Msg;
}



function fncCfgIsIPaddress(fldId, fldIdMsg, msg) {
 var ipformat = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
 var fld = document.getElementById(fldId);

 if (fld.value.match(ipformat)) {
  fncMsgError(fldIdMsg, "");
  fld.focus();
  return true;
 } else {
  fncMsgError(fldIdMsg, msg);
  return false;
 }
}

function fncCfgIsMinLenght(idFldChk, idFldMsg, Msg, MinLenght) {
 var isEmpty = false;
 var oValue = document.getElementById(idFldChk).value.trim();
 var oMsg = document.getElementById(idFldMsg);
 oMsg.value = "";
 oMsg.innerHTML = "";
 if (oValue.length < MinLenght) {
  var msg = " " + Msg + " or less than " + MinLenght;
  fncMsgError(idFldMsg, msg);
  isEmpty = true;
 } else {
  fncMsgError(idFldMsg, "");
  isEmpty = false;
 }
 return isEmpty;
}

function fncMsgError(idFldMsg, msg) {
 var oMsg = document.getElementById(idFldMsg);
 oMsg.innerHTML = msg;
 if (msg == "") {
  oMsg.style.display = true;
  oMsg.innerHTML = "&#x2714;";
  oMsg.style.backgroundColor = "#fff";
  oMsg.style.color = "#090";
 } else {
  oMsg.style.display = true;
  oMsg.style.backgroundColor = "#900";
  oMsg.style.color = '#fff';
 }
}
function fncGpsNavigatorGetInner()
{
  var szurl="http://www.google.com/maps/place/"+document.getElementById("scnGPS").innerHTML;
   //console.log("open= " + szurl);
  window.open(szurl);
  }
function fncGpsNavigatorGet()
{
  //http://www.google.com/maps/place/49.46800006494457,17.11514008755796
  var szurl="http://www.google.com/maps/place/"+document.getElementById("scnGPS").value;
   //console.log("open= " + szurl);
  window.open(szurl);
  }
//---------------



)=====";
#endif