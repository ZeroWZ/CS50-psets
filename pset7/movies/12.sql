SELECT DISTINCT(movies.title) FROM movies JOIN stars ON movies.id = stars.movie_id
WHERE stars.movie_id in (SELECT stars.movie_id FROM stars JOIN people ON people.id = stars.person_id
WHERE people.name = 'Johnny Depp')
AND stars.movie_id in (SELECT stars.movie_id FROM stars JOIN people ON people.id = stars.person_id
WHERE people.name = 'Helena Bonham Carter');
