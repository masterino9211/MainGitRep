<?php
ob_start();
session_start();
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
        <link rel="stylesheet" type="text/css" href="css/stil2.css" />
        <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js" type="text/javascript"></script>
        <script src="js/glavna.js" type="text/javascript"></script>
        <script src="js/validacija.js" type="text/javascript"></script>
        <title>Mali oglasi</title>
    </head>
    <body> 
        <div id="telo">
            <div id="welcome">Dobrodosao/la <?php if (isset($_SESSION['username'])) echo $_SESSION['username']; ?> .
             <?php if(isset($_COOKIE['p_login'])) echo "Trajno ste ulogovani"; ?></div>
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
            <div id="inner_body">
                Dobrodosli na sajt mali oglasi , na glavnoj stranici mozete promeniti lozinku.<br/>Prijatan boravak
                <p></p>
                Mogucnost promene lozinke ovde : <input id="pasch" type="button" value="Promeni Lozinku"/>
                <?php
                if (isset($_GET['pass_change']) && $_GET['pass_change'] == 0)
                    echo "Neuspela promena lozinke!!!";
                else if (isset($_GET['pass_change']) && $_GET['pass_change'] == 1)
                    echo "Lozinka uspesno promenjena! :)";
                ?>
                <input id="shrink" type="button" value="Umanji opet"/>
                <form id="pass" action="change_pass.php" method="post" onsubmit="return pass_vali();" >
                    <fieldset>
                        <legend>Promena Lozinke</legend>
                        Stara lozinka:<input type="password" name="oldpass"/><p></p>
                        Nova lozinka:<input type="text" name="newpass"/><p></p>
                        <input type="submit" value="Promeni lozinku" name="change_pass"/>
                    </fieldset>
                </form>

            </div>
            <br/>
            <br/>
            <br/>
        </div>
        <p style="position:fixed;left:1050px;">
            <a href="http://validator.w3.org/check?uri=referer"><img
                    src="http://www.w3.org/Icons/valid-xhtml10" alt="Valid XHTML 1.0 Strict" height="31" width="88" /></a>
        </p>
    </body>
</html>