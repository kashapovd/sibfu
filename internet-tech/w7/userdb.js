// import fs module
import { existsSync, writeFileSync, readFile, writeFile } from 'fs';
// import uuid module
import { v4 as uuidv4 } from 'uuid';

// user class
class User {
    constructor(username, password) {
        // generate uuid for this user
        this.id = uuidv4();
        this.username = username;
        this.password = password;
    }
}

// simple users database on json file
class UsersDB {
    constructor(fileName) {
        this.fileName = fileName;
        this.users = [];
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
     * This function reads the users from the DB file
     * @returns {Promise}
     */
    readUsers() {
        return new Promise((resolve, reject) => {
            readFile(this.fileName, (err, data) => {
                if (err) {
                    reject(err);
                }
                else {
                    this.users = JSON.parse(data);
                    resolve(true);
                }
            });
        });
    }
    /**
     * This function saves the users to the DB file
     * @returns {Promise}
     */
    saveUsers() {
        return new Promise((resolve, reject) => {
            writeFile(this.fileName, JSON.stringify(this.users), (err) => {
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
     * This function creates a new user and saves database state
     * @param {String} username 
     * @param {String} password 
     * @returns {Promise<User?>}
     */
    createNewUser(username, password) {
        return new Promise(async (resolve, reject) => {
            try {
                const user = new User(username, password);
                this.users.push(user);
                await this.saveUsers();
                resolve(user);
            } catch (err) {
                reject(err);
            }
        });
    }
    /**
     * This function returns a user by id
     * @param {String} id 
     * @returns {User?}
     */
    findUserById(id) {
        return this.users.find(user => user.id === id);
    }
    /**
     * This function searches for a user in the DB and returns it
     * @param {String} username 
     * @returns {User?}
     */
    findUser(username) {
        return this.users.find(u => u.username === username);
    }
    /**
     * This function returns all users
     * @returns {User[]}
     */
    getUsers() {
        return this.users;
    }
}

// export our classes
export { User, UsersDB };