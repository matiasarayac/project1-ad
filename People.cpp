//
// Created by Matias Araya on 10/26/17.
//

#include "People.h"

int NO_EXIST = -1;


People::People(string fname) {

    string line;
    int people_count;
    int rel_count;
    string token;

    ifstream myfile(fname);
    if (myfile.is_open()) {
        getline(myfile, line); // get first line
        people_count = stoi(line); // store first line

        for (int i = 0; i < people_count; ++i) {
            getline(myfile, line);
            phobias.push_back(stoi(line)); //peoples phobias into vector
        }

        getline(myfile, line); // get number of relationships
        rel_count = stoi(line); // store number of relationships

        for (int i = 0; i < rel_count; ++i) {
            getline(myfile, line);
            istringstream iss(line);
            vector<int> v;
            for (int j = 0; j < 2; ++j) {
                getline(iss, token, ' ');
                v.push_back(stoi(token));
            }

            pushBackRelationship(v); // Function to push back vector in the proper community

        }

        printGraphs();


    } else cout << "Unable to open file" << endl;

//    for (auto &i :phobias) {
//        cout << i << endl;
//    }


}

void People::printGraphs() {
    for (auto &i :graphs) {
        for (auto &j: i) {
            cout << j << " ";
        }
        cout << "" << endl;
    }
}

void People::pushBackRelationship(vector<int> v){
    //com = community
    //per = person
    int count = 0;
    uint64_t graphSize = graphs.size(); //64 bits in case it's too long
    int v_zero = NO_EXIST;
    int v_one = NO_EXIST;
    for (int com = 0; com < graphSize; ++com) {
        uint64_t comSize = graphs[com].size(); //64 bits in case it's too long
        for (int per = 0; per < comSize; ++per) {
            //Check if the numbers are in the community
            if (v[0] == graphs[com][per]) v_zero = com; // Will indicate in which community is the person
            else if (v[1] == graphs[com][per]) v_one = com;
        }
    }

    if (v_one == NO_EXIST && v_zero > NO_EXIST) {
        graphs[v_zero].push_back(v[1]);
        count++;
    } else if (v_zero == NO_EXIST && v_one > NO_EXIST) {
        graphs[v_one].push_back(v[0]);
        count++;
    } else if (v_one > NO_EXIST && v_zero > NO_EXIST) {
        if (v_one == v_zero) count++; // Same community
        else {
            //Join communities
            graphs[v_zero].insert(graphs[v_zero].end(), graphs[v_one].begin(), graphs[v_one].end());
            //Erase community
            graphs.erase(graphs.begin() + v_one);
            count++;
        }
    }

    if (count == 0) {
        graphs.push_back(v); // push new vector (new community)
    }
}


