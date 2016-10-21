//
// Created by Edmund Zalenski on 10/9/16.
//

#include <string>
#include <vector>
#include <unordered_map>
#include "json.hpp"
#include "GameMap.h"

#ifndef DECISIONTREE_CHARACTER_H
#define DECISIONTREE_CHARACTER_H

using json = nlohmann::json;

class Character {
public:
#define NUM_ATTRIBUTES 10
    enum attribute_id {
        id,
        rooted_id,
        stunned_id,
        silenced_id,
        armor_id,
        max_health_id,
        health_id,
        damage_id,
        attack_range_id,
        movement_speed_id
    };
    std::shared_ptr<std::string> name;
    std::shared_ptr<std::string> class_id;
    //debuffs
    std::shared_ptr<std::vector<std::pair<int, int>>> abilities;
    //casting
    //buffs
    std::shared_ptr<std::vector<int>> position;
    std::shared_ptr<std::vector<int>> attributes;

    //methods
    Character(json);
    Character(const Character&);
    bool is_dead() const;
    bool is_stunned() const;
    bool can_move() const;
    bool in_range_of(const Character&, const GameMap&) const;

    void move_up();

    void move_down();

    void move_right();

    void move_left();

    void take_dmg(int damage);

    bool operator==(const Character &rhs) const;

    bool operator!=(const Character &rhs) const;
};


#endif //DECISIONTREE_CHARACTER_H