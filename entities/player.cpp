#include "player.h"

namespace university_game {

    void player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();

        sf::Font text_font_;
        text_font_.loadFromFile(path_to_font);

        sf::Color outline_color = sf::Color(73, 103, 113);

        sf::RectangleShape frame_shape(sf::Vector2f(720, 480));
        frame_shape.setFillColor(sf::Color::White);
        frame_shape.setOutlineThickness(10.f);
        frame_shape.setOutlineColor(outline_color);
        frame_shape.setPosition(active_v * (cell_v_size) - 250, active_h * (cell_h_size) - 130);

        sf::RectangleShape split_shape(sf::Vector2f(10, 480));
        split_shape.setFillColor(outline_color);
        split_shape.setPosition(active_v * (cell_v_size) + 100, active_h * (cell_h_size) - 130);

        sf::Text quest_text;
        quest_text.setFont(text_font_);
        quest_text.setString("Available quests:");
        quest_text.setCharacterSize(30);
        quest_text.setFillColor(sf::Color::Black);
        quest_text.setStyle(sf::Text::Bold);
        quest_text.setPosition(active_v * (cell_v_size) - 240, active_h * (cell_h_size) - 120);

        sf::Text inventory_text;
        inventory_text.setFont(text_font_);
        inventory_text.setString("Your inventory:");
        inventory_text.setCharacterSize(30);
        inventory_text.setFillColor(sf::Color::Black);
        inventory_text.setStyle(sf::Text::Bold);
        inventory_text.setPosition(active_v * (cell_v_size) + 150, active_h * (cell_h_size) - 120);

        sf::Text level_text;
        level_text.setFont(text_font_);
        level_text.setString("Your current level: " + std::to_string(get_level()));
        level_text.setCharacterSize(30);
        level_text.setFillColor(sf::Color::Black);
        level_text.setStyle(sf::Text::Bold);
        level_text.setPosition(active_v * (cell_v_size) - 240, active_h * (cell_h_size) + 300);

        target.draw(frame_shape, states);
        target.draw(quest_text, states);
        target.draw(inventory_text, states);
        target.draw(level_text, states);

        quest_text.setString(display_available_quests());
        quest_text.setCharacterSize(15);
        quest_text.setPosition(active_v * (cell_v_size) - 240, active_h * (cell_h_size) - 70);

        inventory_text.setString(show_inventory());
        inventory_text.setCharacterSize(15);
        inventory_text.setPosition(active_v * (cell_v_size) + 150, active_h * (cell_h_size) - 70);

        target.draw(quest_text, states);
        target.draw(inventory_text, states);
        target.draw(split_shape, states);
    }

} // namespace university_game