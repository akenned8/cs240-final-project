#ifndef PLANET_AKBL
#define PLANET_AKBL
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <tuple>
#include <map>

class Planet {
public:
  std::string planetName;
  int xCoor;
  int yCoor;
  int zCoor;
  std::list<Planet*> adjacentPlanets;
  std::vector<std::tuple<int, double, int>> chart;
  int num;
  std::vector<std::vector<Planet *>> paths;
  ~Planet(){}



  /*
    The adjacency list must use an algorithm to determine
    the 4 closest planets based on XYZ coordinates and
    add them to the list
  */

  Planet(std::string planetName, int xCoor, int yCoor, int zCoor);

  /*getters*/
  std::string getName();
  int getXCoor();
  int getYCoor();
  int getZCoor();
  std::list<Planet*> getAdjacent();

  /*additional method*/
  //this will get the distanceBetween from this to other planet
  double distance(Planet);

  double distanceBetween(Planet * other);

  void reset() {
      bool black = false;
      bool gray = false;
      bool white = true;
  }

};

#endif
