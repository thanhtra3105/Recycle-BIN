setInterval(function () {
    getPaper();
    getMetal();
    getPlastic();
}, 1000);


function getPaper() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("paper").innerHTML = this.responseText;

        }
    }
    xhttp.open("GET", "doc_paper", true);
    xhttp.send();

}


function getMetal() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("metal").innerHTML = this.responseText;

        }
    }
    xhttp.open("GET", "doc_metal", true);
    xhttp.send();

}

function getPlastic() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("plastic").innerHTML = this.responseText;

        }
    }
    xhttp.open("GET", "doc_plastic", true);
    xhttp.send();

}