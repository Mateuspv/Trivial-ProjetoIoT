# Documentação do Código ESP8266 com DHT11 e Servidor Web

Este é um código para um dispositivo ESP8266 que lê dados de um sensor DHT11 (umidade e temperatura) e fornece esses dados através de um servidor web.

## Requisitos de Hardware

- ESP8266 (NodeMCU)
- Sensor DHT11
- Acesso a uma rede Wi-Fi

## Requisitos de Software

- Biblioteca `ESP8266WiFi.h`
- Biblioteca `Adafruit_Sensor.h`
- Biblioteca `DHT.h`

## Configuração de Rede Wi-Fi

```cpp
const char *ssid = ""; // Nome da rede Wi-Fi
const char *password = ""; // Senha da rede Wi-Fi
```

Substitua ssid e password pelos detalhes da sua rede Wi-Fi.

## Configuração do Sensor DHT11
```cpp
#definir DHTPIN D1 // Pino ao qual o sensor DHT está conectado
#definir DHTTYPE DHT11 // Tipo do sensor DHT (DHT11 neste caso)
DHT dht(DHTPIN, DHTTYPE); // Instanciando o sensor DHT
```
Defina DHTPIN para o pino onde o sensor DHT11 está conectado.

## Configuração do Servidor Web
```cpp
WiFiServer server(80); // Configuração do servidor web na porta 80
```
O servidor web será executado na porta 80.

## Funcionamento:

### Função setup()
Inicializa a comunicação serial.
Inicializa o sensor DHT11.
Configura a rede Wi-Fi.
Conecta-se à rede Wi-Fi especificada.
Inicia o servidor web.

### Função loop()
Espera por clientes que se conectem ao servidor web.
Lê a primeira linha da solicitação HTTP do cliente.
Lê a umidade e a temperatura do sensor DHT11.
Gera uma página HTML que exibe os dados de umidade e temperatura.
Responde a solicitações HTTP, fornecendo os dados ou a página HTML.

### Solicitação "/get-data"
Se a solicitação do cliente for "/get-data", o servidor responde com os dados de umidade e temperatura em formato de texto.

### Outras Solicitações
Se a solicitação não for "/get-data", o servidor responde com a página HTML que exibe os dados.

### Página HTML
O código HTML está embutido no programa e exibe os dados de umidade e temperatura em tempo real. Ele também inclui links para folhas de estilo CSS e scripts JavaScript para atualizar os dados automaticamente a cada 2 segundos.

## Autores

Projeto criado e executado por: Ana Julia G. Peres, Anna Clara Bragato, Arthur Lunkes e Natali Santos.

## Conclusão

O projeto demonstra a criação de um sistema IoT simples usando um dispositivo ESP8266 (NodeMCU), um sensor DHT11 para medir umidade e temperatura e a criação de um servidor web.
