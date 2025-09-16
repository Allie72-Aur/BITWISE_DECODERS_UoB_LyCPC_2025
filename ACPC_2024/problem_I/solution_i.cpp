#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_set>

/**
 * @file solution_i.cpp
 * @date 2025-09-16
 * @author Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to Problem I "Pharaoh's Sliding Chamber" of the ACPC 2024
 * @details 
 * # Problem Description
 * We are given an $N \times M$ grid representing a sliding puzzle. The grid contains movable tiles,
 * immovable tiles, and exactly one empty hole. A special target tile must be moved from its
 * initial position to the bottom-right corner $(N, M)$. A move consists of sliding a movable
 * tile into an adjacent hole. Adjacency includes all 8 directions (horizontal, vertical, and diagonal).
 * We need to find the minimum number of moves to accomplish this, or determine if it is impossible.
 * # Input
 * - The first line contains two integers $N$ and $M$ ($1 \le N, M \le 200$)
 * - The second line contains the initial coordinates of the target tile ($x_{target}, y_{target}$)
 * - The third line contains the initial coordinates of the hole ($x_{hole}, y_{hole}$)
 * - The fourth line contains an integer $Z$ ($0 \le Z \le (N \times M)/2$), the number of immovable tiles.
 * - The next $Z$ lines contain the coordinates of the immovable tiles.
 * # Output
 * - A single integer representing the minimum number of moves, or -1 if the goal is unreachable.
 * # Algorithm
 * The problem is a classic shortest path problem on a state space graph, which can be solved
 * efficiently using a Breadth-First Search (BFS).
 * The state of the system is defined by the positions of the two key moving entities: the target tile
 * and the hole. A state can be represented by a tuple: `(target_x, target_y, hole_x, hole_y)`.
 * The BFS algorithm proceeds as follows:
 * 1.  A queue is initialized with the starting state, including the initial positions of the target
 * and the hole, and a move count of 0.
 * 2.  A `visited` set is used to store all states that have been explored. This is crucial for
 * preventing cycles and redundant computations, as the state space can be large. Since a simple
 * 2D array for visited states is not feasible, a hash-based data structure (like `std::unordered_set`)
 * is used with a custom hash function for the state tuple.
 * 3.  The BFS explores possible moves level by level. From the current state, we consider sliding
 * any movable tile into the hole. A tile is movable if it is not an immovable tile and it is
 * in one of the 8 adjacent positions to the hole.
 * 4.  For each valid move, a new state is generated where the hole's position and the moved tile's
 * position are swapped. If the moved tile is the target tile, its position is updated in the
 * new state.
 * 5.  If a new state has not been visited, it is added to the queue with an incremented move count
 * and marked as visited.
 * 6.  The search continues until a state is reached where the target tile is at the destination
 * $(N, M)$. At this point, the number of moves for that state is the minimum possible, and the
 * program can terminate and output the result.
 * 7.  If the queue becomes empty and the target has not reached its destination, it means the goal
 * is unreachable, and the program outputs -1.
 */

// Custom hash function for the state tuple (target_x, target_y, hole_x, hole_y)
// This is required for using std::unordered_set to store visited states.
struct StateHash {
    size_t operator()(const std::tuple<int, int, int, int>& state) const {
        const int N = 201, M = 201; // Using max dimensions for hashing
        const auto& [tx, ty, hx, hy] = state;
        return ((size_t)tx * N * M * M) + ((size_t)ty * N * M) + ((size_t)hx * M) + hy;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, M;
    std::cin >> N >> M;

    int xt, yt, xh, yh;
    std::cin >> xt >> yt >> xh >> yh;

    int Z;
    std::cin >> Z;

    std::vector<std::vector<bool>> immovable_tiles(N + 1, std::vector<bool>(M + 1, false));
    for (int i = 0; i < Z; ++i) {
        int x, y;
        std::cin >> x >> y;
        immovable_tiles[x][y] = true;
    }

    // A queue for the BFS. Each element stores the state and the number of moves.
    // State: {target_x, target_y, hole_x, hole_y}
    std::queue<std::tuple<int, int, int, int, int>> q;
    
    // A hash set to keep track of visited states to avoid cycles and redundant computations.
    std::unordered_set<std::tuple<int, int, int, int>, StateHash> visited;

    // Initial state
    q.push({xt, yt, xh, yh, 0});
    visited.insert({xt, yt, xh, yh});

    // The 8 possible directions for a tile to slide into the hole
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    while (!q.empty()) {
        auto [ctx, cty, chx, chy, moves] = q.front();
        q.pop();

        // Check if the target tile has reached the destination
        if (ctx == N && cty == M) {
            std::cout << moves << std::endl;
            return 0;
        }

        // Explore all 8 possible moves from the current hole position
        for (int i = 0; i < 8; ++i) {
            int ntx, nty, nhx, nhy;
            int tile_x = chx + dx[i];
            int tile_y = chy + dy[i];

            // Check if the tile to be moved is within grid bounds
            if (tile_x >= 1 && tile_x <= N && tile_y >= 1 && tile_y <= M) {
                // Check if the tile is not an immovable tile
                if (!immovable_tiles[tile_x][tile_y]) {
                    // A valid tile can be moved into the hole.
                    // The new hole position is the old tile position.
                    nhx = tile_x;
                    nhy = tile_y;
                    
                    // The new tile position is the old hole position.
                    // Check if the moved tile is the target tile.
                    if (tile_x == ctx && tile_y == cty) {
                        ntx = chx;
                        nty = chy;
                    } else {
                        ntx = ctx;
                        nty = cty;
                    }

                    // Create the new state tuple
                    std::tuple<int, int, int, int> new_state = {ntx, nty, nhx, nhy};

                    // If the new state has not been visited, add it to the queue
                    if (visited.find(new_state) == visited.end()) {
                        visited.insert(new_state);
                        q.push({ntx, nty, nhx, nhy, moves + 1});
                    }
                }
            }
        }
    }

    // If the queue becomes empty and the target has not been moved to the destination,
    // it means the goal is unreachable.
    std::cout << -1 << std::endl;

    return 0;
}