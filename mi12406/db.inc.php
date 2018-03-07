<?php
// posto alas ne podrzava funkcije mysqli , rucno napisane neophodne mysqli funkcije
if (function_exists("mysqli_query") == false) {

    function mysqli_query($veza, $upit) {
        return mysql_query($upit);
    }

}

if (function_exists("mysqli_num_rows") == false) {

    function mysqli_num_rows($rezultat) {
        return mysql_num_rows($rezultat);
    }

}

if (function_exists("mysqli_fetch_array") == false) {

    function mysqli_fetch_array($result) {
        return mysql_fetch_array($result, MYSQL_BOTH);
    }

}

if (function_exists("mysqli_insert_id") == false) {

    function mysqli_insert_id($link) {
        return mysql_insert_id();
    }

}


if (function_exists("mysqli_close") == false) {

    function mysqli_close($veza) {
        mysql_close($veza);
    }

}

if (function_exists("mysqli_connect") == false) {

    function mysqli_connect($host, $user, $password, $database) {
        $link = mysql_connect($host, $user, $password);
        mysql_selectdb($database, $link);
        return $link;
    }

}
// 
function connect() {

    $conn = mysqli_connect("localhost", "root", "", "ai11133");
   /* if (mysqli_connect_errno()) {
        echo "Povezivanje nije moguce:" . mysqli_connect_error();
        exit();
    } */ // ne radi na alasu..
    return $conn;
}

?>
