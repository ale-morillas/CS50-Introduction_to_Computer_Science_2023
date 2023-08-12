SELECT name FROM people
JOIN stars ON people.id = person_id
JOIN movies ON movies.id = movie_id
WHERE movies.title = "Toy Story";