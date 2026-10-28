class Solution {
public:
    vector<vector<int>> adj;
    vector<int> disc, low;
    vector<vector<int>> ans;
    int timer = 0;

    void dfs(int node, int parent) {
        disc[node] = low[node] = timer++;

        for (int nei : adj[node]) {
            if (nei == parent) continue;

            if (disc[nei] == -1) {
                dfs(nei, node);

                low[node] = min(low[node], low[nei]);

                // Bridge / critical connection
                if (low[nei] > disc[node]) {
                    ans.push_back({node, nei});
                }
            } else {
                low[node] = min(low[node], disc[nei]);
            }
        }
    }

    vector<vector<int>> criticalConnections(
        int n, vector<vector<int>>& connections
    ) {
        adj.resize(n);
        disc.assign(n, -1);
        low.assign(n, -1);

        for (auto& edge : connections) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        for (int i = 0; i < n; i++) {
            if (disc[i] == -1) {
                dfs(i, -1);
            }
        }

        return ans;
    }
};
