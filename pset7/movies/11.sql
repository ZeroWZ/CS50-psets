SELECT movies.title FROM ((movies JOIN stars JOIN people 
ON movies.id = stars.movie_id AND stars.person_id = people.id) 
movies JOIN ratings ON movies.id = ratings.movie_id) 
WHERE people.name = 'Chadwick Boseman' ORDER BY ratings.rating DESC LIMIT 5;