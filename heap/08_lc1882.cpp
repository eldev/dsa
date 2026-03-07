// https://leetcode.com/problems/process-tasks-using-servers

class Solution {
private:
    struct Server {
        int idx;
        int w;
        long long freeAt;
    };
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        vector<int> ans;
        ans.reserve(tasks.size());

        auto freeCmp = [](const auto& lhs, const auto& rhs) {
            if (lhs.w == rhs.w) return lhs.idx > rhs.idx;
            return lhs.w > rhs.w;
        };
        priority_queue<Server, vector<Server>, decltype(freeCmp)> freePq;
        for (int i = 0; i < servers.size(); i++) {
            freePq.push(Server{i, servers[i], 0});
        }

        auto busyCmp = [](const auto& lhs, const auto& rhs) {
            return lhs.freeAt > rhs.freeAt;
        };
        priority_queue<Server, vector<Server>, decltype(busyCmp)> busyPq;

        long long curTime = 0;
        while (ans.size() < tasks.size()) {
            // 1. Get all available servers from busyPq
            while (!busyPq.empty() && busyPq.top().freeAt <= curTime) {
                auto srv = busyPq.top();
                busyPq.pop();
                freePq.push(srv);
            }
            // 2. If there is no any available server,
            // we need to wait for the first busy server
            if (freePq.empty()) {
                curTime = busyPq.top().freeAt;
                continue;
            }

            int lastAddedIdx = ans.size() - 1;
            for (int t = lastAddedIdx + 1; t <= min<long long>(curTime, tasks.size()-1); t++) {
                if (freePq.empty()) break; // important

                Server srv = freePq.top();
                freePq.pop();
                ans.push_back(srv.idx);

                srv.freeAt = curTime + tasks[t];
                busyPq.push(srv);
            }
            curTime++;
        }

        return ans;
    }
};
