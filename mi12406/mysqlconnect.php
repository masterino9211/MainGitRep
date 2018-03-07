<?php

function connect() {
    $mysql_host = "mysql6.000webhost.com";
	$mysql_database = "a9205921_uvit";
	$mysql_user = "a9205921_uvit";
	$mysql_password = "uvit92";
    $conn = mysqli_connect($mysql_host,$mysql_user,$mysql_password,$mysql_database);
    //$conn=  mysqli_connect("localhost","root","","ai11133"); 
    if (mysqli_connect_errno()) {
        echo "Povezivanje nije moguce:" . mysqli_connect_error();
        exit();
    }
    return $conn;
}

?>
