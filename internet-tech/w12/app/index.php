<?php
require_once 'src/database.php';
require_once 'src/helpers.php';
require_once 'vendor/autoload.php';
require_once 'vendor/pecee/simple-router/helpers.php';

use Pecee\SimpleRouter\SimpleRouter;
$loader = new \Twig\Loader\FilesystemLoader('views');
$twig = new \Twig\Environment($loader, [
    'cache' => false,
]);

session_start();

SimpleRouter::get('/favicon.ico', function() {
    return;
});

SimpleRouter::get('/', function() use($twig) {
    if (getSessionVariable('user') !== null) {
        $user = getSessionVariable('user');
        echo $twig->render('index.twig', [
            'user' => $user,
            'menu' => json_decode(Database::getUserMenu($user)["data"]),
            'gallery' => Database::getPublishedImages()
        ]);
    } else {
        echo $twig->render('propose-auth.twig');
    }
});

SimpleRouter::get('/register', function() use($twig) {
    if (getSessionVariable('user') !== null) {
        return response()->redirect('/');
    }
    $error = input()->get('error', '');
    echo $twig->render('register.twig', [
        'error' => htmlspecialchars($error),
    ]);
});

SimpleRouter::post('/register', function() {
    $login = trim(input()->post('login', ''));
    $password = trim(input()->post('password', ''));

    if (empty($login) || empty($password)) {
        return response()->redirect('/register?error=Пароль или логин не можеть быть пустым');
    }
    
    try {
        Database::createUser($login, $password);
        $user = Database::getUser($login);
        Database::createEmptyMenuForUser($user);
        response()->redirect('/login?message=Потльзователь "'.$login.'" создан');
    } catch (PDOException $e) {
        response()->redirect('/register?error=Пользователь "'.$login.'" уже существует');
    }
});

SimpleRouter::get('/login', function() use($twig) {
    if (getSessionVariable('user') !== null) {
        return response()->redirect('/');
    }
    $message = input()->get('message', '');
    $error = input()->get('error', '');
    echo $twig->render('login.twig', [
        'message' => htmlspecialchars($message),
        'error' => htmlspecialchars($error),
    ]);
});

SimpleRouter::post('/login', function() {
    $login = trim(input()->post('login', ''));
    $password = trim(input()->post('password', ''));
    if (empty($login) || empty($password)) {
        return response()->redirect('/login?error=Неверный пароль или логин.');
    } 
    if (!Database::userExists($login)) {
        return response()->redirect('/login?error=Пользователя "'.$login.'" не существует.');
    }
    if (!Database::verifyUser($login, $password)) {
        return response()->redirect('/login?error=Неверный пароль.');
    }
    
    $user = Database::getUser($login);
    setSessionVariable('user', $user);
    response()->redirect('/');
});

SimpleRouter::get('/logout', function() {
    unsetSessionVariable('user');
    response()->redirect('/');
});

SimpleRouter::get('/editMenu', function() use($twig) {
    if (getSessionVariable('user') === null) {
        return response()->redirect('/');
    }
    $user = getSessionVariable('user');
    echo $twig->render('edit-menu.twig', [
        'user' => $user,
        'menu' => json_decode(Database::getUserMenu($user)["data"]),
    ]);
});

SimpleRouter::post('/editMenu', function() {
    if (getSessionVariable('user') === null) {
        return response()->json([
            'error' => "Not authorized",
            'code'  => 403,
        ]);
    }
    try {
        $user = getSessionVariable('user');
        $menuData = [];
        $menu = input()->post('menu', []);
        for ($i = 0; $i < count($menu->value); $i++) {
            array_push($menuData, [
                'url' => $menu->value[$i]->value['url']->value,
                'name' => $menu->value[$i]->value['name']->value,
            ]);
        }
        Database::setUserMenu($user, json_encode($menuData));
        response()->json([
            'data' => json_encode($menuData),
            'code'  => 200,
        ]);
    } catch (PDOException $e) {
        response()->json([
            'error' => json_encode($e->getMessage()),
            'code'  => 500,
        ]);
    }
});

SimpleRouter::get('/lookupTables', function() use($twig) {
    if (getSessionVariable('user') === null) {
        return response()->redirect('/');
    }
    $tables = [];
    $tableData = [];

    $user = getSessionVariable('user');
    $table = input()->get('table', '');
    $sort = input()->get('sort', 'DESC');
    $col = input()->get('col', '');
    if ($table !== '') {
        $cols = Database::getTableColumns($table);
        if ($col === '') {
            $col = $cols[0]['column_name'];
        } else {
            $col = $col->value;
        }
        $tableData = [
            "header" => $cols,
            "data" => Database::getAnyTableSorted($table, $col, $sort),
        ];
    } else {
        $tables = array_map(function($tbl) {
            return $tbl["table_name"];
        }, Database::getAvailableTables());
    }
    echo $twig->render('lookup-tables.twig', [
        'user' => $user,
        'table' => $table,
        'tables' => $tables,
        'tableData' => $tableData
    ]);
});

SimpleRouter::post('/uploadImage', function() {
    if (getSessionVariable('user') === null) {
        return response()->json([
            'error' => "Not authorized",
            'code'  => 403,
        ]);
    }
    $user = getSessionVariable('user');
    $file = input()->file('file');
    $fileType = $file->type;
    if ($fileType === 'image/jpeg') {
        $filename = $user['login'] . '_' . time() . '.jpg';
        $fullpath = 'data/full/' . $filename;
        $file->move($fullpath);


        $size = getimagesize($fullpath);
        $ratio = $size[0]/$size[1];
        if( $ratio > 1) {
            $width = 200;
            $height = 200/$ratio;
        }
        else {
            $width = 200*$ratio;
            $height = 200;
        }
        $thumb = imagecreatetruecolor($width, $height);
        $source = imagecreatefromjpeg($fullpath);
        
        imagecopyresized($thumb, $source, 0, 0, 0, 0, $width, $height, $size[0], $size[1]);
        $color = imagecolorallocate($thumb, 0, 255, 0);
        imagestring($thumb, 20, 5, 10, 'YKF-'.$user['login'], $color);
        imagejpeg($thumb, 'data/thumb/' . $filename);

        try {
            Database::addImageToGallery($filename, $user);
        } catch (PDOException $e) {
            return response()->json([
                'error' => json_encode($e->getMessage()),
                'code'  => 500,
            ]);
        }

        return response()->json([
            'code'  => 200,
        ]);
    } else {
        return response()->json([
            'error' => "Wrong file type",
            'code'  => 400,
        ]);
    }
});

SimpleRouter::get('/gallery', function() use($twig) {
    if (getSessionVariable('user') === null) {
        return response()->redirect('/');
    }
    $user = getSessionVariable('user');
    $images = Database::getUsersImages($user);
    echo $twig->render('gallery.twig', [
        'user' => $user,
        'images' => $images,
    ]);
});

SimpleRouter::get('/image/{id}', function($id) use($twig) {
    if (getSessionVariable('user') === null) {
        return response()->redirect('/');
    }
    $user = getSessionVariable('user');
    $image = Database::getImage($id);
    if ($image['user_id'] !== $user['id']) {
        return response()->httpCode(403);
    }

    echo $twig->render('image.twig', [
        'user' => $user,
        'image' => $image,
    ]);
});

SimpleRouter::post('/image/{id}', function($id) {
    if (getSessionVariable('user') === null) {
        return response()->redirect('/');
    }
    $user = getSessionVariable('user');
    $image = Database::getImage($id);
    if ($image['user_id'] !== $user['id']) {
        return response()->httpCode(403);
    }

    $description = input()->post('description', '')->value;
    $published = boolval(input()->post('published', 0)->value)?"true":"false";
    try {
        Database::updateImage($id, $description, $published);
    } catch (PDOException $e) {
        return response()->json([
            'error' => json_encode($e->getMessage()),
            'code'  => 500,
        ]);
    }
    
    response()->redirect('/');
});

SimpleRouter::get('/image/{id}/delete', function($id) {
    if (getSessionVariable('user') === null) {
        return response()->redirect('/');
    }
    $user = getSessionVariable('user');
    $image = Database::getImage($id);
    if ($image['user_id'] !== $user['id']) {
        return response()->httpCode(403);
    }
    unlink('data/full/' . $image['filename']);
    unlink('data/thumb/' . $image['filename']);
    Database::deleteImage($id);
    response()->redirect('/gallery');
});

SimpleRouter::all('/images', function() {
    $type = input()->get('type', 'thumb');
    $filename = input()->get('filename', '');
    if (file_exists("data/$type/$filename")) {
        header("Content-type: image/jpeg");
        return file_get_contents("data/$type/$filename");
    } else {
        response()->httpCode(404);
    }
});

SimpleRouter::get('/export', function() {
    if (getSessionVariable('user') === null) {
        return response()->redirect('/');
    }
    header("Content-type: application/xml");
    echo Database::exportUsersXML();
});

SimpleRouter::get('/import', function() use($twig) {
    if (getSessionVariable('user') === null) {
        return response()->redirect('/');
    }
    $user = getSessionVariable('user');
    $message = input()->get('message', '');
    $error = input()->get('error', '');
    echo $twig->render('import.twig', [
        'user' => $user,
        'message' => htmlspecialchars($message),
        'error' => htmlspecialchars($error),
    ]);
});

SimpleRouter::post('/import', function() {
    if (getSessionVariable('user') === null) {
        return response()->redirect('/');
    }
    $xml = input()->post('xml')->value;
    if ($xml) {
        try {
            list($ok, $fail) = Database::importUsersXML($xml);
            response()->redirect("/import?message=OK: $ok, ОШИБОК: $fail"); 
        } catch (Exception $e) {
            response()->redirect("/import?error=" . $e->getMessage());
        }
    } else {
        response()->redirect('/import?error=Произошла ошибка ');
    }
});

SimpleRouter::get('/search', function() use($twig) {
    if (getSessionVariable('user') === null) {
        return response()->redirect('/');
    }
    $user = getSessionVariable('user');
    $search = input()->get('search', '')->value;
    $author = input()->get('author', '')->value;
    $authors = Database::getUsersList();
    $images = [];
    if ($search and $author) {
        $images = Database::searchImages("%".$search."%", $author);
    }
    echo $twig->render('search.twig', [
        'user' => $user,
        'images' => $images,
        'search' => $search,
        'author' => $author,
        'authors' => $authors,
    ]);
});

// create recover password route
SimpleRouter::get('/recover-password', function() use($twig) {
    $message = input()->get('message', '');
    $error = input()->get('error', '');
    $mail = input()->get('mail', '');
    echo $twig->render('recover-password.twig', [
        'message' => htmlspecialchars($message),
        'error' => htmlspecialchars($error),
        'mail' => $mail,
    ]);
});

// create recover password POST route
SimpleRouter::post('/recover-password', function() use ($twig) {
    $login = input()->post('login', '')->value;
    $email = input()->post('email', '')->value;
    if ($login) {
        try {
            $user = Database::getUser($login);
            if ($user) {
                $newPassword = Database::generateUserNewPassword($login);
                $letter = $twig->render('recover-password-mail.twig', [
                    'login' => $login,
                    'password' => $newPassword,
                ]);
                $resp = mail($email, "Смена пароля", $letter);
                response()->redirect('/recover-password?message='.urlencode($letter));
            } else {
                response()->redirect('/recover-password?error=Пользователь "'.$login.'" не найден');
            }
        } catch (PDOException $e) {
            response()->redirect('/recover-password?error=' . $e->getMessage());
        }
    } else {
        response()->redirect('/recover-password?error=Произошла ошибка');
    }
});

SimpleRouter::start();
