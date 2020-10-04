#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <bits/stdc++.h>
#include <sstream>
#include <tuple>
#include <limits>
#include <numeric>
#include <algorithm>
#include <queue>
#include "Planet.h"
#include "Galaxy.h"

using namespace std;

Galaxy::Galaxy(string filename) {
        ifstream inFile(filename);
        if (!inFile) return;

        string id;
        int x;
        int y;
        int z;

        string line;
        numPlanets = 0;
        while (getline(inFile, line))
        {
                std::istringstream iss(line);
                if (!(iss >> id >> x >> y >> z)) { break; } // error
                Planet temp = Planet(id,x,y,z);
                temp.num = numPlanets;
                planets.push_back(temp);
                numPlanets++;
                // process pair (a,b)
        }
        // make adjacentPlanets for each planet
        for (int i = 0; i < planets.size(); i++) {
                /*nested for loop adds every planet besides planets[i] to planets[i]'s adjacency list'*/
                vector<pair<double, int> > vect;
                for (int z= 0; z < planets.size(); z++) {
                        /*if statement ensures planets[i] does not add itself into its adjacency list*/
                        if (i!=z) {
                                vect.push_back(make_pair(planets[i].distance(planets[z]),z));
                        }
                }
                sort(vect.begin(), vect.end());
                // for (auto it = vect.begin(); it != vect.end(); it++) cerr << (*it).second << endl;
                for (int k = 0; k < 4; k++) {
                        planets[i].adjacentPlanets.push_back(&planets[vect[k].second]);
                }

        }
        // cerr << "here" << endl;
        //make chart for every planet
        for (int i = 0; i < planets.size(); i++) {
                //chart = vect
                vector<tuple<int, double, int> > vect;
                int current;
                //fill chart with 0 or inf and save current
                for (int z = 0; z < planets.size(); z++) {
                        if (i == z) {
                                vect.push_back(make_tuple(z,0.0,LDBL_MAX));
                                current = i;
                        }
                        else vect.push_back(make_tuple(z,LDBL_MAX,LDBL_MAX));
                }
                vector<int> white(planets.size());
                vector<int> black;
                queue<int> gray;
                iota(begin(white), end(white), 0);
                // for (auto it = white.begin(); it != white.end(); it++) {
                //     cerr << *it << endl;
                // }
                white.erase(remove(white.begin(), white.end(), current), white.end());
                gray.push(current);
                while (!white.empty() && !gray.empty()) {
                        // cerr << planets[gray.front()].planetName << endl;
                        for (auto it = planets[gray.front()].adjacentPlanets.begin(); it != planets[gray.front()].adjacentPlanets.end(); it++) {
                                // **it = adjacent planets
                                int k;
                                // k = index of **it
                                for (k = 0; k < vect.size(); k++) {
                                        if (planets[get<0>(vect[k])].planetName == (*it)->planetName) break;
                                }
                                vector<int>::iterator found = find(white.begin(), white.end(), k);
                                if (found != white.end()) {
                                        white.erase(remove(white.begin(), white.end(), k), white.end());
                                        gray.push(k);
                                }
                                double dist = planets[gray.front()].distance(planets[k]) + get<1>(vect[gray.front()]);
                                int temp = gray.front();
                                // while (planets[temp].planetName != planets[i].planetName && get<2>(vect[temp]) != LDBL_MAX) {
                                //         dist += get<1>(vect[temp]);
                                //         temp = get<2>(vect[temp]);
                                // }
                                if (dist < get<1>(vect[k])) {
                                        get<1>(vect[k]) = dist;
                                        get<2>(vect[k]) = gray.front();
                                }
                        }
                        black.push_back(gray.front());
                        gray.pop();
                }

                planets[i].chart = vect;
        }
        // for (auto it = vect.begin(); it != vect.end(); it++) {
            //         int third = get<2>(*it);
            //         if (get<2>(*it) > planets.size()) cerr << planets[get<0>(*it)].planetName << " " << get<1>(*it) << " bad" << endl;
            //         else cerr << planets[get<0>(*it)].planetName << " " << get<1>(*it) << " " << planets[get<2>(*it)].planetName << endl;
            // }
        // cerr << planets.size() << endl;
        for (int i = 0; i < planets.size(); i++) {
                for (int z= 0; z < planets.size(); z++) {
                    // cerr << i << z << endl;
                    vector<Planet *> temp = makePath(&planets[i], &planets[z]);
                    (planets[i].paths).push_back(temp);
                }
        }
}



Planet* Galaxy::findByName(string planetName) {
        for (int i = 0; i < numPlanets; i++) {
                if (planets[i].getName() == planetName) {
                        return &planets[i];
                }
        }
        return nullptr;
}

vector<Planet> Galaxy::getPlanets() {
        return planets;
}

unsigned int Galaxy::size() {
        return numPlanets;
}

vector<Planet *> Galaxy::makePath(Planet * start, Planet * dest) {
    vector<Planet *> ret;
    if (get<2>(start->chart[dest->num]) > planets.size() && start != dest) {
        return ret;
    }
    ret.insert(ret.begin(), dest);
    if (start == dest) return ret;
    while (get<2>(start->chart[dest->num]) != start->num) {
        ret.insert(ret.begin(), & planets[get<2>(start->chart[dest->num])]);
        dest = & planets[get<2>(start->chart[dest->num])];
    }
    ret.insert(ret.begin(), & planets[get<2>(start->chart[dest->num])]);
    return ret;
}

vector<Planet *> Galaxy::shortestPath(Planet * start, Planet * dest) {
    return (start->paths)[dest->num];
}

double Galaxy::pathDistance(Planet * start, Planet * dest) {
    return get<1>(start->chart[dest->num]);
}


/* main method used for testing.
   g++ -o test Galaxy.cpp Planet.cpp
   ./test */
// int main() {
//         Galaxy testgalaxy = Galaxy("planetsB.dat");
//         vector<Planet> testplanetvector = testgalaxy.getPlanets();
//         for (auto &i : testplanetvector) {
//                 std::cout << " planet name: " << i.getName()
//                           << " x-coordinate: " << i.getXCoor()
//                           << " y-coordinate: " << i.getYCoor()
//                           << " z-coordinate: " << i.getZCoor() << std::endl;
//         }
//         cout<<"searching for planet named WASP-21b: "<<endl;
//         string pn = "WASP-21b";
//         Planet* alex = testgalaxy.findByName(pn);
//         cout<<"x:"<<alex->getXCoor()<<" y:"<<alex->getYCoor()<<" z:"<<alex->getZCoor()<<endl;
//         cout<<"testing distance function between two planets, should be 38.8587"<<endl;
//         cout<<testplanetvector[0].distance(testplanetvector[1])<<endl;
// }