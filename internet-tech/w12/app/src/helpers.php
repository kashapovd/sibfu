<?php
function setSessionVariable($name, $value) {
    $_SESSION[$name] = $value;
}

function getSessionVariable($name, $default = null) {
    return $_SESSION[$name] ?? $default;
}

function unsetSessionVariable($name) {
    unset($_SESSION[$name]);
}
?>