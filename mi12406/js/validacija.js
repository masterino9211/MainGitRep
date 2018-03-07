function validacija_oglasa() {

    var ime = document.forms["napravi"]["naziv_oglasa"].value;
    var cena = document.forms["napravi"]["cena_oglasa"].value;
    var kontakt = document.forms["napravi"]["kontakt_oglas"].value;
    var output = "";
    var greska = false;
    
    if (kontakt.length < 5)
    {
        greska = true;
        output += "Kontakt polje mora imati vise od 5 karaktera.";
    }
   
    if (ime.length < 3 ) {
        greska = true;
        output += " Ime oglasa mora imati vise od 3 karaktera.";
    }
    if (!is_int(cena))
    {
        greska = true;
        output += " U polju cena upisite pozitivan broj!";
    }
     

    if (greska) {
        alert(output);
        return false;
    }
    
}
function is_int(value) {
    if ((parseFloat(value) == parseInt(value)) && !isNaN(value)) {
        if (value > 0)
            return true;
        else
            return false;
    } else {
        return false;
    }
}
function validacija_novi_korisnik(){
    var user=document.forms["novi_k"]["user"].value;
    var pass=document.forms["novi_k"]["pass"].value;
    var output="";
    if(user.length < 3 || pass.length < 3){
        greska=true;
        output+="Prekrata sifra ili korisnicko ime moraju imati bar vise od 3 karatkera.";
    }
    if(greska)
    alert (output);
}
function pass_vali(){
    
   var  newpass=document.forms["pass"]["newpass"].value;
   if(newpass.length < 3){
       alert("Nova lozinka mora biti duza od 3 karaktera");
       return false;
   }
   else return true;
}