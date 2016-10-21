//
// Created by Edmund Zalenski on 10/9/16.
//

#ifndef DECISIONTREE_DECISIONTREE_H
#define DECISIONTREE_DECISIONTREE_H

#include <vector>
#include "State.h"
#include "GameMap.h"
#include "Character.h"

class DecisionTree {
    GameMap game_map;
    //maybe can just create a non member helper function
    State* _generate_to_level(State*,
                              double,
                              State*,
                              double,
                              State*,
                              bool,
                              int,
                              int,
                              double,
                              double);

public:
    DecisionTree(const State&);
    State* generate_to_level(int, double);
    State _initial_state;
};


#endif //DECISIONTREE_DECISIONTREE_H
