# Documentação do Código ESP8266 com um sensor de solo fornecendo esses dados através de API a um servidor WEB

O projeto visa criar um sistema integrado para monitoramensto e controle da umidade do solo, utilizando dispositivo NodeMCU, a um sensor de solo, realizando a comunição via API com a Biblioteca do Flask e desenvolvimento o visual do projeto com HTML, CSS, e Javascript, alem de utilizar a biblioteca do jquery-3.7.1 para integração dos dados e atualização em tempo real da informação. A solução proposta tem como objetivo principal automatizar o processo de irrigação, garantindo que as plantas recebam a quantidade adequada de água de acordo com as condições do solo.

## Requisitos de Hardware

- ESP8266 (NodeMCU)
- Sensor de solo
- Acesso a uma rede Wi-Fi

## Requisitos de Software e Tecnologias utilizadas


## PlatformIO para desenvolvimento no ESP8266 (NodeMCU)
Criação do codigo do sensor em C++:
Bibliotecas do arduino em C++ utilizadas
- Biblioteca `Arduino.h`
- Biblioteca `ESP8266WiFi.h`

Criação do codigo da API com flask em python utilizadas:
Bibliotecas da API em python
- Biblioteca `Flask, request, jsonify, render_template`
- Biblioteca `psycopg2`
- Biblioteca `CORS`

Criação da WEB utilizando HTML,css e javaScript:
Bibliotecas do HTML utilizadas:
- Biblioteca `jquery-3.7.1`

## Configuração de Rede Wi-Fi no arquivo main.cpp

```cpp
const char *ssid = ""; // Nome da rede Wi-Fi
const char *password = ""; // Senha da rede Wi-Fi
```

## Configuração do banco de dados

```
# Configuração do banco de dados PostgreSQL
db_host = "localhost"  // Ip do host do banco
db_database = "ProjetoFinal" //Nome da base do Banco
db_user = "postgres" //Nome do usuario do Banco
db_password = "postgres" //Senhao do Banco
db_port = "5432" //Porta do Banco
```

## Funcionamento:

A documentar..

### Front end


### Arduino com Sensor de Solo


### API
Se a solicitação do cliente for "/get-data", o servidor responde com os dados de umidade e temperatura em formato de texto.


## Autores

Projeto criado e executado por: Mateus Poleselo, Jean Trojan, Lucas Loeffler

## Conclusão


