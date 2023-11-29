// scripts.js

var status = "Seco";
var corDoTexto = "#8B4513";

var statusDiv = document.getElementById("status");
statusDiv.textContent = "Status: " + status;
statusDiv.style.color = corDoTexto;

// function atualizarUmidadeManual() {
//     var inputUmidade = document.getElementById("inputUmidade");
//     var umidadeSpan = document.getElementById("umidade");

//     var umidadeManual = parseFloat(inputUmidade.value);
//     if (!isNaN(umidadeManual)) {
//         umidadeSpan.textContent = umidadeManual;
//         verificarUmidade(umidadeManual);
//     } else {
//         alert("Por favor, insira um valor numérico válido para a umidade.");
//     }
// }

function verificarUmidade(umidade) {
    var soloDiv = document.getElementById("solo");
    var statusDiv = document.getElementById("status");
    var mensagemIrrigacao = document.getElementById("mensagemIrrigacao");

    if (umidade < 20) {
        soloDiv.style.backgroundColor = "#D2B48C";
        statusDiv.textContent = "Status: Seco";
        statusDiv.style.color = corDoTexto;
        mensagemIrrigacao.style.display = "block";
    } else {
        soloDiv.style.backgroundColor = "#8FBC8F";
        statusDiv.textContent = "Status: Molhado";
        statusDiv.style.color = "#009688";
        mensagemIrrigacao.style.display = "none";
    }
}

// verificarUmidade();


verificarUmidade(0);
