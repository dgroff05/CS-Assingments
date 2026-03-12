/* Dylan Groff */
/* Lab 02: Music (basic) */

/* PROBLEM 1 BEGIN */
-- works
create table label
(
    label_name varchar(15),
    label_street varchar(25),
    label_city varchar(15),
    label_state char(2),
    label_postcode char(5),
    label_nation varchar(5),
    primary key (label_name)
);

create table album
(
    album_id smallint,
    album_label_id varchar(10),
    album_title varchar(15),
    album_year int,
    label_name varchar(15),
    primary key (album_id),
    foreign key (label_name) references label(label_name)
);

create table track
(
    track_id smallint,
    track_num smallint,
    track_title varchar(40),
    track_length numeric(4,2),
    album_id smallint,
    primary key (track_id),
    foreign key (album_id) references album(album_id)
);
/* PROBLEM 1 END */

/* PROBLEM 2 BEGIN */
-- works
SELECT track_title, album_title, track_length
from track, album
where track.album_id = album.album_id 
order by album_title, track_length, track_title;
/* PROBLEM 2 END */

/* PROBLEM 3 BEGIN */
-- works
SELECT track_title, track_length
from (select *
      from album natural join track) as album_track
where album_title = 'Swing';
/* PROBLEM 3 END */

/* PROBLEM 4 BEGIN */
-- works
select album_title, track_title, track_length
from album natural join track
where (album_title, track_length) = some
                                (select album_title, max(track_length)
                                from album natural join track
                                group by album_title);

/* PROBLEM 4 END */

/* PROBLEM 5 BEGIN */
-- works
select album_title, count(track_num), sum(track_length)
from album natural join track
group by album_title
order by count(track_num) desc;
/* PROBLEM 5 END */

/* PROBLEM 6 BEGIN */
-- works
SELECT label_name, label_nation, album_title, sum(track_length) as album_length
from album natural join label natural join track
group by label_name, label_nation, album_title
having album_title in (select album_title
                        from album natural join track
                        group by album_title
                        having sum(track_length) > 40.00);
/* PROBLEM 6 END */

/* PROBLEM 7 BEGIN */
-- works
select album_title, track_title, track_length
from album natural join track
order by track_length asc
limit 3;
/* PROBLEM 7 END */

/* PROBLEM 8 BEGIN */
-- works
create view album_view as 
select album_id, album_label_id, album_title, album_year, album_length
from album natural join (select album_title, sum(track_length) as album_length
from track natural join album
group by album_title) as album_length_title;                        
/* PROBLEM 8 END */

/* PROBLEM 9 BEGIN */
-- works
SELECT track_title, track_length, album_title
from track natural join album
where track_title like 'C%';
/* PROBLEM 9 END */
