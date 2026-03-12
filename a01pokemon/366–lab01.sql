-- Name: Dylan Groff
-- Assignment: Pokemon (a01pokemon)
-- Date: 2/3/26
-- Course: CMSC 366
-- Description: Introduction to SQL using a Pokemon database.

-- Question 1
create table pokemon
(
    name varchar(30),
    type_1 varchar(10),
    type_2 varchar(10),
    total int,
    hit_points int,
    attack int,
    defense int,
    special_attack int,
    special_defense int,
    speed int,
    generation smallint,
    legendary boolean,
    primary key (name,type_1)
);
-- Response: CREATE TABLE

-- Question 2
\copy pokemon FROM 'pokemon.csv' CSV
-- Response: COPY 800

-- Question 3
insert into pokemon values ('Marauder','Fighting',null,400,100,70,50,100,30,50,6,TRUE);
-- Response: INSERT 0 1

-- Question 4
select name
from pokemon
where legendary = TRUE and generation = 1;
/* Response: 
        name         
---------------------
 Articuno
 Zapdos
 Moltres
 Mewtwo
 MewtwoMega Mewtwo X
 MewtwoMega Mewtwo Y
(6 rows)
*/

--Question 5 
select name
from pokemon
where speed > 150 and attack > defense;
/* Response:
       name        
-------------------
 Ninjask
 DeoxysSpeed Forme
(2 rows)
*/

-- Question 6
select type_1,type_2
from pokemon
where speed > 40 and speed < 45;
/* Response:
  type_1  | type_2 
----------+--------
 Water    | 
 Poison   | 
 Psychic  | 
 Water    | 
 Rock     | Ground
 Rock     | Grass
 Dragon   | Ground
 Normal   | 
 Normal   | Flying
 Bug      | Grass
 Bug      | Grass
 Ice      | 
 Fairy    | 
 Fighting | 
 Poison   | Dragon
 Water    | 
 Ghost    | Grass
(17 rows)
*/

-- Question 7
select count(*)
from pokemon;
/* Response
 count 
-------
   801
(1 row)
*/

-- Question 8
select max(hit_points)
from pokemon
where generation = 3;
/* Response:
max 
-----
 170
(1 row)
*/

-- Question 9
select name
from pokemon
where name like 'Z%';
/* Response:
       name       
------------------
 Zubat
 Zapdos
 Zigzagoon
 Zangoose
 Zebstrika
 Zorua
 Zoroark
 Zweilous
 Zekrom
 Zygarde50% Forme
(10 rows)
*/

-- Question 10
delete from pokemon where name = 'Marauder';
-- Response: DELETE 1