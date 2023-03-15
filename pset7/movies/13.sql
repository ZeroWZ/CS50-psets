select DISTINCT(people.name) from people join stars on people.id = stars.person_id
 where not people.name = 'Kevin Bacon' and people.id = stars.person_id and stars.movie_id in
 (select stars.movie_id from people join stars on people.id = stars.person_id
 where people.name = 'Kevin Bacon' and people.birth = 1958);