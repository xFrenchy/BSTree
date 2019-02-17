/*
 * Anthony Dupont
 * Data Structure
 * Final Project
 */

//To be used in conjunction with BSTree.h and BSTree.hpp
//If you modify this, please add your name and list any changes that you made
#ifndef NODE_
#define NODE_

#include "Actors.h"
#include "Movies.h"

#include <iostream>
#include <string>
using namespace std;

// A tree node class for ints

//Placeholder for a composite data type

//need two structures, one for actors and one for movies since they have totally different data types, they can't be the same.
//I turned those into classes instead
/*
struct GeneralData
{
    int number; //Update this to your data field  
	string name;
};

struct MoviesStruct
{
    int year;
    int amountOfNominations;
    int rating; //out of 10
    string name;
    int duration;   //in minutes
    string genre1;
    string genre2;
    string release;    //month
    int metacritic; //out of 100
    string synopsis;
    void print()
    {
        cout << "\nName: " << name << "\nYear: " << year << "\nAmount of Nominations: " << amountOfNominations << "\nRating: " << rating
        <<"\nDuration: " << duration << "\nGenre1: " << genre1 << "\nGenre2: " << genre2 << "\nRelease: " << release
    << "\nMetacritic: " << metacritic << "\nSynopsis: " << synopsis << endl;
    }
};

struct ActorsStruct
{
    int year;
    string award;
    int winner; //1 if they won, 0 if they did not win
    string name;
    string film;
    void print()
    {
        cout << "\nName: " << name << "\nYear: " << year << "\nAward: " << award
        << "\nWinner(0 for no, 1 for yes): " << winner  << "\nFilm: " << film << endl;
    }
};*/


//Binary Tree Node
template <typename DATATYPE, typename KEYTYPE>
class Node {
private:
    KEYTYPE key; //key is what will be used to compare and traverse through the tree and how the tree is sorted
    DATATYPE data;  //holds the data
    Node<DATATYPE, KEYTYPE> *left;
    Node<DATATYPE, KEYTYPE> *right;
    Node<DATATYPE, KEYTYPE> *parent;
public:
    Node() {left=nullptr; right=nullptr; parent = nullptr;};
	//setters
    void setKey(KEYTYPE aKey) { key = aKey; };
	void setData(DATATYPE aData) { data = aData; }
    void setLeft(Node<DATATYPE, KEYTYPE> *aLeft) { left = aLeft; };
    void setRight(Node<DATATYPE, KEYTYPE> *aRight) { right = aRight; };
    void setParent(Node<DATATYPE, KEYTYPE> *aParent) { parent = aParent; };
	//getters
    KEYTYPE Key() { return key; };
	DATATYPE Data() { return data; }
    Node<DATATYPE, KEYTYPE> *Left() { return left; };
    Node<DATATYPE, KEYTYPE> *Right() { return right; };
    Node<DATATYPE, KEYTYPE> *Parent() { return parent; };
};

#endif
