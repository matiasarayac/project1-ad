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
    map<int, vector<int>> person;
    map<int, bool> visited;

    void printGraphs();
    void pushBackRelationship(vector<int> v);
    void createPeopleRelations(vector<int> v);
    void printMap();
    void addRelation(vector<int> v, int myIndex, int friendIndex, vector<int> fzero, vector<int> fone);
    void createCommunities();
    void addEdge(int u, int v);
    void DFSUtil(int u);
    void printVisited();
    void BFS(int u);
//    void DFS(int V);

public:
    People(string fname);

};


#endif //PROJECT1_AD_PEOPLE_H
