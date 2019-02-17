#include "Movies.h"

#include <iostream>

Movies::Movies()
{
    year = "0";
    amountOfNominations = 0;
    rating = "0";
    name = "";
    duration = "0";
    genre1 = "";
    genre2 = "";
    release = "";
    metacritic = 0;
    synopsis = "";
}

void Movies::print()
{
    cout << "\nName: " << name << "\nYear: " << year << "\nAmount of Nominations: " << amountOfNominations << "\nRating: " << rating
         <<"/10\nDuration: " << duration << "min\nGenre1: " << genre1 << "\nGenre2: " << genre2 << "\nRelease: " << release
         << "\nMetacritic: " << metacritic << "/100\nSynopsis: " << synopsis << endl;
}

string Movies::lineForFile()
{
    string lineToAdd;
    lineToAdd = name + "," + year + "," + to_string(amountOfNominations) + "," + rating + "," + duration + "," + genre1 + "," + genre2 + "," + release + "," + to_string(metacritic) + "," + synopsis + "\n";
    return lineToAdd;
}

