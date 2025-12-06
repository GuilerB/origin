----- Task 2 -----

-- назавние и продолжительность самого длительного трека
select title, duration
from tracks t
order by duration desc
limit 1;

-- Название треков, продолжительность которых не менее 3,5 минут
select title
from tracks t
where duration >= 3.5 
order by duration desc;

--Названия сборников, вышедших в период с 2018 по 2020 годы включительно
select title
from compilations c 
where release_year between 2018 and 2020
order by release_year desc;

-- Исполнители, чьё имя состоит из одного слова
select name
from artists
where name NOT LIKE '% %';

-- Название треков, которые содержат слова «мой» или «my»
select title
from tracks
where title LIKE '%my%';


----- Task 3 -----

-- Количество исполнителей в каждом жанре
select genre_id, COUNT(artist_id)                             
FROM artist_genre                             
GROUP by genre_id                            
ORDER by genre_id;  

-- Количество треков, вошедших в альбомы 2019–2020 годов
select a.title, count(track_id) t_q from tracks t
inner join albums a on a.album_id= t.album_id
where release_year between 2019 and 2020
group by a.title;


-- Средняя продолжительность треков по каждому альбому
SELECT a.title, avg(duration) FROM tracks t
JOIN albums a ON a.album_id = t.album_id
GROUP BY a.title;

-- Все исполнители, которые не выпустили альбомы в 2020 году
select a.name t_q from artists a
inner join artist_album a_a on a_a.artist_id= a.artist_id
inner join albums al on al.album_id = a_a.album_id 
where al.release_year not in (2020) 

-- Названия сборников, в которых присутствует конкретный исполнитель (выберите его сами)
select c.title compilation, t.title tracks, a.title albums from compilations c
inner join track_compilation t_c on t_c.compilation_id= c.compilation_id
inner join tracks t on t.track_id = t_c.track_id 
inner join albums a on a.album_id= t.album_id
inner join artist_album a_a on a_a.album_id = a.album_id
inner join artists art on art.artist_id= a_a.artist_id
where art.name = 'djprolet';  

