#include "file_utils.h"

int main() {
    vector<vector<int>> dists, max_data; 
    vector<pair<int, int>> cor; 
    fileReader("./input/test1.txt", dists, max_data, cor); 

    cout << "--- 1. Forma optima de cablear con fibra optica (Prim) ---\n";
    vector<int> cables = prim(dists); 
    indexToLetter(cables); 
    cout << "\n";

    cout << "--- 2. Ruta mas corta para el personal de correspondencia (TSP) ---\n";
    vector<int> optimalRoute = solveTSP(dists);
    printTSP(optimalRoute);
    cout << "\n";

    return 0; 
}