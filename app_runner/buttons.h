#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../constants/constants.h"

struct buttons {
    sf::Font text_font;
    sf::Text head_text;
    sf::Text new_game_button_text;
    sf::RectangleShape new_game_button_shape;
    sf::Text load_game_button_text;
    sf::RectangleShape load_game_button_shape;
    sf::Text settings_button_text;
    sf::RectangleShape settings_button_shape;
    sf::Text copyright_text;
    sf::Text settings_head_text;
    sf::Text settings_main_text;
    sf::Text settings_back_button_text;
    sf::RectangleShape settings_back_button_shape;

    void load() {
        text_font.loadFromFile(path_to_font);

        head_text.setFont(text_font);
        head_text.setString("University Game");
        head_text.setCharacterSize(50);
        head_text.setFillColor(sf::Color::Cyan);
        head_text.setStyle(sf::Text::Bold);
        head_text.setPosition(450, 40);

        new_game_button_text.setFont(text_font);
        new_game_button_text.setString("Start a new game");
        new_game_button_text.setCharacterSize(25);
        new_game_button_text.setFillColor(sf::Color::Cyan);
        new_game_button_text.setStyle(sf::Text::Italic);
        new_game_button_text.setPosition(530, 200);

        new_game_button_shape.setSize(sf::Vector2f(300, 50));
        new_game_button_shape.setPosition(490, 195);
        new_game_button_shape.setOutlineThickness(3.f);
        new_game_button_shape.setFillColor(sf::Color::Transparent);
        new_game_button_shape.setOutlineColor(sf::Color::Cyan);

        load_game_button_text.setFont(text_font);
        load_game_button_text.setString("Load game");
        load_game_button_text.setCharacterSize(25);
        load_game_button_text.setFillColor(sf::Color::Cyan);
        load_game_button_text.setStyle(sf::Text::Italic);
        load_game_button_text.setPosition(570, 300);

        load_game_button_shape.setSize(sf::Vector2f(300, 50));
        load_game_button_shape.setPosition(490, 295);
        load_game_button_shape.setOutlineThickness(3.f);
        load_game_button_shape.setFillColor(sf::Color::Transparent);
        load_game_button_shape.setOutlineColor(sf::Color::Cyan);

        settings_button_text.setFont(text_font);
        settings_button_text.setString("Settings");
        settings_button_text.setCharacterSize(25);
        settings_button_text.setFillColor(sf::Color::Cyan);
        settings_button_text.setStyle(sf::Text::Italic);
        settings_button_text.setPosition(580, 400);

        settings_button_shape.setSize(sf::Vector2f(300, 50));
        settings_button_shape.setPosition(490, 395);
        settings_button_shape.setOutlineThickness(3.f);
        settings_button_shape.setFillColor(sf::Color::Transparent);
        settings_button_shape.setOutlineColor(sf::Color::Cyan);

        copyright_text.setFont(text_font);
        copyright_text.setString("by Bondar F., Mikhaylov B., Mikhaylov D., Sarantsev I., HSE AMI 2024.");
        copyright_text.setCharacterSize(15);
        copyright_text.setFillColor(sf::Color::Cyan);
        copyright_text.setPosition(400, 650);

        settings_head_text.setFont(text_font);
        settings_head_text.setString("Settings");
        settings_head_text.setCharacterSize(50);
        settings_head_text.setFillColor(sf::Color::Cyan);
        settings_head_text.setStyle(sf::Text::Bold);
        settings_head_text.setPosition(530, 40);

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

        settings_back_button_text.setFont(text_font);
        settings_back_button_text.setString("Back");
        settings_back_button_text.setCharacterSize(25);
        settings_back_button_text.setFillColor(sf::Color::Cyan);
        settings_back_button_text.setStyle(sf::Text::Italic);
        settings_back_button_text.setPosition(610, 600);

        settings_back_button_shape.setSize(sf::Vector2f(100, 50));
        settings_back_button_shape.setPosition(590, 595);
        settings_back_button_shape.setOutlineThickness(3.f);
        settings_back_button_shape.setFillColor(sf::Color::Transparent);
        settings_back_button_shape.setOutlineColor(sf::Color::Cyan);
    }

    void draw(sf::RenderWindow &window, bool settings_opened) {
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
};