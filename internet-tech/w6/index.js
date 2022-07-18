// import fs module
const fs = require('fs');
// import http module
const http = require('http');
// import url module
const urlParser = require('url');

// import users from users.json
const users = require('./users.json');

// create http sever
const server = http.createServer((req, res) => {
    // get request ip and method
    const ip = req.headers['x-forwarded-for'] || req.connection.remoteAddress;
    const { method } = req;
    // get query parameters from url using url library
    const url = urlParser.parse(req.url, true);
    // show info about request to console
    console.log(`${ip} ${method} ${url.path}`);

    if (url.pathname === '/') {
        // show index page
        fs.readFile(__dirname + '/views/index.html', (err, data) => {
            if (err) {
                res.writeHead(404, { 'Content-Type': 'text/html' });
                res.end(`<h1>404 Not Found</h1>`);
            } else {
                res.writeHead(200, { 'Content-Type': 'text/html' });
                res.end(data);
            }
        });
    } else if (url.pathname === '/query/json') {
        // show json response
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify(url.query));
    } else if (url.pathname === '/query/text') {
        // show text response
        res.writeHead(200, { 'Content-Type': 'text/plain' });
        let queryString = Object.keys(url.query).map(key => key + ' = ' + url.query[key]).join('\n');
        res.end(queryString);
    } else if (url.pathname === '/cat') {
        // read file from disk and send it to client
        fs.readFile(__dirname + '/public/images/cat.jpg', (err, data) => {
            if (err) {
                res.writeHead(404, { 'Content-Type': 'text/html' });
                res.end(`<h1>404 Not Found</h1>`);
            } else {
                res.writeHead(200, { 'Content-Type': 'image/jpeg' });
                res.end(data);
            }
        });
    } else if (url.pathname === '/login' && method === 'GET') {
        // show login page
        fs.readFile(__dirname + '/views/login.html', (err, data) => {
            if (err) {
                res.writeHead(404, { 'Content-Type': 'text/html' });
                res.end(`<h1>404 Not Found</h1>`);
            } else {
                res.writeHead(200, { 'Content-Type': 'text/html' });
                res.end(data);
            }
        });
    } else if (url.pathname === '/login' && method === 'POST') {
        // get POST data from request
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString();
        });
        req.on('end', () => {
            // parse POST data
            const postData = body.split('&').reduce((acc, pair) => {
                const [key, value] = pair.split('=');
                acc[key] = value;
                return acc;
            }, {});
            // get login and password from request body
            let login = postData.login;
            let password = postData.password;
            console.log(`Login: ${login}, password: ${password}`);
            // check if login and password are correct
            if (users[login] && users[login].password === password) {
                // show message to console
                console.log(`User ${login} logged in`);
                // if yes, redirect success login page with user name full name
                res.writeHead(302, { 'Location': '/login/success?username=' + users[login].fullName });
            } else {
                // show error to console
                console.log(`User ${login} not found`);
                // if no, redirect to login error page
                res.writeHead(302, { 'Location': '/login/error' });
            }
            res.end();
        });
    } else if (url.pathname === '/login/success') {
        // show success login page
        fs.readFile(__dirname + '/views/login-success.html', (err, data) => {
            if (err) {
                res.writeHead(404, { 'Content-Type': 'text/html' });
                res.end(`<h1>404 Not Found</h1>`);
            } else {
                res.writeHead(200, { 'Content-Type': 'text/html' });
                res.end(data.toString().replace('#{username}', url.query.username));
            }
        });
    } else if (url.pathname === '/login/error') {
        // show error login page
        fs.readFile(__dirname + '/views/login-error.html', (err, data) => {
            if (err) {
                res.writeHead(404, { 'Content-Type': 'text/html' });
                res.end(`<h1>404 Not Found</h1>`);
            } else {
                res.writeHead(200, { 'Content-Type': 'text/html' });
                res.end(data);
            }
        });
    } else {
        // show 404 page
        res.writeHead(404, { 'Content-Type': 'text/html' });
        res.end(`<h1>404 Not Found</h1>`);
    }
});

// make server listen on port 8700
server.listen(8700);