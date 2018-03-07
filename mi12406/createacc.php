<?php
    include_once 'db.inc.php';
   
    // pravljenje naloga i provera duzine lozinke( postoji i provera preko jscripta)
    if(isset($_POST['create'])){
        $user=$_POST['user'];
        $pass=$_POST['pass']; 
    if(strlen($pass) < 3 ){
            header("Location:index.php?lozinka_kratka=1");
            exit();
        }
    if(strlen($user) < 3 ){
            header("Location:index.php?lozinka_kratka=2");
            exit();
        }
        $conn=connect();
       $upit=sprintf("SELECT * FROM users WHERE usern='%s';",$user);
        $result= mysqli_query($conn,$upit);
        if(mysqli_num_rows($result) > 0){
           
            header("Location:index.php?user_postoji=1"); 
        } 
        else {
        $upit=  sprintf("INSERT INTO users (usern,passw) VALUES('%s','%s')",$user,$pass);
        mysqli_query($conn,$upit);
        header("Location:index.php?user_kr=1");
        }
        mysqli_close($conn);
    }
?>
