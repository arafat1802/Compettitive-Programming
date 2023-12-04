#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Function to count the number of set bits in a binary representation
int countSetBits(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

// Function to check if two binary numbers differ in only one bit
bool differByOneBit(int a, int b) {
    int xorResult = a ^ b;
    return countSetBits(xorResult) == 1;
}

// Function to perform the Quine-McCluskey algorithm
vector<string> quineMcCluskey(vector<int>& minterms, int numVariables) {
    vector<vector<set<int>>> groups(numVariables + 1);

    // Group the minterms by the number of set bits
    for (int minterm : minterms) {
        int numSetBits = countSetBits(minterm);
        groups[numSetBits].push_back({minterm});
    }
    
    vector<int> essentialPrimeImplicants;

    // Combine groups until no more combining is possible
    for (int i = 0; i < numVariables; ++i) {
        for (int j = 0; j < groups[i].size(); ++j) {
            for (int k = 0; k < groups[i + 1].size(); ++k) {
                for (int minterm1 : groups[i][j]) {
                    for (int minterm2 : groups[i + 1][k]) {
                        if (differByOneBit(minterm1, minterm2)) {
                            set<int> combinedTerms = groups[i][j];
                            combinedTerms.insert(groups[i + 1][k].begin(), groups[i + 1][k].end());
                            groups[i + 1].push_back(combinedTerms);
                        }
                    }
                }
            }
        }
    }
    cerr << "i";
    // Extract essential prime implicants
    for (const auto& group : groups[numVariables]) {
        for (int minterm : group) {
            essentialPrimeImplicants.push_back(minterm);
        }
    }

    // Convert essential prime implicants to binary representation
    vector<string> result;
    for (int implicant : essentialPrimeImplicants) {
        string binaryRepresentation;
        for (int i = numVariables - 1; i >= 0; --i) {
            binaryRepresentation += ((implicant >> i) & 1) ? '1' : '0';
        }
        result.push_back(binaryRepresentation);
    }

    return result;
}

int main() {
    // Example usage
    vector<int> minterms = {0, 1, 2, 5, 7, 8, 10, 11, 14};
    int numVariables = 4;

    vector<string> result = quineMcCluskey(minterms, numVariables);

    // Display the simplified expressions
    cout << "Simplified Expressions:" << endl;
    for (const string& expression : result) {
        cout << expression << endl;
    }

    return 0;
}
