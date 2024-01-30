#include "learned_model/model_connections_helpers.hpp"

std::vector<double> fillVectorUsingMap(
    std::vector<double> vector1, std::vector<double> vector2, std::vector<int> map, bool inverse)
  {
    // index in "map" is index in "vector1" and value in "map" is index in "vector2"
    // inverse = 0 from 1 -> 2; inverse = 1 from 2 -> 1
    for (std::size_t idx = 0; idx < map.size(); idx++) {
      if (map[idx] == -1) continue;
      inverse ? vector1[idx] = vector2[map[idx]] : vector2[map[idx]] = vector1[idx];
    }
    return inverse ? vector1 : vector2;
  }

  std::vector<int> createConnectionsMap(
    std::vector<char *> connection_names_1, std::vector<char *> connection_names_2)
  {
    std::vector<int> connection_map;
    // index in "connection_map" is index in "connection_names_2" and value in "connection_map" is
    // index in "connection_names_1"
    for (auto name_2 : connection_names_2) {
      int mapped_idx = -1;  // -1 means that we cannot create a connection between some signals
      for (std::size_t NAME_1_IDX = 0; NAME_1_IDX < connection_names_1.size(); NAME_1_IDX++) {
        if (strcmp(name_2, connection_names_1[NAME_1_IDX]) == 0) {  // 0 means strings are the same
                                                                    // and we can create connection
          mapped_idx = NAME_1_IDX;
          break;
        }
      }
      connection_map.push_back(mapped_idx);
    }
    return connection_map;
  }