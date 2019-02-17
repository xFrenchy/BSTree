/*
 * Anthony Dupont
 * Data Structure
 * Final Project
 */

#include "Node.h"
#include "BSTree.hpp"   //don't add it to the makefile
#include "Functions.h"
#include "Actors.h"
#include "Movies.h"

#include <iostream>
#include <string>

int main() {
    BSTree<Actors, std::string> *actors = new BSTree<Actors, std::string>();       //if I have problem with root, turn this into a pointer = new bstree
    BSTree<Movies, std::string> *movies = new BSTree <Movies, std::string>();
    //I need to read the files for these BST, problem is that the user provides me with the file
    loopForFiles(actors, movies);
    //This means that I need a loop for reading in the files, to make sure that at the end of the loop, or before we break out of the loop
    //that there is data inside of my trees. I wouldn't need this if I wasn't asking for the file form the user

    //loopForFiles(actors, movies);
    mainMenu(actors, movies);
    return 0;
}

/* TODO:
 * Actors is done
 * Sort by duration isn't accurate for durations that are not 3 digit long
 *
 *
 * Error checking TODO:
 * Accept only ints for when the user is choosing options inside of the menu [DONE]
 *
 * When checking strings for partial or complete, tolower the user string and the node string, remove all spaces as well [DONE]
 *
 * When user can only enter 1 or 0 for modifying node, make sure they can only enter 1 or 0 and don't break the rest of the cin's and getlines [DONE]
 *
 * Putting a 0\ for when it checks if it's a 0 or 1 will carry over the input
 *
 *
 * Errors fixes TODO:
 * getting a syntax error from trying to call a function from my actors and movies BST, something to do with template syntax[DONE]
 *
 * I have duplicate commas in the picture.csv which is causing issues, do i manually get rid of it or get rid of it through code?[DONE, in code]
 *      (line 28)Rain Man,1988,8,8,133,Drama,,December,65,Selfish yuppie Charlie Babbitts father left a fortune to his savant brother Raymond and a pittance to Charlie; they travel cross-country.
 *
 * I can't figure out how to retrieve the pointer of a node from the tree, I'm able to find it correctly but my return is going out of scope[DONE]
 *      My recursion was wrong
 *
 * The delete function deletes based off the key and not a specific node. If I told it to delete Gladys Cooper, it will delete Gladys Cooper
 *      There is no way to be accurate with the delete function. No field is unique. What am I supposed to do? [DONE]
 *      Was told to not worry, however I did create my own delete function that's more accurate
 *
 * The same goes for findNode. The key works on finding the first match
 *
 * When modifying, if you put in a year that's too big, it crashes
 *
 * NOTES:
 * Templates classes need to be defined in the same file. We can't have a .h and a .hpp
 *
 * I am not requiring the user to know the award and winner field for a complete search,
 *      I don't think the user should know these when searching
 *
 * Since findNode and delete not cannot be accurate, I have to write a separate function that is similar but more accurate
 *
 * Partial search for actors is only based on names for now(might expend later)
 *
 * To keep track of what the tree is sorted by, create a variable that keeps track of what it's sorted by
 * 0 = name, 1 = year etc etc. Retrieve this number and addNode respectively and modify as well. This way I know what
 * to pass in and what the key is
 *
 * ----Actors-------
 * sortedBy 0 = name
 * sortedBy 1 = film
 * sortedBy 2 = year
 * ------Movies------
 * sortedBy 3 = name
 * sortedBy 4 = year
 * sortedBy 5 = duration
 * sortedBy 6 = rating
 * sortedBy 7 = metacritic
 * sortedBy 8 = amountOfNominations
 */