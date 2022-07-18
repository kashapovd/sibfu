let langtonData = {
    canvas: null,
    ctx: null,
    width: null,
    height: null,
    position: {x: 400, y: 400},
    direction: 0
}

// langton's ant rule-set: https://en.wikipedia.org/wiki/Langton%27s_ant
function langton() {
    let newPosition = langtonData.position;
    let pixel = langtonData.ctx.getImageData(langtonData.position.x, langtonData.position.y, 1, 1);
    if (pixel.data[0] == 0) {
        pixel.data[0] = 255;
        pixel.data[1] = 255;
        pixel.data[2] = 255;
        langtonData.ctx.putImageData(pixel, langtonData.position.x, langtonData.position.y);
        newDirection = (langtonData.direction + 1) % 4;
    } else {
        pixel.data[0] = 0;
        pixel.data[1] = 0;
        pixel.data[2] = 0;
        langtonData.ctx.putImageData(pixel, langtonData.position.x, langtonData.position.y);
        newDirection = (langtonData.direction + 3) % 4;
    }
    switch (newDirection) {
        case 0:
            newPosition.x += 1;
            break;
        case 1:
            newPosition.y += 1;
            break;
        case 2:
            newPosition.x -= 1;
            break;
        case 3:
            newPosition.y -= 1;
            break;
    }
    langtonData.position = newPosition;
    langtonData.direction = newDirection;
    
    // call this function next frame
    requestAnimationFrame(langton);
}

// prepare langton canvas
function prepareLangton() {
    // get the canvas element
    langtonData.canvas = document.getElementById('langton');
    // get the 2d context
    langtonData.ctx = langtonData.canvas.getContext('2d');
    // translate canvas by half pixel
    langtonData.ctx.translate(0.5, 0.5);

    langtonData.width = langtonData.canvas.width;
    langtonData.height = langtonData.canvas.height;

    // clear canvas
    langtonData.ctx.clearRect(0, 0, langtonData.width, langtonData.height);
    
    // set the background color
    langtonData.ctx.fillStyle = 'white';
    langtonData.ctx.fillRect(0, 0, langtonData.width, langtonData.height);
    
    langton();
}

let staticData = {
    canvas: null,
    ctx: null,
    width: null,
    height: null,
    drawFunctions: {
        "circle": function(ctx, x, y, r) {
            ctx.beginPath();
            ctx.arc(x, y, r, 0, 2 * Math.PI);
            ctx.stroke();
        },
        "square": function(ctx, x, y, w) {
            ctx.fillRect(x, y, w, w);
        },
        "ellipse": function(ctx, x, y, r1, r2) {
            ctx.beginPath();
            ctx.ellipse(x, y, r1, r2, 0, 0, 2 * Math.PI);
            ctx.stroke();
        },
        "bezier": function(ctx, h1x, h1y, h2x, h2y, x, y) {
            ctx.beginPath();
            ctx.bezierCurveTo(h1x, h1y, h2x, h2y, x, y);
            ctx.stroke();
        }
    },
    figures: [
        ["circle", 50, 50, 10],
        ["square", 150, 50, 25],
        ["ellipse", 200, 200, 30, 40],
        ["bezier", 50, 100, 180, 10, 20, 10],
    ]
}

function staticDrawLoop() {
    staticData.ctx.clearRect(0, 0, staticData.width, staticData.height);
    staticData.ctx.fillStyle = 'white';
    staticData.ctx.fillRect(0, 0, staticData.width, staticData.height);
    staticData.ctx.strokeStyle = 'black';
    for (let i = 0; i < staticData.figures.length; i++) {
        let figure = staticData.figures[i];
        staticData.drawFunctions[figure[0]](staticData.ctx, ...figure.slice(1));
    }
    requestAnimationFrame(staticDrawLoop);
}

// prepare static canvas
function prepareStatic() {
    // get the canvas element
    staticData.canvas = document.getElementById('static');
    // get the 2d context
    staticData.ctx = staticData.canvas.getContext('2d');
    // translate canvas by half pixel
    staticData.ctx.translate(0.5, 0.5);

    staticData.width = staticData.canvas.width;
    staticData.height = staticData.canvas.height;

    // add canvas click listening
    staticData.canvas.addEventListener('click', function(evt) {
        // get mouse position on it
        let mousePos = getMousePos(staticData.canvas, evt);
        // add a new figure
        staticData.figures.push(["circle", mousePos.x, mousePos.y, 10]);
    });

    staticDrawLoop();
}

// wait for DOM content loaded
document.addEventListener("DOMContentLoaded", function(event) {
    prepareLangton();
    prepareStatic();
});


// get mouse position on canvas
function getMousePos(canvas, evt) {
    let rect = canvas.getBoundingClientRect();
    return {
        x: evt.clientX - rect.left,
        y: evt.clientY - rect.top
    };
}
