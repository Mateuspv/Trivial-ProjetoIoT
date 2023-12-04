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


### Front end
O Frontend foi Desenvolvido utilizando HTML, css, e js, carregando as imagens existentes, e com o jquery, recebendo os dados da Api, e fazendo o carregamente em tempo real dessas informaçoes, assim o projeto feito de forma responsiva e e com a  capacidade de se ajusta conforme a porcentagem de umidade recebida a qual foi detectada pelo sensor de solo. 

### Arduino com Sensor de Solo
O código para o sensor de solo, conectado ao NodeMCU, foi desenvolvido em C++. Nele, é realizada a medição da umidade do solo utilizando a conexão analógica do sensor. A informação é então mapeada e convertida para uma faixa de 0 a 100%, permitindo medir a porcentagem de umidade no solo.

Com base na porcentagem de umidade, é implementada uma lógica para acionar a irrigação e manter o solo constantemente úmido. Isso ocorre sempre que a detecção do solo indica que ele está seco. Além disso, foi incorporada a funcionalidade de permitir a irrigação por um tempo predefinido após o solo sair do estado "seco", evitando assim que a irrigação fique ligada por um tempo insuficiente.

### API
A API foi desenvolvida utilizando Python e a biblioteca Flask. No código, a aplicação Flask é inicializada e estabelecida a conexão com o banco de dados. Posteriormente, são configuradas as rotas para interação com o banco de dados, além das rotas destinadas ao compartilhamento de dados com as APIs existentes.


## Autores

Projeto criado e executado por: Mateus Poleselo, Jean Trojan, Lucas Loeffler

## Conclusão
O projeto do ESP8266 com um sensor de solo e a implementação da API para monitoramento e controle da umidade do solo oferecem uma solução robusta para automatizar o processo de irrigação, garantindo condições ideais para o crescimento das plantas. Utilizando o NodeMCU e a comunicação via API com a biblioteca Flask, juntamente com HTML, CSS, e JavaScript, o sistema proporciona uma interface web responsiva que reflete em tempo real as condições do solo detectadas pelo sensor.
Este projeto contribui significativamente para a agricultura ao fornecer um sistema automatizado e em tempo real para monitorar e controlar a umidade do solo. Ao garantir uma irrigação eficiente e personalizada, as plantas podem prosperar em condições ideais, resultando em colheitas mais saudáveis e sustentáveis.
Em resumo, a integração harmoniosa de hardware e software neste projeto oferece uma solução abrangente para o manejo inteligente da irrigação, mostrando o potencial da tecnologia para otimizar práticas agrícolas e promover uma produção mais eficiente.

