
---
--- This populates the CD database tables
---
--- This script will delete any existing data, and forces the AUTO_INCREMENT id fields to
--- ensure the IDs all match correctly.
---


--- Delete existing data
delete from track;
delete from cd;
delete from artist;


-- Now the data inserts

--- First the artist (or group) tables
insert into artist(id, name) values(1, 'Pink Floyd');
insert into artist(id, name) values(2, 'Genesis');
insert into artist(id, name) values(3, 'Einaudi');
insert into artist(id, name) values(4, 'Melanie C');

--- Then the cd table
insert into cd(id, title, artist_id, catalogue) values(1, 'Dark Side of the Moon', 1, 'B000024D4P');
insert into cd(id, title, artist_id, catalogue) values(2, 'Wish You Were Here', 1, 'B000024D4S');
insert into cd(id, title, artist_id, catalogue) values(3, 'A Trick of the Tail', 2, 'B000024EXM');
insert into cd(id, title, artist_id, catalogue) values(4, 'Selling England By the Pound', 2, 'B000024E9M');
insert into cd(id, title, artist_id, catalogue) values(5, 'I Giorni', 3, 'B000071WEV');
insert into cd(id, title, artist_id, catalogue) values(6, 'Northern Star', 4, 'B00004YMST');

--- Finally we populate the tracks
insert into track(cd_id, track_id, title) values(1, 1, 'Speak to me');
insert into track(cd_id, track_id, title) values(1, 2, 'Breathe');
insert into track(cd_id, track_id, title) values(1, 3, 'On the run');
insert into track(cd_id, track_id, title) values(1, 4, 'Time');
insert into track(cd_id, track_id, title) values(1, 5, 'Great gig in the sky');
insert into track(cd_id, track_id, title) values(1, 6, 'Money');
insert into track(cd_id, track_id, title) values(1, 7, 'Us and them');
insert into track(cd_id, track_id, title) values(1, 8, 'Any colour you like');
insert into track(cd_id, track_id, title) values(1, 9, 'Brain damage');
insert into track(cd_id, track_id, title) values(1, 10, 'Eclipse ');

insert into track(cd_id, track_id, title) values(2, 1, 'Shine on you crazy diamond');
insert into track(cd_id, track_id, title) values(2, 2, 'Welcome to the machine');
insert into track(cd_id, track_id, title) values(2, 3, 'Have a cigar');
insert into track(cd_id, track_id, title) values(2, 4, 'Wish you were here');
insert into track(cd_id, track_id, title) values(2, 5, 'Shine on you crazy diamond pt.2');



insert into track(cd_id, track_id, title) values(3, 1, 'Dance on a volcano');
insert into track(cd_id, track_id, title) values(3, 2, 'Entangled');
insert into track(cd_id, track_id, title) values(3, 3, 'Squonk');
insert into track(cd_id, track_id, title) values(3, 4, 'Madman moon');
insert into track(cd_id, track_id, title) values(3, 5, 'Robbery assault and battery');
insert into track(cd_id, track_id, title) values(3, 6, 'Ripples');
insert into track(cd_id, track_id, title) values(3, 7, 'Trick of the tail');
insert into track(cd_id, track_id, title) values(3, 8, 'Los Endos');

 
insert into track(cd_id, track_id, title) values(4, 1, 'Dancing with the moonlit knight');
insert into track(cd_id, track_id, title) values(4, 2, 'I know what I like');
insert into track(cd_id, track_id, title) values(4, 3, 'Firth of fifth');
insert into track(cd_id, track_id, title) values(4, 4, 'More fool me');
insert into track(cd_id, track_id, title) values(4, 5, 'Battle of Epping Forest');
insert into track(cd_id, track_id, title) values(4, 6, 'After the ordeal');
insert into track(cd_id, track_id, title) values(4, 7, 'Cinema show');
insert into track(cd_id, track_id, title) values(4, 8, 'Aisle of plenty ');


insert into track(cd_id, track_id, title) values(5, 1, 'Melodia Africana (part 1)');
insert into track(cd_id, track_id, title) values(5, 2, 'I due fiumi');
insert into track(cd_id, track_id, title) values(5, 3, 'In un altra vita');
insert into track(cd_id, track_id, title) values(5, 4, 'Melodia Africana (part 2)');
insert into track(cd_id, track_id, title) values(5, 5, 'Stella del mattino');
insert into track(cd_id, track_id, title) values(5, 6, 'I giorni');
insert into track(cd_id, track_id, title) values(5, 7, 'Samba');
insert into track(cd_id, track_id, title) values(5, 8, 'Melodia Africana (part 3)');
insert into track(cd_id, track_id, title) values(5, 9, 'La nascita delle cose segrete');
insert into track(cd_id, track_id, title) values(5, 10, 'Quel che resta');
insert into track(cd_id, track_id, title) values(5, 11, 'Inizio');
insert into track(cd_id, track_id, title) values(5, 12, 'Limbo');
insert into track(cd_id, track_id, title) values(5, 13, 'Bella notte');
insert into track(cd_id, track_id, title) values(5, 14, 'Canzone Africana (part 4) ');


insert into track(cd_id, track_id, title) values(6, 1, 'Go!');
insert into track(cd_id, track_id, title) values(6, 2, 'Northern Star');
insert into track(cd_id, track_id, title) values(6, 3, 'Going Down');
insert into track(cd_id, track_id, title) values(6, 4, 'I Turn To You');
insert into track(cd_id, track_id, title) values(6, 5, 'If That Were Me');
insert into track(cd_id, track_id, title) values(6, 6, 'Never Be The Same Again');
insert into track(cd_id, track_id, title) values(6, 7, 'Why');
insert into track(cd_id, track_id, title) values(6, 8, 'Suddenly Monday');
insert into track(cd_id, track_id, title) values(6, 9, 'Ga Ga');
insert into track(cd_id, track_id, title) values(6, 10, 'Be The One');
insert into track(cd_id, track_id, title) values(6, 11, 'Closer');
insert into track(cd_id, track_id, title) values(6, 12, 'Feel The Sun');


