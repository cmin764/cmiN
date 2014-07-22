#include "autoturism.hpp"


int main()
{
    /* cream autoturism cu sistem de pornire cu
       preincalzire si avand avelope de [i]arna */
    Autoturism autoturism(true, 'i');

    // un circuit normal
    autoturism.porneste_autoturism();
    autoturism.condu_la_destinatie();
    autoturism.parcheaza_autoturism();

	// motorul s-a oprit dupa parcare
    // incercam sa-l conducem fara sa-l pornim
    autoturism.condu_la_destinatie();

    // acum il pornim si facem 2 trasee consecutive
    autoturism.porneste_autoturism();
    autoturism.condu_la_destinatie();
    autoturism.condu_la_destinatie();

    // incercam sa-l pornim desi nu a fost oprit
    autoturism.porneste_autoturism();

    // mai incercam un traseu, ar cam trebui sa schimbam anvelopele
    autoturism.condu_la_destinatie();
    // si incercam sa-l parcam de doua ori
    autoturism.parcheaza_autoturism();
    // adica in momentul asta nu poate fi parcat, fiindca este oprit
    autoturism.parcheaza_autoturism();

    return 0;
}
