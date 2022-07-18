// there is no __dirname in es6, so we have to emulate it
import { dirname } from 'path';
import { fileURLToPath } from 'url';
const __dirname = dirname(fileURLToPath(import.meta.url));
// import Express library
import express from 'express';
// import mustache-express library
import mustacheExpress from 'mustache-express';
import { Server } from "socket.io";
import http from "http";

const app = express();
// register mustache-express
app.engine('html', mustacheExpress());
// add view engine
app.set('view engine', 'html');
// add view directory
app.set('views', __dirname + '/views');
// add static files
app.use(express.static('public'));

const port = 8700;
const server = http.createServer(app);
const io = new Server(server);

// history for drawing
let drawHistory = [];

// create main route
app.get("/", (req, res) => {
    res.render("index");
});

// websocket connection handler
io.on("connection", (socket) => {
    socket.on("draw", (data) => {
        drawHistory.push([data.type, data.params]);
        io.emit("new", data);
    });

    socket.on("sync", (data) => {
        socket.emit("data", drawHistory);
    });
});

server.listen(port, () => console.log(`Serving on port ${port}`));