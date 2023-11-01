#include <ESP8266WiFi.h>  // Biblioteca para o ESP8266
#include <Adafruit_Sensor.h>  // Biblioteca para o sensor
#include <DHT.h>  // Biblioteca para o DHT

const char *ssid = ""; // Nome da rede (coloque o nome da sua rede Wi-Fi)
const char *password = ""; // Senha da rede (coloque a senha da sua rede Wi-Fi)

#define DHTPIN D1 // Pino do sensor DHT (D1 no ESP8266)
#define DHTTYPE DHT11 // Tipo do sensor DHT (no caso, DHT11)

DHT dht(DHTPIN, DHTTYPE); // Instanciando o sensor DHT
WiFiServer server(80); // Configuração do servidor web na porta padrão 80

void setup() {
  IPAddress local_IP(192, 168, 1, 169); // Endereço IP local
  IPAddress gateway(192, 168, 1, 1); // Endereço IP gateway da rede
  IPAddress subnet(255, 255, 255, 0); // Máscara de sub-rede
  Serial.begin(9600); // Inicialização da porta serial
  dht.begin(); // Inicialização do sensor DHT
  Serial.println();
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  // Se a rede WiFi não estiver configurada ele irá imprimir uma mensagem
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  // Conectando-se a uma rede WiFi
  WiFi.begin(ssid, password);
  // Enquanto o status for diferente de conectado, ele imprimirá "."
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conexão WiFi estabelecida");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP()); // Imprime o endereço IP atribuído
  server.begin(); // Inicia o servidor web
}

void loop() {
  WiFiClient client = server.available();
  // Se o cliente não estiver conectado, retorna
  if (!client) {
    return;
  }
  // Ler a primeira linha da solicitação (exemplo: GET /path HTTP/1.1)
  String request = client.readStringUntil('\r');
  client.flush();
  float h = dht.readHumidity(); // Leitura da umidade
  float t = dht.readTemperature(); // Leitura da temperatura
  Serial.print("Umidade: ");
  Serial.println(h);
  Serial.print("Temperatura: ");
  Serial.println(t);
  // HTML da página web
  String html = R"====(
<html>
<head>
<link href="https://fonts.googleapis.com/css2?family=Anton&display=swap"
rel="stylesheet">
<link rel="stylesheet"
href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">
<style>
body {
font-family: 'Anton';
background: linear-gradient(to right, #83a4d4, #b6fbff);
color: #333;
height: 100vh;
display: flex;
flex-direction: column;
align-items: center;
justify-content: center;
}
h2 {
font-size: 2.5em;
}
p {
font-size: 2em;
}
fas {
  font-size: 1.5em;
margin-right: 10px;
}
</style>
<script>
setInterval(function() {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
var readings = this.responseText.split(";");
document.getElementById("humidity").innerHTML = readings[0] + " %";
document.getElementById("temperature").innerHTML = readings[1] + "
&deg;C";
}
};
xhttp.open("GET", "/get-data", true);
xhttp.send();
}, 2000); // Atualiza a cada 2 segundos
</script>
</head>
<body>
<h2>NodeMCU com DHT11</h2>
<h3>Prof. Rafael Barbosa</h3>
<p><i class="fas fa-tint"></i> Umidade: <span id="humidity"></span></p>
<p><i class="fas fa-thermometer-half"></i> Temperatura: <span
id="temperature"></span></p>
</body>
</html>
)====";
  // Verificar se a solicitação é para "/get-data"
  if (request.indexOf("/get-data") != -1) {
    // Responde à solicitação com dados de umidade e temperatura
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    client.print(String(h) + ";" + String(t));
    return;
  }
  // Se não for para "/get-data", servir a página HTML
  else {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
    client.print(html);
  }
  delay(1);
  client.stop();
}
