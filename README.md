# Plex-Server
## Description
Plex Media Server is a user-friendly way to store data about all your movies in one place and make it accessible from your device. This project is used as an interface for the Plex Media Server such that the data gets stored in files and can be accessed by the user of that device. 

Each node of the splay tree contains the movie’s title, synopsis, genre, quality, duration, frequency, size, left and right node pointers. The title, genre, synopsis, quality and duration are taken as input when adding the movie to the tree.

Frequency and size are calculated for each node during execution. Frequency of search is stored in each node for printing details of the most frequently searched movie. A vector is maintained to store the play history, which contains the movie titles. Details of the movies in the tree are displayed in pre order form.
 
Modifications to the data can only be done admins as it’s password protected. 50000 MB of storage is given as the maximum storage capacity of the server, and when more movies are added, empty storage space decreases based on the quality and duration of each movie.
 
The project also makes use of 3 files:
*	playhistory.txt - To store the play history after closing the program and storing the values in the play_hist vector during execution
*	movies.txt - To store all movie details in the file
*	server.txt - To store the count of movies in the server

The data in these files are loaded into the program (movie data stored as nodes in the splay tree and it will be splayed such that the root node of the tree before closing the program will be the root of the tree after executing it again) when the program is executed. When the user exits the program, the data gets stored in the respective files before execution stops.

## Functions
1.	**PLAY A MOVIE** - To show details and play the movie entered by the user if it’s in the file
2.	**SEARCH A MOVIE** - To search for a movie entered by the user if it’s in the file
3.	**LIST ALL MOVIES** - To print details of all movies stored in the file
4.	**EDIT SERVER** - Only admins can enter password to access this operation
      -	***UPLOAD A MOVIE*** - admins can add new movies to the file
      -	***DELETE A MOVIE*** -  admins can delete the movie if it exists in the file
      -	***BACK*** - To go back to the main menu
5. **MOST FREQUENTLY SEARCHED MOVIE** - To print the details of the most frequently searched movie
6. **PLAY HISTORY** - To print the movie titles of all the movies that have been played by the user
7. **LAST PLAYED** - To print the last played movie that is in the file
8. **SERVER DETAILS** - To print the server details including space available in the server
9. **LIST MOVIES OF SAME GENRE** - To print details of movies belonging to the genre entered by the user
10. **EXIT** - To Exit the program and upload all the data in the splay tree into the files
