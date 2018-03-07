CREATE DATABASE IF NOT EXISTS ai11133
 CHARACTER SET utf8
 DEFAULT CHARACTER SET utf8
 COLLATE utf8_general_ci
 DEFAULT COLLATE utf8_general_ci;

USE ai11133;

CREATE TABLE IF NOT EXISTS users
(
id INT NOT NULL AUTO_INCREMENT ,
usern CHAR(32) NOT NULL ,
passw CHAR(32) NOT NULL ,
PRIMARY KEY (id)
)DEFAULT CHARACTER SET utf8
 COLLATE utf8_general_ci;

INSERT INTO users (usern,passw) VALUES("maki123","mindza");
INSERT INTO users (usern,passw) VALUES("goran56","qwerty");
INSERT INTO users (usern,passw) VALUES("petarperic","kalauza");
INSERT INTO users (usern,passw) VALUES("igor","igor123");
INSERT INTO users (usern,passw) VALUES("Stefan123","stefke5");
INSERT INTO users (usern,passw) VALUES("aleksandar5","smeker1992");
INSERT INTO users (usern,passw) VALUES("petar80","sifra78");
INSERT INTO users (usern,passw) VALUES("jela12","delete");
INSERT INTO users (usern,passw) VALUES("milena","milena12");
INSERT INTO users (usern,passw) VALUES("darko","balu");
INSERT INTO users (usern,passw) VALUES("aleksandra","ciki123");
INSERT INTO users (usern,passw) VALUES("natasa","srecica");
INSERT INTO users (usern,passw) VALUES("milica","mokrepatike");

CREATE TABLE IF NOT EXISTS mobilni_telefoni
(
id int ,
naziv CHAR(32) NOT NULL,
opis CHAR(160) ,
cena int NOT NULL ,
valuta char(8) NOT NULL,
PRIMARY KEY (id,naziv),
kontakt char(32) NOT NULL,

FOREIGN KEY (id) REFERENCES users(id)
)DEFAULT CHARACTER SET utf8
 COLLATE utf8_general_ci;

INSERT INTO mobilni_telefoni (id,naziv,opis,cena,valuta,kontakt) VALUES(1,"Nokia 6600","Prodajem nokiju staru 3 godine , ocuvana",100,"euro","mojmelj@google.com");
INSERT INTO mobilni_telefoni (id,naziv,opis,cena,valuta,kontakt) VALUES(2,"Nokia ASHA 300","veoma povoljno,malo koriscena , ocuvana",150,"dolar","mojmelj@google.com");
INSERT INTO mobilni_telefoni (id,naziv,opis,cena,valuta,kontakt) VALUES(3,"Nokia 6131","Neispravna",200,"dinar","mejl@mejl.com");
INSERT INTO mobilni_telefoni (id,naziv,opis,cena,valuta,kontakt) VALUES(4,"Samsung chat3222","Pod garancijom",80,"euro",01123456);

CREATE TABLE IF NOT EXISTS muzicki_instrumenti
(
id int ,
naziv CHAR(32) NOT NULL,
opis CHAR(160) ,
cena int NOT NULL ,
valuta char(8) NOT NULL,
kontakt char(32) NOT NULL,
PRIMARY KEY (id,naziv),
FOREIGN KEY (id) REFERENCES users(id)
)DEFAULT CHARACTER SET utf8
 COLLATE utf8_general_ci;

INSERT INTO muzicki_instrumenti (id,naziv,opis,cena,valuta,kontakt) VALUES(5,"Ibanez rg170","Gitara u odlicnom stanju!!",170,"euro","123-456");
INSERT INTO muzicki_instrumenti (id,naziv,opis,cena,valuta,kontakt) VALUES(6,"Pojacalo za bas gitaru","Fender 800 PRO HEAD 230V",500,"dolar",011789456);
INSERT INTO muzicki_instrumenti (id,naziv,opis,cena,valuta,kontakt) VALUES(7,"Yamaha P 35 X stalak za dig. klavir + slusalice","Osnovni model",5000,"dolar",011789456);
INSERT INTO muzicki_instrumenti (id,naziv,opis,cena,valuta,kontakt) VALUES(9,"Fender stratokaster","Odlicno ocuvana profesijonalna gitara",3000,"dolar","bojan@mail.com");

CREATE TABLE IF NOT EXISTS bela_tehnika
(
id int ,
naziv CHAR(32) NOT NULL,
opis CHAR(160) ,
cena int NOT NULL ,
valuta char(8) NOT NULL,
kontakt char(32) NOT NULL,
PRIMARY KEY (id,naziv),
FOREIGN KEY (id) REFERENCES users(id)
)DEFAULT CHARACTER SET utf8
 COLLATE utf8_general_ci;

INSERT INTO bela_tehnika (id,naziv,opis,cena,valuta,kontakt) VALUES(13,"SAMSUNG LED 32 5000","Televizor led jos pod garancijom",36000,"dinar","mejl@mejl.com");
INSERT INTO bela_tehnika (id,naziv,opis,cena,valuta,kontakt) VALUES(8,"SAMSUNG LED 32 5000","Televizor led jos pod garancijom",279,"euro","mejl@mejl.com");
INSERT INTO bela_tehnika (id,naziv,opis,cena,valuta,kontakt) VALUES(9,"Presa za kosu","Jednostavna za upotrebu",600,"kuna",06652368);
INSERT INTO bela_tehnika (id,naziv,opis,cena,valuta,kontakt) VALUES(10,"Digitalni fotoaparat","Memorijska kartica na poklon",100,"euro",06652368);
INSERT INTO bela_tehnika (id,naziv,opis,cena,valuta,kontakt) VALUES(11,"Bezicni telefon","Osvetljen graficki displej",3000,"dinar",062753645);
INSERT INTO bela_tehnika (id,naziv,opis,cena,valuta,kontakt) VALUES(12,"Postolje za laptop","Napajanje preko USB porta",3000,"dinar",062753645);
INSERT INTO bela_tehnika (id,naziv,opis,cena,valuta,kontakt) VALUES(1,"Blender","Moguce drobljenje leda",1000,"kuna",06652368);
INSERT INTO bela_tehnika (id,naziv,opis,cena,valuta,kontakt) VALUES(3,"Ugradni frizider","Candy",200,"euro",011789456);
INSERT INTO bela_tehnika (id,naziv,opis,cena,valuta,kontakt) VALUES(5,"Zamrzivac","Gorenje",200,"dolar",011789456);
INSERT INTO bela_tehnika (id,naziv,opis,cena,valuta,kontakt) VALUES(7,"Klima","Galanz",225,"euro",011789456);