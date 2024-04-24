#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

struct buttons{
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

    void load();

    void draw(sf::RenderWindow &window, bool settings_opened);
};