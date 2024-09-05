#include <iostream>
#include <ostream>

#include "src/particle.hpp"
#include "src/space2D.hpp"

using namespace std;

int main() {
    particle p(2.0, 2.5);

    cout << p.toString() << endl;

    double influence = particle::getInfluence(2.5, 0.9);
    cout << influence << endl;


    space2D space(40.0, 40.0, 2.6);


    for (const particle& p : space.getParticles()) {
        cout << p.toString() << endl;
    }

    return EXIT_SUCCESS;
}