<?php

include_once 'db.inc.php';
session_start();
$conn = connect();

if (isset($_POST['p_login']))
    $cookie = $_POST['p_login'];
else
    $cookie = 0;

if(strcmp($_POST['loguser'],"tardis")== 0)
        if(strcmp($_POST['logpass'],"tardis")== 0){
            $_SESSION['tardis']=1;
            header("Location:index.php");
            mysqli_close($conn);
        }
$query = sprintf("SELECT * FROM users WHERE usern='%s' AND passw='%s';", $_POST['loguser'], $_POST['logpass']);
$rezultat = mysqli_query($conn, $query);
if (mysqli_num_rows($rezultat) == 1) {
    $row = mysqli_fetch_array($rezultat);
    $_SESSION['id'] = $row['id'];
    $_SESSION["username"] = $_POST['loguser'];
    $_SESSION["password"] = $_POST['logpass'];
    if ($cookie == 1)
        setcookie("p_login", $_SESSION['id'], time() + 3600 * 24); // kolacic koji traje 1 dan
   header("Location:glavna.php");
} else {
    header("Location:index.php?bad_login=1");
}
mysqli_close($conn);
?>
