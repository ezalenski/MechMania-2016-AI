//
// Created by Edmund Zalenski on 10/9/16.
//

#ifndef DECISIONTREE_GAMEMAP_H
#define DECISIONTREE_GAMEMAP_H


#include <vector>

class GameMap {
    std::vector<std::vector<int>> walls;
    int width;
    int height;
    bool is_same_col(const std::vector<int>&, const std::vector<int>&) const;
    bool is_same_row(const std::vector<int>&, const std::vector<int>&) const;
    bool in_walls(const std::vector<int>&) const;
    bool is_wall_between_col(const std::vector<int> &pos1, const std::vector<int> &pos2) const;
    bool is_wall_between_row(const std::vector<int> &pos1, const std::vector<int> &pos2) const;

public:
    GameMap();
    bool is_in_bounds(const std::vector<int>&) const;
    bool in_vision_of(const std::vector<int>&, const std::vector<int>&, int) const;
};


#endif //DECISIONTREE_GAMEMAP_H
