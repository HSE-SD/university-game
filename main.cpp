#include <SFML/Graphics.hpp>
#include "constants/constants.h"
#include "quest/quest.h"
#include "entities/player.h"
#include "entities/teacher.h"
#include "map/game.h"
#include "app_runner/buttons.h"
#include <random>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "University game");
    window.setKeyRepeatEnabled(true);
    window.setFramerateLimit(1000);

    sf::View standard_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    standard_view.setCenter(640, 360);

    buttons buttons;
    buttons.load();

    university_game::quest first_quest;
    university_game::quest second_quest;
    university_game::quest third_quest;
    first_quest.create_from_json("quest1.json");
    second_quest.create_from_json("quest2.json");
    third_quest.create_from_json("quest3.json");
    university_game::item first_required = first_quest.get_required_item();
    university_game::item third_required = third_quest.get_required_item();

    std::vector<university_game::quest> initial_quests = {first_quest, second_quest, third_quest};
    std::vector<university_game::item> initial_items{};
    university_game::player player_1("You", initial_quests, initial_items);
    university_game::teacher teacher_1("Mr. Antipoff", 2, 1, 1,
                                       {"Hey! Wanna mark? Bring me my algebra book.",
                                        "Did you actually find it?", "Alright, here we go."}, first_quest.get_name());
    university_game::teacher teacher_2("Mr. Khrabroff", 3, 12, 5,
                                       {"Hey!",
                                        "I've heard that you're a trickster now.",
                                        "Good job! See you later."}, second_quest.get_name());
    university_game::teacher teacher_3("Pashok", 4, 22, 2,
                                       {"Yo! Find a wall, where I've hidden money.",
                                        "You've found it, right?",
                                        "Thank you, man. Appreciate that."}, third_quest.get_name());

    university_game::game my_game(&window, buttons.text_font, player_1);
    my_game.setPosition(40.f, 40.f);
    my_game.load_textures();

    bool game_started = false;
    bool settings_opened = false;
    bool inventory_and_quests_opened = false;
    bool teacher_speaking = false;
    bool something_extra_opened = false; // true if inventory opened
    bool game_started_ever = false;
    int executing_id = 0;
    int id = 0;

    while (window.isOpen()) {
        if (game_started) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    if (!something_extra_opened) { //game moves, interaction with objects, starting any minigame
                        //or opening inventory
                        if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                            for (int i = 1; i < 51; i++) {
                                if (!my_game.move(1, i)) {
                                    break;
                                }
                                window.clear();
                                window.draw(my_game);
                                window.display();
                            }
                        }
                        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                            for (int i = 1; i < 51; i++) {
                                if (!my_game.move(2, i)) {
                                    break;
                                }
                                window.clear();
                                window.draw(my_game);
                                window.display();
                            }
                        }
                        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                            for (int i = 1; i < 51; i++) {
                                if (!my_game.move(3, i)) {
                                    break;
                                }
                                window.clear();
                                window.draw(my_game);
                                window.display();
                            }
                        }
                        if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                            for (int i = 1; i < 51; i++) {
                                if (!my_game.move(4, i)) {
                                    break;
                                }
                                window.clear();
                                window.draw(my_game);
                                window.display();
                            }
                        }
                        if (event.key.code == sf::Keyboard::X) {
                            id = my_game.check_presence_of_teacher();
                            if (id > 0 && (executing_id == 0
                                           || executing_id == id
                                           || my_game.get_teachers()[executing_id - 2].get_quest_stage() > 2)) {
                                executing_id = id;
                                teacher_speaking = true;
                            }
                            my_game.take_item_if_possible();
                        }
                        if (event.key.code == sf::Keyboard::E) {
                            inventory_and_quests_opened = true;
                            something_extra_opened = true;
                        }
                    } else { // closing inventory
                        if (event.key.code == sf::Keyboard::E && inventory_and_quests_opened) {
                            inventory_and_quests_opened = false;
                            something_extra_opened = false;
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (event.mouseButton.x > 0
                        && event.mouseButton.x < 110
                        && event.mouseButton.y > 0
                        && event.mouseButton.y < 50
                        && !something_extra_opened) {
                        game_started = false;
                        window.setView(standard_view);
                    }
                }
            }

            if (game_started) { // drawing process starts here
                window.clear();
                window.draw(my_game);
                if (inventory_and_quests_opened) {
                    window.draw(my_game.get_player());
                }
                if (teacher_speaking) {
                    const sf::Time freezeLength{sf::seconds(3.f)};
                    sf::Clock freezeClock;
                    while (freezeClock.getElapsedTime() < freezeLength) {
                        window.draw(my_game.get_teachers()[id - 2]);
                        window.display();
                    }
                    teacher_speaking = false;
                    my_game.get_teachers()[id - 2].satisfy_quest(my_game.get_player());
                }
                window.display();
            }
        } else {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (event.mouseButton.x > 490 && event.mouseButton.x < 790
                        && event.mouseButton.y > 195 && event.mouseButton.y < 245 &&
                        !settings_opened) { // start new game

                        game_started = true;
                        game_started_ever = true;

                        university_game::game new_game(&window, buttons.text_font, player_1);
                        new_game.load_textures();
                        my_game = new_game;
                        my_game.setPosition(40.f, 40.f);

                        my_game.get_teachers()[0] = teacher_1;
                        my_game.get_teachers()[1] = teacher_2;
                        my_game.get_teachers()[2] = teacher_3;
                        first_required.set_displayed(true);
                        my_game.get_displayed_items()[0] = first_required;
                        third_required.set_displayed(true);
                        my_game.get_displayed_items()[1] = third_required;
                    }
                    if (event.mouseButton.x > 490 && event.mouseButton.x < 790 && event.mouseButton.y > 295 &&
                        event.mouseButton.y < 345 && !settings_opened && game_started_ever) { // load game
                        game_started = true;
                    }
                    if (event.mouseButton.x > 490 && event.mouseButton.x < 790
                        && event.mouseButton.y > 395 && event.mouseButton.y < 445 && !settings_opened) {
                        settings_opened = true;
                    }
                    if (event.mouseButton.x > 590 && event.mouseButton.x < 690
                        && event.mouseButton.y > 595 && event.mouseButton.y < 645 && settings_opened) {
                        settings_opened = false;
                    }
                }
            }
            window.clear();
            buttons.draw(window, settings_opened);
        }
    }

    return 0;
}