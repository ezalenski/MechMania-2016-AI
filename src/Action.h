//
// Created by Edmund Zalenski on 10/9/16.
//

#ifndef DECISIONTREE_ACTION_H
#define DECISIONTREE_ACTION_H


class Action {
public:
    enum action_t {no_action, move_up, move_down, move_right, move_left, attack, ability};

private:
    action_t type;
    int actor_index;
    bool actor_is_team_1;
    int target_index;
    bool target_is_team_1;
    //ability_id ?

public:
    Action(Action::action_t, int, bool);
    Action(Action::action_t, int, bool, int);
    Action(Action::action_t, int, bool, int, bool);
    Action(const Action&);
    bool is_movement() const;
    bool is_attack() const;
    bool is_ability() const;
    bool is_no_action() const;
    bool is_actor_team_1() const;
    bool is_target_team_1() const;
    int get_actor_index() const;
    int get_target_index() const;
    action_t get_type() const;

};


#endif //DECISIONTREE_ACTION_H
