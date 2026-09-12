#include <array>
#include <cstddef>
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>

#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

#include <boost/container_hash/hash.hpp>

size_t alfa{ 0 };

struct point {
  point() = default;
  point(size_t x_coord, size_t y_coord)
    : x{ x_coord }
    , y{ y_coord }
  { }

  size_t x, y;
  bool visited;

  bool operator==(const point& p) const { 
    return (this->x == p.x && this->y == p.y); 
  }
};

struct hash_point {
  size_t operator() (const point& p) const {
    size_t seed{ 0 };
    boost::hash_combine(seed, std::floor(p.x / alfa));
    boost::hash_combine(seed, std::floor(p.y / alfa));

    return seed;
  }
};

int main (int argc, char* argv[]) { 
  
  assert((argc == 3));

  alfa = std::atoi(argv[2]);
  
  // all_points contains all the points received as input. Note that further in the algorithm 
  // instead of using references to points -when possible- indexes of all_points are used
  std::vector<point> all_points;
  // a cell is defined as a square of side alfa, containing all the points in a range
  // [ (i*alfa, j*alfa), (i*alfa+alfa, j*alfa+alfa) ]
  // cells is a bucket list containing buckets of ids of points inside the same cell
  // the key for the mapped is attained using hash_point function (see above)
  std::unordered_map<size_t, std::vector<size_t>> cells;
  // visited[i] == true if all_points[i] is visited 
  std::vector<bool> visited;
  // the priority queue contains pairs distance-parent_id, where parent_id is the id of the
  // second point in the edge of lenght double. the other point's id can be found using parent map
  std::priority_queue<
    std::pair<double, size_t>, 
    std::vector<std::pair<double, size_t>>, 
    std::greater<std::pair<double, size_t>>
      > queue;
  // maps parents ids with childs ids
  // this act sort of as a container of edges
  std::unordered_map<size_t, size_t> parent;

  // initialize all_points
  std::ifstream input_file;
  input_file.open(argv[1]);
  
  std::string line;
  while (std::getline(input_file, line)) {
    std::istringstream line_ss(line);
    size_t x, y;
    char _;
    line_ss >> _ >> x >> _ >> y >> _;
    all_points.push_back(point{ x, y });
    visited.push_back(false);
  }
  
  input_file.close();
  
  // Inizialize cells
  hash_point hash;
  for (int i{ 0 }; i<all_points.size(); i++) {
    cells[hash(all_points[i])].push_back(i);
  }

  // main loop
  
  // 1 set a first point
  // 2 for each point P in the adjacent cells, calculate the distance D
  // 3 if distance <= alfa and P is not yet visited, add (D,P) to the queue 
  // 4 pop from the queue, and repeat from 1 with the popped point
  
   

  // return 0;
}

