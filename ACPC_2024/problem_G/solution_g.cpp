#include <iostream>

/**
 * @file solution_g.cpp
 * @date 2025-09-12
 * @author Allie Phenish (alliephenish@gmail.com)
 * @brief Solution to Problem G "Pharaoh's Parabolic Games" of the ACPC 2024
 * @details 
 * # Problem Description
 * We are tasked with determining if a ball, following a parabolic trajectory, will land on a
 * rectangular table on the $xy$-plane. We are given the starting point $A$ and the highest point $B$
 * of the trajectory. Due to the symmetry of a parabola, the landing point $C$ on the $xy$-plane
 * ($z=0$) will be a reflection of the starting point $A$ across the highest point $B$ in the
 * horizontal plane. We must calculate the coordinates of point $C$ and check if they fall within
 * the given rectangular boundaries of the table.
 * # Input
 * - The first line contains four integers: $x_{min}$, $x_{max}$, $y_{min}$, $y_{max}$
 * ($-10^9 \le x_{min} < x_{max} \le 10^9$, $-10^9 \le y_{min} < y_{max} \le 10^9$)
 * defining the table's boundaries.
 * - The second line contains an integer $q$ ($1 \le q \le 2 \cdot 10^5$), the number of queries.
 * - For each of the $q$ queries:
 * - The coordinates of point $A=(x_A, y_A, 0)$ ($-10^9 \le |x_A|, |y_A| \le 10^9$).
 * - The coordinates of point $B=(x_B, y_B, z_B)$ ($-10^9 \le |x_B|, |y_B| \le 10^9$, $0 < z_B \le 10^9$).
 * # Output
 * - For each query, print a single line with "YES" if the ball lands on the table, and "NO" otherwise.
 * # Algorithm
 * The problem states that the ball's trajectory is a parabola with its vertex at point $B$.
 * A key property of a parabola is its symmetry. The trajectory of the ball is symmetric about
 * a vertical line passing through its vertex $B$. This implies that the horizontal path of the ball,
 * from the starting point $A$ to the landing point $C$, is symmetric with respect to the horizontal
 * coordinates of the vertex $B$.
 * * Let the starting point be $A=(x_A, y_A, 0)$ and the vertex be $B=(x_B, y_B, z_B)$.
 * The horizontal displacement from the starting point $A$ to the vertex $B$ is:
 * - $\Delta x = x_B - x_A$
 * - $\Delta y = y_B - y_A$
 * * Due to the symmetry of the parabola, the horizontal displacement from the vertex $B$ to the
 * landing point $C$ will be the same. Let the landing point be $C=(x_C, y_C, 0)$. The coordinates
 * of $C$ can be calculated by adding the displacement to the vertex coordinates:
 * - $x_C = x_B + \Delta x = x_B + (x_B - x_A) = 2x_B - x_A$
 * - $y_C = y_B + \Delta y = y_B + (y_B - y_A) = 2y_B - y_A$
 * * The solution is straightforward:
 * 1. Read the table boundaries ($x_{min}, x_{max}, y_{min}, y_{max}$).
 * 2. Read the number of queries, $q$.
 * 3. Loop $q$ times:
 * a. Read the coordinates of points $A$ and $B$.
 * b. Calculate the landing coordinates $(x_C, y_C)$ using the formulas above.
 * c. Since the input coordinates can be large ($10^9$), the intermediate values in the calculation
 * ($2x_B - x_A$) can exceed the capacity of a standard 32-bit integer. Therefore, we use `long long`
 * for all coordinate variables to prevent integer overflow.
 * d. Check if the calculated landing point is within the table boundaries:
 * `$x_{min} \le x_C \le x_{max}$ AND $y_{min} \le y_C \le y_{max}$`
 * e. Print "YES" if the condition is true, and "NO" otherwise.
 * This approach has a time complexity of $O(q)$ since each query is processed in constant time,
 * making it well within the time limit.
 */

int main() {
    // Fast I/O for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long x_min, x_max, y_min, y_max;
    std::cin >> x_min >> x_max >> y_min >> y_max;

    int q;
    std::cin >> q;

    for (int i = 0; i < q; ++i) {
        long long x_a, y_a, x_b, y_b, z_b;
        std::cin >> x_a >> y_a >> x_b >> y_b >> z_b;

        // Calculate the landing coordinates using the symmetry of the parabola.
        long long x_c = 2 * x_b - x_a;
        long long y_c = 2 * y_b - y_a;

        // Check if the landing point falls within the table boundaries.
        if (x_c >= x_min && x_c <= x_max && y_c >= y_min && y_c <= y_max) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}