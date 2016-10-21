//
// Created by Edmund Zalenski on 10/9/16.
//

#ifndef DECISIONTREE_STATE_H
#define DECISIONTREE_STATE_H


#include "Character.h"
#include "Action.h"
#include "json.hpp"

using json = nlohmann::json;

class State {
    //fields
    bool is_team_1;
    double expected_value;
    std::vector<std::shared_ptr<Character>> team_1;
    std::vector<std::shared_ptr<Character>> team_2;
    std::vector<State> children;

public:
    //construtors
    State(const std::vector<std::shared_ptr<Character>>&, const std::vector<std::shared_ptr<Character>>&, bool);
    State(const State&);
    State(const State&, bool new_team_bool);

    //methods
    std::unique_ptr<std::vector<std::shared_ptr<Action>>> generate_team_1_actions(int, const GameMap&);
    std::unique_ptr<std::vector<std::shared_ptr<Action>>> generate_team_2_actions(int, const GameMap&);
    void eval_action(const Action&, const GameMap&);
    const std::vector<State> & get_children() const;
    std::vector<State>& get_change_children();
    void add_child(const State& child);
    void clear_children();
    const std::vector<std::shared_ptr<Character>> & get_team_1() const;
    const std::vector<std::shared_ptr<Character>> & get_team_2() const;
    double get_expected_value() const;
    void calc_expected_value();
    void set_expected_value(double expected_value);
    json get_actions() const;
    void clear_actions();

    std::vector<Action> actions_acted;
};


#endif //DECISIONTREE_STATE_H
