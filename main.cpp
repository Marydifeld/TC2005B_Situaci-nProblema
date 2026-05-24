#include "file_utils.h"

int main() {
    vector<vector<int>> dists, max_data; 
    vector<pair<int, int>> cor; 
    fileReader("./input/test1.txt", dists, max_data, cor); 
    vector<int> cables = prim(dists); 
    indexToLetter(cables); 
    return 0; 
}