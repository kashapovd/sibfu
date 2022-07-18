// there is no __dirname in es6, so we have to emulate it
import { dirname } from 'path';
import { fileURLToPath } from 'url';
const __dirname = dirname(fileURLToPath(import.meta.url));
// import Express library
import express from 'express';

// create an instance of express
const app = express();

// create main route
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/views/index.html');
});

// start server
app.listen(8700, () => {
    console.log('server started on port 8700');
});