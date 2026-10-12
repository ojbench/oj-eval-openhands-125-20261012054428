#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    // Use faster input/output
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<tuple<int, int, int>> constraints;
        vector<int> variables;
        
        // Read all constraints and collect variables
        for (int i = 0; i < n; i++) {
            int a, b, e;
            scanf("%d %d %d", &a, &b, &e);
            constraints.emplace_back(a, b, e);
            variables.push_back(a);
            variables.push_back(b);
        }
        
        // Coordinate compression
        sort(variables.begin(), variables.end());
        variables.erase(unique(variables.begin(), variables.end()), variables.end());
        
        // Map original variable indices to compressed indices
        map<int, int> varToIndex;
        for (int i = 0; i < variables.size(); i++) {
            varToIndex[variables[i]] = i;
        }
        
        // Create UnionFind with compressed indices
        UnionFind uf(variables.size());
        
        // Process equality constraints
        bool valid = true;
        vector<pair<int, int>> inequalities;
        
        for (auto& [a, b, e] : constraints) {
            int idxA = varToIndex[a];
            int idxB = varToIndex[b];
            
            if (e == 1) {
                // Equality constraint: a == b
                uf.unite(idxA, idxB);
            } else {
                // Inequality constraint: a != b
                inequalities.emplace_back(idxA, idxB);
            }
        }
        
        // Check if any inequality constraint is violated
        for (auto& [a, b] : inequalities) {
            if (uf.connected(a, b)) {
                valid = false;
                break;
            }
        }
        
        if (valid) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}