drop table Elev;
drop table Prieten;
drop table Place;

create table Elev(ID int, nume VARCHAR2(10), clasa int);
create table Prieten(ID1 int, ID2 int);
create table Place(ID1 int, ID2 int);

/* Populate the tables with our data */
insert into Elev values (1510, 'Jordan', 9);
insert into Elev values (1689, 'Gabriel', 9);
insert into Elev values (1381, 'Tiffany', 9);
insert into Elev values (1709, 'Cassandra', 9);
insert into Elev values (1101, 'Haley', 10);
insert into Elev values (1782, 'Andrew', 10);
insert into Elev values (1468, 'Kris', 10);
insert into Elev values (1641, 'Brittany', 10);
insert into Elev values (1247, 'Alexis', 11);
insert into Elev values (1316, 'Austin', 11);
insert into Elev values (1911, 'Gabriel', 11);
insert into Elev values (1501, 'Jessica', 11);
insert into Elev values (1304, 'Jordan', 12);
insert into Elev values (1025, 'John', 12);
insert into Elev values (1934, 'Kyle', 12);
insert into Elev values (1661, 'Logan', 12);

insert into Prieten values (1510, 1381);
insert into Prieten values (1510, 1689);
insert into Prieten values (1689, 1709);
insert into Prieten values (1381, 1247);
insert into Prieten values (1709, 1247);
insert into Prieten values (1689, 1782);
insert into Prieten values (1782, 1468);
insert into Prieten values (1782, 1316);
insert into Prieten values (1782, 1304);
insert into Prieten values (1468, 1101);
insert into Prieten values (1468, 1641);
insert into Prieten values (1101, 1641);
insert into Prieten values (1247, 1911);
insert into Prieten values (1247, 1501);
insert into Prieten values (1911, 1501);
insert into Prieten values (1501, 1934);
insert into Prieten values (1316, 1934);
insert into Prieten values (1934, 1304);
insert into Prieten values (1304, 1661);
insert into Prieten values (1661, 1025);
insert into Prieten select ID2, ID1 from Prieten;

insert into Place values(1689, 1709);
insert into Place values(1709, 1689);
insert into Place values(1782, 1709);
insert into Place values(1911, 1247);
insert into Place values(1247, 1468);
insert into Place values(1641, 1468);
insert into Place values(1316, 1304);
insert into Place values(1501, 1934);
insert into Place values(1934, 1501);
insert into Place values(1025, 1101);
