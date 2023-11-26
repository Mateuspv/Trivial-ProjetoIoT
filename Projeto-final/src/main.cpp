#include <Arduino.h>
#include <ESP8266WiFi.h>

#define umidadeAnalogica A0 // Atribui o pino A0 à variável umidade - leitura analógica do sensor

const char* ssid = "Mateus";      // Nome da sua rede Wi-Fi
const char* password = "mat252525";  // Senha da sua rede Wi-Fi

int valorUmidade; // Declaração da variável que armazenará o valor da umidade lida - saída analógica
boolean validaTroca = true;
boolean ativadorTimer = false;
unsigned long tempoDeDesligamento;
unsigned long DuracaoDeDesligamento = 12000;
int tempoDesligamento = tempoDeDesligamento + DuracaoDeDesligamento - millis()/1000;

WiFiServer server(80);

void setup() {
  IPAddress local_IP(192,168,1,133);  // Endereço IP fixo para o ESP8266
  IPAddress gateway(192,168,0,1);     // Gateway da rede
  IPAddress subnet(255,255,255,0);    // Máscara de sub-rede

  Serial.begin(9600); // Inicia a comunicação serial
  pinMode(umidadeAnalogica, INPUT); // Define umidadeAnalogica como entrada

  Serial.println();
  Serial.println("Conectando-se a " + String(ssid));


  WiFi.begin(ssid, password);  // Conecta-se à rede Wi-Fi

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conexão WiFi estabelecida");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  server.begin();  // Inicia o servidor web
}


void loop() {
  valorUmidade = analogRead(umidadeAnalogica); // Realiza a leitura analógica do sensor e armazena em valorumidade
  valorUmidade = map(valorUmidade, 1023, 315, 0, 100); // Transforma os valores analógicos em uma escala de 0 a 100

if (validaTroca == true){
  if (valorUmidade >= 40){
  Serial.print("Solo Umido ");
  Serial.print(valorUmidade);
  Serial.println(" %");
}else{
  Serial.println("Ligado Sprinter");
  validaTroca = false;
  }
}
if (validaTroca == false){
  if (valorUmidade < 40){
    Serial.print("Solo Seco ");
    Serial.print(valorUmidade);
    Serial.println(" %, Agua Ligada");
  }
  else if(valorUmidade > 40 && ativadorTimer == false){
    Serial.println("Solo está umido, Desativando Sprinter");
    tempoDeDesligamento = millis();
    ativadorTimer = true; 
  }
}

if(ativadorTimer == true){
  if(tempoDeDesligamento + DuracaoDeDesligamento < millis()){
  validaTroca = true;
  ativadorTimer = false;
  }
  else{
    Serial.println("Desligando Sprinter em:");
    Serial.println((tempoDeDesligamento + DuracaoDeDesligamento - millis())/1000);
  }
}

WiFiClient client;

String url = "/get-sensor-data?umidade=" + String(valorUmidade) + "&validartroca=" + String(validaTroca) + "&tempoDesligamento=" + String(tempoDesligamento) + "&ativadorTimer=" + String(ativadorTimer) ;

  if (client.connect("192.168.0.101", 5000)) {  // Conecta-se ao servidor web
    Serial.println("Conectado ao servidor");

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: 192.168.0.101\r\n" +
                 "Connection: close\r\n\r\n");
    // Envia uma requisição GET HTTP para o servidor com a URL construída

    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
      }
    }

    client.stop();  // Encerra a conexão com o servidor web
  } else {
    Serial.println("Connection to server failed");
  }

  delay(1000);  // Aguarda 1 segundo antes de enviar os dados novamente
}





