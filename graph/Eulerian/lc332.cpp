// https://leetcode.com/problems/reconstruct-itinerary/

// Eulerian Circuite + smallest order + multiset
class Solution {
private:
    void dfs(unordered_map<string, multiset<string>>& g, vector<string>& ans, string u) {
        while (!g[u].empty()) {
            // The task requires the smallest lexical order
            // so we use (ordered) multiset and fetch the smallest (first) element.
            // Also note multiset is used, because some airports can be presented
            // multiple times in this task.
            auto it = g[u].begin();
            string next = *it;
            g[u].erase(it);
            dfs(g, ans, next);
            ans.push_back(next);
        }
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, multiset<string>> g;
        for (auto& edge : tickets) {
            string from = edge[0], to = edge[1];
            g[from].insert(to);
        }
        vector<string> ans;
        dfs(g, ans, "JFK");

        // Need to reverse, because we add elements from end to begin.
        ans.push_back("JFK");
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
