#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include <string>

using namespace std;


class particle {
public:
    particle(double x, double y);
    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    [[nodiscard]] double getMass() const;
    void setX(double x);
    void setY(double y);
    [[nodiscard]] double getDistance(double x, double y) const;
    [[nodiscard]] string toString() const;

    static double getInfluence(double x, double y);
    void setZone(int zone);
    [[nodiscard]] double getZone() const;

private:
    double x;
    double y;
    int zone = -1;
    const double mass = 1.0;
};


#endif //PARTICLE_HPP
