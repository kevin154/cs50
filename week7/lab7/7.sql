SELECT AVG(energy) FROM songs where artist_id = (SELECT ID FROM artists where name = 'Drake');
