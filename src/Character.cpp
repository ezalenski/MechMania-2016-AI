//
// Created by Edmund Zalenski on 10/9/16.
//

#include "Character.h"

Character::Character(json character_json)
{
    this->abilities = std::make_shared<std::vector<std::pair<int, int>>>();
    this->attributes = std::make_shared<std::vector<int>>(NUM_ATTRIBUTES);
    this->name = std::make_shared<std::string>(character_json["Name"].get<std::string>());
    this->class_id = std::make_shared<std::string>(character_json["ClassId"].get<std::string>());
    this->attributes->at(Character::id) = character_json["Id"];
    json ability_json = character_json["Abilities"];
    for(auto it = ability_json.begin();
        it != ability_json.end();
        ++it)
    {

        this->abilities->push_back(std::make_pair(std::stoi(it.key()), it.value()));
    }
    this->position = std::make_shared<std::vector<int>>(character_json["Position"].get<std::vector<int>>());
    json attributes_json = character_json["Attributes"];
    this->attributes->at(Character::rooted_id) = attributes_json["Rooted"];
    this->attributes->at(Character::stunned_id) = attributes_json["Stunned"];
    this->attributes->at(Character::silenced_id) = attributes_json["Silenced"];
    this->attributes->at(Character::armor_id) = attributes_json["Armor"];
    this->attributes->at(Character::max_health_id) = attributes_json["MaxHealth"];
    this->attributes->at(Character::health_id) = attributes_json["Health"];
    this->attributes->at(Character::damage_id) = attributes_json["Damage"];
    this->attributes->at(Character::attack_range_id) = attributes_json["AttackRange"];
    this->attributes->at(Character::movement_speed_id) = attributes_json["MovementSpeed"];
}

bool Character::operator==(const Character &rhs) const {
    return *name == *rhs.name &&
           *class_id == *rhs.class_id &&
           std::equal(abilities->begin(), abilities->end(), rhs.abilities->begin()) &&
           std::equal(position->begin(), position->end(), rhs.position->begin()) &&
           std::equal(attributes->begin(), attributes->end(), rhs.attributes->begin());
}

bool Character::operator!=(const Character &rhs) const {
    return !(rhs == *this);
}

Character::Character(const Character& other_char)
    : name{ other_char.name },
      class_id{ other_char.class_id },
      abilities{ other_char.abilities },
      position{ other_char.position },
      attributes{ other_char.attributes }
{ }

bool Character::is_dead() const
{
    return (this->attributes->at(Character::health_id) <= 0);
}

bool Character::can_move() const
{
    return !(this->attributes->at(Character::stunned_id) | this->attributes->at(Character::rooted_id));
}

bool Character::in_range_of(const Character& enemy,
                            const GameMap& game_map) const
{
    return game_map.in_vision_of(*this->position, *enemy.position, this->attributes->at(attack_range_id));
}

void Character::move_up()
{
    std::vector<int> new_position = *this->position;
    new_position[1] -= 1;
    this->position.reset();
    this->position = std::make_shared<std::vector<int>>(new_position);
}

void Character::move_down()
{
    std::vector<int> new_position = *this->position;
    new_position[1] += 1;
    this->position.reset();
    this->position = std::make_shared<std::vector<int>>(new_position);
}

void Character::move_right()
{
    std::vector<int> new_position = *this->position;
    new_position[0] += 1;
    this->position.reset();
    this->position = std::make_shared<std::vector<int>>(new_position);
}

void Character::move_left()
{
    std::vector<int> new_position = *this->position;
    new_position[0] -= 1;
    this->position.reset();
    this->position = std::make_shared<std::vector<int>>(new_position);
}

void Character::take_dmg(int damage) {
    std::vector<int> after_damage = *this->attributes;
    after_damage.at(Character::health_id) += damage;
    this->attributes.reset();
    this->attributes = std::make_shared<std::vector<int>>(after_damage);
}

bool Character::is_stunned() const {
    return this->attributes->at(Character::stunned_id);
}



















