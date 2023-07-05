#include "kpop.h"


int KPopBand::play(MusicBand *other)
{
    int score;
    
    if(dynamic_cast<KPopBand *>(other) != nullptr) 
        score = (this->get_fan_count() +(int) (0.1 * this->get_talent() * this->get_energy())) * 2.0 ;
    else
        score = (this->get_fan_count() +(int) (0.1 * this->get_talent() * this->get_energy())) * 0.5 ;

    this->set_energy((int) (this->get_energy() * 0.8));
    
    return score;
}

void KPopBand::rehearse(void) 
{
    this->set_energy((int) (this->get_energy() * (1 - 0.5 * 0.8)));
    return;
}