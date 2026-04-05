SELECT
    (AVG(danceability) + AVG(energy) + AVG(valence)) / 3.0 AS overall_average
FROM (
    SELECT *
    FROM songs
    LIMIT 100
);