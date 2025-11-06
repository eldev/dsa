// https://leetcode.com/problems/alien-dictionary/

class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, vector<char>> g;
        unordered_map<char, int> indegree;
        for (const auto& w : words) {
            for (auto c : w) {
                if (g.find(c) != g.end()) continue;
                g[c] = vector<char>();
                indegree[c] = 0;
            }
        }
        // Надо сравнить соседние слова, отбросить равные префиксы
        // и выяснить первую различную букву. Это различие и покажет
        // связь from -> to (пример: w1="wrt", w2="wrf", тогда 't' -> 'f').
        for (int i = 0; i < words.size() - 1; i++) {
            string w1 = words[i];
            string w2 = words[i+1];
            for (int k = 0; k < w1.size(); k++) {
                if (k >= w2.size()) {
                    // Это corner case, когда мы рассмотрели все буквы w2,
                    // то есть w2 - префикс w1 (например, w1="wr", w2="w").
                    // С точки зрения лексикографического порядка
                    // это некорректный инпут => по условию задачи возвращаем "".
                    return "";
                }
                if (w1[k] == w2[k]) continue;
                char from = w1[k], to = w2[k];
                indegree[to]++;
                g[from].push_back(to);
                break;
            }
        }
        vector<char> topsort;
        // The Kahn's algorithm
        queue<char> q;
        for (auto it : indegree)
            if (it.second == 0) q.push(it.first);
        while (!q.empty()) {
            char from = q.front();
            q.pop();
            topsort.push_back(from);
            for (char to : g[from]) {
                indegree[to]--;
                if (indegree[to] == 0) q.push(to);
            }
        }
        if (topsort.size() < g.size()) {
            // если в topsort не попали все буквы,
            // то это значит, что в графе есть циклы,
            // т.е. инпут некорректный.
            return "";
        }
        return std::string(topsort.begin(), topsort.end());
    }
};
