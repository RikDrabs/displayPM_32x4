/************************************************************************
 * Adapted from parts of the AirRohr firmware                           *
 * Copyright (C) 2016-2020  Code for Stuttgart a.o.                     *
 * Copyright (C) 2019-2020  Dirk Mueller                                *
 * Copyright (C) 2021-2025  Sensor.Community                            *
 * Modifs/additions Copyright (C) 2025  Rik Drabs                       *
 *                                                                      *
 * This program is free software: you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * This program is distributed in the hope that it will be useful,      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with this program. If not, see <http://www.gnu.org/licenses/>. *
 *                                                                      *
 ************************************************************************/
const char TXT_CONTENT_TYPE_JSON[]       PROGMEM = "application/json";
const char TXT_CONTENT_TYPE_TEXT_HTML[]  PROGMEM = "text/html; charset=utf-8";
const char TXT_CONTENT_TYPE_TEXT_CSS[]   PROGMEM = "text/css";
const char TXT_CONTENT_TYPE_TEXT_PLAIN[] PROGMEM = "text/plain";
const char TXT_CONTENT_TYPE_IMAGE_PNG[]  PROGMEM = "image/png";

const char WEB_PAGE_HEADER[] PROGMEM = "\
<!DOCTYPE html><html lang='" INTL_LANG "'>\
<head><meta charset='utf-8'/>\
<title>{t}</title>";

const char WEB_PAGE_STATIC_CSS[] PROGMEM = "\
body{font-family:Arial,sans-serif;margin:0}\
.content{margin:10px}\
.footer{height:48px;background:#f5f5f5;width:100%}\
.r{text-align:right}\
td{vertical-align:top}\
.v>tbody>tr:nth-child(odd){background:#efefef}\
.b{text-decoration:none;padding:10px;background:#2a9;color:#fff;display:block;width:auto;border-radius:5px;}\
.wifi{background:0 0;color:#00f;padding:5px;display:inline;border:0;}\
input[type=text]{width:100%}\
input[type=password]{width:100%}\
input[type=submit]{color:#fff;text-align:left;cursor:pointer;border-radius:5px;\
font-size:medium;background:#b33;padding:9px!important;width:100%;border-style:none}\
input[type=submit]:hover{background:#d44}\
.s_green{padding:9px !important;width:100%;border-style:none;background:#3ba;color:#fff;text-align:left}\
.tabs{display:flex;flex-direction:row;align-items:stretch;align-content:flex-end;justify-content:flex-start}\
.tab{padding:10px 20px;display:inline-block;color:#333}\
.panels{min-height:200px;overflow:hidden;padding:20px;border:2px solid #3ba;margin-bottom:1em;}\
.radio{display:none}.panel{display:none}\
.canvas{min-height:118px;background:#3ba;margin-bottom:20px;}\
#r1:checked~.panels>#panel1,#r3:checked~.panels>#panel3,#r4:checked~.panels>#panel4,\
#r5:checked~.panels>#panel5,#r2:checked~.panels>#panel2{display:block}\
#r1:checked~.tabs>#tab1,#r3:checked~.tabs>#tab3,#r4:checked~.tabs>#tab4,\
#r5:checked~.tabs>#tab5,#r2:checked~.tabs>#tab2{background:#3ba;color:#fff}";

#define STATIC_PREFIX "/" INTL_LANG "_s1"

const char WEB_PAGE_HEADER_HEAD[] PROGMEM = "<meta name='viewport' content='width=device-width'/>\
<meta name='theme-color' content='#3ba'>\
<link rel='stylesheet' href='" STATIC_PREFIX "?r=css'>\
</style></head><body><div class='canvas'>\
<a class='b' href='/' style='background:none;display:inline'>\
<img src='" STATIC_PREFIX "?r=logo' alt='" INTL_BACK_TO_HOME_PAGE "' style='float:left;margin:16px' width='100' height='89'/></a>";

const char WEB_PAGE_HEADER_BODY[] PROGMEM = "<h3 style='color:#fff;margin:0 10px'>" INTL_DISPLAY "</h3>\
<br/><small style='color:#fff;font-weight:700'>&copy; 2019-2025 InfluencAir \
<br/>" INTL_FIRMWARE SOFTWARE_VERSION_STR " / " INTL_LANG "&nbsp;(" __DATE__ ")\
<br/></small></div><div class='content'><h4>" INTL_HOME " {n} {t}</h4>";

const char WEB_PAGE_FOOTER1[] PROGMEM = "<br/><br/>\
<a class='b' href='/' style='display:inline;'>" INTL_BACK_TO_HOME_PAGE "</a><br/>";

const char WEB_PAGE_FOOTER2[] PROGMEM = "<br/><br/>\
<a class='b' href='/' style='display:inline;'>" INTL_BACK_TO_HOME_PAGE_DISCARD "</a><br/>";

const char BR_TAG[] PROGMEM = "<br/>";
const char WEB_DIV_PANEL[] PROGMEM = "</div><div class='panel' id='panel{v}'>";
const char TABLE_TAG_OPEN[] PROGMEM = "<table>";
const char TABLE_TAG_CLOSE_BR[] PROGMEM = "</table>";
const char EMPTY_ROW[] PROGMEM = "<tr><td colspan='3'>&nbsp;</td></tr>";

const char WEB_UPTIME[] PROGMEM = "\
<h4>" INTL_UPTIME "{t}<br/>" INTL_RESET_REASON "{r}</h4>";

const char WEB_READUPTO[] PROGMEM = "\
<h4>" INTL_READ_UPTO "{r}</h4>";

const char WEB_PAGE_FOOTER[] PROGMEM = "<br/><br/>\
</div><footer class='footer'><div style='padding:16px'>\
<a href='https://github.com/luchtpijp/displayPM' target='_blank' rel='noreferrer' style='color:#3ba;'>\
&copy; DisplayPM on GitHub </a>&nbsp;&nbsp\
(<a href='mailto:influencair2017@gmail.com' target='_blank' rel='noreferrer'>" INTL_REPORT_ISSUE "</a>)\
</div></footer></body></html>\r\n";

const char WEB_ROOT_PAGE_CONTENT[] PROGMEM = "\
<a class='b' href='/values'>{t}</a><br/>\
<a class='b' href='/config'>{conf}</a><br/>\
<a class='b' href='/param'>{param}</a><br/>\
<a class='b' href='/removeConfig'>{confdel}</a><br/>\
<a class='b' href='/reset'>{restart}</a><br/>";

const char WEB_REMOVE_CONFIG_CONTENT[] PROGMEM = "<h3>" INTL_CONFIGURATION_REALLY_DELETE "</h3>\
<table><tr><td><form method='POST' action='/removeConfig'>\
<input type='submit' class='s_red' name='submit' value='" INTL_DELETE "'/></form></td>\
<td><a class='b' href='/'>" INTL_CANCEL "</a></td></tr></table>";

const char WEB_RESET_CONTENT[] PROGMEM = "<h3>" INTL_REALLY_RESTART_DISPLAY "</h3>" \
"<table><tr><td><form method='POST' action'/reset'>" \
"<input type='submit' class='s_red' name='submit' value='" INTL_RESTART "'/>"\
"</form></td><td><a class='b' href='/'>" INTL_CANCEL "</a></td></tr></table>";

const char WEB_CONFIG_SCRIPT[] PROGMEM = "<script>\
function setSSID(ssid){document.getElementById('wlanssid').value=ssid.innerText||ssid.textContent;document.getElementById('wlanpwd').focus();}\
function load_wifi_list(){var x=new XMLHttpRequest();x.open('GET','/wifi');x.onload = function(){if (x.status === 200) {document.getElementById('wifilist').innerHTML = x.responseText;}};x.send();}\
</script>";

const char SET_SSID_SCRIPT[] PROGMEM = "<script>\
function setSSID(ssid){document.getElementById('wlanssid')\
.value=ssid.innerText||ssid.textContent;\
document.getElementById('wlanpwd').focus();}</script>";

const char WIFI_LIST_SCRIPT[] PROGMEM = "<script>\
function load_wifi_list(){var x=new XMLHttpRequest();\
x.open('GET','/wifi');\
x.onload = function(){if (x.status === 200) \
{document.getElementById('wifilist').innerHTML = x.responseText;}};\
x.send();}</script>";

const char WEB_IOS_REDIRECT[] PROGMEM = "<html><body>Redirecting...\
<script type=\"text/javascript\">\
window.location = \"http://192.168.4.1/config\";\
</script>\
</body></html>";

const char WEB_B_BR_BR[] PROGMEM = "</b><br/><br/>";
const char WEB_BRACE_BR[] PROGMEM = ")<br/>";
const char WEB_B_BR[] PROGMEM = "</b><br/>";
const char WEB_BR_BR[] PROGMEM = "<br/><br/>";
const char WEB_BR_FORM[] PROGMEM = "<br/></form>";
const char WEB_BR_LF_B[] PROGMEM = "<br/>\n<b>";
const char WEB_LF_B[] PROGMEM = "\n<b>";
const char WEB_NBSP_NBSP_BRACE[] PROGMEM = "&nbsp;&nbsp;(";
const char WEB_REPLN_REPLV[] PROGMEM = "\"{n}\":\"{v}\",";

const char WEB_PAGE_FORM_INPUT[] PROGMEM = "\
<tr><td title='[&lt;= {l}]'{o}>{i}:&nbsp;</td>\
<td style='width:{l2}em'>\
<input type='{t}' name='{n}' id='{n}' placeholder='{i}' value='{v}' maxlength='{l}'/>\
</td></tr>";

const char WEB_PAGE_FORM_SUBMIT[] PROGMEM = "\
<input type='submit' name='submit' value='{v}' />";

const char WEB_PAGE_ROW_SEL_TITLE[] PROGMEM = "\
<table cellspacing='2' cellpadding='5' class='v'><b><tr>\
<th style='width:{w1}em'> {n1} </th>\
<th style='width:{w2}em'> {n2} </th>\
<th style='width:{w3}em'> {n3} </th>\
</tr></b>";

const char WEB_PAGE_ROW_SELECT[] PROGMEM = "<tr>\
<td style='width:{w}em'>{nam1}</td>\
<td style='width:{w}em'>{nam2}</td>\
<td style='width:{w1}em'>{val1} {val2} </td>\
</tr>";

const char WEB_LOCATION_ROW_TITLE[] PROGMEM = "\
<table cellspacing='2' cellpadding='5' class='v'><b><tr>\
<th style='width:{wn}em'>{n}</th>\
<th style='width:{w1}em'>{1}</th>\
<th style='width:{w2}em'>{2}</th>\
<th style='width:{w3}em'>{3}</th>\
<th style='width:{w4}em'>{4}</th>\
</tr></b>";

const char WEB_PAGE_ROW_INPUT[] PROGMEM = "<tr>\
<td style='width:{wn}em'><input type={tx} name='{nn}' id='{nn}' value='{vn}' maxlength='{wn}'/></td>\
<td style='width:{w1}em'><input type={tx} name='{n1}' id='{n1}' value='{v1}' maxlength='{w1}'/></td>\
<td style='width:{w2}em'><input type={tx} name='{n2}' id='{n2}' value='{v2}' maxlength='{w2}'/></td>\
<td style='width:{w3}em'><input type={tx} name='{n3}' id='{n3}' value='{v3}' maxlength='{w3}'/></td>\
<td style='width:{w4}em'><input type={tx} name='{n4}' id='{n4}' value='{v4}' maxlength='{w4}'/></td>\
</tr>";

const char WEB_PAGE_HOR_RADIO2[] PROGMEM = "{i}\
<td style='width:5em'><input type='radio' id='pm25' name='{n}' value='0' {c0}>\
<label for='pm25'> PM2.5</label></td>\
<td style='width:5em'><input type='radio' id='pm10' name='{n}' value='1' {c1}>\
<label for='pm10'> PM10</label></td>\
<br>";

const char WEB_PAGE_VERT_RADIO2[] PROGMEM = "<style>\
.radio-group{display:flex; flex-direction:column;}</style>\
<form action=''><div class='radio-group'>\
<label><input type='radio' name='{n}' value='0' {c0}> {i0} </label>\
<label><input type='radio' name='{n}' value='1' {c1}> {i1} </label>\
</div></form>";

const char WEB_PAGE_FORM_CHECKBOX[] PROGMEM = "\
<label for='{n}'>\
<input type='checkbox' name='{n}' value='1' id='{n}' {c}/>\
<input type='hidden' name='{n}' value='0'/>\
{i}</label><br/>";
