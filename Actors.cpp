#include "Actors.h"

#include <iostream>

void Actors::print()
{
    cout << "\nName: " << name << "\nYear: " << year << "\nAward: " << award
         << "\nWinner(0 for no, 1 for yes): " << winner  << "\nFilm: " << film << endl;
}

Actors::Actors() {
    year = "0";
    award =  "";
    winner = 0;
    name = "";
    film = "";
}

string Actors::lineForFile()
{
    string lineToAdd;
    lineToAdd = year + "," + award + "," + to_string(winner) + "," + name + "," + film + "\n";
    return lineToAdd;
}
