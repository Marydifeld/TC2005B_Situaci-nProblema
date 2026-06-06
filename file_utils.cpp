#include "file_utils.h"

#include <fstream>
#include <stdexcept>
#include <sstream> 
#include <queue> 


void fileReader(const string& FILE_PATH, vector<vector<int>>& 
                dist_colonias, vector<vector<int>>& max_data,
                vector<pair<int,int>>& coordinates) {

    ifstream file(FILE_PATH, ios::binary);
    if (!file) {
        throw runtime_error("Could not open file");
    }

    string line; 
    int N, line_count = 0; 

    while (getline(file, line)) {
        if (line_count == 0) {
            N = stoi(line);
            dist_colonias.resize(N);
            max_data.resize(N);  
            coordinates.resize(N);
            line_count++; 
            continue; 
        } 

        if (line.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        }

        stringstream ss(line);  
        if (line_count <= N) {
            int n;
            while (ss >> n) {
                dist_colonias[line_count - 1].push_back(n);
            }
        } 
        else if (line_count <= 2 * N) {
            int n;
            while (ss >> n) {
                max_data[line_count - (N + 1)].push_back(n);
            }
        } 
        else {
            string token;
            while (ss >> token) {
                stringstream ss2(token);

                char open, comma, close;
                int x, y;

                ss2 >> open >> x >> comma >> y >> close;

                coordinates[line_count - (2 * N + 1)] = {x, y};
            }
        }

        line_count++; 
    }
    file.close(); 
}


int nearestNode(vector<int>& dists, vector<bool>& visited) {
    int min_val = 1e9, min_index = -1; 

    for (int i = 0; i < visited.size(); i++) {
        if(visited[i] == false && dists[i] < min_val) {
            min_index = i; 
            min_val = dists[i]; 
        }
    }

    return min_index; 
}
vector<int> prim(const vector<vector<int>>& adj) {
    int n = adj.size(); 
    int INF = 1e9;

    vector<bool> visited (n, false);
    vector<int> distance (n, INF); 
    vector<int> path (n, -1); 

    distance[0] = 0;

    for (int i = 0; i < n; i++) {
        int small = nearestNode(distance, visited); 
        visited[small] = true; 

        for (int j = 0; j < n; j++) {
            if (adj[small][j] && visited[j] ==false &&
            adj[small][j] < distance[j]) {
                path[j] = small; 
                distance[j] = adj[small][j]; 
            }
        }

    }
    return path; 
}

void indexToLetter(vector<int> cables) { 
    for (int i = 0; i < cables.size(); i++) {
        if (cables[i] != -1) {
            cout << '(' << char('A' + cables[i]) << ','
            << char('A' + i) << ')' << endl; 
        }
    }
}

void tspBacktrack(int currentNode, int visitedCount, int currentCost, 
                  vector<int>& currentPath, vector<int>& bestPath, 
                  int& minCost, vector<bool>& visited, 
                  const vector<vector<int>>& dists) {
    int n = dists.size();

    if (visitedCount == n) {
        if (dists[currentNode][0] > 0) {
            int totalCost = currentCost + dists[currentNode][0];
            
            if (totalCost < minCost) {
                minCost = totalCost;
                bestPath = currentPath;
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (visited[i] == false && dists[currentNode][i] > 0) {
                
                if (currentCost + dists[currentNode][i] < minCost) {
                    
                    visited[i] = true;
                    currentPath.push_back(i);

                    tspBacktrack(i, visitedCount + 1, currentCost + dists[currentNode][i], 
                                 currentPath, bestPath, minCost, visited, dists);

                    currentPath.pop_back();
                    visited[i] = false;
                }
            }
        }
    }
}

vector<int> solveTSP(const vector<vector<int>>& dists) {
    int n = dists.size();
    vector<int> currentPath;
    vector<int> bestPath;
    vector<bool> visited(n, false);
    
    int minCost = 1e9; 

    visited[0] = true;
    currentPath.push_back(0);

    tspBacktrack(0, 1, 0, currentPath, bestPath, minCost, visited, dists);

    if (bestPath.size() > 0) {
        bestPath.push_back(0);
    }

    return bestPath;
}

void printTSP(const vector<int>& bestPath) {
    int size = bestPath.size();
    for (int i = 0; i < size; i++) {
        cout << char('A' + bestPath[i]);
        
        if (i < size - 1) {
            cout << " -> ";
        }
    }
    cout << "\n";
}