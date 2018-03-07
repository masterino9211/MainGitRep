<?php
include_once 'db.inc.php';
session_start();
$conn = connect();
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
        <link rel="stylesheet" type="text/css" href="css/stil2.css" />
        <link rel="stylesheet" type="text/css" href="css/tabla.css" />
        <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>
        <title>Mali oglasi</title>
    </head>
    <body> 

        <div id="telo">
            <div id="welcome">Dobrodosao/la <?php if (isset($_SESSION['username'])) echo $_SESSION['username']; ?> .
                <?php if (isset($_COOKIE['p_login'])) echo "Trajno ste ulogovani"; ?></div>
            <div id="line"></div>
            <div id="logo">Mali oglasi</div>

            <ul>
                <li class="meni"><a href="glavna.php">Glavna Stranica</a></li>
                <li class="meni"><a href="pregledo.php">Pregled Oglasa</a></li>
                <li class="meni"><a href="mojio.php">Moji Oglasi</a></li>
                <li class="meni"><a href="novi_oglas.php">Napravi novi oglas</a></li>
                <li class="meni"><a href="logout.php">Izloguj se</a></li>
            </ul>
            <div id="line2"></div>
            <br/><br/><br/>

            Mobilni Telefoni: <br/>
            <?php
            $table = "mobilni_telefoni";
            $query = sprintf("SELECT * FROM %s WHERE id=%d;", $table, $_SESSION['id']);
            $rezultat = mysqli_query($conn, $query);
            while ($row = mysqli_fetch_array($rezultat)) {
                ?> <table class='oglas'>
                    <tr>
                        <td ><?php echo $row['naziv']; ?></td>
                        <td >Cena je : <?php echo$row['cena']; ?> , valuta je :<?php echo$row['valuta']; ?></td>

                    </tr>
                    <tr>
                        <td ><?php echo $row['opis']; ?></td>
                        <td>
                            <form action="usrdel.php" method="get">
                                <fieldset>
                                    <input type="hidden" name="id" value="<?php echo $_SESSION['id'] ?>" /> 
                                    <input type="hidden" name="naziv" value="<?php echo $row['naziv'] ?>" />
                                    <input type="hidden" name="tabela" value="<?php echo $table ?>" />
                                    <input type="submit" value="Obrisi oglas" name="delete"/>
                                </fieldset>
                            </form>
                        </td>
                    </tr>
                    <tr>
                        <td class="toggle"><?php echo $row['kontakt']; ?></td>

                    </tr>
                </table>
                <br/>
            <?php } ?>
            <br/>
            Bela Tehnika: <br/>
            <?php
            $table = "bela_tehnika";
            $query = sprintf("SELECT * FROM %s WHERE id=%d;", $table, $_SESSION['id']);
            $rezultat = mysqli_query($conn, $query);
            while ($row = mysqli_fetch_array($rezultat)) {
                ?> <table class='oglas'>
                    <tr>
                        <td ><?php echo $row['naziv']; ?></td>
                        <td >Cena je : <?php echo$row['cena']; ?> , valuta je :<?php echo$row['valuta']; ?></td>

                    </tr>
                    <tr>
                        <td><?php echo $row['opis']; ?></td>
                        <td>
                            <form action="usrdel.php" method="get">
                                <fieldset>
                                    <input type="hidden" name="id" value="<?php echo $_SESSION['id'] ?>" /> 
                                    <input type="hidden" name="naziv" value="<?php echo $row['naziv'] ?>" />
                                    <input type="hidden" name="tabela" value="<?php echo $table ?>" />
                                    <input type="submit" value="Obrisi oglas" name="delete"/>
                                </fieldset>
                            </form>
                        </td>
                    </tr>
                    <tr>
                        <td class="toggle"><?php echo $row['kontakt']; ?></td>

                    </tr>
                </table>
                <br/>
            <?php } ?>
            <br/>
            Muzicki Instrumenti: <br/>
            <?php
            $table = "muzicki_instrumenti";
            $query = sprintf("SELECT * FROM %s WHERE id=%d;", $table, $_SESSION['id']);
            $rezultat = mysqli_query($conn, $query);
            while ($row = mysqli_fetch_array($rezultat)) {
                ?> <table class='oglas'>
                    <tr>
                        <td ><?php echo $row['naziv']; ?></td>
                        <td >Cena je : <?php echo$row['cena']; ?> , valuta je :<?php echo$row['valuta']; ?></td>

                    </tr>
                    <tr>
                        <td><?php echo $row['opis']; ?></td>
                        <td>
                            <form action="usrdel.php" method="get">
                                <fieldset>
                                    <input type="hidden" name="id" value="<?php echo $_SESSION['id'] ?>" /> 
                                    <input type="hidden" name="naziv" value="<?php echo $row['naziv'] ?>" />
                                    <input type="hidden" name="tabela" value="<?php echo $table ?>" />
                                    <input type="submit" value="Obrisi oglas" name="delete"/>
                                </fieldset>
                            </form>
                        </td>
                    </tr>
                    <tr>
                        <td class="toggle"> <?php echo $row['kontakt']; ?></td>

                    </tr>
                </table>
                <br/>
            <?php } ?>
        </div>
        <p style="position:fixed;left:1050px;">
            <a href="http://validator.w3.org/check?uri=referer"><img
                    src="http://www.w3.org/Icons/valid-xhtml10" alt="Valid XHTML 1.0 Strict" height="31" width="88" /></a>
        </p>
    </body>
</html>