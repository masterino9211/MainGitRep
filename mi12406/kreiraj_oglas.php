<?php
    include_once 'db.inc.php';
    session_start();
    $conn=  connect();
    if(isset($_POST['kreiraj_upit']) && isset($_POST['naziv_oglasa']) ){
        $naziv=$_POST['naziv_oglasa'];
        $opis=$_POST['opis_oglasa'];
        $cena=intval($_POST['cena_oglasa']); 
        $valuta=$_POST['valuta_oglas'];
        $tabela=$_POST['kategorija_oglasa'];
        $kontakt=$_POST['kontakt_oglas'];
        
        $upit=sprintf("INSERT INTO %s (id,naziv,opis,cena,valuta,kontakt) VALUES(%d,'%s','%s',%d,'%s','%s');",$tabela,$_SESSION['id'],$naziv,$opis,$cena,$valuta,$kontakt);
        mysqli_query($conn, $upit);
        header("Location:mojio.php?oglas_kreiran=1");
        
        
    }
    else;
mysqli_close($conn);
?>

