// function which downloads json using jquery ajax with promise
function getJSON(url) {
    return new Promise(function (resolve, reject) {
        $.getJSON(url, function (data) {
            resolve(data);
        })
        .fail(function (error) {
            reject(error);
        });
    });
}

// function to create tabs from array using jquery-ui
function createTabs() {
    getJSON("/galleries/galleries.json").then(function (data) {
        // create ul list using jquery
        $("#tabs").append("<ul id='tabs-list'></ul>");
        data["galleries"].forEach(function (galerie) {
            // append gallery tab name
            $("#tabs-list").append("<li><a href='#" + galerie["name"] + "'>" + galerie["name"] + "</a></li>");
            // append gallery data holder to tabs
            $("#tabs").append("<div id='" + galerie["name"] + "'></div>");
            // append images hoder to gallery data holder
            $("#" + galerie["name"]).append("<div class='gal-list'></div>");
            // create progressbar and append it to gallery data holder
            $("#" + galerie["name"]).append("<div class='progressbar'></div>");
            // make progressbar
            $("#" + galerie["name"] + " .progressbar").progressbar({
                value: false,
            });
            // load gallery data
            getJSON("/" + galerie["path"] + "/" + galerie["name"] + ".json").then(function (data) {
                // remove progressbar
                $("#" + galerie["name"] + " .progressbar").remove();
                // append gallery images to gallery
                data["images"].forEach(function (image) {
                    $("#" + galerie["name"] + " .gal-list").append("<img alt='" + image["name"] + "' data-full='" + image["file"] + "' src='/galleries/" + image["thumb"] + "'>");
                });
                // add click listener to all images in this tab
                $("#" + galerie["name"] + " .gal-list img").click(function () {
                    // get full image url
                    let full = $(this).attr("data-full");
                    // check if image has next sibling
                    let [next, prev] = [null, null];
                    if ($(this).next().length) {
                        // if it has, get next sibling
                        next = $(this).next();
                    }
                    // check if image has previuos sibling
                    if ($(this).prev().length) {
                        // if it has, get previous sibling
                        prev = $(this).prev();
                    }
                    // open image in modal
                    openModalFullscreen("/galleries/" + full, next, prev);
                });
                // create slider element for this tab
                $("#" + galerie["name"]).append("<div id='" + galerie["name"] + "-slider'></div>");
                // create slider for this tab
                $("#" + galerie["name"] + "-slider").slider({
                    min: 0,
                    max: 10000,
                    slide: function(event, ui) {
                        const scrlgal = $("#" + galerie["name"] + " .gal-list");
                        const rpad = scrlgal[0].scrollWidth - scrlgal[0].clientWidth;
                        scrlgal[0].scroll(rpad * (ui.value / 10000), 0);
                    }
                });
            });
        });
        // create tabs using jquery-ui
        $("#tabs").tabs();
    }).catch(function (error) {
        console.error(error);
    });
}

// jquery-ui initialization 
$(function () {
    // init jquery-ui accordion
    $("#accordion").accordion({
        collapsible: true,
        active: false
    });

    createTabs();

    // create button to change all images class
    $("#change-class").button().click(function () {
        $("img").toggleClass("img-omg");
    });

    // init datepicker
    $("#datepicker").datepicker({
        dateFormat: "dd.mm.yy",
        changeYear: true,
        yearRange: "2017:2037",
        showButtonPanel: true,
        firstDay: 1,
    });
});

// function to open modal with image using jquery-ui with animation fullscreen
function openModalFullscreen(image, next, prev) {
    // jquery viewport width and height
    let viewportWidth = $(window).width();
    let viewportHeight = $(window).height();
    let buttons = {};
    if (next) { 
        buttons["Next"] = function () {
            next.click();
        };
    }
    if (prev) {
        buttons["Previous"] = function () {
            prev.click();
        };
    }

    $("#modal").dialog({
        modal: true,
        width: viewportWidth*.9,
        height: viewportHeight*.9,
        draggable: false,
        buttons: buttons,
        position: { my: "center", at: "center", of: window },
        show: {
            effect: "explode",
            duration: 1000
        },
        hide: {
            effect: "explode",
            duration: 1000
        }
    });
    $("#modal").html("<img src='" + image + "'>");
}

