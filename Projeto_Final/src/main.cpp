#include <Arduino.h>
#include <ESP8266WiFi.h>

// Definição do pino analógico para leitura do sensor de umidade
#define umidadeAnalogica A0

// Credenciais da rede Wi-Fi
const char* ssid = "Mateus";
const char* password = "mat252525";

// Variáveis globais para controle do sistema
int valorUmidade;                 // Valor da umidade lida - saída analógica
boolean validaTroca = true;       // Indica se a troca de estado do sistema é válida
boolean ativadorTimer = false;    // Ativa o temporizador para desligar o sistema
unsigned long tempoDeDesligamento; // Tempo em que o sistema foi desligado
unsigned long DuracaoDeDesligamento = 12000; // Duração do período de desligamento (em milissegundos)
int tempoDesligamento = tempoDeDesligamento + DuracaoDeDesligamento - millis() / 1000;

WiFiServer server(80); // Inicia o servidor web na porta 80

void setup() {
  // Configuração do endereço IP fixo, gateway e máscara de sub-rede
  IPAddress local_IP(192, 168, 1, 133);
  IPAddress gateway(192, 168, 0, 1);
  IPAddress subnet(255, 255, 255, 0);

  // Inicia a comunicação serial
  Serial.begin(9600);

  // Configura o pino do sensor de umidade como entrada
  pinMode(umidadeAnalogica, INPUT);

  // Exibe informações sobre a conexão Wi-Fi no monitor serial
  Serial.println();
  Serial.println("Conectando-se a " + String(ssid));

  // Conecta-se à rede Wi-Fi
  WiFi.begin(ssid, password);

  // Aguarda a conexão à rede Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Exibe informações sobre a conexão estabelecida
  Serial.println("");
  Serial.println("Conexão WiFi estabelecida");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Inicia o servidor web
  server.begin();
}

void loop() {
  // Realiza a leitura analógica do sensor de umidade e mapeia para uma escala de 0 a 100
  valorUmidade = analogRead(umidadeAnalogica);
  valorUmidade = map(valorUmidade, 1023, 315, 0, 100);

  // Controle de umidade e acionamento do sistema
  if (validaTroca == true) {
    if (valorUmidade >= 40) {
      Serial.print("Solo Úmido ");
      Serial.print(valorUmidade);
      Serial.println(" %");
    } else {
      Serial.println("Ligado Sprinter");
      validaTroca = false;
    }
  }

  // Controle de irrigação e temporizador
  if (validaTroca == false) {
    if (valorUmidade < 40) {
      Serial.print("Solo Seco ");
      Serial.print(valorUmidade);
      Serial.println(" %, Água Ligada");
    } else if (valorUmidade > 40 && ativadorTimer == false) {
      Serial.println("Solo está úmido, Desativando Sprinter");
      tempoDeDesligamento = millis();
      ativadorTimer = true; 
    }
  }

  // Temporizador para desligar o sistema
  if (ativadorTimer == true) {
    if (tempoDeDesligamento + DuracaoDeDesligamento < millis()) {
      validaTroca = true;
      ativadorTimer = false;
    } else {
      Serial.println("Desligando Sprinter em:");
      Serial.println((tempoDeDesligamento + DuracaoDeDesligamento - millis()) / 1000);
    }
  }

  // Conexão ao servidor web e envio de dados
  WiFiClient client;

  // Construção da URL com os dados relevantes
  String url = "/get-sensor-data?umidade=" + String(valorUmidade) + "&validartroca=" + String(validaTroca) + "&tempoDesligamento=" + String(tempoDesligamento) + "&ativadorTimer=" + String(ativadorTimer);

  // Conecta-se ao servidor web
  if (client.connect("192.168.0.101", 5000)) {
    Serial.println("Conectado ao servidor");

    // Envia uma requisição GET HTTP para o servidor com a URL construída
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: 192.168.0.101\r\n" +
                 "Connection: close\r\n\r\n");

    // Aguarda e exibe a resposta do servidor no monitor serial
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
      }
    }

    // Encerra a conexão com o servidor web
    client.stop();
  } else {
    Serial.println("Falha na conexão com o servidor");
  }

  // Aguarda 1 segundo antes de enviar os dados novamente
  delay(1000);
}