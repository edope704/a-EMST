# α-EMST (Alpha-Euclidean Minimum Spanning Tree)

An efficient C++ implementation for computing the Euclidean Minimum Spanning Tree (EMST) of a given set of points in the plane, subject to a maximum edge weight constraint $\alpha$.

## Algorithm & Complexity

The implementation expects $O(n \log n)$ time complexity and is optimized for large datasets by utilizing:
*   **Prim's Algorithm**: Greedily expands the spanning tree using a standard min-heap priority queue.
*   **Grid-Based Spatial Hashing**: The 2D plane is partitioned into a uniform grid with cell dimensions $\alpha \times \alpha$. Coordinates are hashed into these buckets, constraining spatial queries to adjacent cells. This reduces the required edge evaluations from $O(n^2)$ down to an expected $O(n)$ subset.

## Dependencies

*   A C++17 compatible compiler.
*   **Boost C++ Libraries**: Specifically `<boost/container_hash/hash.hpp>` for `boost::hash_combine`.

## Build and Execution

```bash
# Compilation
g++ -std=c++17 -O3 a-EMST.cpp -o a-EMST

# Execution
./a-EMST <input_file_path> <alpha_value>
```

## I/O Specifications

**Input**: A standard text file defining the vertices. Each line represents a point with integer coordinates, strictly formatted as `(x,y)`.

*Example (`inputs/input_n10.txt`):*
```text
(0,1)
(3,2)
(2,5)
```

**Output**: 
Prints the sum of the weights of the computed $\alpha$-EMST as a double-precision floating point. If the point set contains components that remain disconnected under the $\alpha$ constraint, the algorithm will output `FAIL`.

## Roadmap / Current State
- [ ] Finalize standard `FAIL` condition implementation for disconnected subgraphs.
- [ ] Implement explicit structural output (edge list) for $n \le 10$.