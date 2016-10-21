//
// Created by Edmund Zalenski on 10/9/16.
//

#include "State.h"

State::State(const std::vector<std::shared_ptr<Character>>& team_1,
             const std::vector<std::shared_ptr<Character>>& team_2,
             bool is_team_1)
    : is_team_1{ is_team_1 }
{
    this->team_1 = team_1;
    this->team_2 = team_2;
}

State::State(const State& other_state)
{
    this->team_1 = other_state.team_1;
    this->team_2 = other_state.team_2;
    this->is_team_1 = other_state.is_team_1;
    this->expected_value = other_state.expected_value;
    this->actions_acted = other_state.actions_acted;
    this->children = other_state.children;
}

State::State(const State& other_state, bool new_team_bool)
        : team_1{ other_state.team_1 },
          team_2{ other_state.team_2 },
          is_team_1{ new_team_bool },
          expected_value{ other_state.expected_value },
          actions_acted{ other_state.actions_acted },
          children{ other_state.children }
{ }

const std::vector<State> &State::get_children() const
{
    return this->children;
}

void State::add_child(const State& child)
{
    this->children.push_back(child);
}

void State::clear_children()
{
    this->children.clear();
}

const std::vector<std::shared_ptr<Character>>& State::get_team_1() const
{
    return this->team_1;
}

const std::vector<std::shared_ptr<Character>>& State::get_team_2() const
{
    return this->team_2;
}

double State::get_expected_value() const
{
    return expected_value;
}

void State::set_expected_value(double expected_value)
{
    State::expected_value = expected_value;
}

void State::eval_action(const Action& action,
                        const GameMap& game_map)
{
    this->actions_acted.push_back(action);
    if(action.is_no_action()) {
        return;
    }
    std::shared_ptr<Character> actor;
    if(action.is_actor_team_1()) {
        this->team_1[action.get_actor_index()].reset(new Character(*this->team_1[action.get_actor_index()]));
        actor = this->team_1[action.get_actor_index()];
    } else {
        this->team_2[action.get_actor_index()].reset(new Character(*this->team_2[action.get_actor_index()]));
        actor = this->team_2[action.get_actor_index()];
    }

    if (action.is_movement()) {
        switch (action.get_type()) {
            case Action::move_up:
                actor->move_up();
                break;
            case Action::move_down:
                actor->move_down();
                break;
            case Action::move_right:
                actor->move_right();
                break;
            case Action::move_left:
                actor->move_left();
                break;
            default:
                break;
        }
    } else {
        std::shared_ptr<Character> target;
        if(action.is_target_team_1()) {
            this->team_1[action.get_target_index()].reset(new Character(*this->team_1[action.get_target_index()]));
            target = this->team_1[action.get_target_index()];
        } else {
            this->team_2[action.get_target_index()].reset(new Character(*this->team_2[action.get_target_index()]));
            target = this->team_2[action.get_target_index()];
        }
        if(action.is_attack()) {
            int dmg = std::min(0, (-1 * actor->attributes->at(Character::damage_id)) +
                    target->attributes->at(Character::armor_id));
            target->take_dmg(dmg);
        } else {
            //to be added :(
        }
    }
}

std::unique_ptr<std::vector<std::shared_ptr<Action>>> State::generate_team_1_actions(int char_i,
                                                                    const GameMap& game_map)
{
    bool is_team_1 = true;
    std::shared_ptr<Character> actor = this->team_1[char_i];
    std::vector<std::shared_ptr<Character>> enemies = this->team_2;
    std::unique_ptr<std::vector<std::shared_ptr<Action>>> ret(new std::vector<std::shared_ptr<Action>>());

    if(actor->is_dead() || actor->is_stunned()) {
        ret->emplace_back(new Action(Action::no_action, char_i, is_team_1));
        return ret;
    }

    if(actor->can_move()) {
        if(game_map.is_in_bounds({ actor->position->at(0), actor->position->at(1) - 1}))
            ret->emplace_back(new Action(Action::move_up, char_i, is_team_1));
        if(game_map.is_in_bounds({ actor->position->at(0) + 1, actor->position->at(1)}))
            ret->emplace_back(new Action(Action::move_right, char_i, is_team_1));
        if(game_map.is_in_bounds({ actor->position->at(0), actor->position->at(1) + 1}))
            ret->emplace_back(new Action(Action::move_down, char_i, is_team_1));
        if(game_map.is_in_bounds({ actor->position->at(0) - 1, actor->position->at(1)}))
            ret->emplace_back(new Action(Action::move_left, char_i, is_team_1));
    }

    for(int i = 0; i < enemies.size(); ++i) {
        if(actor->in_range_of(*enemies[i], game_map) && !enemies[i]->is_dead()) {
            ret->emplace_back(new Action(Action::attack, char_i, is_team_1, i));
        }
        //need to do skills
    }

    return ret;
}

std::unique_ptr<std::vector<std::shared_ptr<Action>>> State::generate_team_2_actions(int char_i,
                                                                    const GameMap& game_map)
{
    bool is_team_1 = false;
    std::shared_ptr<Character> actor = this->team_2[char_i];
    std::vector<std::shared_ptr<Character>> enemies = this->team_1;
    std::unique_ptr<std::vector<std::shared_ptr<Action>>> ret(new std::vector<std::shared_ptr<Action>>());

    if(actor->is_dead()) {
        ret->emplace_back(new Action(Action::no_action, char_i, is_team_1));
        return ret;
    }

    if(actor->can_move()) {
        if(game_map.is_in_bounds({ actor->position->at(0), actor->position->at(1) - 1}))
            ret->emplace_back(new Action(Action::move_up, char_i, is_team_1));
        if(game_map.is_in_bounds({ actor->position->at(0) + 1, actor->position->at(1)}))
            ret->emplace_back(new Action(Action::move_right, char_i, is_team_1));
        if(game_map.is_in_bounds({ actor->position->at(0), actor->position->at(1) + 1}))
            ret->emplace_back(new Action(Action::move_down, char_i, is_team_1));
        if(game_map.is_in_bounds({ actor->position->at(0) - 1, actor->position->at(1)}))
            ret->emplace_back(new Action(Action::move_left, char_i, is_team_1));
    }

    for(int i = 0; i < enemies.size(); ++i) {
        if(actor->in_range_of(*enemies[i], game_map) && !enemies[i]->is_dead()) {
            ret->emplace_back(new Action(Action::attack, char_i, is_team_1, i));
        }
        //need to do skills
    }

    return ret;
}

void State::calc_expected_value() {
    std::unordered_map<std::string, int> dps_map;
    dps_map["Archer"] = 100;
    dps_map["Assassin"] = 125;
    dps_map["Druid"] = 60;
    dps_map["Enchanter"] = 45;
    dps_map["Paladin"] = 50;
    dps_map["Sorcerer"] = 96;
    dps_map["Warrior"] = 75;
    dps_map["Wizard"] = 100;

    double our_ev = 0;
    for(const std::shared_ptr<Character>& character : this->team_1) {
        our_ev += (((double)character->attributes->at(Character::health_id)/character->attributes->at
                (Character::armor_id)) *
                dps_map[*character->class_id]);
    }

    double enemy_ev = 0;
    for(const std::shared_ptr<Character>& character : this->team_2) {
        enemy_ev += (((double)character->attributes->at(Character::health_id)/character->attributes->at
                (Character::armor_id)) *
                     dps_map[*character->class_id]);
    }

    this->expected_value = (our_ev - enemy_ev);
}

json State::get_actions() const
{
    json ret;
    for(const Action& acted : this->actions_acted) {
        json action_json;
        std::shared_ptr<Character> actor;
        std::shared_ptr<Character> target;
        if(!acted.is_no_action()) {
            if (acted.is_actor_team_1()) {
                actor = this->team_1[acted.get_actor_index()];
            } else {
                actor = this->team_2[acted.get_actor_index()];
            }
            if (acted.is_movement()) {
                json position_json;
                position_json.push_back(actor->position->at(0));
                position_json.push_back(actor->position->at(1));
                action_json["Action"] = "Move";
                action_json["CharacterId"] = actor->attributes->at(Character::id);
                action_json["Location"] = position_json;
            } else if (acted.is_attack()) {
                if (acted.is_target_team_1()) {
                    target = this->team_1[acted.get_target_index()];
                } else {
                    target = this->team_2[acted.get_target_index()];
                }
                action_json["Action"] = "Attack";
                action_json["CharacterId"] = actor->attributes->at(Character::id);
                action_json["TargetId"] = target->attributes->at(Character::id);
            } else {
                //to be added
            }
        }
        else {
            action_json = json::object();
        }
        ret.push_back(action_json);
    }
    return ret;
}

void State::clear_actions() {
    this->actions_acted.clear();
}

std::vector<State> &State::get_change_children() {
    return this->children;
}



