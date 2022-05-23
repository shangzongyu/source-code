# calc_standings2.sql

# Calculate team standings using table that contains multiple sets of team
# records.

# Note: winning percentages are calculated as wins/(wins+losses).  In
# situations where a team may not have played any games yet, that involves
# division by zero. To avoid that, use IF(wins=0,0,wins/(wins+losses)).

# Compute best wins-losses value for each half season, each division

CREATE TEMPORARY TABLE firstplace
SELECT half, division, MAX(wins-losses) AS wl_diff
FROM standings2
GROUP BY half, division;

SELECT * FROM firstplace;

# Compute standings for each half season, division

SELECT st.half, st.division, st.team, st.wins AS W, st.losses AS L,
TRUNCATE(st.wins/(st.wins+st.losses),3) AS PCT,
TRUNCATE((fp.wl_diff - (st.wins-st.losses)) / 2,1) AS GB
FROM standings2 AS st, firstplace AS fp
WHERE st.half = fp.half AND st.division = fp.division
ORDER BY st.half, st.division, st.wins-st.losses DESC, PCT DESC;

# Compute standings for each half season, division, with leader
# GB displayed as '-'

SELECT st.half, st.division, st.team, st.wins AS W, st.losses AS L,
TRUNCATE(st.wins/(st.wins+st.losses),3) AS PCT,
IF(fp.wl_diff = st.wins-st.losses,
   '-',TRUNCATE((fp.wl_diff - (st.wins-st.losses)) / 2,1)) AS GB
FROM standings2 AS st, firstplace AS fp
WHERE st.half = fp.half AND st.division = fp.division
ORDER BY st.half, st.division, st.wins-st.losses DESC, PCT DESC;

