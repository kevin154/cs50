SELECT name FROM songs where artist_id = (SELECT ID FROM artists where name = 'Post Malone');
