// there is no __dirname in es6, so we have to emulate it
import { dirname } from 'path';
import { fileURLToPath } from 'url';
const __dirname = dirname(fileURLToPath(import.meta.url));
// import Express library
import express from 'express';
// import body-parser library
import bodyParser from 'body-parser';
// import mustache-express library
import mustacheExpress from 'mustache-express';
// import session library
import session from 'express-session';
// import users database
import { UsersDB, User } from './userdb.js';
// import notes database
import { NotesDB, Note } from './notesdb.js';

// create users database instance
const users = new UsersDB('./users.json');
users.ensureFileExists();
users.readUsers();

// create notes database instance
const notes = new NotesDB('./notes.json');
notes.ensureFileExists();
notes.readNotes();

// create an instance of express
const app = express();
// register mustache-express
app.engine('html', mustacheExpress());
// add view engine
app.set('view engine', 'html');
// add view directory
app.set('views', __dirname + '/views');
// add static files
app.use(express.static('public'));
// add body-parser middleware
app.use(bodyParser.urlencoded({ extended: false }));
// use session middleware
app.use(session({
    secret: 'rtfgfyhujiosdfhgyuewbhrhjitt9834htnfh999',
    cookie: {
        maxAge: 1000 * 60 * 60 * 24 * 7
    },
    resave: false,
    saveUninitialized: false
}));

// create main route
app.get('/', (req, res) => {
    res.render('index', {
        session: req.session,
        title: 'Notes',
        notes: notes.getNotes()
    });
});

// create note route
app.get('/note/:id', (req, res) => {
    const note = notes.findNoteById(req.params.id);
    if (note) {
        const user = users.findUserById(note.ownerId);
        res.render('note', {
            session: req.session,
            title: note.title,
            note: note,
            user: user
        });
    } else {
        // add redirect header with time
        res.set('Refresh', '2; url=/');
        res.status(404).send('Note not found');
    }
});

// create note deletion route
app.get('/note/:id/delete', (req, res) => {
    const note = notes.findNoteById(req.params.id);
    if (note) {
        // check if user in session owns this note
        if (note.ownerId === req.session.userId) {
            notes.deleteNoteById(note.id);
            res.redirect('/');
        } else {
            // add redirect header with time
            res.set('Refresh', '2; url=/');
            res.status(403).send('You are not allowed to delete this note');
        }
    } else {
        // add redirect header with time
        res.set('Refresh', '2; url=/');
        res.status(404).send('Note not found');
    }
});

// create user route
app.get('/user/:id', (req, res) => {
    const user = users.findUserById(req.params.id);
    if (user) {
        const userNotes = notes.findNotesByOwnerId(req.params.id);
        res.render('user', {
            session: req.session,
            title: user.name,
            user: user,
            notes: userNotes
        });
    } else {
        // add redirect header with time
        res.set('Refresh', '2; url=/');
        res.status(404).send('User not found');
    }
});

// create register route
app.get('/register', (req, res) => {
    // if user is already logged in, redirect to main page
    if (req.session.userId) {
        res.redirect('/');
    } else {
        res.render('register', {
            session: req.session,
            title: 'Register'
        });
    }
});

// create registration route POST handler
app.post('/register', (req, res) => {
    // check if username and password in request
    if (req.body.username && req.body.password) {
        // check if user with such username already exists
        const user = users.findUser(req.body.username);
        if (user) {
            // add redirect header with time
            res.set('Refresh', '2; url=/register');
            res.status(400).send('User with such username already exists');
        } else {
            // create new user
            users.createNewUser(req.body.username, req.body.password);
            // redirect to login page
            res.redirect('/login');
        }
    } else {
        // add redirect header with time
        res.set('Refresh', '2; url=/register');
        res.status(400).send('Username and password are required');
    }
});

// create login route
app.get('/login', (req, res) => {
    // if user is already logged in, redirect to main page
    if (req.session.userId) {
        res.redirect('/');
    } else {
        res.render('login', {
            session: req.session,
            title: 'Login'
        });
    }
});

// create login route POST handler
app.post('/login', (req, res) => {
    // check if username and password in request
    if (req.body.username && req.body.password) {
        // check if user with such username exists
        const user = users.findUser(req.body.username);
        if (user) {
            // check if password is correct
            if (user.password === req.body.password) {
                // add session
                req.session.userId = user.id;
                // redirect to main page
                res.redirect('/');
            } else {
                // add redirect header with time
                res.set('Refresh', '2; url=/login');
                res.status(400).send('Incorrect password');
            }
        } else {
            // add redirect header with time
            res.set('Refresh', '2; url=/login');
            res.status(400).send('User with such username does not exist');
        }
    } else {
        // add redirect header with time
        res.set('Refresh', '2; url=/login');
        res.status(400).send('Username and password are required');
    }
});

// create logout route
app.get('/logout', (req, res) => {
    // remove session
    req.session.destroy();
    // redirect to main page
    res.redirect('/');
});

// create note creation route
app.get('/create', (req, res) => {
    // if note/create is not logged in, redirect to login page
    if (!req.session.userId) {
        res.redirect('/login');
    } else {
        res.render('create', {
            session: req.session,
            title: 'Create note'
        });
    }
});

// create note creation POST handler
app.post('/create', async (req, res) => {
    // if user is not logged in, redirect to login page
    if (!req.session.userId) {
        res.redirect('/login');
    } else {
        // check if title and text in request
        if (req.body.title && req.body.text) {
            // create new note
            const note = await notes.createNote(req.session.userId, req.body.title, req.body.text);
            // redirect to main page
            res.redirect('/note/' + note.id);
        } else {
            // add redirect header with time
            res.set('Refresh', '2; url=/create');
            res.status(400).send('Title and text are required');
        }
    }
});

// create user notes route
app.get('/notes', (req, res) => {
    // if user is not logged in, redirect to login page
    if (!req.session.userId) {
        res.redirect('/login');
    } else {
        // check if user with such id exists
        const user = users.findUserById(req.session.userId);
        if (user) {
            // get user notes
            const userNotes = notes.findNotesByOwnerId(req.session.userId);
            res.render('user-notes', {
                session: req.session,
                title: 'My notes',
                user: user,
                notes: userNotes
            });
        } else {
            // add redirect header with time
            res.set('Refresh', '2; url=/');
            res.status(404).send('User not found');
        }
    }
});

// start server
app.listen(8700, () => {
    console.log('server started on port 8700');
});