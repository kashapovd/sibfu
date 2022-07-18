<?php
class Database {
    private static $db;
    private static $dsn = 'pgsql:host=db;port=5432;dbname=work12-db';
    private static $username = 'postgres';
    private static $password = 'passw0rd';
    private static $options = [
        PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
        PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
        PDO::ATTR_EMULATE_PREPARES => false,
    ];
    
    public static function getDB() {
        if (!isset(self::$db)) {
            try {
                self::$db = new PDO(self::$dsn, self::$username, self::$password, self::$options);
            } catch (PDOException $e) {
                throw new PDOException($e->getMessage(), (int)$e->getCode());
            }
        }
        return self::$db;
    }

    public static function userExists($login) {
        $db = self::getDB();
        $query = $db->prepare('SELECT * FROM users WHERE login = :login');
        $query->bindParam(':login', $login);
        $query->execute();
        return $query->rowCount() > 0;
    }

    public static function createUser($login, $password) {
        $db = self::getDB();
        $query = $db->prepare('INSERT INTO users (login, password) VALUES (:login, :password)');
        $query->bindParam(':login', $login);
        $query->bindParam(':password', $password);
        $query->execute();
    }

    public static function verifyUser($login, $password) {
        $db = self::getDB();
        $query = $db->prepare('SELECT * FROM users WHERE login = :login AND password = :password');
        $query->bindParam(':login', $login);
        $query->bindParam(':password', $password);
        $query->execute();
        return $query->rowCount() > 0;
    }

    public static function getUser($login) {
        $db = self::getDB();
        $query = $db->prepare('SELECT * FROM users WHERE login = :login');
        $query->bindParam(':login', $login);
        $query->execute();
        return $query->fetch();
    }

    public static function generateUserNewPassword($login) {
        $db = self::getDB();
        $query = $db->prepare('UPDATE users SET password = :password WHERE login = :login');
        $query->bindParam(':login', $login);
        $query->bindParam(':password', $password);
        $password = bin2hex(random_bytes(8));
        $query->execute();
        return $password;
    }

    public static function getUsersList() {
        $db = self::getDB();
        $query = $db->prepare('SELECT id, login FROM users');
        $query->execute();
        return $query->fetchAll();
    }

    public static function createEmptyMenuForUser($user) {
        $db = self::getDB();
        $query = $db->prepare('INSERT INTO menu (user_id) VALUES (:user_id)');
        $query->bindParam(':user_id', $user["id"]);
        $query->execute();
    }

    public static function getUserMenu($user) {
        $db = self::getDB();
        $query = $db->prepare('SELECT data FROM menu WHERE user_id = :user_id');
        $query->bindParam(':user_id', $user["id"]);
        $query->execute();
        return $query->fetch();
    }

    public static function setUserMenu($user, $data) {
        $db = self::getDB();
        $query = $db->prepare('UPDATE menu SET data = :data WHERE user_id = :user_id');
        $query->bindParam(':data', $data);
        $query->bindParam(':user_id', $user["id"]);
        $query->execute();
    }

    public static function addImageToGallery($filename, $user) {
        $db = self::getDB();
        $query = $db->prepare('INSERT INTO images (user_id, filename) VALUES (:user_id, :filename)');
        $query->bindParam(':filename', $filename);
        $query->bindParam(':user_id', $user["id"]);
        $query->execute();
    }

    public static function getUsersImages($user) {
        $db = self::getDB();
        $query = $db->prepare('SELECT id, filename FROM images WHERE user_id = :user_id');
        $query->bindParam(':user_id', $user["id"]);
        $query->execute();
        return $query->fetchAll();
    }

    public static function getPublishedImages() {
        $db = self::getDB();
        $query = $db->prepare('SELECT id, filename FROM images WHERE published = TRUE');
        $query->execute();
        return $query->fetchAll();
    }

    public static function getImage($id) {
        $db = self::getDB();
        $query = $db->prepare('SELECT * rk12-nginx
        8b017cfb4843   nginx          "/docker-entrypoint.…"   8 weeks ago         Up 7 weeks         0.0.0.0:80->80/tcp, :::80->80/tcp FROM images WHERE id = :id');
        $query->bindParam(':id', $id);
        $query->execute();
        return $query->fetch();
    }

    public static function searchImages($search, $author) {
        $db = self::getDB();
        if (intval($author) !== -1) {
            $query = $db->prepare('SELECT * FROM images WHERE description LIKE :search AND user_id = :author');
            $query->bindParam(':search', $search);
            $query->bindParam(':author', $author);
        } else {
            $query = $db->prepare('SELECT * FROM images WHERE description LIKE :search');
            $query->bindParam(':search', $search);
        }
        $query->execute();
        return $query->fetchAll();
    }

    public static function updateImage($id, $description, $published) {
        $db = self::getDB();
        $query = $db->prepare('UPDATE images SET published = :published, description = :description WHERE id = :id');
        $query->bindParam(':id', $id);
        $query->bindParam(':published', $published);
        $query->bindParam(':description', $description);
        $query->execute();
    }

    public static function deleteImage($id) {
        $db = self::getDB();
        $query = $db->prepare('DELETE FROM images WHERE id = :id');
        $query->bindParam(':id', $id);
        $query->execute();
    }

    public static function getAnyTableSorted($table, $sort_by, $sort_order) {
        $db = self::getDB();
        $query = $db->prepare('SELECT * FROM ' . $table . ' ORDER BY ' . $sort_by . ' ' . $sort_order);
        $query->execute();
        return $query->fetchAll();
    }

    public static function getTableColumns($table) {
        $db = self::getDB();
        $query = $db->prepare('SELECT column_name FROM information_schema.columns WHERE table_schema = \'public\' AND table_name = :table_name');
        $query->bindParam(':table_name', $table);
        $query->execute();
        return $query->fetchAll();
    }

    public static function getAvailableTables() {
        $db = self::getDB();
        $query = $db->prepare('SELECT table_name FROM information_schema.tables WHERE table_schema = \'public\' ORDER BY table_name');
        $query->execute();
        return $query->fetchAll();
    }

    public static function exportUsersXML() {
        $db = self::getDB();
        $query = $db->prepare('SELECT * FROM users');
        $query->execute();
        $users = $query->fetchAll();
        $xml = new DOMDocument('1.0', 'UTF-8');
        $xml->formatOutput = true;
        $root = $xml->createElement('users');
        $xml->appendChild($root);
        foreach ($users as $user) {
            $user_node = $xml->createElement('user');
            $root->appendChild($user_node);
            $user_node->setAttribute('exported_id', $user['id']);
            $user_node->setAttribute('login', $user['login']);
            $user_node->setAttribute('password', $user['password']);
        }
        return $xml->saveXML();
    }

    public static function importUsersXML($xmlData) {
        $xml = new DOMDocument();
        $xml->loadXML($xmlData);
        $users = $xml->getElementsByTagName('user');

        $ok = 0;
        $fail = 0;
        foreach ($users as $user) {
            try {
                $login = $user->getAttribute('login');
                $password = $user->getAttribute('password');
                self::createUser($login, $password);
                $user = self::getUser($login);
                self::createEmptyMenuForUser($user);
                $ok += 1;
            } catch (PDOException $e) {
                $fail += 1;
            }
        }
        return [$ok, $fail];
    }
}
?>