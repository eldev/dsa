// https://leetcode.com/problems/task-scheduler/
class Solution {
public:
    // Идеи решения:
    // 1. в определенный момент времени из всех доступных тасок надо взять
    // ту, у которой кол-во больше всего (жадный алгоритм)
    // Для этого будем использовать max heap по кол-ву (см. pq)
    // 2. Если в момент времени curTime мы выполняем таску t,
    // то в следующий момент, когда эта таска снова может быть выполнена,
    // это в момент времени curTime + n + 1. Соответственно,
    // до этого момента времени эту таску можно не рассматривать
    // т.е. до этого момента в pq эту таску не надо возвращать.
    // Чтобы держать список таких тасок будем использовать min heap
    // по времени рассмотрения (см. toPush).
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, long> counter;
        for (char t : tasks) {
            if (counter.count(t) == 0) counter[t] = 0;
            counter[t]++;
        }

        priority_queue<pair<long,char>> pq; // max heap by count
        for (const auto& [t, count] : counter)
            pq.push(make_pair(count, t));
        
        priority_queue<pair<long,char>, vector<pair<long,char>>, greater<pair<long,char>>> toPush; // min heap by time to push

        long curTime = 0;
        while (!pq.empty() || !toPush.empty()) {
            if (!toPush.empty() && toPush.top().first == curTime) {
                // если наступил нужный момент времени, когда первая таска из toPush
                // может быть выполнена, то надо ее вернуть в pq.
                char c = toPush.top().second;
                toPush.pop();
                pq.push(make_pair(counter[c], c));
            }

            auto f = pq.top();
            pq.pop();
            char c = f.second;
            counter[c]--;
            if (counter[c] > 0) {
                if (n == 0) {
                    pq.push(make_pair(counter[c], c));
                } else {
                    toPush.push(make_pair(curTime + n + 1, c));
                }
            }

            if (!pq.empty()) curTime++;
            else if (!toPush.empty()) curTime = toPush.top().first;
        }
        return curTime + 1;
    }
};
