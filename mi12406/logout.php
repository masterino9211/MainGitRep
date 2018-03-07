<?php
session_start();
setcookie("p_login", $_SESSION['id'], time() - 3600);
session_destroy();
header("Location:index.php");
?>
