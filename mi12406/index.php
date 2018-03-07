<?php
include_once 'db.inc.php';
$conn = connect();
session_start();
if(isset($_COOKIE['p_login'])) //trajno (automacko)logovanje 
    header("Location:cookielogin.php");
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
        
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
        <link rel="stylesheet" type="text/css" href="css/stil.css" />
        <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js" type='text/javascript'></script>
        <script src="js/index_js.js" type='text/javascript'></script>
        <script src="js/validacija.js" type='text/javascript'></script>
        <title>Mali oglasi</title>
    </head>
    <body>
        <div id='main'>
            <div id="create">
                Napravite novog korisnika. :&nbsp;<br/>
                <form  id="novi_k" action="createacc.php" method="post" onsubmit="return validacija_novi_korisnik();" >
                    <fieldset class="indeks">
                        Ime:<input  type="text" name="user" />
                        Lozinka:<input type="text" name="pass" />
                        <input type="submit" value="Napravi nalog" name="create"/>
                    </fieldset>
                </form>
                <?php
                if (isset($_GET['user_kr']) && $_GET['user_kr']) {
                    ?>  <div class='info2'> Korisnik  kreiran</div> <?php
                } else if (isset($_GET['user_postoji']) && $_GET['user_postoji']) {
                    ?> <div class='info2'> Korisnik postoji</div> <?php
                } else if (isset($_GET['lozinka_kratka']) && $_GET['lozinka_kratka']) {
                    ?> <div class='info2'> Lozinka je prekratka!</div> <?php } ?>   
            </div>

            <div id="login">
                Ulogujte sa na vas account: &nbsp;<br/>
                <form  action="logincheck.php" method="post" >
                    <fieldset class="indeks">
                        Ime:<input type="text" name="loguser"/>
                        Lozinka:<input type="password" name="logpass"/>
                        <input type="submit" value="Uloguj se" name="create"/>
                        Trajno logovanje? <input type="checkbox" name="p_login" value='1' />
                    </fieldset>
                </form>
<?php
if (isset($_GET['bad_login']) && $_GET['bad_login']) {
    ?> <div class='info'> Neuspesno Logovanje!</div> <?php } ?>
            </div>
            <div id='text'>
                Dobrodosli na sajt mali oglasi. <br/>
                Molimo vas da se ulogujete ili <br/>
                napravite nalog ako ste nov <br/>
                korisnik.
            </div>
            Sajt mali oglasi vam omogucuje postavljanje oglasa kao i njihov pregled. <br/>
            <p>
                <a href="http://validator.w3.org/check?uri=referer"><img
                        src="http://www.w3.org/Icons/valid-xhtml10" alt="Valid XHTML 1.0 Strict" height="31" width="88" /></a>
            </p>
        </div>
        <?php if(isset($_SESSION['tardis']) && $_SESSION['tardis']== 1){ ?>
        <script>
            $(document).ready(function(){
               setTimeout(function(){
         var appear=0;
         $("#tardis").prepend("<embed name='tardis' src='sounds/tardis12.mp3' loop='true' hidden='true' autostart='true'></embed>");
             var mat= window.setInterval(function(){
           
            $("#tardis").fadeToggle(1500);
            appear++;
            if(appear==9) {
                $("#tardis").fadeIn(1200);
                clearInterval(mat);}
        },300);
     },1500);
            });
        </script>
        <div id="tardis"> <img alt="tardis" src="slike/tardis.jpeg"/>        
        </div>
        <?php }
           unset($_SESSION['tardis']);
        ?>
    </body>
</html>
<?php
mysqli_close($conn);
?>