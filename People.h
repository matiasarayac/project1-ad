//
// Created by Matias Araya on 10/26/17.
//

#ifndef PROJECT1_AD_PEOPLE_H
#define PROJECT1_AD_PEOPLE_H

#include "includes.h"

class People {
private:
    vector<int> phobias;
    map<int, vector<int>> person;
    map<int, bool> visited;
    map<int, int> p_count;
    int communities;
    vector<int> solution;

    void addEdge(int u, int v);
    void printVisited();
    void BFS(int u);

public:
    People(string fname, string output);

};


#endif //PROJECT1_AD_PEOPLE_H
