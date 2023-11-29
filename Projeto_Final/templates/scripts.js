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
//         verificarUmidade(umidadeManual); // Passe a umidade manual como argumento para a função
//     } else {
//         alert("Por favor, insira um valor numérico válido para a umidade.");
//     }
// }

function verificarUmidade(umidade) {
    var soloDiv = document.getElementById("solo");
    var statusDiv = document.getElementById("status");
    var mensagemIrrigacao = document.getElementById("mensagemIrrigacao");

    if (umidade < 20) {
        soloDiv.style.backgroundColor = "#D2B48C"; // Marrom claro para seco
        statusDiv.textContent = "Status: Seco";
        statusDiv.style.color = corDoTexto;
        mensagemIrrigacao.style.display = "block"; // Exibe a mensagem quando estiver seco
    } else {
        soloDiv.style.backgroundColor = "#8FBC8F"; // Verde claro para molhado
        statusDiv.textContent = "Status: Molhado";
        statusDiv.style.color = "#009688";
        mensagemIrrigacao.style.display = "none"; // Oculta a mensagem quando estiver molhado
    }
}
// Comente ou descomente a linha a seguir para alternar entre automático e manual
// verificarUmidade();

// Chame a função inicialmente para configurar a imagem com base na umidade
verificarUmidade(0); // Inicialize com um valor, por exemplo, 0
