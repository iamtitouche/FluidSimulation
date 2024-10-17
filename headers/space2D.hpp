#ifndef SPACE2D_HPP
#define SPACE2D_HPP

#include <vector>

#include "particle.hpp"

using namespace std;

class space2D {
public:
    space2D(double length, double width);
    space2D(double length, double width, double dst);
    void evenlyInitParticles(double dst);
    void randomInitParticles(int numParticles);
    void addParticle(particle p);
    vector<particle>& getParticles();
    double getDensity(double x, double y, double infl_radius) const;
private:
    const double length, width;
    vector<particle> particles;
};


#endif //SPACE2D_HPP
