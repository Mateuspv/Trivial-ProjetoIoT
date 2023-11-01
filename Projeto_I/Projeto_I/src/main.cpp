#include<Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configurações da rede Wi-Fi
const char* ssid = "HOME";      // Nome da rede Wi-Fi
const char* password = "senhasenha";  // Senha da rede Wi-Fi

// Criação de um objeto do servidor web na porta 80
ESP8266WebServer server(80);

// Pino de saída conectado ao LED (D1 no ESP8266)
const int output5 = 5; // D1

// Configuração de endereço IP estático para o ESP8266
IPAddress local_IP(192,168,1,169);  // Endereço IP do dispositivo
IPAddress gateway(192,168,1,1);     // Endereço IP do gateway (roteador)
IPAddress subnet(255,255,255,0);    // Máscara de sub-rede

// Funções para lidar com solicitações HTTP
void handleRoot();
void handleOn();
void handleOff();

void handleRoot() {
  // Constrói uma página web simples com botões para controlar o LED
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<link rel=\"icon\" href=\"data:,\">";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  html += ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;";
  html += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
  html += ".button2 {background-color: #77878A;}</style></head>";
  html += "<body><h1>ESP8266 Web Server</h1>";
  html += "<h2>Prof. Rafael</h2>";
  html += "<button onclick=\"toggleLED('on')\" class=\"button\">ON</button>";
  html += "<button onclick=\"toggleLED('off')\" class=\"button button2\">OFF</button>";
  html += "<script>";
  html += "function toggleLED(state) {";
  html += " var xhr = new XMLHttpRequest();";
  html += " xhr.open('GET', '/5/' + state, true);";
  html += " xhr.send();";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(output5, HIGH);  // Liga o LED
  server.send(200, "text/plain", "LED Ligado!");  // Envia uma resposta simples
}

void handleOff() {
  digitalWrite(output5, LOW);  // Desliga o LED
  server.send(200, "text/plain", "LED Desligado!");  // Envia uma resposta simples
}

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial para depuração
  pinMode(output5, OUTPUT);  // Define o pino D1 como saída
  digitalWrite(output5, LOW);  // Inicialmente, desliga o LED

  // Configura o endereço IP estático
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password);  // Conecta-se à rede Wi-Fi

  // Aguarda a conexão com a rede Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Configura os tratadores de solicitações HTTP
  server.on("/", HTTP_GET, handleRoot);
  server.on("/5/on", HTTP_GET, handleOn);
  server.on("/5/off", HTTP_GET, handleOff);

  server.begin();  // Inicia o servidor web na porta 80
}

void loop() {
  server.handleClient();  // Lida com as solicitações HTTP dos clientes
}
