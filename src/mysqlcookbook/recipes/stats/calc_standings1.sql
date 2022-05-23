# calc_standings1.sql

# Calculate team standings using table that contains a single set of team
# records.

# Note: winning percentages are calculated as wins/(wins+losses).  In
# situations where a team may not have played any games yet, that involves
# division by zero. To avoid that, use IF(wins=0,0,wins/(wins+losses)).

# Get best wins-losses value

SELECT @wl_diff := MAX(wins-losses) FROM standings1;

# Compute standings

SELECT team, wins AS W, losses AS L,
TRUNCATE(wins/(wins+losses),3) AS PCT,
TRUNCATE((@wl_diff - (wins-losses)) / 2,1) AS GB
FROM standings1
ORDER BY wins-losses DESC, PCT DESC;

# Compute standings, with leader GB displayed as '-'

SELECT team, wins AS W, losses AS L,
TRUNCATE(wins/(wins+losses),3) AS PCT,
IF(@wl_diff = (wins-losses),
   '-',TRUNCATE((@wl_diff - (wins-losses)) / 2,1)) AS GB
FROM standings1
ORDER BY wins-losses DESC, PCT DESC;
