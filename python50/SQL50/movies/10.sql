SELECT DISTINCT name 
FROM people
WHERE id IN
(
    SELECT person_id
    FROM directors
    WHERE movie_id IN
    (
        SELECT id
        FROM movies
        JOIN ratings ON movies.id = ratings.movie_id
        WHERE ratings.rating >= 9.0
    )
);


SELECT DISTINCT name
FROM people
JOIN directors ON people.id = directors.person_id
JOIN movies ON directors.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating >= 9.0;
