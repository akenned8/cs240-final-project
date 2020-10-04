#include "Planet.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

Planet::Planet(std::string name, int x, int y, int z) {
  planetName = name;
  xCoor = x;
  yCoor = y;
  zCoor = z;
}

/*getters*/
string Planet::getName(){return planetName;}
int Planet::getXCoor(){return xCoor;}
int Planet::getYCoor(){return yCoor;}
int Planet::getZCoor(){return zCoor;}

/*This list can be a vector*/
list<Planet*> Planet::getAdjacent(){return adjacentPlanets;}

double Planet::distance(Planet other) {
  double x1 = (double)this->getXCoor();
  double y1 = (double)this->getYCoor();
  double z1 = (double)this->getZCoor();

  double x2 = (double)other.getXCoor();
  double y2 = (double)other.getYCoor();
  double z2 = (double)other.getZCoor();

  /*distance formula for three coordinates*/
  return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1));
}

double Planet::distanceBetween(Planet * other) {
    return this->distance(*other);
}