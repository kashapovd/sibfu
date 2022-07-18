// import fs module
import { existsSync, writeFileSync, readFile, writeFile } from 'fs';
// import uuid module
import { v4 as uuidv4 } from 'uuid';

// note class
class Note {
    constructor(ownerId, title, content) {
        this.id = uuidv4();
        this.ownerId = ownerId;
        this.title = title;
        this.content = content;
    }
}

// simple notes database on json file
class NotesDB {
    constructor(fileName) {
        this.fileName = fileName;
        this.notes = [];
    }
    /**
     * This function ensures that the DB file exists
     */
    ensureFileExists() {
        if (!existsSync(this.fileName)) {
            writeFileSync(this.fileName, '[]');
        }
    }
    /**
     * This function reads the notes from the DB file
     * @returns {Promise}
     */
    readNotes() {
        return new Promise((resolve, reject) => {
            readFile(this.fileName, (err, data) => {
                if (err) {
                    reject(err);
                }
                else {
                    this.notes = JSON.parse(data);
                    resolve(true);
                }
            });
        });
    }
    /**
     * This function saves the notes to the DB file
     * @returns {Promise}
     */
    saveNotes() {
        return new Promise((resolve, reject) => {
            writeFile(this.fileName, JSON.stringify(this.notes), (err) => {
                if (err) {
                    reject(err);
                }
                else {
                    resolve();
                }
            });
        });
    }
    /**
     * This function creates a new note of user with
     * @param {String} ownerId 
     * @param {String} title 
     * @param {String} content 
     * @returns {Promise<Note?>}
     */
    createNote(ownerId, title, content) {
        return new Promise(async (resolve, reject) => {
            try {
                const note = new Note(ownerId, title, content);
                this.notes.push(note);
                await this.saveNotes();
                resolve(note);
            } catch (err) {
                reject(err);
            }
        });
    }
    /**
     * This function returns note with id equal to id
     * @param {String} id 
     * @returns {Note?}
     */
    findNoteById(id) {
        return this.notes.find(note => note.id === id);
    }
    /**
     * This function searches notes of user with id equal to ownerId
     * @param {String} ownerId 
     * @returns {Promise<Note[]>}
     */
    findNotesByOwnerId(ownerId) {
        return this.notes.filter(note => note.ownerId === ownerId);
    }
    /**
     * This function deletes note with id equal to id
     * @param {String} id 
     * @returns 
     */
    async deleteNoteById(id) {
        this.notes = this.notes.filter(note => note.id !== id);
        await this.saveNotes();
    }
    /**
     * This function returns all notes
     * @returns {Note[]}
     */
    getNotes() {
        return this.notes;
    }
}

// export our classes
export { Note, NotesDB };