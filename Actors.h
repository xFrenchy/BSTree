#ifndef DUPONTFINAL_ACTOR_H
#define DUPONTFINAL_ACTOR_H

#include <string>
using namespace std;

class Actors
{
private:
    string year;
    string award;
    int winner; //1 if they won, 0 if they did not win
    string name;
    string film;
public:
    Actors();
    void setYear(string _year) {year = _year;}
    void setAward(string _award) {award = _award;}
    void setWinner(int _winner) {winner = _winner;}
    void setName(string _name) {name = _name;}
    void setFilm(string _film) {film = _film;}

    string getYear() {return year;}
    string getAward() {return award;}
    int getWinner() {return winner;}
    string getName() {return name;}
    string getFilm() {return film;}

    void print();
    string lineForFile();
};
#endif //DUPONTFINAL_ACTOR_H
