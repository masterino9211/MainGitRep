<?php
    include_once 'db.inc.php';
    session_start();
    $conn=  connect();
    if(isset($_POST['change_pass'])){
           
        if(strcmp($_POST['oldpass'],$_SESSION['password']) == 0){ // uporedjuvanje unete lozinke za lozinkom korisnika i promena u bazi
            $query= sprintf("UPDATE users SET passw='%s' WHERE usern='%s';",$_POST['newpass'],$_SESSION['username']);
            $_SESSION['password']=$_POST['newpass'];
            mysqli_query($conn, $query);
            header("Location:glavna.php?pass_change=1");
            mysqli_close($conn);
        }
        else
           header("Location:glavna.php?pass_change=0");
    }
    
        mysqli_close($conn);
?>
