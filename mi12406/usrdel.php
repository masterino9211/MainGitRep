<?php
include_once 'db.inc.php';
$conn = connect();
if (isset($_GET['id']) && isset($_GET['naziv']) && isset($_GET['tabela'])) {
    $query= sprintf("DELETE FROM %s WHERE naziv='%s' AND id=%d ",$_GET['tabela'],$_GET['naziv'],$_GET['id']);
   $rezultat= mysqli_query($conn,$query);
    
    header("Location:mojio.php?neuspelo_brisanje=0");
} else {
    mysqli_close($conn);
    header("Location:mojio.php?neuspelo_brisanje=1");
}
?>
