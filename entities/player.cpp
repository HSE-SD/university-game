#include "player.h"

namespace university_game {

    player::player(std::string
                   name_,
                   std::vector<quest> &list_of_quests_,
                   std::vector<item>
                   &inventory_) :
            name(std::move(name_)),
            list_of_quests(list_of_quests_),
            inventory(inventory_),
            active_v(v_table / 2),
            active_h(h_table / 2),
            active_v_compare(v_table / 2),
            active_h_compare(h_table / 2) {}

    void player::set_name(std::string new_name) {
        name = std::move(new_name);
    }

    [[nodiscard]] std::string player::get_name() const {
        return name;
    }

    [[nodiscard]] int player::get_level() const {
        return level;
    }

    [[nodiscard]] std::vector<quest> &player::get_list_of_quests() {
        return list_of_quests;
    }

    [[nodiscard]] double player::get_v() const {
        return active_v;
    }

    [[nodiscard]] double player::get_h() const {
        return active_h;
    }

    [[nodiscard]] int player::get_v_compare() const {
        return active_v_compare;
    }

    [[nodiscard]] int player::get_h_compare() const {
        return active_h_compare;
    }

    [[nodiscard]] std::string player::get_quest_taken() const {
        return quest_taken;
    }

    [[nodiscard]] std::vector<item> player::get_inventory() const {
        return inventory;
    }

    [[nodiscard]] int player::get_direction() const {
        return direction;
    }

    [[nodiscard]] int player::get_graphic_phase() const {
        return graphic_phase;
    }

    void player::set_graphic_phase(int new_graphic_phase) {
        graphic_phase = new_graphic_phase;
    }

    void player::set_direction(int new_direction) {
        direction = new_direction;
    }

    void player::set_quest_taken(const std::string &new_quest_name) {
        quest_taken = new_quest_name;
    }

    void player::set_v(double new_v) {
        active_v = new_v;
    }

    void player::set_h(double new_h) {
        active_h = new_h;
    }

    void player::set_v_compare(int new_v) {
        active_v_compare = new_v;
    }

    void player::set_h_compare(int new_h) {
        active_h_compare = new_h;
    }

    void player::add_to_inventory(const item &new_item) {
        inventory.push_back(new_item);
    }

    void player::set_inventory(std::vector<item> new_inventory) {
        inventory = std::move(new_inventory);
    }

    void player::check_for_level_up() {
        for (const auto &m_quest: list_of_quests) {
            if (m_quest.get_required_level() <= get_level() && m_quest.get_condition() == "NOT COMPLETED") {
                return;
            }
        }
        level++;
    }

    [[nodiscard]] std::string player::display_available_quests() const {
        std::string res;
        int count = 1;
        for (const auto &m_quest: list_of_quests) {
            if (m_quest.get_required_level() <= get_level()) {
                res += std::to_string(count++) + ") " + m_quest.get_name() + " ";
                res += "\t'" + m_quest.get_condition() + "'\n";
                res += m_quest.get_description() + "\n\n";
            }
        }
        return res;
    }

    [[nodiscard]] std::string player::show_inventory() const {
        std::string res;
        if (inventory.empty()) {
            res = "You have no items yet.\n\n";
            return res;
        }
        int count = 1;
        for (const auto &m_item: inventory) {
            res += std::to_string(count++) + ") " + m_item.get_info();
        }
        return res;
    }

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