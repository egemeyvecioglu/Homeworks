#include "kpop.h"
#include "jazz.h"
#include "music_band.h"
#include "tournament.h"
#include "tournament_round.h"


int main()
{
    JazzBand band1("eski bir grup", 440, 21, 100);
    MusicBand *band2 = new JazzBand("as", 440, 21, 100);
    std::cout << band1.play(band2);
    return 0;
}