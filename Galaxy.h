#ifndef GALAXY_AKBL
#define GALAXY_AKBL
#include "Planet.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

class Galaxy {
public:
  std::vector<Planet> planets;

  int numPlanets;

  std::map<std::string, int> dict;

  Galaxy(std::string filename);
  //Takes in a filename and build a list of planets with adjacencies

  unsigned int size();
  //The number of planets currently contained in the galaxy

  Planet* findByName(std::string planetName);
  //Returns the planet object with the associated name

  std::vector<Planet> getPlanets();

  std::vector<Planet *> shortestPath(Planet * start, Planet * dest);

  std::vector<Planet *> makePath(Planet * start, Planet * dest);

  double pathDistance(Planet * start, Planet * dest);

  ~Galaxy(){}

};

#endif