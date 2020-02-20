#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> getPermutations(vector<char> vocab) {
    int n = vocab.size();
    if (n == 0) {
        return {{}};
    }
    vector<vector<char>> permutations(0);
    for (int i = 0; i < n; i++) {
        auto reducedVocab = vocab;
        reducedVocab.erase(reducedVocab.begin() + i);
        auto lowerPermutations = getPermutations(reducedVocab);
        for (auto permutation : lowerPermutations) {
            permutation.push_back(vocab[i]);
            permutations.push_back(permutation);
        }
    }
    return permutations;
}

int main() {
    vector<char> vocab;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        vocab.push_back('A' + i);
        cout << vocab[i] << " ";
    }
    cout << endl;
    auto permutations = getPermutations(vocab);
    for (auto permutation : permutations) {
        for (auto ch : permutation) {
            cout << ch << " ";
        }
        cout << endl;
    }
    return 0;
}