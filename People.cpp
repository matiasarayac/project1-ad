//
// Created by Matias Araya on 10/26/17.
//

#include "People.h"

People::People(string fname) {

    string line;
    int people_count;
    int rel_count;
    string token;
    vector<vector<int>> adj;
    communities = 0;

    ifstream myfile(fname);
    if (myfile.is_open()) {
        getline(myfile, line); // get first line
        people_count = stoi(line); // store first line
//        cout << "People count: " << people_count << endl;
        for (int i = 1; i <= people_count; ++i) {
//            cout << "i people: " << i << endl;
            getline(myfile, line);
            phobias.push_back(stoi(line)); //peoples phobias into vector
            visited[i] = false;
            p_count[stoi(line)] = 0;
        }

        getline(myfile, line); // get number of relationships
        rel_count = stoi(line); // store number of relationships
//        cout << "Relationship: " << rel_count << endl;


        for (int i = 0; i < rel_count; ++i) {
//            cout << "Rel count: " << i << endl;
            getline(myfile, line);
            istringstream iss(line);
            vector<int> v;
            for (int j = 0; j < 2; ++j) {
                getline(iss, token, ' ');
                v.push_back(stoi(token));
            }

            addEdge(v[0], v[1]); // Add edge to the graph

        }

        for (int i = 1; i <= visited.size(); ++i) {
            if (visited[i] == false) {
                BFS(i);
                ++communities;
            }
        }

        cout << "communities: " << communities << endl;
        for(auto &i: solution){
            cout << "phobia: " << i << endl;
        }

    } else cout << "Unable to open file" << endl;

}

void People::addEdge(int u, int v) {
    person[u].push_back(v);
    person[v].push_back(u);
}

// Search for all neighbors nodes from given vertex u
void People::BFS(int u) {
    queue<int> q;
    q.push(u);
    visited[u] = true;
    int t;
    map<int, int> aux;
    aux = p_count; //p_count contain a map with all phobias with count 0

    while (!q.empty()) {
        t = q.front();
        ++aux[phobias[t - 1]]; //added 1 to specific phobia
        q.pop();
        for (auto &i : person[t]) {
            if (visited[i] == false) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    generateSolution(aux);

}

// Search for the more common phobia O(n) and added to vector solution
void People::generateSolution(map<int, int> aux){
    int biggerCount = 0, phobia = 0;
    for (auto elem: aux) {
        if (elem.second > biggerCount) {
            phobia = elem.first;
            biggerCount = elem.second;
        } else if (elem.second == biggerCount) {
            if (phobia > elem.first) {
                phobia = elem.first;
            }
        }
    }

    solution.push_back(phobia);
}

// Util function to check vector visited
void People::printVisited() {
    for (auto elem :visited) {
        cout << elem.first << ": ";
        cout << elem.second << endl;
    }
}