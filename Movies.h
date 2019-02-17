#ifndef DUPONTFINAL_MOVIES_H
#define DUPONTFINAL_MOVIES_H

#include <string>
using namespace std;

class Movies
{
private:
    string year;
    int amountOfNominations;
    string rating; //out of 10
    string name;
    string duration;   //in minutes
    string genre1;
    string genre2;
    string release;    //month
    int metacritic; //out of 100
    string synopsis;
public:
    Movies();
    void setYear(string _year) {year = _year;}
    void setNomination(int _nomination) {amountOfNominations = _nomination;}
    void setRating(string _rating) {rating = _rating;}
    void setName(string _name) {name = _name;}
    void setDuration(string _duration) {duration = _duration;}
    void setGenre1(string _genre1) {genre1 = _genre1;}
    void setGenre2(string _genre2) {genre2 = _genre2;}
    void setRelease(string _release) {release = _release;}
    void setMetacritic(int _metacritic) {metacritic = _metacritic;}
    void setSynopsis(string _synopsis) {synopsis = _synopsis;}

    string getYear() {return year;}
    int getNomination() {return amountOfNominations;}
    string getRating() {return rating;}
    string getName() {return name;}
    string getDuration() {return duration;}
    string getGenre1() {return genre1;}
    string getGenre2() { return  genre2;}
    string getRelease() {return release;}
    int getMetacritic() {return metacritic;}
    string getSynopsis() {return synopsis;}

    void print();
    string lineForFile();
};
#endif //DUPONTFINAL_MOVIES_H
