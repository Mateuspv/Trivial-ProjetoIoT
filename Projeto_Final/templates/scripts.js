// scripts.js

var status = "Seco";
var corDoTexto = "#5a2d0d";
var humidadeholder = 0;

var statusDiv = document.getElementById("status");
statusDiv.textContent = "Status: " + status;
statusDiv.style.color = corDoTexto;


// Adicione essa função ao scripts.js
function atualizarUmidadeManual() {
    var inputUmidade = document.getElementById("inputUmidade");
    var umidadeSpan = document.getElementById("umidade");

    // Certifique-se de que o valor inserido é um número válido
    var umidadeManual = parseFloat(inputUmidade.value);
    if (!isNaN(umidadeManual)) {
        humidade = umidadeManual;
        umidadeSpan.textContent = humidade;
        verificarUmidade(); // Atualiza a imagem do solo com base na umidade
    } else {
        alert("Por favor, insira um valor numérico válido para a umidade.");
    }
}

function verificarUmidade() {
    var imagemSolo = document.getElementById("imagemSolo");
    var humidadeSpan = document.getElementById("umidade");
    var statusDiv = document.getElementById("status");

    if (parseFloat(humidadeSpan.textContent) < 21) {
        imagemSolo.src = "img/seco.jpg";
        statusDiv.textContent = "Status: Seco";
        statusDiv.style.color = corDoTexto;
    } else {
        imagemSolo.src = "img/molhado.jpg";
        statusDiv.textContent = "Status: Molhado";
        statusDiv.style.color = "#009688";
    }
}

// Chame a função inicialmente para configurar a imagem com base na umidade
verificarUmidade();

// A função pode ser chamada sempre que for necessário verificar a umidade
// por exemplo, após uma atualização da API de umidade
// verificarUmidade();