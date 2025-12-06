		-- independencies
insert into genres (genre_id, name)
values (1, 'classic') , (2, 'strangerock'), (3, 'eclectic'), (4, 'dialectic')

insert into artists (artist_id, name)
values (1, 'bach') , (2, 'dancelens'), (3, 'djprolet'), (4, 'nuevosrotas'), (5, 'theolds')

insert into albums (album_id, title, release_year)
values (1, 'old_n_dark', 1900) , 
	   (2, 'new_n_red', 1970), 
	   (3, 'salad', 1995), 
	   (4, 'replay', 2020), 
	   (5, 'highliens', 1961)
	 
insert into compilations (compilation_id, title, release_year)
values (1, 'colors', 1971) , 
	   (2, 'diffs', 2020), 
	   (3, 'phils', 1980 ), 
	   (4, 'calm', 2020), 
	   (5, 'light', 2025)	   	   	   

	   -- dependencies
insert into tracks (track_id, title, duration, album_id)
values (1, 'dark', 14, 1) , 
	   (2, 'red', 15, 2), 
	   (3, 'mushrooms', 10, 3), 
	   (4, 'reverse', 4, 4), 
	   (5, 'myalienrock', 9, 5), 
	   (6, 'highhigh', 5, 4),
	   (7, 'newtophilosophy', 8, 2)	   
	   
insert into artist_genre (artist_id, genre_id)
values (1, 1) , 
	   (2, 3), 
	   (3, 2), 
	   (4, 4),
	   (5, 1)
  	   
insert into artist_album (artist_id, album_id)
values (1, 1), 
	   (2, 3), 
	   (3, 5), 
	   (4, 2),
	   (5, 4)
	   
insert into track_compilation (track_id, compilation_id)
values (1, 1) , 
	   (2, 1), 
	   (3, 2), 
	   (4, 4),
	   (5, 5),
	   (6, 5),
	   (7, 3)
	   
