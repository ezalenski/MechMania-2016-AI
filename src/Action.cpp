//
// Created by Edmund Zalenski on 10/9/16.
//

#include "Action.h"
#include <stdexcept>

//must be movement
Action::Action(Action::action_t action_type,
               int actor_i,
               bool is_team_1)
{
    if(action_type == attack || action_type == ability) {
        throw std::invalid_argument("invalid action_type");
    }
    this->type = action_type;
    this->actor_index = actor_i;
    this->actor_is_team_1 = is_team_1;
    this->target_index = -1;
}

Action::Action(Action::action_t action_type,
               int actor_i,
               bool is_team_1,
               int target_i)
{
    if(action_type != attack) {
        throw std::invalid_argument("invalid action_type");
    }
    this->type = action_type;
    this->actor_index = actor_i;
    this->actor_is_team_1 = is_team_1;
    this->target_index = target_i;
    this->target_is_team_1 = !is_team_1;
}

Action::Action(const Action& other_action)
    : type{ other_action.type },
      actor_index{ other_action.actor_index },
      actor_is_team_1{ other_action.actor_is_team_1 },
      target_index{ other_action.target_index }
{ }

Action::Action(Action::action_t action_type,
               int actor_i,
               bool actor_is_team_1,
               int target_i,
               bool target_is_team_1)
{
    if(action_type != ability) {
        throw std::invalid_argument("invalid action_type");
    }
    this->type = action_type;
    this->actor_index = actor_i;
    this->actor_is_team_1 = actor_is_team_1;
    this->target_index = target_i;
    this->target_is_team_1 = target_is_team_1;
}


bool Action::is_movement() const
{
    return (this->type > no_action && this->type < attack);
}

bool Action::is_attack() const
{
    return this->type == attack;
}

bool Action::is_ability() const
{
    return this->type == ability;
}

bool Action::is_no_action() const
{
    return this->type == no_action;
}

bool Action::is_actor_team_1() const
{
    return this->actor_is_team_1;
}

bool Action::is_target_team_1() const
{
    return this->target_is_team_1;
}


int Action::get_target_index() const {
    return target_index;
}

int Action::get_actor_index() const {
    return actor_index;
}

Action::action_t Action::get_type() const {
    return type;
}