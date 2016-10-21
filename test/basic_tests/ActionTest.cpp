//
// Created by Edmund Zalenski on 10/9/16.
//
#include <gtest/gtest.h>
#include "Action.h"

TEST (ActionTest, ActionTest_Exception_Test) {
    Action* action_test;
    ASSERT_THROW((action_test = new Action(Action::attack, 0, true)), std::invalid_argument);
    ASSERT_THROW((action_test = new Action(Action::ability, 0, true)), std::invalid_argument);
    ASSERT_THROW((action_test = new Action(Action::move_up, 0, true, 0)), std::invalid_argument);
    ASSERT_THROW((action_test = new Action(Action::no_action, 0, true, 0)), std::invalid_argument);
    ASSERT_THROW((action_test = new Action(Action::ability, 0, true, 0)), std::invalid_argument);
    ASSERT_THROW((action_test = new Action(Action::attack, 0, true, 0, true)), std::invalid_argument);
}

TEST (ActionTest, ActionTest_IsMovement_Test) {
    Action* no_action = new Action(Action::no_action, 0, true);
    Action* attack = new Action(Action::attack, 0, true, 0);
    Action* movement_left = new Action(Action::move_left, 0, true);
    Action* movement_up = new Action(Action::move_up, 0, true);
    ASSERT_FALSE(no_action->is_movement());
    ASSERT_FALSE(attack->is_movement());
    ASSERT_TRUE(movement_left->is_movement());
    ASSERT_TRUE(movement_up->is_movement());
    delete no_action;
    delete attack;
    delete movement_left;
    delete movement_up;
}

TEST (ActionTest, ActionTest_IsAttack_Test) {
    Action* no_action = new Action(Action::no_action, 0, true);
    Action* attack = new Action(Action::attack, 0, true, 0);
    Action* ability = new Action(Action::ability, 0, true, 0, true);
    Action* movement_up = new Action(Action::move_up, 0, true);
    ASSERT_FALSE(no_action->is_attack());
    ASSERT_TRUE(attack->is_attack());
    ASSERT_FALSE(ability->is_attack());
    ASSERT_FALSE(movement_up->is_attack());
    delete no_action;
    delete attack;
    delete ability;
    delete movement_up;
}

TEST (ActionTest, ActionTest_IsAbility_Test) {
    Action* no_action = new Action(Action::no_action, 0, true);
    Action* attack = new Action(Action::attack, 0, true, 0);
    Action* ability = new Action(Action::ability, 0, true, 0, true);
    Action* movement_up = new Action(Action::move_up, 0, true);
    ASSERT_FALSE(no_action->is_ability());
    ASSERT_FALSE(attack->is_ability());
    ASSERT_TRUE(ability->is_ability());
    ASSERT_FALSE(movement_up->is_ability());
    delete no_action;
    delete attack;
    delete ability;
    delete movement_up;
}

TEST (ActionTest, ActionTest_IsNoAction_Test) {
    Action* no_action = new Action(Action::no_action, 0, true);
    Action* attack = new Action(Action::attack, 0, true, 0);
    Action* ability = new Action(Action::ability, 0, true, 0, true);
    Action* movement_up = new Action(Action::move_up, 0, true);
    ASSERT_TRUE(no_action->is_no_action());
    ASSERT_FALSE(attack->is_no_action());
    ASSERT_FALSE(ability->is_no_action());
    ASSERT_FALSE(movement_up->is_no_action());
    delete no_action;
    delete attack;
    delete ability;
    delete movement_up;
}

TEST (ActionTest, ActionTest_IsActorTeam1_Test) {
    Action* no_action = new Action(Action::no_action, 0, true);
    Action* attack = new Action(Action::attack, 0, true, 0);
    Action* ability = new Action(Action::ability, 0, false, 0, false);
    Action* movement_up = new Action(Action::move_up, 0, false);

    ASSERT_TRUE(no_action->is_actor_team_1());
    ASSERT_TRUE(attack->is_actor_team_1());
    ASSERT_FALSE(ability->is_actor_team_1());
    ASSERT_FALSE(movement_up->is_actor_team_1());

    delete no_action;
    delete attack;
    delete ability;
    delete movement_up;
}

TEST (ActionTest, ActionTest_IsTargetTeam1_Test) {
    Action* ability = new Action(Action::ability, 0, false, 0, true);
    Action* ability2 = new Action(Action::ability, 0, true, 0, false);
    Action* attack = new Action(Action::attack, 0, true, 0);
    Action* attack2 = new Action(Action::attack, 0, false, 0);

    ASSERT_TRUE(ability->is_target_team_1());
    ASSERT_FALSE(ability2->is_target_team_1());
    ASSERT_FALSE(attack->is_target_team_1());
    ASSERT_TRUE(attack2->is_target_team_1());

    delete ability;
    delete ability2;
    delete attack;
    delete attack2;
}