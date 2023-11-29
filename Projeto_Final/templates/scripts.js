// scripts.js

var status = "Seco";
var corDoTexto = "#5a2d0d";

var statusDiv = document.getElementById("status");
statusDiv.textContent = "Status: " + status;
statusDiv.style.color = corDoTexto;

// function atualizarUmidadeManual() {
//     var inputUmidade = document.getElementById("inputUmidade");
//     var umidadeSpan = document.getElementById("umidade");

//     var umidadeManual = parseFloat(inputUmidade.value);
//     if (!isNaN(umidadeManual)) {
//         umidadeSpan.textContent = umidadeManual;
//         verificarUmidade();
//     } else {
//         alert("Por favor, insira um valor numérico válido para a umidade.");
//     }
// }

function verificarUmidade() {
    var imagemSolo = document.getElementById("imagemSolo");
    var statusDiv = document.getElementById("status");

    if (parseFloat(umidade) < 10) {
        imagemSolo.src = "img/seco.jpg";
        statusDiv.textContent = "Status: Seco";
        statusDiv.style.color = corDoTexto;
    } else {
        imagemSolo.src = "img/molhado.jpg";
        statusDiv.textContent = "Status: Molhado";
        statusDiv.style.color = "#009688";
    }
}


verificarUmidade();
