#include <Arduino.h>

#define umidadeAnalogica A0 // Atribui o pino A0 à variável umidade - leitura analógica do sensor

int valorUmidade; // Declaração da variável que armazenará o valor da umidade lida - saída analógica
boolean validaTroca = true;
boolean ativadorTimer = false;
unsigned long tempoDeDesligamento;
unsigned long DuracaoDeDesligamento = 12000;

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial
  pinMode(umidadeAnalogica, INPUT); // Define umidadeAnalogica como entrada
}

void loop() {
  valorUmidade = analogRead(umidadeAnalogica); // Realiza a leitura analógica do sensor e armazena em valorumidade
  valorUmidade = map(valorUmidade, 1023, 315, 0, 100); // Transforma os valores analógicos em uma escala de 0 a 100

delay(500);

if (validaTroca == true){
  if (valorUmidade >= 40){
  Serial.print("Solo Umido");
  Serial.print(valorUmidade);
  Serial.println(" %");
}else{
  Serial.println("Ligado Sprinter");
  validaTroca = false;
  }
}
if (validaTroca == false){
  if (valorUmidade < 40){
    Serial.print("Solo Seco");
    Serial.print(valorUmidade);
    Serial.println(" %, Agua Ligada");
  }
  else if(valorUmidade > 40 && ativadorTimer == false){
    Serial.println("Solo está umido,Desativando Sprinter");
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
}




