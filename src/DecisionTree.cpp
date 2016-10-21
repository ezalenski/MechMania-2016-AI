//
// Created by Edmund Zalenski on 10/9/16.
//

#include <cfloat>
#include "DecisionTree.h"

DecisionTree::DecisionTree(const State& initial_state)
    : _initial_state{ initial_state }
{ }

State* DecisionTree::generate_to_level(int target_level,
                                       double time_out)
{
    return _generate_to_level(&this->_initial_state, -DBL_MAX, nullptr, DBL_MAX, nullptr,
                                        true, 0, target_level, 0, time_out);
}

State* DecisionTree::_generate_to_level(State* prev_state,
                                        double alpha,
                                        State* alpha_node,
                                        double beta,
                                        State* beta_node,
                                        bool is_team_1,
                                        int current_level,
                                        int target_level,
                                        double current_time,
                                        double time_out)
{
    if(current_level == target_level || current_time >= time_out)
        return prev_state;
    else {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();

        prev_state->clear_children();
        std::vector<std::vector<std::shared_ptr<Action>>> team_actions;

        if(is_team_1) {
            for(int i = 0; i < prev_state->get_team_1().size(); ++i) {
                std::unique_ptr<std::vector<std::shared_ptr<Action>>> actions = prev_state->generate_team_1_actions(i,
                                                                                                            game_map);
                team_actions.push_back(*actions);
            }
        } else {
            for(int i = 0; i < prev_state->get_team_2().size(); ++i) {
                std::unique_ptr<std::vector<std::shared_ptr<Action>>> actions = prev_state->generate_team_2_actions(i,
                                                                                                               game_map);
                team_actions.push_back(*actions);
            }
        }

        for(const auto& action_1 : team_actions[0]) {
            for(const auto& action_2 : team_actions[1]) {
                for(const auto& action_3 : team_actions[2]) {
                    State next_state = State(*prev_state, is_team_1);
                    next_state.clear_children();
                    next_state.clear_actions();

                    next_state.eval_action(*action_1, game_map);
                    next_state.eval_action(*action_2, game_map);
                    next_state.eval_action(*action_3, game_map);
                    next_state.calc_expected_value();

                    prev_state->add_child(next_state);
                }
            }
        }
        if(is_team_1) {
            std::sort(prev_state->get_change_children().begin(), prev_state->get_change_children().end(),
                      [](const State &s1, const State &s2) {
                          return (s1.get_expected_value() > s2.get_expected_value());
                      });
            double local_alpha = -DBL_MAX;
            State* local_alpha_node = nullptr;
            for(auto child = prev_state->get_change_children().begin();
                child != prev_state->get_change_children().end(); ++child) {

                end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = end-start;

                State* best_grandchild = _generate_to_level(&(*child), alpha, alpha_node, beta, beta_node, !is_team_1,
                                                            current_level + 1, target_level, current_time +
                                                                    elapsed_seconds.count(), time_out);
                if(best_grandchild->get_expected_value() > local_alpha ||
                        (best_grandchild->get_expected_value() == local_alpha &&
                                child->get_expected_value() > local_alpha_node->get_expected_value())) {
                    local_alpha = best_grandchild->get_expected_value();
                    local_alpha_node = &(*child);
                }
                if(local_alpha > alpha) {
                    alpha = local_alpha;
                    alpha_node = local_alpha_node;
                }
                if(beta <= alpha) {
                    break;
                }
            }
            return local_alpha_node;
        } else {
            std::sort(prev_state->get_change_children().begin(), prev_state->get_change_children().end(),
                      [](const State &s1, const State &s2) {
                          return (s1.get_expected_value() < s2.get_expected_value());
                      });
            double local_beta = DBL_MAX;
            State* local_beta_node = nullptr;
            for(auto child = prev_state->get_change_children().begin(); child != prev_state->get_change_children().end(); ++child) {
                end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = end-start;

                State* best_grandchild = _generate_to_level(&(*child), alpha, alpha_node, beta, beta_node, !is_team_1,
                                                            current_level + 1, target_level, current_time +
                                                                                             elapsed_seconds.count(), time_out);
                if(best_grandchild->get_expected_value() < local_beta  ||
                        (best_grandchild->get_expected_value() == local_beta &&
                                child->get_expected_value() < local_beta_node->get_expected_value())) {
                    local_beta = best_grandchild->get_expected_value();
                    local_beta_node = &(*child);
                }
                if(local_beta < beta) {
                    beta = local_beta;
                    beta_node = local_beta_node;
                }
                if(beta <= alpha) {
                    break;
                }
            }
            return local_beta_node;
        }
    }
}