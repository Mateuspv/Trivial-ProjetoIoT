#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char* ssid = "PROF.RAFAEL";
const char* password = "";
ESP8266WebServer server(80);
const int output5 = 5;  // D1
IPAddress local_IP(192, 168, 1, 19); // Troque o IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void handleRoot();
void handleToggle();

void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<link rel=\"icon\" href=\"data:,\">";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  html += ".switch { position: relative; display: inline-block; width: 60px; height: 34px;}";
  html += ".switch input { opacity: 0; width: 0; height: 0;}";
  html += ".slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; -webkit-transition: .4s; transition: .4s;}";
  html += ".slider:before { position: absolute; content: \"\"; height: 26px; width: 26px; left: 4px; bottom: 4px; background-color: white; -webkit-transition: .4s; transition: .4s;}";
  html += "input:checked + .slider { background-color: #2196F3;}";
  html += "input:focus + .slider { box-shadow: 0 0 1px #2196F3;}";
  html += "input:checked + .slider:before { -webkit-transform: translateX(26px); -ms-transform: translateX(26px); transform: translateX(26px);}";
  html += "</style></head>";
  html += "<body><h1>ESP8266 Web Server</h1>";
  html += "<h2>Prof. Rafael</h2>";
  html += "<label class=\"switch\">";
  html += "<input type=\"checkbox\" onclick=\"toggleLED(this.checked)\">";
  html += "<span class=\"slider\"></span>";
  html += "</label>";
  html += "<script>";
  html += "function toggleLED(state) {";
  html += " var xhr = new XMLHttpRequest();";
  html += " xhr.open('GET', '/toggle?state=' + state, true);";
  html += " xhr.send();";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleToggle() {
  String state = server.arg("state");
  if (state == "true") {
    digitalWrite(output5, HIGH);
    server.send(200, "text/plain", "LED Ligado!");
  } else {
    digitalWrite(output5, LOW);
    server.send(200, "text/plain", "LED Desligado!");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(output5, OUTPUT);
  digitalWrite(output5, LOW);
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", HTTP_GET, handleRoot);
  server.on("/toggle", HTTP_GET, handleToggle);
  server.begin();
}

void loop() {
  server.handleClient();
}
