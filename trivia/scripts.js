document.querySelector("#red").onclick = function() {
    document.querySelector("#red").style.backgroundColor = "red";
    document.querySelector("#red").style.color = "white";
    document.querySelector("#response").innerHTML = "Incorrect";
};

document.querySelector("#green").onclick = function() {
    document.querySelector("#green").style.backgroundColor = "red";
    document.querySelector("#green").style.color = "white";
    document.querySelector("#response").innerHTML = "Incorrect";
};

document.querySelector("#blue").onclick = function() {
    document.querySelector("#blue").style.backgroundColor = "green";
    document.querySelector("#blue").style.color = "white";
    document.querySelector("#response").innerHTML = "Correct!";
};

document.querySelector("#respond_text").onclick = function() {
    if (document.querySelector('#input_text').value == "It looks nice.")
    {
        document.querySelector("#input_text").style.backgroundColor = "green";
        document.querySelector("#input_text").style.color = "white";
        document.querySelector("#response_text").innerHTML = "Correct!";
    }
    else
    {
        document.querySelector("#input_text").style.backgroundColor = "red";
        document.querySelector("#input_text").style.color = "white";
        document.querySelector("#response_text").innerHTML = "Incorrect";
    }
};
