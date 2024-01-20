//*************************************************************************
// Web page for display setup
//
// HTML page on remote
String sendHTML() {
  String ptr="<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>sensor.community display</title>\n";
  ptr += "<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: left;}\n";
  ptr += "body {margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Sensor.community configurable display</h1>\n";

  /*
  ptr += "<p>Welcome: "; ptr += tempInDoor; ptr += "&deg;C</p>";
  ptr += "<p>Buiten: "; ptr += tempOutDoor; ptr += "&deg;C</p>";
  ptr += "<p>Pre-Collector: "; ptr += tempPreCollector; ptr += "&deg;C</p>";
  ptr += "<p>Mid-Collector: "; ptr += tempMidCollector; ptr += "&deg;C</p>";
  ptr += "<p>Post-Collector: "; ptr += tempPostCollector; ptr += "&deg;C</p>";
  ptr += "<p>ByPass: "; ptr += tempByPass; ptr += "&deg;C</p>";
  ptr += "<p>Top Vat: "; ptr += tempTopBarrel; ptr += "&deg;C</p>";
  ptr += "<p>Bodem Vat: "; ptr += tempBottomBarrel; ptr += "&deg;C</p>";
  ptr += "<p>Pre-Radiator: "; ptr += tempPreRadiator; ptr += "&deg;C</p>";
  ptr += "<p>Post-Radiator: "; ptr += tempPostRadiator; ptr += "&deg;C</p>";
  ptr += "<p>Gewenste temp: "; ptr += TEMPinDemand; ptr += "&deg;C</p>";
  ptr += "<p>Op tijdstip: "; ptr += "00:00"; ptr += "</p>";
  ptr += "<p>Collector Status: "; ptr += statusHeatingMes [heatingState]; ptr += "</p>";
  ptr += "<p>Verwarming Status: "; ptr += statusWarmingMes [warmingState]; ptr += "</p>";
  ptr += "<p>Control Status: "; ptr += statusControlMes [controlState]; ptr += "</p>"; 
  */
  ptr += "<script>"; 
  ptr += "response.setHeader";
  /*
  ptr += "("Refresh", "0; URL="request.getContextPath()")"; 
  */
  ptr += "</script>";
  //
  ptr += "</div>\n"; 
  ptr += "</body>\n"; 
  ptr += "</html>\n";
  return ptr;
}
