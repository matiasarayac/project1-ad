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
    vector<vector<int>> adj;

    ifstream myfile(fname);
    if (myfile.is_open()) {
        getline(myfile, line); // get first line
        people_count = stoi(line); // store first line
        cout << "People count: " << people_count << endl;

        for (int i = 0; i < people_count; ++i) {
            cout << "i people: " << i << endl;
            getline(myfile, line);
            phobias.push_back(stoi(line)); //peoples phobias into vector
            visited[i + 1] = false;
        }

        getline(myfile, line); // get number of relationships
        rel_count = stoi(line); // store number of relationships
        cout << "Relationship: " << rel_count << endl;


        for (int i = 0; i < rel_count; ++i) {
            cout << "Rel count: " << i << endl;
            getline(myfile, line);
            istringstream iss(line);
            vector<int> v;
            for (int j = 0; j < 2; ++j) {
                getline(iss, token, ' ');
                v.push_back(stoi(token));
            }

            addEdge(v[0], v[1]);

//            createPeopleRelations(v);
        }


        cout << "visited size: " << visited.size() << endl;
        for (int i = 1; i <= visited.size(); ++i) {
            cout << "visited: " << i << endl;
            if (visited[i] == false) {
                BFS(i);
                cout << "" << endl;
            }
        }

//        printVisited();
        // Function to create communities
//        createCommunities();

//        printMap();


    } else cout << "Unable to open file" << endl;

}

void People::printGraphs() {
    for (auto &i :graphs) {
        for (auto &j: i) {
            cout << j << " ";
        }
        cout << "" << endl;
    }
}

void People::printMap() {
    for (auto elem :person) {
        cout << elem.first << ": ";
        for (auto &j: elem.second) {
            cout << j << " ";
        }
        cout << "" << endl;
    }
}

// This function currently it's unused because it's too slow.
void People::pushBackRelationship(vector<int> v) {
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

void People::createPeopleRelations(vector<int> v) {

    vector<int> fzero = person[v[0]]; // friends of v[0]
    vector<int> fone = person[v[1]];  // friends of v[1]

    addRelation(v, 0, 1, fzero, fone); //add v[1] to v[0] and add friends of v[1] to v[0]
    addRelation(v, 1, 0, fone, fzero); //add v[0] to v[1] and add friends of v[0] to v[1]

}

void People::addRelation(vector<int> v, int myIndex, int friendIndex, vector<int> fzero, vector<int> fone) {

    int count = 0;

    //add the person relationship
    for (auto &i: fzero) {
        if (i == v[friendIndex]) count++; //if he is already my friend
    }
    if (count == 0) person[v[myIndex]].push_back(v[friendIndex]); //if not, added

    count = 0;
    //add the friends of that person
    if (!fone.empty()) {
        for (auto &i: fone) {
            for (auto &j: fzero) {
                if (i == j) count++; //if his friends are already my friend
            }
            if (count == 0) person[v[myIndex]].push_back(i); //if not, added
        }

    }
}

void People::createCommunities() {

    //Check for communities
    for (auto elem :person) {
//        cout << "elem.first: " << elem.first;
//        cout << " size first: " << person[elem.first].size() << endl;
        for (auto &j: elem.second) {
//            cout << " j: " << j;
//            cout << " size j: " << person[j].size() << endl;

            // Delete friends with less friends than me
            // Create the communities
            // The final map person will contain only communities
            if (person[j].size() <= person[elem.first].size()) person.erase(j);
        }

    }
}


void People::addEdge(int u, int v) {
    person[u].push_back(v);
    person[v].push_back(u);
}


void People::DFSUtil(int u) {
    visited[u] = true;
//    cout << u << " ";
    if (!person[u].empty()) {
        cout << "person size: " << person[u].size() << endl;
        for (auto &i : person[u]) {
            if (visited[i] == false) DFSUtil(i);
        }
    }
}

void People::BFS(int u) {
    queue<int> q;
    q.push(u);
    visited[u] = true;
    int t;

    while (!q.empty()) {
        t = q.front();
        cout << t << " ";
        q.pop();
        for (auto &i : person[t]) {
            if (visited[i] == false) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

void People::printVisited() {
    for (auto elem :visited) {
        cout << elem.first << ": ";
        cout << elem.second << endl;
    }
}


