//
// Created by Edmund Zalenski on 10/9/16.
//

#include <cstdlib>
#include "GameMap.h"

GameMap::GameMap()
    : width{ 5 },
      height{ 5 },
      walls{ { {1, 1}, {3, 1}, {1, 3}, {3, 3} } }
{ }

bool GameMap::is_in_bounds(const std::vector<int>& pos) const
{
    return (pos[0] >= 0 && pos[0] < this->width && pos[1] >= 0 && pos[1] < this->height && !in_walls(pos));
}

bool GameMap::in_walls(const std::vector<int>& pos) const
{
    for(const std::vector<int>& wall : this->walls) {
        if (wall[0] == pos[0] && wall[1] == pos[1]) {
            return true;
        }
    }
    return false;
}

bool GameMap::in_vision_of(const std::vector<int>& pos1, const std::vector<int>& pos2, int range) const
{
    if (pos1[0] == pos2[0] && pos1[1] == pos2[1]) {
        return true;
    }

    if (is_same_col(pos1, pos2)) {
        return (std::abs(pos1[1] - pos2[1]) <= range && !is_wall_between_col(pos1, pos2));
    } else if (is_same_row(pos1, pos2)) {
        return (std::abs(pos1[0] - pos2[0]) <= range && !is_wall_between_row(pos1, pos2));
    }
    return false;
}

bool GameMap::is_same_col(const std::vector<int>& pos1, const std::vector<int>& pos2) const
{
    return (pos1[0] == pos2[0]);
}

bool GameMap::is_same_row(const std::vector<int>& pos1, const std::vector<int>& pos2) const
{
    return (pos1[1] == pos2[1]);
}

bool GameMap::is_wall_between_col(const std::vector<int> &pos1, const std::vector<int> &pos2) const {
    for(int start = std::min(pos1[1], pos2[1]);
        start != std::max(pos1[1], pos2[1]); ++start) {
        if(in_walls({pos1[0], start}))
            return true;
    }
    return false;
}

bool GameMap::is_wall_between_row(const std::vector<int> &pos1, const std::vector<int> &pos2) const {
    for(int start = std::min(pos1[0], pos2[0]);
        start != std::max(pos1[0], pos2[0]); ++start) {
        if(in_walls({start, pos1[1]}))
            return true;
    }
    return false;
}

















