#include <cstddef>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>

#include <functional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <unordered_map>

#include <boost/container_hash/hash.hpp>

size_t alfa{ 0 };

struct point {
  point() = default;
  point(int64_t x_coord, int64_t y_coord)
    : x{ x_coord }
    , y{ y_coord }
  { }

  int64_t x, y;
};

size_t hash_point(const point& p) {
    size_t seed{ 0 };
    boost::hash_combine(seed, std::floor(p.x / alfa));
    boost::hash_combine(seed, std::floor(p.y / alfa));

    return seed;
}

int main (int argc, char* argv[]) { 
  
  assert((argc == 3));
  alfa = std::atoi(argv[2]);
  double total_distance{ 0 };
  size_t visited_count{ 0 };
  
  // all_points contains all the points received as input. Note that further in the algorithm 
  // instead of using references to points -when possible- indexes of all_points are used
  std::vector<point> all_points;

  // a cell is defined as a square of side alfa, containing all the points in a range
  // [ (i*alfa, j*alfa), (i*alfa+alfa, j*alfa+alfa) ]
  // cells is a bucket list containing buckets of ids of points inside the same cell
  // the key for the map is attained using hash_point function (see above)
  std::unordered_map<size_t, std::vector<size_t>> cells;

  // visited[i] == true if all_points[i] is visited 
  std::vector<bool> visited;
  
  // parents[i] = j means that all_points[i] is first visited by all_points[j]
  // this act sort of as a container of edges
  std::vector<int64_t> parents;

  // the priority queue contains pairs distance-parent_id, where parent_id is the id of the
  // second point in the edge of lenght double. the other point's id can be found using parent map
  std::priority_queue<
    std::pair<double, size_t>, 
    std::vector<std::pair<double, size_t>>, 
    std::greater<std::pair<double, size_t>>
      > queue;

  // initialize all_points
  std::ifstream input_file;
  input_file.open(argv[1]);
  if ( !input_file.is_open() ) {
    std::cerr << "Couldn't open the file'" << std::endl;
    return 0;
  }
  
  std::string line;
  while (std::getline(input_file, line)) {
    std::istringstream line_ss(line);
    int64_t x, y;
    char _;
    line_ss >> _ >> x >> _ >> y >> _;
    all_points.push_back(point{ x, y });
    visited.push_back(false);
    parents.push_back(-1);
  }
  
  input_file.close();
  
  // Inizialize cells
  for (int i{ 0 }; i<all_points.size(); i++) {
    cells[hash_point(all_points[i])].push_back(i);
  }

  // main loop

  size_t curr_point_index{ 0 };
  queue.push( std::pair<double, size_t>{0, 0} );

  while( !queue.empty() && visited_count < all_points.size() ) {
    
    auto best_next = queue.top();
    queue.pop(); 
    if (visited[best_next.second]) continue;
    visited[best_next.second] = true;
    visited_count++;
    total_distance += best_next.first;
    curr_point_index = best_next.second;
  
    for (int i{ -1 }; i<= 1; i++) {
      for (int j{ -1 }; j<= 1; j++) {
        int64_t new_point_x = all_points[curr_point_index].x-i*alfa;
        int64_t new_point_y = all_points[curr_point_index].y-j*alfa;

        if (new_point_x >= 0 && new_point_y >= 0) { 
          point new_point{ new_point_x, new_point_y };
          auto it = cells.find( hash_point(new_point) );

          if (it != cells.end()) {
            for (auto neighboor_index : it->second) {
              if (neighboor_index == curr_point_index) continue;
              double distance = std::sqrt (
                  std::pow( (all_points[curr_point_index].x - all_points[neighboor_index].x), 2 ) + 
                  std::pow( (all_points[curr_point_index].y - all_points[neighboor_index].y), 2 ) 
                  );
              if (visited[neighboor_index] == false && distance <= alfa) {
                parents[neighboor_index] = curr_point_index;
                queue.push( std::pair<double, size_t>{distance, neighboor_index} );
              }
            }
          }
        }
      }
    }
  }

  std::cout << "Total distance: " << total_distance << std::endl;
  return 0;
}
