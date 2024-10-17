#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include <string>

using namespace std;


class particle {
public:
    particle(double x, double y);
    double getX() const;
    double getY() const;
    double getMass() const;
    void setX(double x);
    void setY(double y);
    double getDistance(double x, double y) const;
    string toString() const;

    static double getInfluence(double x, double y);
private:
    double x;
    double y;
    const double mass = 1.0;
};


#endif //PARTICLE_HPP
