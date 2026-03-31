#include <string>
#include <algorithm>
#include <cassert>
#include <charconv>
#include <vector>
#include <cmath>
#include <iostream>

namespace {
  constexpr int office_to_corridor = 5;
  constexpr int corridor_to_corridor = 5;
  constexpr int corridor_to_elevator = 8;
  constexpr int tower_to_tower = 100;
  constexpr int floor_width = 14;
  constexpr int floor_limit = 1000;
}

using namespace std;

std::vector<int> partial_length(const std::vector<std::string> &path,  int** w) {
  if(path.size() == 0) return {};
  std::vector<int> costs(path.size(), -1);
  costs[0] = 0;
  for(int i = 1; i < path.size(); ++i)
  {
    auto n1 = path[i-1];
    auto n2 = path[i];
    int dist = -1;
    char * nil;
    if(n1[1] == 'C' && n2[1] == 'C') dist = corridor_to_corridor;
    else if( (n1[1] == 'C' && n2[1] == 'E') || (n2[1] == 'C' && n1[1] == 'E') ) dist = corridor_to_elevator;
    else if( n1[1] == 'E' && n2[1] == 'E' && n1[0] != n2[0] ) dist = tower_to_tower;
    else if( n1[1] <= '9' && n2[1] <= '9' ) dist = w[0][0];
    else if( (n1[1] == 'C' && n2[1] <= '9') || (n1[1] <= '9' && n2[1] <= 'C') ) dist = office_to_corridor;
    else if( (n1[1] == 'E' && n2[1] == 'E' && n1[0] == n2[0]) ) dist = w[ (n1[0] - 'A') * 2 + (n1.back() - '1') ][ strtol(n1.c_str() + 2, &nil, 10)/100 - 1 ];
    if(dist == -1) {
      cout << "suspicious step from " << n1 << " to " << n2 << "\n";
    }
    costs[i] = costs[i - 1] + dist;
  }
  return costs;
}

enum node_type {office, elevator, corridor, invalid};
auto parse_node(string node) {
  int numeric;
  auto [ptr, ec] = from_chars(node.data() + (node[1] <= '9' ? 1 : 2), node.data() + node.size(), numeric);
  node_type type = node[1] == 'C' ? corridor : (node[1] == 'E' ? elevator : (node[1] >= '0' && node[1] <= '9' ? office : invalid));
  if(type == invalid) cout << "Second char illegal.\n";
  if(ec != std::errc()) {type = invalid; cout << "unparsable.\n";}
  if(node[0] < 'A' || node[0] > 'B') {type = invalid; cout << "Illegal tower.\n";}
  int floor = numeric / 100 - 1;
  int room = numeric % 100 - 1;
  if(floor < 0) {type = invalid; cout << "negative floor.\n";}
  if(room > 27 || room < 0) {type = invalid; cout << "Room out of range.\n";}
  if(type == elevator && room > 1) {type = invalid; cout <<"elevator > 02";}
  if(type == corridor && room > 13) {type = invalid; cout << "corr out of range.\n";}
  return tuple{node[0], type, floor, room};
}

auto check_path(const std::vector<std::string> &path) {
  for(int i = 1; i < path.size(); ++i)
  {
    auto n1 = path[i-1];
    auto n2 = path[i];
    auto [n1_bld, n1_type, n1_floor, n1_room] = parse_node(n1);
    auto [n2_bld, n2_type, n2_floor, n2_room] = parse_node(n2);
    if(n1_type == invalid) return tuple{false, n1+string(" illegal node.")};
    if(n2_type == invalid) return tuple{false, n2+string(" illegal node.")};
    if(n1_type == elevator) {
      if(n2_type == elevator && n1_bld == n2_bld && abs(n1_floor - n2_floor) != 1)
        return tuple{false, n1+" to "+n2+" illegal step."};
      if(n2_type == elevator && n1_bld != n2_bld && (n1_floor != 0 || n2_floor != 0))
        return tuple{false, n1+" to "+n2+" illegal step."};
      if(n2_type == corridor && (n1_bld != n2_bld || (n1_room == 0 && n2_room != 0) || (n1_room == 1 && n2_room != 13)))
        return tuple{false, n1+" to "+n2+" illegal step."};
      if(n2_type == office)
        return tuple{false, n1+" to "+n2+" illegal step."};
    }
    if(n1_type == corridor) {
      if(n2_type == corridor && (n1_bld != n2_bld || n1_floor != n2_floor || abs(n1_room - n2_room) != 1))
        return tuple{false, n1+" to "+n2+" illegal step."};
      if(n2_type == office && (n1_bld != n2_bld || n1_floor != n2_floor || (n2_room % 14) != n1_room))
        return tuple{false, n1+" to "+n2+" illegal step."};
      if(n2_type == elevator && (n1_bld != n2_bld || n1_floor != n2_floor || !( (n1_room == 0 && n2_room == 0) || (n1_room == 13 && n2_room == 1) )))
        return tuple{false, n1+" to "+n2+" illegal step."};
    }
    if(n1_type == office) {
      if(n2_type == elevator)
        return tuple{false, n1+" to "+n2+" illegal step."};
      if(n2_type == corridor && (n1_bld != n2_bld || n1_floor != n2_floor || (n1_room % 14) != n2_room))
        return tuple{false, n1+" to "+n2+" illegal step."};
      if(n2_type == office) {
        if(n1_bld == n2_bld)
          return tuple{false, n1+" to "+n2+" illegal step."};
        if (n1_bld == 'A') {
          if(n1_floor % 10 != 9)
            return tuple{false, n1+" to "+n2+" illegal step."};
          if(n1_room != 21 && n1_room != 22)
            return tuple{false, n1+" to "+n2+" illegal step."};
          if(n1_room == 21 && (n2_floor != n1_floor - 1 || n2_room != 7))
            return tuple{false, n1+" to "+n2+" illegal step."};
          if(n1_room == 22 && (n2_floor != n1_floor + 1 || n2_room != 8))
            return tuple{false, n1+" to "+n2+" illegal step."};
        }
        if (n1_bld == 'B') {
          if(n1_floor % 10 != 8 && (n1_floor % 10 != 0 || n1_floor == 0))
            return tuple{false, n1+" to "+n2+" illegal step."};
          if(n1_floor % 10 == 8 && (n1_room != 7 || n2_floor != n1_floor + 1 || n2_room != 21))
            return tuple{false, n1+" to "+n2+" illegal step."};
          if(n1_floor % 10 == 0 && (n1_room != 8 || n2_floor != n1_floor - 1 || n2_room != 22))
            return tuple{false, n1+" to "+n2+" illegal step."};
        }
      }
    }
  }
  return tuple{true, string("NULL")};
}

bool goes_up(const vector<string>& path, string start, string end) {
  char *nil;
  int m = max(strtol(start.c_str() + 1, &nil, 10)/100, strtol(end.c_str() + 1, &nil, 10)/100);
  return any_of(path.begin(), path.end(), [&](const string& n) { return strtol(n.c_str() + 1 + (n[1] >= 'C'), &nil, 10)/100 > m; });
}
