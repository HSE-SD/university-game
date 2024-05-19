#include <SFML/Graphics.hpp>
#include <sstream>
#include "state.h"
#include "../quest/quest.h"
#include "../entities/player.h"
#include "../entities/teacher.h"
#include "../map/game.h"
#include "../app_runner/buttons.h"

namespace university_game {
    struct Application {
        sf::RenderWindow& window;
        sf::View standard_view;
        buttons buttons;
        state state;
        university_game::item first_required;
        university_game::item third_required;
        std::vector<university_game::quest> initial_quests;
        std::vector<university_game::item> initial_items;
        university_game::player player_1;
        university_game::teacher teacher_1;
        university_game::teacher teacher_2;
        university_game::teacher teacher_3;
        university_game::game my_game;
        std::vector<quest> quests;


        Application(sf::RenderWindow &w, university_game::game& myGame) : window(w), my_game(myGame) {
            window.setKeyRepeatEnabled(true);
            window.setFramerateLimit(1000);

            sf::View standard_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
            standard_view.setCenter(640, 360);

            buttons.load();

            uint64_t quests_count = 3;
            quests.resize(quests_count);
            for (int i = 0; i < quests_count; ++i) {
                std::stringstream file;
                file << "quest" << (i + 1) << ".json";
                quests[i].create_from_json(file.str());
            }
            first_required = quests[0].get_required_item();
            third_required = quests[2].get_required_item();

            initial_quests = quests;

            my_game.setPosition(40.f, 40.f);
            my_game.load_textures();
        }
    };
}