#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class UnionFind {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
    
public:
    int find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        
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

// Fast input function
inline int readInt() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

int main() {
    // Use faster input/output
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t = readInt();
    
    while (t--) {
        int n = readInt();
        
        vector<pair<int, int>> inequalities;
        UnionFind uf;
        
        // Process all constraints
        for (int i = 0; i < n; i++) {
            int a = readInt();
            int b = readInt();
            int e = readInt();
            
            if (e == 1) {
                // Equality constraint: a == b
                uf.unite(a, b);
            } else {
                // Inequality constraint: a != b
                inequalities.push_back({a, b});
            }
        }
        
        // Check if any inequality constraint is violated
        bool valid = true;
        for (auto& p : inequalities) {
            if (uf.connected(p.first, p.second)) {
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