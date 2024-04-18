#include "teacher.h"

namespace university_game {

    void teacher::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();

        sf::Font text_font_;
        text_font_.loadFromFile(path_to_font);

        sf::Color outline_color = sf::Color(73, 103, 113);

        sf::RectangleShape frame_shape(sf::Vector2f(720, 60));
        frame_shape.setFillColor(sf::Color::White);
        frame_shape.setOutlineThickness(10.f);
        frame_shape.setOutlineColor(outline_color);
        frame_shape.setPosition(active_v * (cell_v_size) - 250, active_h * (cell_h_size) - 50);

        sf::Text quest_text;
        quest_text.setFont(text_font_);
        if (quest_stage > 2) {
            quest_text.setString("Sorry, nothing else for you today");
        } else {
            quest_text.setString(phrases[quest_stage]);
        }

        quest_text.setCharacterSize(30);
        quest_text.setFillColor(sf::Color::Black);
        quest_text.setStyle(sf::Text::Italic);
        quest_text.setPosition(active_v * (cell_v_size) - 240, active_h * (cell_h_size) - 40);

        target.draw(frame_shape, states);
        target.draw(quest_text, states);
    }

} // namespace university_game
