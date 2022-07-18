// import users database
import { UsersDB, User } from './userdb.js';
// import notes database
import { NotesDB, Note } from './notesdb.js';

// create users database instance
const users = new UsersDB('./users.json');
users.ensureFileExists();

// create notes database instance
const notes = new NotesDB('./notes.json');
notes.ensureFileExists();

for (let i = 0; i < 10; i++) {
    const user = await users.createNewUser('User' + i, 'User' + i);
    console.log(user);
}

for (let i = 0; i < 50; i++) {
    const randomUser = users.getUsers()[Math.floor(Math.random() * users.getUsers().length)];
    const note = await notes.createNote(randomUser.id, 'Note' + i, 'Note' + i);
    console.log(note);
}