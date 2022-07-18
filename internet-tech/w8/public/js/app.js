const socket = io();

let sizeSlider;
let colorPicker;
let drawings = [];

const syncDrawing = function(data) {
    const {type, params} = data;

    push();
    drawCmd(type, params);
    pop();
}

const syncHistory = function(data) {
    push();
    for (const hItem of data) {
        const [type, params] = hItem;
        drawCmd(type, params);
    }
    pop();
}

const drawCmd = function(type, params) {
    if (type == "stroke") {
        fill(...params.color);
        ellipse(params.x, params.y, params.strokeSize);
    }
}

function setup() {
    createCanvas(windowWidth, windowHeight);

    sizeSlider = createSlider(1, 100, 6);
    sizeSlider.position(10, 10);
    sizeSlider.style("width", "200px");

    colorPicker = createColorPicker(color(255, 204, 0));
    colorPicker.position(10, 40);

    noStroke();

    socket.on("new", syncDrawing);
    socket.on("data", syncHistory);
    
    socket.emit("sync");
}

function draw() {
    fill(colorPicker.color());
}

function mouseDragged(event) {
    if (!event.target.classList.value.includes("p5Canvas")) return;

    socket.emit("draw", { type: "stroke", params: { color: colorPicker.color().levels, strokeSize: sizeSlider.value(), x: mouseX, y: mouseY } });
}

function windowResized() {
    resizeCanvas(windowWidth, windowHeight);
    socket.emit("sync");
}