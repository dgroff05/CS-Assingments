/* REPLACE THIS WITH YOUR NAME */
/* Lab 03: Music (full) */

/* PROBLEM 1 BEGIN */
-- works
create table label (
    label_name varchar(15),
    label_street varchar(25),
    label_city varchar(15),
    label_state char(2),
    label_postcode char(5),
    label_nation varchar(5),
    primary key (label_name)
);
create table artist (
    artist_name varchar(30),
    primary key (artist_name)
);
create table album (
    album_id smallint,
    album_label_id varchar(10),
    album_title varchar(15),
    album_year int,
    artist_name varchar(30),
    label_name varchar(15),
    primary key (album_id),
    foreign key (label_name) references label(label_name),
    foreign key (artist_name) references artist(artist_name)
);
create table person (
    person_id smallint,
    person_first_name varchar(15),
    person_last_name varchar(15),
    primary key (person_id)
);
create table is_member_of (
    start_date char(10),
    end_date char(10),
    artist_name varchar(30),
    person_id smallint,
    primary key (start_date, artist_name, person_id),
    foreign key (artist_name) references artist(artist_name),
    foreign key (person_id) references person(person_id)
);
create table composition (
    composition_id int,
    composition_title varchar(30),
    composition_year int,
    primary key (composition_id)
);
create table composes (
    composes_role varchar(10),
    composes_order smallint,
    composition_id smallint,
    person_id smallint,
    primary key (composes_role, composition_id, person_id),
    foreign key (composition_id) references composition(composition_id),
    foreign key (person_id) references person (person_id)
);
create table recording (
    recording_id int,
    recording_length numeric(4, 2),
    recording_date char(10),
    composition_id int,
    primary key (recording_id, composition_id),
    foreign key (composition_id) references composition (composition_id)
);
create table performs (
    performs_role varchar(15),
    composition_id int,
    person_id smallint,
    recording_id int,
    primary key (performs_role, composition_id, person_id, recording_id),
    foreign key (person_id) references person (person_id),
    foreign key (recording_id, composition_id) references recording (recording_id, composition_id)
);
create table track (
    track_num int,
    album_id smallint,
    composition_id int,
    recording_id int,
    primary key (track_num, album_id, composition_id, recording_id),
    unique (track_num, album_id),
    foreign key (album_id) references album (album_id),
    foreign key (recording_id, composition_id) references recording (recording_id, composition_id)
);
/* PROBLEM 1 END */

/* PROBLEM 2 BEGIN */
-- works
SELECT track_num, composition_title
from track natural join composition
where album_id = (select album_id
                from album
                where album_title = 'Giant Steps');
/* PROBLEM 2 END */

/* PROBLEM 3 BEGIN */
-- works
select person_first_name, person_last_name, performs_role
from performs natural join recording natural join person
where recording_date = '1959-05-04' and composition_id = (select composition_id
                                                            from composition
                                                            where composition_title = 'Giant Steps'); 
/* PROBLEM 3 END */

/* PROBLEM 4 BEGIN */
-- works
SELECT person_first_name, person_last_name
from person natural join composes
where person_id = some (select person_id
                        from person natural join performs
                        where performs_role = 'tenor sax');
/* PROBLEM 4 END */

/* PROBLEM 5 BEGIN */
-- works
SELECT composition_title, track_num, album_title
from composition natural join track natural join album
where (composition_id, album_id) = some (select composition_id, album_id
                            from composition natural join track
                            group by composition_id, album_id
                            having count(composition_id) > 1)
order by composition_title, track_num;
/* PROBLEM 5 END */

/* PROBLEM 6 BEGIN */
SELECT recording_id, recording_date
from recording as r
where not exists (select *
                    from album as a
                    where not exists (select *
                                        from track as t
                                        where r.recording_id = t.recording_id and a.album_id = t.album_id));
/* PROBLEM 6 END */

/* PROBLEM 7 BEGIN */
select recording_id, recording_date
from recording natural join track
group by recording_id, recording_date
having count(distinct album_id) = (select count(*) from album);
/* PROBLEM 7 END */
