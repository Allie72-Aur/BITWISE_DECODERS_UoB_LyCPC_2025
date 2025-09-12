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
 */
