---
--- SQL for creating the sample application database
---

-- Drop any existing tables
-- Uncomment the next lines to drop the tables if needed.
-- drop table cd;
-- drop table artist;
-- drop table track;

create table cd (
	id INTEGER AUTO_INCREMENT NOT NULL PRIMARY KEY,
	title VARCHAR(70) NOT NULL,	    
	artist_id INTEGER NOT NULL,
	catalogue VARCHAR(30) NOT NULL
);

create table artist (
	id INTEGER AUTO_INCREMENT NOT NULL PRIMARY KEY,
	name VARCHAR(100) NOT NULL
);

create table track (
	cd_id INTEGER NOT NULL,
	track_id INTEGER NOT NULL,
	title VARCHAR(70),
	PRIMARY KEY(cd_id, track_id)
);


