#include "tournament_round.h"

// TournamentRound functions goes here

TournamentRound::TournamentRound() { }
TournamentRound::TournamentRound(std::list<MusicBand*>_bands): bands(_bands){ }
TournamentRound::TournamentRound(std::vector<MusicBand*>_bands)
{
    bands = std::list<MusicBand*>(_bands.begin(), _bands.end());
}

std::size_t TournamentRound::size() { return bands.size(); }
    
/*TournamentRound::TournamentRound(TournamentRound& other)
{
    bands = other.bands;
}
TournamentRound::TournamentRound(TournamentRound&& other)
{
    bands = other.bands;
    other.bands.clear();
}*/
TournamentRound& TournamentRound::operator=(TournamentRound&& other)
{
    bands = other.bands;
    other.bands.clear();
    return *this;
}

TournamentRound& TournamentRound::get_next_round()
{
    std::list<MusicBand*> new_bands;
    while(bands.size() > 1)
    {
        MusicBand* team1 = bands.front();
        bands.pop_front();
        MusicBand* team2 = bands.back();
        bands.pop_back();

        int score1 = team1->play(team2);
        int score2 = team2->play(team1);

        MusicBand* winner = score1 >= score2 ? team1 : team2;
        MusicBand* loser = score1 >= score2 ? team2 : team1;
        
        int fan_change = score1 >= score2 ? score1 - score2 : score2 - score1;
        
        if(fan_change > loser -> get_fan_count()) fan_change = loser -> get_fan_count();
        

        winner->set_fan_count(winner->get_fan_count() + fan_change);
        loser->set_fan_count(loser->get_fan_count() - fan_change);

        new_bands.push_back(winner);
    }
    if(bands.size() == 1)
    {
        new_bands.push_back(bands.front());
        bands.pop_front();
    }
    return  *(new TournamentRound(new_bands)); 
}

std::ostream& operator<< (std::ostream &os, TournamentRound &other)
{ 
    //Overloads the << operator. Used by the Tournament class to
    // print the current band names in the TournamentRound, 
    //separated by a single tab.

        for (MusicBand* band : other.bands) {
            os << band->get_name();
            if (band != other.bands.back()) os << "\t";
        }
        return os;

    return os; 
}