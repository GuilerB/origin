-- жанры
CREATE TABLE IF NOT EXISTS genres (
    genre_id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL UNIQUE
);

-- исполнители
CREATE table IF NOT EXISTS artists (
    artist_id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT null UNIQUE
);

-- жанры - исполнители
CREATE TABLE IF NOT exists artist_genre (
    artist_id INTEGER REFERENCES artists(artist_id),
    genre_id INTEGER REFERENCES genres(genre_id),
    CONSTRAINT pk PRIMARY KEY (artist_id, genre_id)
);

-- Создание таблицы альбомов
CREATE table IF NOT EXISTS albums (
    album_id SERIAL PRIMARY KEY,
    title VARCHAR(200) NOT NULL,
    release_year INTEGER NOT NULL CHECK (release_year >= 1900)
);

-- исполнители - альбомы
CREATE TABLE IF NOT exists artist_album (
    artist_id INTEGER REFERENCES artists(artist_id),
    album_id INTEGER REFERENCES albums(album_id),
    CONSTRAINT pk PRIMARY KEY (artist_id, album_id)
);

-- треки
CREATE TABLE IF NOT exists tracks (
    track_id SERIAL PRIMARY KEY,
    title VARCHAR(200) NOT NULL,
    duration INTEGER NOT NULL CHECK (duration > 0), -- Длительность в секундах
    album_id INTEGER NOT NULL REFERENCES albums(album_id)
);

-- сборники
CREATE TABLE IF NOT exists compilations (
    compilation_id SERIAL PRIMARY KEY,
    title VARCHAR(200) NOT NULL,
    release_year INTEGER NOT NULL CHECK (release_year >= 1850)
);

-- сборники и треки
CREATE TABLE IF NOT exists track_compilation (
    track_id INTEGER REFERENCES tracks(track_id) ON DELETE CASCADE,
    compilation_id INTEGER REFERENCES compilations(compilation_id) ON DELETE CASCADE,
    CONSTRAINT pk PRIMARY KEY (track_id, compilation_id)
);