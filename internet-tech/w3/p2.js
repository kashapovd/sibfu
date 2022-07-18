"use strict";

let menuElement = null;
let paragraphElement = null;

const copyMenu = function() {
    paragraphElement.textContent += menuElement.textContent;
}

const changeCss = function() {
    document.querySelectorAll(".menu-type-two").forEach(el => el.classList.toggle("menu-type-two-styled"));
}

const doSearch = function(event) {
    Array.from(menuElement.children).forEach(element => {
        element.innerHTML = element.innerText;
    });
    const searchTerm = event.target.value;
    if (searchTerm !== "") {
        Array.from(menuElement.children).forEach(element => {
            element.innerHTML = element.innerText.replace(new RegExp(searchTerm, "ig"), '<span class="highlighted">$&</span>');
        });
    }
}


const init = function() {
    menuElement = document.getElementById("menu");
    paragraphElement = document.getElementById("paragraph");

    document.getElementById("btn-copy-menu").addEventListener("click", copyMenu);
    document.getElementById("btn-change-css").addEventListener("click", changeCss);
    document.getElementById("search-bar").addEventListener("input", doSearch);
}

document.addEventListener("DOMContentLoaded", () => init());
