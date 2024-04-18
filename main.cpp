#include <SFML/Graphics.hpp>
#include "constants/constants.h"
#include "quest/quest.h"
#include "entities/player.h"
#include "entities/teacher.h"
#include "map/game.h"
#include <random>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "University game");
    window.setKeyRepeatEnabled(true);
    window.setFramerateLimit(1000);

    sf::View standard_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    standard_view.setCenter(640, 360);

    sf::Font text_font;
    text_font.loadFromFile(path_to_font);

    sf::Text head_text;
    head_text.setFont(text_font);
    head_text.setString("University Game");
    head_text.setCharacterSize(50);
    head_text.setFillColor(sf::Color::Cyan);
    head_text.setStyle(sf::Text::Bold);
    head_text.setPosition(450, 40);

    sf::Text new_game_button_text;
    new_game_button_text.setFont(text_font);
    new_game_button_text.setString("Start a new game");
    new_game_button_text.setCharacterSize(25);
    new_game_button_text.setFillColor(sf::Color::Cyan);
    new_game_button_text.setStyle(sf::Text::Italic);
    new_game_button_text.setPosition(530, 200);

    sf::RectangleShape new_game_button_shape;
    new_game_button_shape.setSize(sf::Vector2f(300, 50));
    new_game_button_shape.setPosition(490, 195);
    new_game_button_shape.setOutlineThickness(3.f);
    new_game_button_shape.setFillColor(sf::Color::Transparent);
    new_game_button_shape.setOutlineColor(sf::Color::Cyan);

    sf::Text load_game_button_text;
    load_game_button_text.setFont(text_font);
    load_game_button_text.setString("Load game");
    load_game_button_text.setCharacterSize(25);
    load_game_button_text.setFillColor(sf::Color::Cyan);
    load_game_button_text.setStyle(sf::Text::Italic);
    load_game_button_text.setPosition(570, 300);

    sf::RectangleShape load_game_button_shape;
    load_game_button_shape.setSize(sf::Vector2f(300, 50));
    load_game_button_shape.setPosition(490, 295);
    load_game_button_shape.setOutlineThickness(3.f);
    load_game_button_shape.setFillColor(sf::Color::Transparent);
    load_game_button_shape.setOutlineColor(sf::Color::Cyan);

    sf::Text settings_button_text;
    settings_button_text.setFont(text_font);
    settings_button_text.setString("Settings");
    settings_button_text.setCharacterSize(25);
    settings_button_text.setFillColor(sf::Color::Cyan);
    settings_button_text.setStyle(sf::Text::Italic);
    settings_button_text.setPosition(580, 400);

    sf::RectangleShape settings_button_shape;
    settings_button_shape.setSize(sf::Vector2f(300, 50));
    settings_button_shape.setPosition(490, 395);
    settings_button_shape.setOutlineThickness(3.f);
    settings_button_shape.setFillColor(sf::Color::Transparent);
    settings_button_shape.setOutlineColor(sf::Color::Cyan);

    sf::Text copyright_text;
    copyright_text.setFont(text_font);
    copyright_text.setString("by Bondar F., Mikhaylov B., Mikhaylov D., Sarantsev I., HSE AMI 2024.");
    copyright_text.setCharacterSize(15);
    copyright_text.setFillColor(sf::Color::Cyan);
    copyright_text.setPosition(400, 650);

    sf::Text settings_head_text;
    settings_head_text.setFont(text_font);
    settings_head_text.setString("Settings");
    settings_head_text.setCharacterSize(50);
    settings_head_text.setFillColor(sf::Color::Cyan);
    settings_head_text.setStyle(sf::Text::Bold);
    settings_head_text.setPosition(530, 40);

    sf::Text settings_main_text;
    settings_main_text.setFont(text_font);
    settings_main_text.setString("Keyboard bindings: \n\n"
                                 "~ Interact with objects/characters:        X\n"
                                 "~ Open/close inventory/list of quests:   E\n"
                                 "~ Leave game:                                       ESC\n"
                                 "~ Move player:                                       Arrow keys or WASD\n"
                                 "~ Start/end tetris minigame:                  T\n"
                                 "~ Start/end sudoky minigame:              G\n"
                                 "~ Start/end bugs minigame:                  B\n");
    settings_main_text.setCharacterSize(25);
    settings_main_text.setFillColor(sf::Color::Cyan);
    settings_main_text.setPosition(50, 195);

    sf::Text settings_back_button_text;
    settings_back_button_text.setFont(text_font);
    settings_back_button_text.setString("Back");
    settings_back_button_text.setCharacterSize(25);
    settings_back_button_text.setFillColor(sf::Color::Cyan);
    settings_back_button_text.setStyle(sf::Text::Italic);
    settings_back_button_text.setPosition(610, 600);

    sf::RectangleShape settings_back_button_shape;
    settings_back_button_shape.setSize(sf::Vector2f(100, 50));
    settings_back_button_shape.setPosition(590, 595);
    settings_back_button_shape.setOutlineThickness(3.f);
    settings_back_button_shape.setFillColor(sf::Color::Transparent);
    settings_back_button_shape.setOutlineColor(sf::Color::Cyan);

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

    university_game::game my_game(&window, text_font, player_1);
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

                        university_game::game new_game(&window, text_font, player_1);
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
            if (!settings_opened) {
                window.draw(head_text);
                window.draw(new_game_button_text);
                window.draw(new_game_button_shape);
                window.draw(load_game_button_text);
                window.draw(load_game_button_shape);
                window.draw(settings_button_text);
                window.draw(settings_button_shape);
                window.draw(copyright_text);
            } else {
                window.draw(settings_head_text);
                window.draw(settings_main_text);
                window.draw(settings_back_button_text);
                window.draw(settings_back_button_shape);
            }
            window.display();
        }
    }

    return 0;
}