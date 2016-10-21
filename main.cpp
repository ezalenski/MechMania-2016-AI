#include <iostream>
#include <fstream>
#include <State.h>
#include <DecisionTree.h>
//#define DEBUG
using namespace std;
using json = nlohmann::json;

int main() {
#ifdef DEBUG
    std::cout << "DEBUG ON" << std::endl;
    std::ifstream ifs("testinput.json");
    if(!ifs.is_open()) {
        std::cout << "can't find input file" << std::endl;
        return 1;
    }
    json j(ifs);
#else
    json j;
    std::cin >> j;
#endif

    std::vector<std::shared_ptr<Character>> team_1;
    std::vector<std::shared_ptr<Character>> team_2;
    int team_id;
    int turn_number;

    turn_number = j["TurnNumber"];
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
    State initial_state(team_1, team_2, true);
    DecisionTree *dt = new DecisionTree(initial_state);
    auto best_move = dt->generate_to_level(3, 15.0);
    json result = best_move->get_actions();
    if(!result.empty()) {
        std::cout << result;
    } else {
        std::cout << "{}";
    }
    delete dt;
    return 0;
}