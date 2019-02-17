/*
 * Anthony Dupont
 * Data Structure
 * Final Project
 */
#ifndef DUPONTFINAL_FUNCTIONS_H
#define DUPONTFINAL_FUNCTIONS_H

#include "BSTree.hpp"
#include "Node.h"
#include "Actors.h"
#include "Movies.h"

#include <string>

void mainMenu(BSTree<Actors, std::string> *actors, BSTree<Movies, std::string> *movies);
void loopForFiles(BSTree<Actors, std::string> *actors, BSTree<Movies, std::string> *movies);
//this is not templated because I only want to take BST that are of type actors and movies
int intCheck();
int intCheckWinner();

#endif //DUPONTFINAL_FUNCTIONS_H
