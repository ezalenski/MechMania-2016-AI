//
// Created by Edmund Zalenski on 10/11/16.
//

#include <gtest/gtest.h>
#include <Character.h>
#include <fstream>
#include <State.h>

class StateTest : public ::testing::Test
{
protected:
    virtual void TearDown() {
        team_1.clear();
        team_1.clear();
    }

    virtual void SetUp() {
        std::ifstream ifs("testinput.json");
        if(!ifs.is_open()) {
            std::cout << "can't find input file" << std::endl;
            return;
        }
        json j(ifs);

        int team_id;

        json player_json = j["PlayerInfo"];
        team_id = player_json["TeamId"];

        for (json::iterator it1 = j["Teams"].begin();
             it1 != j["Teams"].end(); ++it1) {
            json o = *it1;
            int current_team_id = o["Id"];
            for(json::iterator it = o["Characters"].begin();
                it != o["Characters"].end(); ++it) {
                std::shared_ptr<Character> char_copy = std::make_shared<Character>(*it);
                if(current_team_id == team_id)
                    team_1.push_back(char_copy);
                else
                    team_2.push_back(char_copy);
            }
        }
    }

public:
    StateTest() : Test() {
    }

    virtual ~StateTest() {
    }

    GameMap game_map;
    std::vector<std::shared_ptr<Character>> team_1;
    std::vector<std::shared_ptr<Character>> team_2;
};

TEST_F (StateTest, Eval_Next_1_Action_Test) {
    State prev_state(team_1, team_2, true);
    Action move_up(Action::move_up, 0, true);
    State next_state(prev_state);
    std::vector<std::shared_ptr<Character>> prev_team_1 = prev_state.get_team_1();
    std::vector<std::shared_ptr<Character>> next_team_1 = next_state.get_team_1();
    std::vector<std::shared_ptr<Character>> prev_team_2 = prev_state.get_team_2();
    std::vector<std::shared_ptr<Character>> next_team_2 = next_state.get_team_2();
    ASSERT_TRUE(std::equal(prev_team_1.begin(),
                           prev_team_1.end(),
                           next_team_1.begin(),
                           [](const std::shared_ptr<Character>& cp1, const std::shared_ptr<Character>& cp2){
                               return *cp1 == *cp2;
                           })) <<
                                                                                                                "prev and next state team_1 are not "
                        "equal "
                        "before action";
    ASSERT_TRUE(std::equal(prev_team_2.begin(),
                           prev_team_2.end(),
                           next_team_2.begin(),
                           [](const std::shared_ptr<Character>& cp1, const std::shared_ptr<Character>& cp2){
                               return *cp1 == *cp2;
                           })) << "prev and next state team_2 are not equal before action";

    next_state.eval_action(move_up, game_map);
    prev_team_1 = prev_state.get_team_1();
    next_team_1 = next_state.get_team_1();
    prev_team_2 = prev_state.get_team_2();
    next_team_2 = next_state.get_team_2();
    ASSERT_FALSE(std::equal(prev_team_1.begin(),
                           prev_team_1.end(),
                           next_team_1.begin(),
                            [](const std::shared_ptr<Character>& cp1, const std::shared_ptr<Character>& cp2){
                                return *cp1 == *cp2;
                            })) << "prev and next state team_1 are equal after action";
    ASSERT_TRUE(std::equal(prev_team_2.begin(),
                           prev_team_2.end(),
                           next_team_2.begin(),
                           [](const std::shared_ptr<Character>& cp1, const std::shared_ptr<Character>& cp2){
                               return *cp1 == *cp2;
                           })) << "prev and next state team_2 are not equal after action";
}

TEST_F (StateTest, Eval_Next_3_Action_Test) {
    State prev_state(team_1, team_2, true);
    Action move_up_1(Action::no_action, 0, true);
    Action move_up_2(Action::move_up, 1, true);
    Action move_up_3(Action::attack, 2, true, 0);
    State next_state(prev_state);
    next_state.clear_actions();
    next_state.clear_children();
    std::vector<std::shared_ptr<Character>> prev_team_1 = prev_state.get_team_1();
    std::vector<std::shared_ptr<Character>> next_team_1 = next_state.get_team_1();
    std::vector<std::shared_ptr<Character>> prev_team_2 = prev_state.get_team_2();
    std::vector<std::shared_ptr<Character>> next_team_2 = next_state.get_team_2();
    ASSERT_TRUE(std::equal(prev_team_1.begin(),
                           prev_team_1.end(),
                           next_team_1.begin(),
                           [](const std::shared_ptr<Character>& cp1, const std::shared_ptr<Character>& cp2){
                               return *cp1 == *cp2;
                           })) << "prev and next state team_1 are not equal before action";
    ASSERT_TRUE(std::equal(prev_team_2.begin(),
                           prev_team_2.end(),
                           next_team_2.begin(),
                           [](const std::shared_ptr<Character>& cp1, const std::shared_ptr<Character>& cp2){
                               return *cp1 == *cp2;
                           })) << "prev and next state team_2 are not equal before action";

    next_state.eval_action(move_up_1, game_map);
    next_state.eval_action(move_up_2, game_map);
    next_state.eval_action(move_up_3, game_map);

    prev_team_1 = prev_state.get_team_1();
    next_team_1 = next_state.get_team_1();
    prev_team_2 = prev_state.get_team_2();
    next_team_2 = next_state.get_team_2();
    ASSERT_FALSE(std::equal(prev_team_1.begin(),
                            prev_team_1.end(),
                            next_team_1.begin(),
                            [](const std::shared_ptr<Character>& cp1, const std::shared_ptr<Character>& cp2){
                                return *cp1 == *cp2;
                            })) << "prev and next state team_1 are equal after action";
    ASSERT_FALSE(std::equal(prev_team_2.begin(),
                           prev_team_2.end(),
                           next_team_2.begin(),
                           [](const std::shared_ptr<Character>& cp1, const std::shared_ptr<Character>& cp2){
                               return *cp1 == *cp2;
                           })) << "prev and next state team_2 are equal after action";
    prev_state.add_child(next_state);
    ASSERT_EQ(prev_state.get_children().size(), 1);
    ASSERT_EQ(next_state.get_children().size(), 0);
    ASSERT_EQ(prev_state.actions_acted.size(), 0);
    ASSERT_EQ(next_state.actions_acted.size(), 3);
}