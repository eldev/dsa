// https://leetcode.com/problems/the-maze
// BFS with state (row, column, move index).
// And also note that the object keeps the direction
// compared to the original BFS where the object can choose a direction at each BFS step.

class Solution {
private:
    const vector<vector<int>> moves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };
    struct State {
        int i, j; // coordinates
        int moveIdx; // idx of move (the ball keeps the current direction until it reaches a wall)
        State(int i, int j, int moveIdx): i(i), j(j), moveIdx(moveIdx) {}

        // the following code is requierd for unordered_set
        // ref: https://stackoverflow.com/a/64151007
        // but actually, i can use vector<vector<vector<int>>> visited - for (i,j,moveIdx)
        bool operator==(const State& rhs) const {
            return i == rhs.i && j == rhs.j && moveIdx == rhs.moveIdx;
        }
        struct HashFunction {
            size_t operator()(const State& state) const {
                size_t iHash = std::hash<int>()(state.i);
                size_t jHash = std::hash<int>()(state.j) << 1;
                size_t moveIdxHash = std::hash<int>()(state.moveIdx) << 2;
                return iHash ^ jHash ^ moveIdxHash;
            }
        };
    };
    bool bfs(const vector<vector<int>>& maze, const vector<int>& start, const vector<int>& destination, unordered_set<State, State::HashFunction>& visited, int startMoveIdx) const {
        State startCell(start[0], start[1], startMoveIdx);
        visited.insert(startCell);
        queue<State> q;
        q.push(startCell);
        while (!q.empty()) {
            auto curCell = q.front();
            q.pop();
            // the ball should keep the current direction
            int ii = curCell.i + moves[curCell.moveIdx][0];
            int jj = curCell.j + moves[curCell.moveIdx][1];
            if (ii < 0 || ii >= maze.size() || jj < 0 || jj >= maze[ii].size() || maze[ii][jj] == 1) {
                // there is a border cell or wall

                // firstly, check if we reach the destination cell
                if (curCell.i == destination[0] && curCell.j == destination[1]) return true;

                // otherwise, we can choose any possible (and not visited) direction
                for (int moveIdx = 0; moveIdx < moves.size(); moveIdx++) {
                    int newRow = curCell.i + moves[moveIdx][0];
                    int newCol = curCell.j + moves[moveIdx][1];
                    if (newRow < 0 || newRow >= maze.size() || newCol < 0 || newCol >= maze[newRow].size()) continue;
                    if (maze[newRow][newCol] == 1) continue;
                    State nextCell(newRow, newCol, moveIdx);
                    if (visited.find(nextCell) != visited.end()) continue;

                    visited.insert(nextCell);
                    q.push(nextCell);
                }
            } else {
                State nextCell(ii, jj, curCell.moveIdx);
                visited.insert(nextCell);
                q.push(nextCell);
            }
        }
        return false;
    }
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        unordered_set<State, State::HashFunction> visited; // visited states

        // Actually, from the start position the ball is able to choose any
        // (possible) move. So we need to iterate over these moves.
        for (int i = 0; i < moves.size(); i++) {
            if (visited.find(State(start[0], start[1], i)) == visited.end()) {
                if (bfs(maze, start, destination, visited, i)) return true;
            }
        }
        return false;
    }
};
