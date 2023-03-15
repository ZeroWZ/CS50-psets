-- SELECT DISTINCT(people.name) FROM movies, ratings, people, directors WHERE ratings.rating >= 9.0 AND ratings.movie_id = movies.id AND movies.id = directors.movie_id AND directors.person_id = people.id;
-- SELECT DISTINCT(people.name) FROM movies JOIN ratings JOIN people JOIN directors
--   ON ratings.movie_id = movies.id and movies.id = directors.movie_id
--   and directors.person_id = people.id WHERE ratings.rating >= 9.0;


SELECT DISTINCT(people.name) FROM
directors JOIN people ON directors.person_id = people.id
JOIN movies ON directors.movie_id = movies.id
WHERE movies.id IN (SELECT ratings.movie_id FROM ratings WHERE ratings.rating >= 9);












