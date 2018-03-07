<?php

include_once 'db.inc.php';
session_start();
$conn = connect();
// kolacic koji cuva id korisnika (prmarni kljuc tabele)
$cookie_id = $_COOKIE['p_login'];
$query = sprintf("SELECT * FROM users WHERE id=%d;", $cookie_id);
$rezultat = mysqli_query($conn, $query);
if (mysqli_num_rows($rezultat) == 1) {
    $korisnik = mysqli_fetch_array($rezultat);
    $_SESSION['id'] = $cookie_id;
    $_SESSION['username'] = $korisnik['usern'];
    $_SESSION['password'] = $korisnik['passw'];
    header("Location:glavna.php");
}
mysqli_close($conn);
?>
