#include <iostream>
#include <chrono>

#include "universe.h"

#define timer_start (std::chrono::high_resolution_clock::now())
#ifdef timer_start
#define timer_elapsed(t) (std::chrono::duration_cast \
                                <std::chrono::milliseconds> \
                                (std::chrono::high_resolution_clock \
                                        ::now() - t).count())
#endif

int main() {

    uint universeSize=10;
    uint numOfGenerations=10000;

    std::cout << "Size of cube: ";
    std::cin >> universeSize;

    std::cout << "Number of generations: ";
    std::cin >> numOfGenerations;

    char printGenInfo = 'y';
    char printGenMaps = 'n';
    do {
        std::cout << "Print generations info? [y/n]: ";
        std::cin >> printGenInfo;
    }
    while(!std::cin.fail() && std::tolower(printGenInfo) !='y' && std::tolower(printGenInfo) !='n');

    if (printGenInfo == 'y') {
	do {
	    std::cout << "Print cube layers? [y/n]: ";
	    std::cin >> printGenMaps;
	}
	while(!std::cin.fail() && std::tolower(printGenMaps) !='y' && std::tolower(printGenMaps) !='n');
    }

    std::cout << "Life has begun...\n";
    auto timer = timer_start;

    auto u = new universe(universeSize);
    bool lifeDie = false;
    std::ostream &ost(std::cout);
    for (uint i=0; i < numOfGenerations; ++i) {

        if (printGenInfo == 'y') {
            std::cout << "GEN: " << u->getGeneraton() << " LIVING: " << u->getNumberOfLiving() << std::endl;
	    if (printGenMaps == 'y') 
                u->print(ost);
        }
        if (!u->nextgen()) {
            lifeDie = true;
            numOfGenerations = i+1;
            break;
        }
    }
    auto elapsed = timer_elapsed(timer);
    if (lifeDie) {
        std::cout << "All cellulars died due to mass extinction on " << numOfGenerations << " generation\n";
    }
    std::cout << "Life for " << numOfGenerations << " generations took " << elapsed << " microseconds" << std::endl;
    delete u;
    u = nullptr;
    return 0;
}
