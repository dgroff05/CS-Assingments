-- sql to be used by JDBC in Eclipse
-- implemented into psql a01pokemon_dtgroff
-- password: 13347

create extension pgcrypto;

create table client (
    username varchar(20) not null unique,
    password varchar(100) not null,
    first_name varchar(20) not null,
    last_name varchar(20) not null,
    email varchar(40),
    phone_number numeric(10),
    primary key (username)
);

select *
from client;