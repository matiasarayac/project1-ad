//
// Created by Matias Araya on 10/26/17.
//

#ifndef PROJECT1_AD_PEOPLE_H
#define PROJECT1_AD_PEOPLE_H

#include "includes.h"

extern int NO_EXIST;


class People {
private:
    vector<int> phobias;
    vector<vector<int>> graphs;

    void printGraphs();
    void pushBackRelationship(vector<int> v);

public:
    People(string fname);

};

#endif //PROJECT1_AD_PEOPLE_H
