#include <WiFi.h>
#include <WebServer.h>

#define DIGITAL_PIN 21  // DO connected here

// Wi-Fi Access Point credentials
const char* ssid = "ESP32_Moisture";
const char* password = "";

// Web server
WebServer server(80);

int moistureDigital = 0;

// HTML, CSS & JS interface
String getHTMLPage() {
  String html = "<!DOCTYPE html><html lang='en'><head>";
  html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Soil Moisture Monitor</title>";
  html += "<style>";
  html += "body { font-family: 'Segoe UI', Tahoma, sans-serif; background: linear-gradient(135deg,#74ebd5,#ACB6E5); margin:0; padding:0; display:flex; justify-content:center; align-items:center; height:100vh; }";
  html += ".card { background:#fff; padding:30px; border-radius:20px; box-shadow:0 8px 20px rgba(0,0,0,0.2); width:350px; text-align:center; transition:0.3s; }";
  html += ".card:hover { transform: scale(1.02); }";
  html += "h1 { color:#333; margin-bottom:20px; }";
  html += ".value { font-size:2rem; margin:15px 0; color:#222; }";
  html += ".status { font-size:1.5rem; padding:10px; border-radius:10px; display:inline-block; margin-top:10px; }";
  html += ".wet { background:#d0f0fd; color:#0077b6; }";
  html += ".dry { background:#fde2e4; color:#d90429; }";
  html += ".footer { margin-top:20px; font-size:0.8rem; color:#666; }";
  html += "</style>";
  html += "<script>";
  html += "function updateData(){ fetch('/data').then(r=>r.json()).then(d=>{";
  html += "document.getElementById('digital').innerText = d.digital;";
  html += "let statusEl=document.getElementById('status');";
  html += "statusEl.innerText = d.status;";
  html += "if(d.digital==0){ statusEl.className='status wet'; } else { statusEl.className='status dry'; }";
  html += "}); }";
  html += "setInterval(updateData,1000); window.onload=updateData;";
  html += "</script></head><body>";
  html += "<div class='card'>";
  html += "<h1>🌱 Soil Moisture</h1>";
  html += "<div class='value'>Digital Value: <span id='digital'>--</span></div>";
  html += "<div id='status' class='status'>--</div>";
  html += "<div class='footer'>ESP32 Moisture Monitor</div>";
  html += "</div></body></html>";
  return html;
}

// Serve main page
void handleRoot() {
  server.send(200, "text/html", getHTMLPage());
}

// Serve JSON data
void handleData() {
  String status;
  if (moistureDigital == LOW) status = "WET (below threshold)";
  else status = "DRY (above threshold)";

  String json = "{";
  json += "\"digital\": " + String(moistureDigital) + ",";
  json += "\"status\": \"" + status + "\"";
  json += "}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  pinMode(DIGITAL_PIN, INPUT);

  // Start Wi-Fi AP
  WiFi.softAP(ssid, password);
  Serial.println("ESP32 Access Point Started");
  Serial.print("SSID: "); Serial.println(ssid);
  Serial.print("Password: "); Serial.println(password);
  Serial.print("IP Address: "); Serial.println(WiFi.softAPIP());

  // Routes
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
  Serial.println("Web server running...");
}

void loop() {
  server.handleClient();

  // Read sensor
  moistureDigital = digitalRead(DIGITAL_PIN);

  // Serial output
  Serial.print("Digital Value: ");
  Serial.println(moistureDigital);

  if (moistureDigital == LOW) {
    Serial.println("DO: Soil is WET (below threshold)");
  } else {
    Serial.println("DO: Soil is DRY (above threshold)");
  }

  Serial.println("--------------------");
  delay(1000);
}
