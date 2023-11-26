// scripts.js

var status = "Seco";
var corDoTexto = "#5a2d0d";

var statusDiv = document.getElementById("status");
statusDiv.textContent = "Status: " + status;
statusDiv.style.color = corDoTexto;


document.addEventListener("keydown", function(event) {
    if (event.keyCode === 32) {
        var imagemSolo = document.getElementById("imagemSolo");

        if (imagemSolo.src.endsWith("img/seco.jpg")){
            imagemSolo.src = "img/molhado.jpg";
        }else{
            imagemSolo.src = "img/seco.jpg";
        }
 
    }
});