/*
 * Anthony Dupont
 * Data Structure
 * Final Project
 */

#include "Functions.h"
#include "BSTree.hpp"
#include "Node.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>    //transform and erase
#include <time.h>       //nano sleep
//#include <windows.h>    //sleep doesn't work on csegrid, usleep doesn't work either


using std::cout;
using std::string;
using std::getline;

void mainMenu(BSTree<Actors, std::string> *actors, BSTree<Movies, std::string> *movies) {
    bool mainMenuLoop = true, match = false;
    int userMenuOption;
    string actorName, actorFilm, actorAward, junkString, actorYear;
    int actorWinner;
    Actors actorToBeAdded, tempActStruct;
    string movieYear, movieName, movieGenre1, movieGenre2, movieRelease, movieSynopsis, movieDuration, movieRating;
    int movieNomination, movieMetacritic;
    Node<Actors, string> *tempNodeAct;    //tempNode is a node Datatype = struct of actors, keytype = string
    Node<Movies, string> *tempNodeMov;
    Movies movieToBeAdded;
    vector<Node<Actors, string> > vecOfActors;
    vector<Node<Movies, string> > vecOfMovies;
    timespec sleepTime;     //https://stackoverflow.com/questions/3072912/boostthis-threadsleep-vs-nanosleep
    timespec returnTime;
    sleepTime.tv_sec = 1;
    sleepTime.tv_nsec = 1000;

    while(mainMenuLoop == true)
    {
        cout << "Welcome to the main menu!\n"
            << "1)Actor Database\n"
            << "2)Movies Database\n"
            << "3)Exit\n"
            << "Choose an option: ";
        userMenuOption = intCheck();
        //I will use if/else statements for a short menu like this one, I will use a case for when there is a lot more option
        //I don't want a nested switch case, I believe I was told it does not work well
        if(userMenuOption == 1) //actors
        {
            bool secondMenuLoop = true;
            while(secondMenuLoop == true)
            {
                cout << "Actors Database: \n";
                cout << "\t1)Add Record\n"
                     << "\t2)Print tree\n"
                     << "\t3)Search and Modify record\n"
                     << "\t4)Complete Search\n"
                     << "\t5)Sort by Field\n"
                     << "\t6)Partial Search\n"
                     << "\t7)Search and Delete record\n"
                     << "\t8)Write Current Tree to a File\n"
                     << "\t9)Go Back To Previous Menu...\n"
                     << "\t10)Exit\n"
                     << "\tChoose an option: ";
                userMenuOption = intCheck();
                switch (userMenuOption)
                {
                    case 1:
                        //add record
                        //I must pass in a key(what the tree is sorted on) and data (actor object)
                        cin.ignore();
                        cout << "What is the name of this actor?\n";
                        getline(cin, actorName);    //getting actor name
                        transform(actorName.begin(), actorName.end(), actorName.begin(), ::tolower);    //setting the name to lowercase
                        actorName[0] = toupper(actorName[0]);   //making the first letter uppcase
                        //actor name is now lowercased except for the first letter to match how the names are stored in the tree
                        actorToBeAdded.setName(actorName);  //setting the actor name of the object that will be added to the tree
                        cout << "What is the film this actor is being nominated for?\n";
                        getline(cin, actorFilm);
                        transform(actorFilm.begin(), actorFilm.end(), actorFilm.begin(), ::tolower);    //setting the name to lowercase
                        actorFilm[0] = toupper(actorFilm[0]);   //making the first letter uppcase
                        actorToBeAdded.setFilm(actorFilm);
                        cout << "What is the award this actor is being given?\n";
                        getline(cin, actorAward);
                        actorToBeAdded.setAward(actorAward);
                        cout << "What is the year this actor is being nominated?\n";
                        getline(cin, actorYear);
                        actorToBeAdded.setYear(actorYear);
                        cout << "Has this actor won before? (0 = no, 1 = yes)\n";
                        actorWinner = intCheckWinner(); //need to make sure this is only a 0 or a 1
                        actorToBeAdded.setWinner(actorWinner);
                        if(actors->getSortedBy() == 0)  //name = 0
                            actors->addNode(actorName, actorToBeAdded);
                        if(actors->getSortedBy() == 1)    //film = 1
                            actors->addNode(actorFilm, actorToBeAdded);
                        if(actors->getSortedBy() == 2)  //year = 2
                            actors->addNode(actorYear, actorToBeAdded);
                        cout << "\nActor has been added to the data base!\n";
                        nanosleep(&sleepTime, &returnTime);    //sleeps for 1 second before returning to the menu
                        break;
                    case 2:
                        //Print the tree
                        actors->printInorder();
                        cout << "\nDone printing the tree!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 3:
                        //search and modify a node
                        //ask info about node
                        cin.ignore();       //needed for getline
                        cout << "To edit a node, I will need details to find the specific node\n"
                            <<"If you do not know the details, go back and partial search the node you're looking for\n";
                        cout << "I will need you to provide me with every field accurately\n"
                             <<"Name: ";
                        getline(cin, actorName);
                        transform(actorName.begin(), actorName.end(), actorName.begin(), ::tolower); //https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
                        //now it's all lowercase
                        actorName.erase(remove(actorName.begin(), actorName.end(), ' '), actorName.end());
                        //removed all spaces, reason for this is when i compare it, I removed all spaces and lowercase the name from the node so that the user can
                        //have spaces or no spaces and not worry about uppercase or lowercase when searching
                        cout << "\nFilm: ";
                        getline(cin, actorFilm);
                        transform(actorFilm.begin(), actorFilm.end(), actorFilm.begin(), ::tolower);
                        actorFilm.erase(remove(actorFilm.begin(), actorFilm.end(), ' '), actorFilm.end());
                        cout << "\nYear: ";
                        getline(cin, actorYear);
                        if(actors->getSortedBy() == 0)
                            actors->searchAndModifyAct(actorName, actorFilm, actorYear);
                        else//reason for resorting is that the actor name is always the key for search and modify function
                        {
                            cout << "I have to sort the tree by name for this search, hang on...\n";
                            actors->sortByField(0, actors);
                            actors->searchAndModifyAct(actorName, actorFilm, actorYear);
                        }
                        cout << "\nDone modifying the actor!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 4:
                        //do a complete search, ask the user for data on the name, film, and year field, then search through the tree
                        cin.ignore();   //needed because we use getline after stream operator and cin after
                        cout << "This is a complete search, I will need you to provide me with every field accurately\n"
                            <<"Name: ";
                        getline(cin, actorName);
                        cout << "\nFilm: ";
                        getline(cin, actorFilm);
                        cout << "\nYear: ";
                        getline(cin, actorYear);
                        if(actors->getSortedBy() == 0)
                            actors->completeSearchAct(actorName, actorFilm, actorYear);
                        else    //complete search for actors only works if the tree is sorted by name
                        {
                            cout << "I have to sort the tree by name for this search, hang on...\n";
                            actors->sortByField(0, actors);
                            actors->completeSearchAct(actorName, actorFilm, actorYear);
                        }
                        cout << "\nComplete search done!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 5:
                        //prompt the user for what field they would like to sort the tree by through a menu
                        //for actors, sort by name, sort by year, sort by film are the only ones that make sense
                        match = false;
                        while(match == false)
                        {
                            cout << "0)Sort by name\n1)Sort by Film\n2)Sort by Year\n";
                            cin >> userMenuOption;
                            if(cin.fail())
                            {
                                cout << "That was not an int, try again\n";
                                cin.clear();
                                cin.ignore(256, '\n');
                                match = false;
                            }
                            else if(userMenuOption == 0 || userMenuOption == 1 || userMenuOption == 2)
                                match = true;
                            else
                            {
                                cout << "That was not between 0-2, try again\n";
                                match = false;
                            }
                        }
                        actors->sortByField(userMenuOption, actors);
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 6:
                        //prompt the user for a string then use that string to search
                        cin.ignore();
                        cout << "Partial search\nPlease provide the name or part of the name of this actor: ";
                        getline(cin, actorName);
                        transform(actorName.begin(), actorName.end(), actorName.begin(), ::tolower);
                        actorName.erase(remove(actorName.begin(), actorName.end(), ' '), actorName.end());
                        //actorName is now lowercase and no spaces
                        actors->partialSearch(actorName, vecOfActors);
                        cout << "Here are all the possible matches: \n";
                        for(int i = 0; i < vecOfActors.size(); i++)
                        {
                            vecOfActors[i].Data().print();
                        }
                        if(vecOfActors.size() == 0)
                            cout << "There was no matches!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 7:
                        //prompt user for name of the node, and delete node if found
                        cin.ignore();
                        cout << "Please enter the name of the actor you want to delete:\n";
                        getline(cin, actorName);
                        transform(actorName.begin(), actorName.end(), actorName.begin(), ::tolower);
                        actorName.erase(remove(actorName.begin(), actorName.end(), ' '), actorName.end());
                        //actorName is now lowercase and no spaces
                        if(actors->getSortedBy() == 0)
                        {
                            actors->deleteNode(actorName);
                            //actors->searchAndDeleteAct(actorName, actorFilm, actorYear);
                        }

                        else
                        {
                            //the delete function only works with the name
                            cout << "I have to sort the tree by name for this search, hang on...\n";
                            actors->sortByField(0, actors);
                            actors->deleteNode(actorName);
                            //actors->searchAndDeleteAct(actorName, actorFilm, actorYear);
                        }
                        cout << "\nSearch and delete done!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 8:
                        cout << "Writing the actor tree to a file call: 'actorFile.csv'\n";
                        actors->writeToFileAct();
                        cout << "\nDone writing tree to file!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 9:
                        //go back to the previous menu
                        secondMenuLoop = false; //this is needed to break out of the loop
                        break;
                    case 10:
                        //exit
                        cout << "Exiting...\n";
                        secondMenuLoop = false;
                        mainMenuLoop = false;
                        break;
                    default:
                        //invalid option
                        cout << "Invalid option, try again\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                }//switch case
            }//while second menu loop
        }//if userMenuOption is 1
        else if(userMenuOption == 2)    //movies
        {
            bool thirdMenuLoop = true;
            while(thirdMenuLoop == true)
            {
                cout << "Movies Database: \n";
                cout << "\t1)Add record\n"
                     << "\t2)Print tree\n"
                     << "\t3)Search and Modify record\n"
                     << "\t4)Complete Search\n"
                     << "\t5)Sort by Field\n"
                     << "\t6)Partial Search\n"
                     << "\t7)Search and Delete record\n"
                     << "\t8)Write Current Tree to a File\n"
                     << "\t9)Go Back To Previous Menu...\n"
                     << "\t10)Exit\n"
                     << "\tChoose an option: ";
                userMenuOption = intCheck();
                switch (userMenuOption)
                {
                    case 1:
                        //add record
                        //I must pass in a key(what the tree is sorted on) and data (actor object)
                        cin.ignore();
                        cout << "What is the name of this Movie?\n";
                        getline(cin, movieName);
                        transform(movieName.begin(), movieName.end(), movieName.begin(), ::tolower);
                        movieName[0] = toupper(movieName[0]);
                        //movie name now matches how the names in the tree is stored
                        movieToBeAdded.setName(movieName);
                        cout << "What is the year this movie is being nominated?\n";
                        getline(cin, movieYear);
                        movieToBeAdded.setYear(movieYear);
                        cout << "How any nominations does this movie have?\n";
                        getline(cin, junkString);
                        movieNomination = stoi(junkString);
                        movieToBeAdded.setNomination(movieNomination);
                        cout << "What is the rating for this movie?\n";
                        getline(cin, movieRating);
                        movieToBeAdded.setRating(movieRating);
                        cout << "What is the duration of this movie?\n";
                        getline(cin, movieDuration);
                        movieToBeAdded.setDuration(movieDuration);
                        cout << "What is the primary genre of this movie?\n";
                        getline(cin, movieGenre1);
                        movieToBeAdded.setGenre1(movieGenre1);
                        cout << "What is the secondary genre of this movie?\n";
                        getline(cin, movieGenre2);
                        movieToBeAdded.setGenre2(movieGenre2);
                        cout << "What month was this movie relased?\n";
                        getline(cin, movieRelease);
                        movieToBeAdded.setRelease(movieRelease);
                        cout << "What is the metacritic rating for this movie?\n";
                        getline(cin, junkString);
                        movieMetacritic = stoi(junkString);
                        movieToBeAdded.setMetacritic(movieMetacritic);
                        cout << "What is the synopsis of this movie?\n";
                        getline(cin, movieSynopsis);
                        movieToBeAdded.setSynopsis(movieSynopsis);
                        if(movies->getSortedBy() == 3)
                            movies->addNode(movieName, movieToBeAdded);
                        if(movies->getSortedBy() == 4)
                            movies->addNode(movieYear, movieToBeAdded);
                        if(movies->getSortedBy() == 5)
                            movies->addNode(movieDuration, movieToBeAdded);
                        if(movies->getSortedBy() == 6)
                            movies->addNode(movieRating, movieToBeAdded);
                        cout << "\nMovie has been added to the data base!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 2:
                        //Print the tree
                        movies->printInorder();
                        cout << "\nDone printing the tree!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 3:
                        //search and modify a node
                        //ask info about node
                        cin.ignore();       //needed for getline
                        cout << "To edit a node, I will need details to find the specific node\n"
                             <<"If you do not know the details, go back and partial search the node you're looking for\n";
                        cout << "I will need you to provide me with every field accurately\n"
                             <<"Movie Name: ";
                        getline(cin, movieName);
                        transform(movieName.begin(), movieName.end(), movieName.begin(), ::tolower); //https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
                        //now it's all lowercase
                        movieName.erase(remove(movieName.begin(), movieName.end(), ' '), movieName.end());
                        //removed all spaces
                        cout << "\nMovie Year: ";
                        getline(cin, movieYear);
                        //call search and modify
                        if(movies->getSortedBy() == 3)
                            movies->searchAndModifyMov(movieName, movieYear);
                        else
                        {
                            cout << "Had to sort the tree for this search!\n";
                            movies->sortByFieldMov(3, movies);
                            movies->searchAndModifyMov(movieName, movieYear);
                        }
                        cout << "\nDone modifying the actor!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 4:
                        //do a complete search
                        cin.ignore();
                        cout << "This is a complete search, I will need you to provide me with the entire field\n"
                             <<"Movie Name: ";
                        getline(cin, movieName);
                        if(movies->getSortedBy() == 3)  //3 is name
                            movies->completeSearchMov(movieName);
                        else
                        {
                            cout << "Had to sort the tree for this search!\n";
                            movies->sortByFieldMov(3, movies);
                            movies->completeSearchMov(movieName);
                        }
                        cout << "\nComplete search done!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 5:
                        //prompt the user for what field they would like to sort the tree by through a menu
                        cout << "3)Sort by name\n4)Sort by Year\n5)Sort by Duration\n6)Sort by Rating";
                        cin >> userMenuOption;
                        movies->sortByFieldMov(userMenuOption, movies);
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 6:
                        //prompt the user for a string then use that string to search
                        cin.ignore();
                        cout << "Partial search\nPlease provide the name or part of the name of this movie: ";
                        getline(cin, movieName);
                        transform(movieName.begin(), movieName.end(), movieName.begin(), ::tolower);
                        movieName.erase(remove(movieName.begin(), movieName.end(), ' '), movieName.end());
                        //movieName is now lowercase and no spaces
                        movies->partialSearch(movieName, vecOfMovies);
                        cout << "Here are all the possible matches: \n";
                        for(int i = 0; i < vecOfMovies.size(); i++)
                        {
                            vecOfMovies[i].Data().print();
                        }
                        if(vecOfMovies.size() == 0)
                            cout << "There was no matches!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 7:
                        //prompt user for info and then delete if match
                        cin.ignore();
                        cout << "Please enter the name of the movie you want to delete:\n";
                        getline(cin, movieName);
                        transform(movieName.begin(), movieName.end(), movieName.begin(), ::tolower);
                        movieName.erase(remove(movieName.begin(), movieName.end(), ' '), movieName.end());
                        //actorName is now lowercase and no spaces
                        if(movies->getSortedBy() == 3)  //3 is name
                        {
                            movies->deleteNode(movieName);  //name is unique for movies so this function will work
                        }

                        else
                        {
                            //the delete function only works with the name
                            cout << "Had to sort the tree by name for this delete!\n";
                            movies->sortByFieldMov(3, movies);
                            movies->deleteNode(movieName);
                        }
                        cout << "\nSearch and delete done!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 8:
                        cout << "Writing the movie tree to a file call: 'movieFile.csv'\n";
                        movies->writeToFileMov();
                        cout << "\nDone writing tree to file!\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                    case 9:
                        //go back to the previous menu
                        thirdMenuLoop = false; //this is needed to break out of the loop
                        break;
                    case 10:
                        //exit
                        cout << "Exiting...\n";
                        thirdMenuLoop = false;
                        mainMenuLoop = false;
                        break;
                    default:
                        //invalid option
                        cout << "Invalid option, try again\n";
                        nanosleep(&sleepTime, &returnTime);
                        break;
                }//switch case
            }//while third menu loop
        }//if userMenuOption is 2
        else if(userMenuOption == 3)    //exit
        {
            cout << "Exiting...\n";
            mainMenuLoop = false;
        }
        else    //default
        {
            cout << "Invalid option, try again\n";
        }
    }

}

void loopForFiles(BSTree<Actors, std::string> *actors, BSTree<Movies, std::string> *movies) {
    string fileName;
    bool fileHasBeenOpened = false;
    timespec sleepTime;     //https://stackoverflow.com/questions/3072912/boostthis-threadsleep-vs-nanosleep
    timespec returnTime;
    sleepTime.tv_sec = 1;
    sleepTime.tv_nsec = 1000;

    cout << "\nHello user! I will need you to provide me the text file I will be reading for the actor & movie tree!\n";
    nanosleep(&sleepTime, &returnTime);
    while(fileHasBeenOpened == false)
    {
        cout << "\nFiles available to open(open both to enter the main menu): \n\n#########################\n\tactor-actress.csv \n\tpictures.csv\n#########################\n\n";
        nanosleep(&sleepTime, &returnTime);
        cout << "Remember this is case sensitive! the extension is needed\nIf you fail to provide me a correct file"
             << " I will keep asking until I am given a file to open\nPlease type in your file name: ";
        getline(std::cin, fileName);    //user input is inside of fileName now
        std::ifstream infile;
        infile.open(fileName);
        if(infile.is_open())            //if it has opened, we will set the loop to false and read
        {
            cout << "\nSuccefully opened the file!\n";
            nanosleep(&sleepTime, &returnTime);
            //Now I have to determine which function to call, the user could have typed either the actors or movies file
            if(fileName == "actor-actress.csv")
            {
                actors->readActors();
                actors->getHasData();
            }
            else if(fileName == "pictures.csv") //I don't want to use else because I don't want to assume that it has to be movies if it's not actors
            {
                movies->readMovies();
                movies->getHasData();
            }
            if(actors->getHasData() == true && movies->getHasData() == true)  //this means that both databases have been filled
            {
                fileHasBeenOpened = true;   //both files has been opened, the read functions have been called, we can exit
            }
            else    //else not both of the databases have data inside
            {
                fileHasBeenOpened = false;  //should already be false, can't hurt to set it to false anyway
                cout << "\n\nNow that we've read that file, go ahead and open the other file.";
                nanosleep(&sleepTime, &returnTime);
            }
        }
        else
        {
            cout << "\nUnavailable to open the file, let's try that again\n";
            fileHasBeenOpened = false;  //this should not be needed since the variable should be false, extra security
        }
    }
}

/* Make sure that the input is an int*/
int intCheck()
{
    int value;
    bool loop = false;
    while (loop == false) {
        cin >> value;
        if (cin.fail())  //if cin is not an int
        {
            cout << "That wasn't an int, try again\n";
            cin.clear();    //without this clear, an infinite loop is created
            cin.ignore(256, '\n');
            loop = false;   //not needed
        } else {
            return value;
            loop = true;    //not needed
        }
    }
}
/* Makes sure the input is an int and that's it's only 0 or 1*/
int intCheckWinner()
{
    int value;
    bool loop = false;
    while (loop == false)
    {
        cin >> value;
        if(cin.fail())          //if cin was not an int
        {
            cout << "That wasn't an int, try again\n";
            cin.clear();
            cin.ignore(256, '\n');
            loop = false;
        }
        else if(value == 0)     //valid option
            return value;
        else if(value == 1)     //valid option
            return value;
        else
        {
            cout << "Wrong input, answer must be a 0 or a 1!\nTry again\n";
            loop = false;
        }
    }
}