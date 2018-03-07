<?php
session_start();
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <meta  http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
        <link href="css/stil2.css" rel="stylesheet" type="text/css"/>
        <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>
        <script src="js/validacija.js" type='text/javascript'></script>
        <script src="js/novio.js" type='text/javascript'></script>
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
            <div id="novi_oglas">
                <br/>
                <br/>
                <p>Ovde mozete napraviti novi oglas:</p>
                <form  id="napravi" action='kreiraj_oglas.php' method='post' onsubmit="return validacija_oglasa();">
                    <fieldset>
                        Izaberite kategoriju:
                        <select name='kategorija_oglasa'>
                            <option value="mobilni_telefoni">Mobilni Telefoni</option>
                            <option value="bela_tehnika">Bela Tehnika</option>
                            <option value="muzicki_instrumenti">Muzicki Instrumenti</option>
                        </select>
                        <p/>
                        Naziv oglasa:<input type='text' name='naziv_oglasa'/><p/>
                        Kratak opis:<br/><textarea name='opis_oglasa' rows="4" cols="25">U 160 karaktera opisite oglas.</textarea>
                        <p/>
                        Cena:<input type='text' name='cena_oglasa'/> <p/>
                        Valuta:
                        Dolar<input type='radio' name='valuta_oglas' value='dolar' checked="checked"/>
                        Dinar<input type='radio' name='valuta_oglas' value='dinar'/>
                        Funta<input type='radio' name='valuta_oglas' value="funta"/>
                        Kuna<input type='radio' name='valuta_oglas' value="kuna"/>
                        Euro<input type='radio' name='valuta_oglas' value='euro'/> <p/>
                        Kontakt email ili telefon:<input type='text' name='kontakt_oglas'/> <p/>
                        <input type='submit' name='kreiraj_upit' value='Napravi novi oglas!'/>
                        <input type="button" value="Resetuj" onclick="this.form.reset()" />
                    </fieldset>
                </form>
            </div>
        </div>
        <p style="position:fixed;left:1050px;">
            <a href="http://validator.w3.org/check?uri=referer"><img
                    src="http://www.w3.org/Icons/valid-xhtml10" alt="Valid XHTML 1.0 Strict" height="31" width="88" /></a>
        </p>
    </body>
</html>