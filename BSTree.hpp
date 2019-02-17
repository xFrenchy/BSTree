/*
 * Anthony Dupont
 * Data Structure
 * Final Project
 */

//To be used in conjunction with Node.h and BSTree<DATATYPE, KEYTYPE>.cpp
//If you modify this, please add your name and list any changes that you made

#ifndef BSTREEINT_H
#define BSTREEINT_H

#include "Node.h"
//#include "Functions.h"    //can't do this because bstree will include itself, have to use extern, learned about extern in TA office hour
#include "Actors.h"
#include "Movies.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

extern int intCheckWinner();
extern int intCheck();

// Binary Search Tree class
template <typename DATATYPE, typename KEYTYPE>
class BSTree {
private:
    Node<DATATYPE, KEYTYPE> *root;	//this is the root of the tree
    void addNode(KEYTYPE key, Node<DATATYPE, KEYTYPE> *leaf, DATATYPE &data);
    Node<DATATYPE, KEYTYPE> *deleteNode(Node<DATATYPE, KEYTYPE> *node, KEYTYPE key);
    Node<DATATYPE, KEYTYPE> *deleteNodeAct(Node<DATATYPE, KEYTYPE> *node, KEYTYPE key, string film, string year);
    void freeNode(Node<DATATYPE, KEYTYPE> *leaf);
	void printInorder(Node<DATATYPE, KEYTYPE> *node);
	Node<DATATYPE, KEYTYPE> *findNode(KEYTYPE key, Node<DATATYPE, KEYTYPE> *node);
	void partialSearch(string key, Node<DATATYPE, KEYTYPE> *node, vector<Node<DATATYPE,KEYTYPE> > &vec);
    bool searchAndModifyAct(string key, string film, string year, Node<DATATYPE, KEYTYPE> *node);
    bool searchAndModifyMov(string key, string year, Node<DATATYPE, KEYTYPE> *node);
    void sortByField(Node<DATATYPE, KEYTYPE> *node, int choice, BSTree<DATATYPE, KEYTYPE> *newSortedTree);
    void sortByFieldMov(Node<DATATYPE, KEYTYPE> *node, int choice, BSTree<DATATYPE, KEYTYPE> *newSortedTree);
    Node<DATATYPE,KEYTYPE> *completeSearchAct(Node<DATATYPE, KEYTYPE> *node, KEYTYPE key, string film, string year);
    Node<DATATYPE,KEYTYPE> *completeSearchMov(Node<DATATYPE, KEYTYPE> *node, KEYTYPE key);
    void writeToFileAct(Node<DATATYPE, KEYTYPE> *node, ofstream &file);
    void writeToFileMov(Node<DATATYPE, KEYTYPE> *node, ofstream &file);
    int sortedBy;
	bool hasData;
	int size;
public:
    BSTree<DATATYPE, KEYTYPE>();
    ~BSTree<DATATYPE, KEYTYPE>();
    Node<DATATYPE, KEYTYPE> *Root() { return root; }
    void setRoot(Node<DATATYPE, KEYTYPE> *_root) {root = _root;}
    void addNode(KEYTYPE key, DATATYPE &data);
	Node<DATATYPE, KEYTYPE> *findNode(KEYTYPE key);
	void printInorder();
	void print(ostream & out, const DATATYPE & data);
    void deleteNode(KEYTYPE key);
	Node<DATATYPE, KEYTYPE> *min(Node<DATATYPE, KEYTYPE> *node);
	Node<DATATYPE, KEYTYPE> *max(Node<DATATYPE, KEYTYPE> *node);
	void readActors();  //Should have no parameters
	void readMovies();  //^
    void searchAndModifyAct(string key, string film, string year);
    void searchAndModifyMov(string key, string year);
    void searchAndDeleteAct(string key, string film, string year);
    void partialSearch(string key, vector<Node<DATATYPE, KEYTYPE>> &vec);
    Node<DATATYPE,KEYTYPE> *completeSearchAct(KEYTYPE key, string film, string year);
    Node<DATATYPE,KEYTYPE> *completeSearchMov(KEYTYPE key);
    int sortByField(int choice, BSTree<DATATYPE, KEYTYPE> *currentTree);
    int sortByFieldMov(int choice, BSTree<DATATYPE, KEYTYPE> *currentTree);
    void writeToFileAct();
    void writeToFileMov();
    void setHasData(bool _hasData) {hasData = _hasData;}
	bool getHasData() {return hasData;}
	void setSize(int _size) {size = _size;}
	int getSize() {return size;}
	void setSortedBy(int _sortedBy) {sortedBy = _sortedBy;}
    int getSortedBy() {return sortedBy;}
};

// Constructor
template <typename DATATYPE, typename KEYTYPE>
BSTree<DATATYPE, KEYTYPE>::BSTree() {
	root = nullptr;
	hasData = false;
	size = 0;
    sortedBy = 0;
}

// Destructor
template <typename DATATYPE, typename KEYTYPE>
BSTree<DATATYPE, KEYTYPE>::~BSTree() {
	if (root !=nullptr)
		freeNode(root);
}

// Free the node
//this means to clear everything under the node, make sure there is no memory leak
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::freeNode(Node<DATATYPE, KEYTYPE> * leaf)
{
    /*
	//Student must fill in
	//if the root is the leaf, delete that leaf
	// otherwise if the leaf is not null
	//now delete the leaf
    */
    if(!leaf)
        return;
    if(!leaf->Left() && !leaf->Right()) //there is no path to the left or right so we delete this one
        delete leaf;
    else
    {
        if(leaf->Left())        //if there is a path to the left we traverse left
            freeNode(leaf->Left());
        if(leaf->Right())       //if there is a path to the right we traverse right
            freeNode(leaf->Right());
        delete leaf;
    }
}

// Add a node
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::addNode(KEYTYPE key, DATATYPE &data)
{
	if (Root() == nullptr)
	{
		Node<DATATYPE, KEYTYPE> *newNodePtr = new Node<DATATYPE, KEYTYPE>();
		newNodePtr->setKey(key);
		newNodePtr->setData(data);
		root = newNodePtr;
		root->setParent(root);

	}
	else
		addNode(key, root, data);
}

// Add a node (private)
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::addNode(KEYTYPE key, Node<DATATYPE, KEYTYPE> * leaf, DATATYPE& data) {
	//Student must fill in
	//Don't forget to set your key, Parent, then left or right
	//Based on the case you use you will addNode recursively to the left or right

	//First check if root is null
	if(root == nullptr)
    {
        //make a new node
        Node<DATATYPE, KEYTYPE> *nodePtr = new Node<DATATYPE, KEYTYPE>();
        //set the key and data
        nodePtr->setKey(key);
        nodePtr->setData(data);
        nodePtr->setParent(root);
        nodePtr->setLeft(nullptr);
        nodePtr->setRight(nullptr);
        //set the root
        root = nodePtr; //root points to this node which means this Node is my root
    }
    else    //else root is not empty and we have to traverse the tree to figure out where to add
    {
        //Otherwise
        //Check to see if the key is < the leaf's key
        if(key < leaf->Key())   //if the key is less than the leaf's key, we want to add this node to the left
        {
            // if left is not null then
            if(leaf->Left() != nullptr)
            {
                //Add the node to the left (recursively)
                addNode(key, leaf->Left(), data);	//passing the node at the left with the data I want to add
            }
            else    // Otherwise make a new node and attach it to the left because the left is a nullptr
            {
                Node<DATATYPE, KEYTYPE> *nodePtr = new Node<DATATYPE, KEYTYPE>();
                nodePtr->setKey(key);
                nodePtr->setData(data);
                nodePtr->setParent(leaf);
                nodePtr->setLeft(nullptr);
                nodePtr->setRight(nullptr);
                leaf->setLeft(nodePtr);     //the left pointer no longer points to null but points to this node now
            }
        }
        //Check to see if the key >= leaf's key
        if(key >= leaf->Key())      //this is like my else statement, it's either going to be less than or greater than/equal
        {
            // if leaf's right is not null then
            if(leaf->Right() != nullptr)
            {
                //Add the node to the right (recursively)
                addNode(key, leaf->Right(), data);
            }
            else    //else I can add it to the right
            {
                // Otherwise make new node and attach it to the right
                Node<DATATYPE, KEYTYPE> *nodePtr = new Node<DATATYPE, KEYTYPE>();
                nodePtr->setKey(key);
                nodePtr->setData(data);
                nodePtr->setParent(leaf);
                nodePtr->setLeft(nullptr);
                nodePtr->setRight(nullptr);
                leaf->setRight(nodePtr);
            }
        }
    }
}

template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> *BSTree<DATATYPE, KEYTYPE>::findNode(KEYTYPE key)
{
	return findNode(key, root);
}

// Find a node
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> *BSTree<DATATYPE, KEYTYPE>::findNode(KEYTYPE key, Node<DATATYPE, KEYTYPE> *node)
{
	//Student must fill in
	// trap nullptr first in case we've hit the end unsuccessfully.
	// success base case
	//Greater than (Right), Less than (Left)
	if(node == nullptr)
	{
		return nullptr;
	}

	if(key < node->Key())	//go left
	{
		return findNode(key, node->Left());
	}
	else if(key > node->Key())	//go right
	{
		return findNode(key, node->Right());
	}
	else if(key == node->Key())	//it should be here
	{
		return node;
	}

}
//public
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::printInorder()
{
	printInorder(root);
}
//private print in order for the tree
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::printInorder(Node<DATATYPE, KEYTYPE> *node)
{
	//Student must fill in.  Use recursive algorithm.
	//Note that this prints using an Inorder, Depth-first search
	//but you may want to do something else when "visiting" the node....
	//like moving visited data to another datastructure
	//Don't forget your base case!

	if(Root() == nullptr)
    {
	    cout << "The tree is empty!\n";
	    return;
    }
    else
    {
        if(node->Left() != nullptr) //if it's possible to go to the left
            printInorder(node->Left());

        node->Data().print();		//we are as far left as possible so we print out the value

        if(node->Right() != nullptr)    //if it's possible to go to the right
            printInorder(node->Right());
    }
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::print(ostream & out, const DATATYPE & data)
{
	out << data.number << "\t" << data.name << endl;
}
//public
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::deleteNode(KEYTYPE key)
{
	setRoot(deleteNode(Root(), key));
}

//deleteNode (Private)
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::deleteNode(Node<DATATYPE, KEYTYPE> * aRoot,KEYTYPE value)
{

	/* Given a binary search tree and a key, this function deletes the key
	and returns the new root */

	// base case
	if (aRoot == nullptr) return aRoot;

	// If the key to be deleted is smaller than the aRoot's key,
	// then it lies in left subtree
	string key = aRoot->Key();
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    key.erase(remove(key.begin(), key.end(), ' '), key.end());

	if (value < key)
		aRoot->setLeft(deleteNode(aRoot->Left(), value));

		// If the key to be deleted is greater than the root's key,
		// then it lies in right subtree
	else if (value > key)
		aRoot->setRight(deleteNode(aRoot->Right(), value));

		// if key is same as root's key, then This is the node
		// to be deleted

	else
	{
		// node with only one child or no child
		if (aRoot->Left() == nullptr)
		{
			Node<DATATYPE, KEYTYPE> *temp = aRoot->Right();
			delete aRoot;
			return temp;
		}
		else if (aRoot->Right() == nullptr)
		{
			Node<DATATYPE, KEYTYPE> *temp = aRoot->Left();
			delete aRoot;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		Node<DATATYPE, KEYTYPE> * temp = min(aRoot->Right());

		// Copy the inorder successor's content to this node
		aRoot->setKey(temp->Key());
		aRoot->setData(temp->Data());

		// Delete the inorder successor
		aRoot->setRight(deleteNode(aRoot->Right(), temp->Key()));
	}
	return aRoot;
}


// Find the node with min key
// Traverse the left sub-BSTree recursively
// till left sub-BSTree is empty to get min
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::min(Node<DATATYPE, KEYTYPE> * node)
{
	Node<DATATYPE, KEYTYPE> * current = node;

	/* loop down to find the leftmost leaf */
	while (current->Left() != nullptr)
		current = current->Left();

	return current;
}

// Find the node with max key
// Traverse the right sub-BSTree recursively
// till right sub-BSTree is empty to get max
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::max(Node<DATATYPE, KEYTYPE> * node)
{
	Node<DATATYPE, KEYTYPE> * tempNode = node;
	if (node == nullptr)
		tempNode = nullptr;
	else if (node->Right())
		tempNode = max(node->Right());
	else
		tempNode = node;

	return tempNode;
}
//opens the file actor-actress and reads the file into the tree
template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::readActors()
{
	//remember to set the hasData variable of that tree to true at the end
	cout << "I will begin to read in the actors!\n";
    /* Actors is:
     * Year
     * Award
     * Winner
     * Name
     * Film
     */
    string fileData;
    int winner;
    Actors actor;
    string actorName, year;
    ifstream infile;
    infile.open("actor-actress.csv");
    if(infile.is_open())
    {
        getline(infile, fileData);  //first line is a description, we ignore it
        while(!infile.eof())
        {
            getline(infile, fileData, ',');     //this is year(string)
            if(fileData.size() == 0)            //I need this condition because the file ends with an empty line
                break;
            //year = stoi(fileData);              //http://www.cplusplus.com/reference/string/stoi/
            actor.setYear(fileData);
            getline(infile, fileData, ',');     //this is award(string)
            actor.setAward(fileData);
            getline(infile, fileData, ',');     //this is winner(int)
            winner = stoi(fileData);
            actor.setWinner(winner);
            getline(infile, fileData, ',');     //this is name(string)
            //I have a condition for names, if it starts with " then there will be a commas seperating their name and prefix
            if(fileData[0] == 34)       //34 is the ascii of "
            {
                actorName = fileData;
                getline(infile, fileData, ',');
                actorName += fileData;
                //actor.name now looks like "name name Jr." I want to get rid of the "
                fileData = actorName;
                fileData.erase(remove(fileData.begin(), fileData.end(), '"'), fileData.end());
                //removed the quote from the string
                actor.setName(fileData);
            }
            else
                actor.setName(fileData);
            getline(infile, fileData);     //this is film(string), there is no comma at the end so we don't stop at comma
            actor.setFilm(fileData);

            addNode(actor.getName(), actor); //key, datatype

        }
    }
    else
    {
        cout << "Oops something went wrong and I coulnd't open the actor file!\n";
    }
    infile.close();
	hasData = true;	//the BST for actors has been filled
}

//opens the file for movies and reads the file into the tree
template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::readMovies() {
	//remember to set the hasData variable of that tree to true at the end
	cout << "I will begin to read in the movies!\n";
    /* Movies is:
     * Name(string)
     * Year(int)
     * Nominations(int)
     * Rating(int)
     * Duration(int)
     * Genre1(string)
     * Genre2(string)
     * Release(string)
     * Metacritic(int)
     * Synopsis(string)
     */
    int nominations, metacritic;
    string fileData, year, duration, rating;
    Movies movie;
    ifstream infile;
    infile.open("pictures.csv");
    if(infile.is_open())
    {
        getline(infile, fileData);
        while(!infile.eof())
        {
            getline(infile, fileData, ',');     //this is name(string)
            if(fileData.size() == 0)            //I need this condition because the file ends with an empty line
                break;                          //this means we're starting empty and the file is over, if this was in the middle
                                                //that would mean an empty field
            //In movies, there is a space in front of all the names, I need to get rid of this space
            fileData.erase(fileData.begin());
            movie.setName(fileData);
            getline(infile, fileData, ',');     //this is year(string)
            if(fileData.size() == 0 || fileData == "-")            //empty fields are either empty or marked with a dash
            {
                movie.setYear("0");
            }
            else    //not an empty field and we turn string into int
            {
                //year = stoi(fileData);
                movie.setYear(fileData);
            }

            getline(infile, fileData, ',');     //this is nomination(int)
            if(fileData.size() == 0 || fileData == "-")
            {
                movie.setNomination(0);
            }
            else
            {
                nominations = stoi(fileData);
                movie.setNomination(nominations);
            }

            getline(infile, fileData, ',');     //this is rating(string)
            if(fileData.size() == 0 || fileData == "-")
            {
                movie.setRating("0");
            }
            else
            {
                //rating = stoi(fileData);
                movie.setRating(fileData);
            }

            getline(infile, fileData, ',');     //this is duration(string)
            if(fileData.size() == 0 || fileData == "-")
            {
                movie.setDuration("0");
            }
            else
            {
                //duration = stoi(fileData);
                movie.setDuration(fileData);
            }

            getline(infile, fileData, ',');     //this is genre1(string)
            if(fileData.size() == 0)    //don't need the dash since i'm not converting from string to int
                movie.setGenre1("unknown");
            else
                movie.setGenre1(fileData);

            getline(infile, fileData, ',');     //this is genre2(string)
            if(fileData.size() == 0)
                movie.setGenre2("unknown");
            else
                movie.setGenre2(fileData);

            getline(infile, fileData, ',');     //this is release(string)
            if(fileData.size() == 0)
                movie.setRelease("unknown");
            else
                movie.setRelease(fileData);

            getline(infile, fileData, ',');     //this is metacritic(int)
            if(fileData.size() == 0 || fileData == "-")
            {
                movie.setMetacritic(0);
            }
            else
            {
                metacritic = stoi(fileData);
                movie.setMetacritic(metacritic);
            }

            getline(infile, fileData);     //this is synopsis(string)
            if(fileData.size() == 0)
                movie.setSynopsis("unknown");
            else
                movie.setSynopsis(fileData);

            addNode(movie.getName(), movie);
        }
    }
    else
    {
        cout << "Oops something went wrong and I coulnd't open the actor file!\n";
    }
    infile.close();
	hasData = true;	//the BST for movies has been filled
}

//public
template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::partialSearch(string key, vector<Node<DATATYPE, KEYTYPE>> &vec)
{
    partialSearch(key, root, vec);
}
//private
template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::partialSearch(string key, Node<DATATYPE, KEYTYPE> *node, vector<Node<DATATYPE, KEYTYPE> > &vec)
{
    if(Root() == nullptr)
    {
        cout << "The tree is empty!\n";
        return;
    }
    else
    {
        if(node->Left() != nullptr) //if it's possible to go to the left
            partialSearch(key, node->Left(), vec);

        string actorName = node->Data().getName();		//we are as far left as possible so we print out the value
        transform(actorName.begin(), actorName.end(), actorName.begin(), ::tolower);
        actorName.erase(remove(actorName.begin(), actorName.end(), ' '), actorName.end());
        //actorname is now lowercase and no spaces
        size_t found = actorName.find(key);     //http://www.cplusplus.com/reference/string/string/find/

        if(found != string::npos)
            vec.push_back(*node);

        if(node->Right() != nullptr)    //if it's possible to go to the right
            partialSearch(key, node->Right(), vec);
    }
}

//public
template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::searchAndModifyAct(string key, string film, string year)
{
    searchAndModifyAct(key, film, year, root);
}

//private
//this assumes the key is a string (the name)
template<typename DATATYPE, typename KEYTYPE>
bool BSTree<DATATYPE, KEYTYPE>::searchAndModifyAct(string key, string film, string year, Node<DATATYPE, KEYTYPE> *node)
{
    if(node == nullptr)
    {
        cout << "No matches were found!\n";
        return false;
    }

    string nodeKey = node->Key();
    transform(nodeKey.begin(), nodeKey.end(), nodeKey.begin(), ::tolower);
    nodeKey.erase(remove(nodeKey.begin(), nodeKey.end(), ' '), nodeKey.end());

    if(key < nodeKey)	//go left
    {
        searchAndModifyAct(key, film, year, node->Left());
    }
    else if(key > nodeKey)	//go right
    {
        searchAndModifyAct(key, film, year, node->Right());
    }
    else if(key == nodeKey)	//it should be here
    {
        Actors tempObj;
        string nodeFilm = node->Data().getFilm(), junkString;
        transform(nodeFilm.begin(), nodeFilm.end(), nodeFilm.begin(), ::tolower);
        nodeFilm.erase(remove(nodeFilm.begin(), nodeFilm.end(), ' '), nodeFilm.end());
        //now we check if the node is exactly a match instead of just the key being a match
        //we already know the name matches, now check if the film and year matches as well
        if(film == nodeFilm)
        {
            if(year == node->Data().getYear())
            {
                //we have found the node, time to edit
                //Go through each field and ask if the user wants to edit this field
                int userMenuOption, actorWinner;
                string actorName, actorAward, actorFilm, actorYear;
                //cin.ignore();
                cout << "Would you like to edit the name?\n0)No\n1)Yes\n";
                userMenuOption = intCheckWinner();  //reusing this function, can only be 0 or 1
                cin.ignore();
                //getline(cin, junkString);
                //userMenuOption = stoi(junkString);

                //if user wants to edit
                if(userMenuOption == 1)
                {
                    //ask for info
                    cout << "\nEnter new name: ";
                    getline(cin, actorName);
                    actorName[0] = toupper(actorName[0]);
                    tempObj.setName(actorName); //saving new name in data
                    //if we have a new name, we need a new key(assuming the tree is sorted by name)
                } else{
                    tempObj.setName(node->Data().getName());    //else we keep the same name
                }
                //cin.ignore();
                cout << "\nWould you like to edit the year?\n0)No\n1)Yes\n";
                userMenuOption = intCheckWinner();
                cin.ignore();
                //getline(cin, junkString);
                //userMenuOption = stoi(junkString);
                if(userMenuOption == 1)
                {
                    //cin.ignore();
                    cout << "\nEnter new year: ";
                    getline(cin, actorYear);
                    //actorYear = stoi(junkString);
                    //cin >> actorYear;
                    //cin.ignore(255, '\n');
                    tempObj.setYear(actorYear);
                } else{
                    tempObj.setYear(node->Data().getYear());
                }
                cout << "\nWould you like to edit the award?\n0)No\n1)Yes\n";
                userMenuOption = intCheckWinner();
                cin.ignore();
                //getline(cin, junkString);
                //userMenuOption = stoi(junkString);
                if(userMenuOption == 1)
                {
                    //cin.ignore();
                    cout << "\nEnter new award: ";
                    getline(cin, actorAward);
                    tempObj.setAward(actorAward);
                } else{
                    tempObj.setAward(node->Data().getAward());
                }
                cout << "\nWould you like to edit the winner?\n0)No\n1)Yes\n";
                userMenuOption = intCheckWinner();
                cin.ignore();
                //getline(cin, junkString);
                //userMenuOption = stoi(junkString);
                if(userMenuOption == 1)
                {
                    cout << "\nEnter new winner(0 = no, 1 = yes): ";
                    actorWinner = intCheckWinner();
                    cin.ignore();
                    //getline(cin, junkString);
                    //actorWinner = stoi(junkString);
                    tempObj.setWinner(actorWinner);
                } else{
                    tempObj.setWinner(node->Data().getWinner());
                }
                cout << "\nWould you like to edit the film?\n0)No\n1)Yes\n";
                userMenuOption = intCheckWinner();
                cin.ignore();
                //getline(cin, junkString);
                //userMenuOption = stoi(junkString);
                if(userMenuOption == 1)
                {
                    cout << "\nEnter new film: ";
                    getline(cin, actorFilm);
                    tempObj.setFilm(actorFilm);
                } else{
                    tempObj.setFilm(node->Data().getFilm());
                }
                //updating the node
                //node->setKey(actorName);
                //node->setData(tempObj);
                //deleteNode(node->Data().getName());
                searchAndDeleteAct(node->Data().getName(), node->Data().getFilm(), node->Data().getYear());
                //Node has been deleted

                addNode(tempObj.getName(), tempObj);
                //New node has been added, the reason for deletion is so that the node can reorder itself

                return true;
            }
            else    //else year didn't match
            {
                if(node->Right() != nullptr)
                    searchAndModifyAct(key, film, year, node->Right());
                else    //we reached the end and there was no match
                {
                    cout << "There was no match!\n";
                    return false;
                }
            }
        }
        else    //else film didn't match, go right, since the name matches, it could not be on the left due to how we order a tree
        {
            if(node->Right() != nullptr)
                searchAndModifyAct(key, film, year, node->Right());
            else    //we reached the end and there was no match
            {
                cout << "There was no match!\n";
                return false;
            }
        }
    }
}

template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::searchAndDeleteAct(string key, string film, string year)
{
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    key.erase(remove(key.begin(), key.end(), ' '), key.end());

    transform(film.begin(), film.end(), film.begin(), ::tolower);
    film.erase(remove(film.begin(), film.end(), ' '), film.end());

    //finished converting the key and film to lowercase with no spaces

    setRoot(deleteNodeAct(Root(), key, film, year));
}

template<typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> *BSTree<DATATYPE, KEYTYPE>::deleteNodeAct(Node<DATATYPE, KEYTYPE> *aRoot, KEYTYPE value, string film, string year)
{
    /* Given a binary search tree and a key, this function deletes the key
	and returns the new root */

    // base case
    if (aRoot == nullptr) return aRoot;

    // If the key to be deleted is smaller than the aRoot's key,
    // then it lies in left subtree

    string nodeKey = aRoot->Key();
    transform(nodeKey.begin(), nodeKey.end(), nodeKey.begin(), ::tolower);
    nodeKey.erase(remove(nodeKey.begin(), nodeKey.end(), ' '), nodeKey.end());

    if (value < nodeKey)
        aRoot->setLeft(deleteNodeAct(aRoot->Left(), value, film, year));

        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
    else if (value > nodeKey)
        aRoot->setRight(deleteNodeAct(aRoot->Right(), value, film, year));

        // if key is same as root's key, then This is the node
        // to be deleted
    string nodeFilm = aRoot->Data().getFilm();
    transform(nodeFilm.begin(), nodeFilm.end(), nodeFilm.begin(), ::tolower);
    nodeFilm.erase(remove(nodeFilm.begin(), nodeFilm.end(), ' '), nodeFilm.end());

    if(film == nodeFilm)    //match of the key has been found, need to see if it's the correct node
    {
        if(year == aRoot->Data().getYear())
        {   //correct match has been found
            // node with only one child or no child
            if (aRoot->Left() == nullptr)
            {
                Node<DATATYPE, KEYTYPE> *temp = aRoot->Right();
                delete aRoot;
                //cout << "Node found and deleted!\n";
                return temp;
            }
            else if (aRoot->Right() == nullptr)
            {
                Node<DATATYPE, KEYTYPE> *temp = aRoot->Left();
                //Node<DATATYPE, KEYTYPE> *parentTemp = aRoot->Parent();
                delete aRoot;
                //cout << "Node found and deleted!\n";
                //parentTemp->setRight(temp);
                return temp;
            }

            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            Node<DATATYPE, KEYTYPE> * temp = min(aRoot->Right());

            // Copy the inorder successor's content to this node
            aRoot->setKey(temp->Key());
            aRoot->setData(temp->Data());

            // Delete the inorder successor
            aRoot->setRight(deleteNodeAct(aRoot->Right(), temp->Key(), film, year));
        }//end of correct match
        else
        {
            if(aRoot->Right() == nullptr)
            {
                //cout << "No node matches that name!\n";
                return nullptr;
            }

            else
                aRoot->setRight(deleteNodeAct(aRoot->Right(), value, film, year));
        }
    }//end of else if correct match
    return aRoot;
}

template<typename DATATYPE, typename KEYTYPE>
int BSTree<DATATYPE, KEYTYPE>::sortByField(int choice, BSTree<DATATYPE, KEYTYPE> *currentTree)
{
    //choice = 0, sort by name
    if(choice == sortedBy)
    {
        cout << "Tree is already sorted by that field!\n";
        return 0;
    }
    else
    {
        if(choice <= 2)   //dealing with an actor tree
        {
            BSTree<Actors, std::string> *newSortedTree = new BSTree<Actors, std::string>();
            sortByField(root, choice, newSortedTree);
            //new tree has been made and sorted
            //free the root and assign it to the new sorted tree
            //freeNode(root);
            freeNode(root);
            root = newSortedTree->Root();
            sortedBy = choice;      //setting the variable that says what the tree is sorted by
            cout << "Tree has been sorted!\n";
            return 1;
        }
    }
}

//private
template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::sortByField(Node<DATATYPE, KEYTYPE> *node, int choice, BSTree<DATATYPE, KEYTYPE> *newSortedTree)
{
    if(Root() == nullptr)
    {
        cout << "The tree is empty!\n";
        return;
    }

    else
    {
        if(node->Left() != nullptr) //if it's possible to go to the left
            sortByField(node->Left(), choice, newSortedTree);

        //here we want to add things to the new tree
        if(choice == 0) //sort by name
        {
            Actors newNode;
            newNode.setName(node->Data().getName());
            newNode.setFilm(node->Data().getFilm());
            newNode.setWinner(node->Data().getWinner());
            newNode.setAward(node->Data().getAward());
            newNode.setYear(node->Data().getYear());
            newSortedTree->addNode(node->Data().getName(), newNode);
            //DO NOT add the node since it has other nodes attached to it, create a new node and add the new one
        }
        if(choice == 1) //sort by film
        {
            Actors newNode;
            newNode.setName(node->Data().getName());
            newNode.setFilm(node->Data().getFilm());
            newNode.setWinner(node->Data().getWinner());
            newNode.setAward(node->Data().getAward());
            newNode.setYear(node->Data().getYear());
            newSortedTree->addNode(node->Data().getFilm(), newNode);
        }
        if(choice == 2) //sort by year
        {
            Actors newNode;
            newNode.setName(node->Data().getName());
            newNode.setFilm(node->Data().getFilm());
            newNode.setWinner(node->Data().getWinner());
            newNode.setAward(node->Data().getAward());
            newNode.setYear(node->Data().getYear());
            newSortedTree->addNode(node->Data().getYear(), newNode);
        }
        /*if(choice == 3) //rating
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getRating(), newNodeMov);
        }
        if(choice == 4) //amount of nominations
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getNomination(), newNodeMov);
        }
        if(choice == 5) //duration
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getDuration(), newNodeMov);
        }
        if(choice == 6) //metacritic
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getMetacritic(), newNodeMov);
        }
        if(choice == 7) //name again
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getName(), newNodeMov);
        }
        if(choice == 8) //year again
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getYear(), newNodeMov);
        }
        */
        if(node->Right() != nullptr)    //if it's possible to go to the right
            sortByField(node->Right(), choice, newSortedTree);
    }
}

//public
template<typename DATATYPE, typename KEYTYPE>
Node<DATATYPE,KEYTYPE> *BSTree<DATATYPE, KEYTYPE>::completeSearchAct(KEYTYPE key, string film, string year)
{
    string nodeFilm = film;
    string nodeName = key;
    transform(nodeFilm.begin(), nodeFilm.end(), nodeFilm.begin(), ::tolower);
    nodeFilm.erase(remove(nodeFilm.begin(), nodeFilm.end(), ' '), nodeFilm.end());
    //film has been lowercased and any space has been erased
    transform(nodeName.begin(), nodeName.end(), nodeName.begin(), ::tolower);
    nodeName.erase(remove(nodeName.begin(), nodeName.end(), ' '), nodeName.end());
    //same with the name
    completeSearchAct(root, nodeName, nodeFilm, year);
}

template<typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> *BSTree<DATATYPE, KEYTYPE>::completeSearchAct(Node<DATATYPE, KEYTYPE> *node, KEYTYPE key, string film, string year)
{
    if(node == nullptr)
    {
        cout << "No matches were found!\n";
        return nullptr;
    }

    string nodeKey = node->Key();
    transform(nodeKey.begin(), nodeKey.end(), nodeKey.begin(), ::tolower);
    nodeKey.erase(remove(nodeKey.begin(), nodeKey.end(), ' '), nodeKey.end());
    //key has been lowercased and removed any spaces

    if(key < nodeKey)
        completeSearchAct(node->Left(), key, film, year);
    else if(key > nodeKey)
        completeSearchAct(node->Right(), key, film, year);
    else if(key == nodeKey)
    {
        //key matches, check if other fields matches
        string nodeFilm = film;
        transform(nodeFilm.begin(), nodeFilm.end(), nodeFilm.begin(), ::tolower);
        nodeFilm.erase(remove(nodeFilm.begin(), nodeFilm.end(), ' '), nodeFilm.end());
        //film has been converted to lowercase and removed spaces
        if(film == nodeFilm)
        {
            //no conversation needed for year
            if(year == node->Data().getYear())
            {
                //perfect match
                node->Data().print();
                return node;
            }
            else
            {
                if(node->Right() != nullptr)
                    completeSearchAct(node->Right(), key, film, year);
                else
                {
                    cout << "No matches were found!\n";
                    return nullptr;
                }

            }//else go right if possible
        }
        //else go right if possible
        else
        {
            if(node->Right() != nullptr)
                completeSearchAct(node->Right(), key, film, year);
            else
            {
                cout << "No matches were found!\n";
                return nullptr;
            }
        }
    }//end of key matches
}

//public
template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::searchAndModifyMov(string key, string year) {
    searchAndModifyMov(key, year, root);
}

template<typename DATATYPE, typename KEYTYPE>
bool BSTree<DATATYPE, KEYTYPE>::searchAndModifyMov(string key, string year, Node<DATATYPE, KEYTYPE> *node)
{
    if(node == nullptr)
    {
        cout << "No matches were found!\n";
        return false;
    }

    string nodeKey = node->Key();
    transform(nodeKey.begin(), nodeKey.end(), nodeKey.begin(), ::tolower);
    nodeKey.erase(remove(nodeKey.begin(), nodeKey.end(), ' '), nodeKey.end());

    if(key < nodeKey)	//go left
    {
        searchAndModifyMov(key, year, node->Left());
    }
    else if(key > nodeKey)	//go right
    {
        searchAndModifyMov(key, year, node->Right());
    }
    else if(key == nodeKey)	//it should be here
    {
        //now we check if the node is exactly a match instead of just the key being a match
        //we already know the name matches, now check if the year matches
        if(year == node->Data().getYear()) {
            //we have found the node, time to edit
            //Go through each field and ask if the user wants to edit this field
            Movies tempObj;
            int userMenuOption, movieNomination, movieMetacritic;
            string movieYear, movieName, movieGenre1, movieGenre2, movieRelease, movieSynopsis, movieDuration, junkString, movieRating;
            //cin.ignore();
            cout << "Would you like to edit the name?\n0)No\n1)Yes\n";
            userMenuOption = intCheckWinner();  //reusing this function, can only be 0 or 1
            cin.ignore();
            //getline(cin, junkString);
            //userMenuOption = stoi(junkString);
            //cin >> userMenuOption;
            //if user wants to edit
            if (userMenuOption == 1) {
                //ask for info
                cout << "\nEnter new name: ";
                getline(cin, movieName);
                movieName[0] = toupper(movieName[0]);
                tempObj.setName(movieName); //saving new name in data
                //if we have a new name, we need a new key(assuming the tree is sorted by name)
            } else {
                tempObj.setName(node->Data().getName());    //else we keep the same name
            }
            cout << "\nWould you like to edit the year?\n0)No\n1)Yes\n";
            userMenuOption = intCheckWinner();
            cin.ignore();
            //getline(cin, junkString);
            //userMenuOption = stoi(junkString);
            if (userMenuOption == 1) {
                //cin.ignore();
                cout << "\nEnter new year: ";
                getline(cin, movieYear);
                tempObj.setYear(movieYear);
            } else {
                tempObj.setYear(node->Data().getYear());
            }
            cout << "\nWould you like to edit the amount of nominations?\n0)No\n1)Yes\n";
            userMenuOption = intCheckWinner();
            cin.ignore();
            //getline(cin, junkString);
            //userMenuOption = stoi(junkString);
            if (userMenuOption == 1) {
                //cin.ignore();
                cout << "\nEnter new amount of nominations(int only): ";
                movieNomination = intCheck();
                cin.ignore();
                //getline(cin, junkString);
                //movieNomination = stoi(junkString);
                tempObj.setNomination(movieNomination);
            } else {
                tempObj.setNomination(node->Data().getNomination());
            }
            cout << "\nWould you like to edit the rating?\n0)No\n1)Yes\n";
            userMenuOption = intCheckWinner();
            cin.ignore();
            //getline(cin, junkString);
            //userMenuOption = stoi(junkString);
            if (userMenuOption == 1) {
                cout << "\nEnter new rating: ";
                getline(cin, movieRating);
                tempObj.setRating(movieRating);
            } else {
                tempObj.setRating(node->Data().getRating());
            }
            cout << "\nWould you like to edit the duration?\n0)No\n1)Yes\n";
            userMenuOption = intCheckWinner();
            cin.ignore();
            //getline(cin, junkString);
            //userMenuOption = stoi(junkString);
            if (userMenuOption == 1) {
                //cin.ignore();
                cout << "\nEnter new duration: ";
                getline(cin, movieDuration);
                tempObj.setDuration(movieDuration);
            } else {
                tempObj.setDuration(node->Data().getDuration());
            }
            cout << "\nWould you like to edit the primary genre?\n0)No\n1)Yes\n";
            userMenuOption = intCheckWinner();
            cin.ignore();
            //getline(cin, junkString);
            //userMenuOption = stoi(junkString);
            if(userMenuOption == 1)
            {
                cout << "\nEnter new primary genre: ";
                getline(cin, movieGenre1);
                tempObj.setGenre1(movieGenre1);
            } else{
                tempObj.setGenre1(node->Data().getGenre1());
            }
            cout << "\nWould you like to edit the secondary genre?\n0)No\n1)Yes\n";
            userMenuOption = intCheckWinner();
            cin.ignore();
            //getline(cin, junkString);
            //userMenuOption = stoi(junkString);
            if(userMenuOption == 1)
            {
                cout << "\nEnter new secondary genre: ";
                getline(cin, movieGenre2);
                tempObj.setGenre2(movieGenre2);
            } else{
                tempObj.setGenre2(node->Data().getGenre2());
            }
            cout << "\nWould you like to edit the release month?\n0)No\n1)Yes\n";
            userMenuOption = intCheckWinner();
            cin.ignore();
            //getline(cin, junkString);
            //userMenuOption = stoi(junkString);
            if(userMenuOption == 1)
            {
                cout << "\nEnter new release month: ";
                getline(cin, movieRelease);
                tempObj.setRelease(movieRelease);
            }
            else{
                tempObj.setRelease(node->Data().getRelease());
            }
            cout << "\nWould you like to edit the metacritic?\n0)No\n1)Yes\n";
            userMenuOption = intCheckWinner();
            cin.ignore();
            //getline(cin, junkString);
            //userMenuOption = stoi(junkString);
            if(userMenuOption == 1)
            {
                cout << "\nEnter new metacritic: ";
                movieMetacritic = intCheck();
                cin.ignore();
                //getline(cin, junkString);
                //movieMetacritic = stoi(junkString);
                tempObj.setMetacritic(movieMetacritic);
            }
            else{
                tempObj.setMetacritic(node->Data().getMetacritic());
            }
            cout << "\nWould you like to edit the synopsis?\n0)No\n1)Yes\n";
            userMenuOption = intCheckWinner();
            cin.ignore();
            //getline(cin, junkString);
            //userMenuOption = stoi(junkString);
            if(userMenuOption == 1)
            {
                cout << "\nEnter new synopsis: ";
                getline(cin, movieSynopsis);
                tempObj.setSynopsis(movieSynopsis);
            }
            else{
                tempObj.setSynopsis(node->Data().getSynopsis());
            }
            //updating the node
            deleteNode(node->Data().getName()); //name is unique in movies so I can use deleteNode
            //Node has been deleted
            addNode(tempObj.getName(), tempObj);
            //New node has been added, the reason for deletion is so that the node can reorder itself
            return true;
        }//end of if year matches
        else    //else year didn't match
        {
            if(node->Right() != nullptr)
                searchAndModifyMov(key, year, node->Right());
            else    //we reached the end and there was no match
            {
                cout << "There was no match!\n";
                return false;
            }
        }
    }
    else    //else film didn't match, go right, since the name matches, it could not be on the left due to how we order a tree
    {
        if(node->Right() != nullptr)
            searchAndModifyMov(key, year, node->Right());
        else    //we reached the end and there was no match
        {
            cout << "There was no match!\n";
            return false;
        }
    }
}

//public
template<typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> *BSTree<DATATYPE, KEYTYPE>::completeSearchMov(KEYTYPE key)
{
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    key.erase(remove(key.begin(), key.end(), ' '), key.end());
    completeSearchMov(root, key);
    return nullptr;
}

template<typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> *BSTree<DATATYPE, KEYTYPE>::completeSearchMov(Node<DATATYPE, KEYTYPE> *node, KEYTYPE key)
{
    if(node == nullptr)
    {
        cout << "No matches were found!\n";
        return nullptr;
    }

    string nodeKey = node->Key();
    transform(nodeKey.begin(), nodeKey.end(), nodeKey.begin(), ::tolower);
    nodeKey.erase(remove(nodeKey.begin(), nodeKey.end(), ' '), nodeKey.end());
    //key has been lowercased and removed any spaces

    if(key < nodeKey)
        completeSearchMov(node->Left(), key);
    else if(key > nodeKey)
        completeSearchMov(node->Right(), key);
    else if(key == nodeKey) {
        //key matches, key is unique for movie
        node->Data().print();
        return node;
    }
}
//public
template<typename DATATYPE, typename KEYTYPE>
int BSTree<DATATYPE, KEYTYPE>::sortByFieldMov(int choice, BSTree<DATATYPE, KEYTYPE> *currentTree) {
    if(choice == sortedBy)
    {
        cout << "Tree is already by that field sorted!\n";
        return 0;
    }
    else
    {
        if(choice >= 3)   //dealing with an movie tree
        {
            BSTree<Movies, std::string> *newSortedTreeMov = new BSTree <Movies, std::string>();
            sortByFieldMov(root, choice, newSortedTreeMov);
            freeNode(root);
            root = newSortedTreeMov->Root();
            sortedBy = choice;
            cout << "Tree has been sorted!\n";
            return 1;
        }
    }
}

template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::sortByFieldMov(Node<DATATYPE, KEYTYPE> *node, int choice, BSTree<DATATYPE, KEYTYPE> *newSortedTree)
{
    if(Root() == nullptr)
    {
        cout << "The tree is empty!\n";
        return;
    }

    else
    {
        if(node->Left() != nullptr) //if it's possible to go to the left
            sortByFieldMov(node->Left(), choice, newSortedTree);

        //here we want to add things to the new tree
        if(choice == 3) //name
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getName(), newNodeMov);
        }
        if(choice == 4) //year
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getYear(), newNodeMov);
        }
        if(choice == 5) //duration
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getDuration(), newNodeMov);
        }
        if(choice == 6) //rating
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getRating(), newNodeMov);
        }
        /*if(choice == 7) //name again
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getName(), newNodeMov);
        }
        if(choice == 8) //year again
        {
            Movies newNodeMov;
            newNodeMov.setYear(node->Data().getYear());
            newNodeMov.setName(node->Data().getName());
            newNodeMov.setSynopsis(node->Data().getSynopsis());
            newNodeMov.setMetacritic(node->Data().getMetacritic());
            newNodeMov.setRelease(node->Data().getRelease());
            newNodeMov.setGenre2(node->Data().getGenre2());
            newNodeMov.setGenre1(node->Data().getGenre1());
            newNodeMov.setDuration(node->Data().getDuration());
            newNodeMov.setRating(node->Data().getRating());
            newNodeMov.setNomination(node->Data().getNomination());
            newSortedTree->addNode(node->Data().getYear(), newNodeMov);
        }
        */
        if(node->Right() != nullptr)    //if it's possible to go to the right
            sortByFieldMov(node->Right(), choice, newSortedTree);
    }
}

//public
template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::writeToFileAct()
{
    ofstream file;
    file.open("actorFile.csv");
    string actorLayout = "Year,Award,Winner,Name,Film\n";
    file << actorLayout;
    writeToFileAct(root, file);
}

template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::writeToFileAct(Node<DATATYPE, KEYTYPE> *node, ofstream &file)
{
    if(Root() == nullptr)
    {
        cout << "The tree is empty!\n";
        return;
    }

    else
    {
        if(node->Left() != nullptr) //if it's possible to go to the left
            writeToFileAct(node->Left(), file);

        //here we want to write to the file
        string line = node->Data().lineForFile();
        file << line;

        if(node->Right() != nullptr)    //if it's possible to go to the right
            writeToFileAct(node->Right(), file);
    }
}

template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::writeToFileMov()
{
    ofstream file;
    file.open("movieFile.csv");
    string actorLayout = "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis\n";
    file << actorLayout;
    writeToFileMov(root, file);
}

template<typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::writeToFileMov(Node<DATATYPE, KEYTYPE> *node, ofstream &file)
{
    if(Root() == nullptr)
    {
        cout << "The tree is empty!\n";
        return;
    }

    else
    {
        if(node->Left() != nullptr) //if it's possible to go to the left
            writeToFileMov(node->Left(), file);

        //here we want to write to the file
        string line = node->Data().lineForFile();
        file << line;

        if(node->Right() != nullptr)    //if it's possible to go to the right
            writeToFileMov(node->Right(), file);
    }
}

#endif  //BST
