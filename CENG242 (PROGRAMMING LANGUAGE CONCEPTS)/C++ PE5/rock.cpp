#include "metal.h"
#include "kpop.h"
#include "rock.h"
#include "jazz.h"

int RockBand::play(MusicBand *other)
{
    int score;
    if(dynamic_cast<MetalBand *>(other) != nullptr)
        score = (this->get_fan_count() +(int) (0.1 * this->get_talent() * this->get_energy())) * 1.4 ;
    else if(dynamic_cast<KPopBand *>(other) != nullptr) 
        score = (this->get_fan_count() +(int) (0.1 * this->get_talent() * this->get_energy())) * 0.5 ;
    else if(dynamic_cast<RockBand *>(other) != nullptr)
        score = (this->get_fan_count() +(int) (0.1 * this->get_talent() * this->get_energy())) * 1.0 ;
    else if(dynamic_cast<JazzBand *>(other) != nullptr) 
        score = (this->get_fan_count() +(int) (0.1 * this->get_talent() * this->get_energy())) * 0.8 ;
    
    
    this->set_energy((int) (this->get_energy() * 0.9));
    
    return score;
}

void RockBand::rehearse(void) 
{
    this->set_energy((int) (this->get_energy() * (1 - 0.5 * 0.9)));
    this->set_talent((int) (this->get_talent() + 10));
    return;

}