#include <SFML/Graphics.hpp>
#include <utility>
#include "Application.cpp"

namespace university_game {
    struct OnKeyPressed {
        sf::Event event;
        Application app;

        explicit OnKeyPressed(const sf::Event &event, Application app) : event(event), app(std::move(app)) {}

        void action() {
            if (event.key.code == sf::Keyboard::Escape) {
                app.window.close();
            }
            if (!app.state.something_extra_opened) { //game moves, interaction with objects, starting any minigame
                //or opening inventory
                if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                    for (int i = 1; i < 51; i++) {
                        if (!app.my_game.move(1, i)) {
                            break;
                        }
                        app.window.clear();
                        app.window.draw(app.my_game);
                        app.window.display();
                    }
                }
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                    for (int i = 1; i < 51; i++) {
                        if (!app.my_game.move(2, i)) {
                            break;
                        }
                        app.window.clear();
                        app.window.draw(app.my_game);
                        app.window.display();
                    }
                }
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                    for (int i = 1; i < 51; i++) {
                        if (!app.my_game.move(3, i)) {
                            break;
                        }
                        app.window.clear();
                        app.window.draw(app.my_game);
                        app.window.display();
                    }
                }
                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                    for (int i = 1; i < 51; i++) {
                        if (!app.my_game.move(4, i)) {
                            break;
                        }
                        app.window.clear();
                        app.window.draw(app.my_game);
                        app.window.display();
                    }
                }
                if (event.key.code == sf::Keyboard::X) {
                    app.state.id = app.my_game.check_presence_of_teacher();
                    if (app.state.id > 0 && (app.state.executing_id == 0
                                   || app.state.executing_id == app.state.id
                                   || app.my_game.get_teachers()[app.state.executing_id - 2].get_quest_stage() > 2)) {
                        app.state.executing_id = app.state.id;
                        app.state.teacher_speaking = true;
                    }
                    app.my_game.take_item_if_possible();
                }
                if (event.key.code == sf::Keyboard::E) {
                    app.state.inventory_and_quests_opened = true;
                    app.state.something_extra_opened = true;
                }
            } else { // closing inventory
                if (event.key.code == sf::Keyboard::E && app.state.inventory_and_quests_opened) {
                    app.state.inventory_and_quests_opened = false;
                    app.state.something_extra_opened = false;
                }
            }
        }
    };
}