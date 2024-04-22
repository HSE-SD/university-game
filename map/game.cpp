#include "game.h"

namespace university_game {

    sf::Texture walkable_field_texture;
    sf::Texture unwalkable_field_texture;
    sf::Texture active_player_texture_front;
    sf::Texture active_player_texture_right;
    sf::Texture active_player_texture_left;
    sf::Texture active_player_texture_back;
    sf::Texture active_player_texture_front_moving;
    sf::Texture active_player_texture_right_moving;
    sf::Texture active_player_texture_left_moving;
    sf::Texture active_player_texture_back_moving;
    sf::Texture teacher1_texture;
    sf::Texture teacher2_texture;
    sf::Texture teacher3_texture;
    sf::Texture item1_texture;
    sf::Texture bug_texture;

    game::game(sf::RenderWindow *window_, const sf::Font &text_font_param, player new_player) :
            window(window_),
            text_font(text_font_param),
            active_player(std::move(new_player)) {
        map.resize(h_table);
        for (auto &line: map) {
            line.resize(v_table);
        }
        teachers.resize(3);
        displayed_items.resize(2);
        map = {{0,  0,  0,  0,  0,  -2, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, -2, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0},
               {0,  2,  0,  0,  0,  -2, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, -1, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0},
               {0,  0,  0,  0,  0,  -2, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0,  0,  4,  0, 0, 0, 0, 0},
               {0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, -2, 0, 0, -2, -2, -2, 0, 0, 0, 0, 0},
               {-2, -2, -2, -2, -2, -2, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0,  0, 0, 0,  0,  0,  0, 0, 0, 0, 0},
               {0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0,  0, 3, 0, 0, 0, 0, 0,  0, 0, 0,  0,  0,  0, 0, 0, 0, 0}};
    }

    [[nodiscard]] int game::check_presence_of_teacher() {
        int active_v = active_player.get_v_compare();
        int active_h = active_player.get_h_compare();
        for (auto &teacher_: teachers) {
            int teacher_active_v = teacher_.get_v();
            int teacher_active_h = teacher_.get_h();
            if (abs(active_h - teacher_active_h) <= 1 && abs(active_v - teacher_active_v) <= 1) {
                for (auto &quest_: active_player.get_list_of_quests()) {
                    if (quest_.get_name() == teacher_.get_associated_quest_name()) {
                        if (quest_.get_required_level() <= active_player.get_level()) {
                            return teacher_.get_id();
                        } else {
                            return 0;
                        }
                    }
                }
            }
        }
        return 0;
    }

    void game::take_item_if_possible() {
        int active_v = active_player.get_v_compare();
        int active_h = active_player.get_h_compare();
        for (auto &item_: displayed_items) {
            int item_active_v = item_.get_v();
            int item_active_h = item_.get_h();
            if (abs(active_h - item_active_h) <= 1 && abs(active_v - item_active_v) <= 1 && item_.get_displayed()) {
                item_.set_displayed(false);
                active_player.add_to_inventory(item_);
                map[item_.get_h()][item_.get_v()] = 0;
            }
        }
    }

    bool game::move(int direction, int iteration) {
        double active_v = active_player.get_v();
        double active_h = active_player.get_h();
        int active_v_compare = active_player.get_v_compare();
        int active_h_compare = active_player.get_h_compare();
        active_player.set_direction(direction);

        if (iteration % 10 == 0) {
            active_player.set_graphic_phase((active_player.get_graphic_phase() + 1) % 2);
        }

        if (iteration == 1) {
            if (direction == 1) {
                if (!(active_v_compare < v_table - 1 && map[active_h_compare][active_v_compare + 1] == 0)) {
                    return false;
                }
                active_v += 0.02;
                active_player.set_v_compare(++active_v_compare);
            }
            if (direction == 2) {
                if (!(active_h_compare > 0 && map[active_h_compare - 1][active_v_compare] == 0)) {
                    return false;
                }
                active_h -= 0.02;
                active_player.set_h_compare(--active_h_compare);
            }
            if (direction == 3) {
                if (!(active_v_compare > 0 && map[active_h_compare][active_v_compare - 1] == 0)) {
                    return false;
                }
                active_v -= 0.02;
                active_player.set_v_compare(--active_v_compare);
            }
            if (direction == 4) {
                if (!(active_h_compare < h_table - 1 && map[active_h_compare + 1][active_v_compare] == 0)) {
                    return false;
                }
                active_h += 0.02;
                active_player.set_h_compare(++active_h_compare);
            }
        } else {
            if (iteration == 50) {
                active_player.set_graphic_phase(0);
            }
            if (direction == 1) {
                active_v += 0.02;
            }
            if (direction == 2) {
                active_h -= 0.02;
            }
            if (direction == 3) {
                active_v -= 0.02;
            }
            if (direction == 4) {
                active_h += 0.02;
            }
        }
        active_player.set_h(active_h);
        active_player.set_v(active_v);
        return true;
    }

    [[nodiscard]] player &game::get_player() {
        return active_player;
    }

    [[nodiscard]] std::vector<teacher> &game::get_teachers() {
        return teachers;
    }

    [[nodiscard]] std::vector<std::vector<int>> &game::get_map() {
        return map;
    }

    [[nodiscard]] std::vector<item> &game::get_displayed_items() {
        return displayed_items;
    }

    void game::load_textures() {
        walkable_field_texture.loadFromFile("../images/walkable_field.png");
        unwalkable_field_texture.loadFromFile("../images/unwalkable_field.png");
        active_player_texture_front.loadFromFile("../images/player_default.png");
        active_player_texture_right.loadFromFile("../images/player_default_right.png");
        active_player_texture_left.loadFromFile("../images/player_default_left.png");
        active_player_texture_back.loadFromFile("../images/player_default_back.png");
        active_player_texture_front_moving.loadFromFile("../images/player_default_moving.png");
        active_player_texture_right_moving.loadFromFile("../images/player_default_right_moving.png");
        active_player_texture_left_moving.loadFromFile("../images/player_default_left_moving.png");
        active_player_texture_back_moving.loadFromFile("../images/player_default_back_moving.png");
        teacher1_texture.loadFromFile("../images/teacher_default.png");
        teacher2_texture.loadFromFile("../images/teacher_khrabroff.png");
        teacher3_texture.loadFromFile("../images/teacher_pashok.png");
        item1_texture.loadFromFile("../images/item_default.png");
        bug_texture.loadFromFile("../images/bug.png");
    }

    void game::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        double active_v = active_player.get_v();
        double active_h = active_player.get_h();

        states.transform *= getTransform();

        sf::Color bg_color = sf::Color(254, 226, 183);
        sf::Color outline_color = sf::Color(58, 0, 0);

        sf::RectangleShape frame_shape(sf::Vector2f(2520, 750));
        frame_shape.setFillColor(sf::Color::White);
        frame_shape.setOutlineThickness(20.f);
        frame_shape.setOutlineColor(outline_color);
        target.draw(frame_shape, states);

        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(cell_v_size, cell_h_size));
        //shape.setOutlineThickness(1.f);
        //shape.setOutlineColor(color);

        for (unsigned int i = 0; i < h_table; i++) {
            for (unsigned int j = 0; j < v_table; j++) {
                if (map[i][j] == -2) {
                    shape.setTexture(&unwalkable_field_texture);
                } else {
                    shape.setTexture(&walkable_field_texture);
                }
                sf::Vector2f position(j * (cell_v_size), i * (cell_h_size));
                shape.setPosition(position);
                target.draw(shape, states);
            }
        }

        sf::RectangleShape active_player_shape(sf::Vector2f(cell_v_size, cell_h_size));
        if (active_player.get_graphic_phase() == 0) {
            if (active_player.get_direction() == 1) {
                active_player_shape.setTexture(&active_player_texture_right);
            } else if (active_player.get_direction() == 2) {
                active_player_shape.setTexture(&active_player_texture_back);
            } else if (active_player.get_direction() == 3) {
                active_player_shape.setTexture(&active_player_texture_left);
            } else if (active_player.get_direction() == 4) {
                active_player_shape.setTexture(&active_player_texture_front);
            }
        } else {
            if (active_player.get_direction() == 1) {
                active_player_shape.setTexture(&active_player_texture_right_moving);
            } else if (active_player.get_direction() == 2) {
                active_player_shape.setTexture(&active_player_texture_back_moving);
            } else if (active_player.get_direction() == 3) {
                active_player_shape.setTexture(&active_player_texture_left_moving);
            } else if (active_player.get_direction() == 4) {
                active_player_shape.setTexture(&active_player_texture_front_moving);
            }
        }

        sf::Vector2f active_player_position(active_v * (cell_v_size),
                                            active_h * (cell_h_size));
        active_player_shape.setPosition(active_player_position);

        sf::RectangleShape teacher1_shape(sf::Vector2f(cell_v_size, cell_h_size));
        teacher1_shape.setTexture(&teacher1_texture);
        sf::Vector2f teacher1_position(teachers[0].get_v() * (cell_v_size),
                                       teachers[0].get_h() * (cell_h_size));
        teacher1_shape.setPosition(teacher1_position);

        sf::RectangleShape teacher2_shape(sf::Vector2f(cell_v_size, cell_h_size));
        teacher2_shape.setTexture(&teacher2_texture);
        sf::Vector2f teacher2_position(teachers[1].get_v() * (cell_v_size),
                                       teachers[1].get_h() * (cell_h_size));
        teacher2_shape.setPosition(teacher2_position);

        sf::RectangleShape teacher3_shape(sf::Vector2f(cell_v_size, cell_h_size));
        teacher3_shape.setTexture(&teacher3_texture);
        sf::Vector2f teacher3_position(teachers[2].get_v() * (cell_v_size),
                                       teachers[2].get_h() * (cell_h_size));
        teacher3_shape.setPosition(teacher3_position);

        sf::RectangleShape item1_shape(sf::Vector2f(cell_v_size, cell_h_size));
        item1_shape.setTexture(&item1_texture);
        sf::Vector2f item1_position(displayed_items[0].get_v() * (cell_v_size),
                                    displayed_items[0].get_h() * (cell_h_size));
        item1_shape.setPosition(item1_position);

        sf::RectangleShape item2_shape(sf::Vector2f(cell_v_size, cell_h_size));
        item2_shape.setTexture(&unwalkable_field_texture);
        sf::Vector2f item2_position(displayed_items[1].get_v() * (cell_v_size),
                                    displayed_items[1].get_h() * (cell_h_size));
        item2_shape.setPosition(item2_position);

        sf::RectangleShape menu_button(sf::Vector2f(100, 40));
        menu_button.setFillColor(sf::Color::White);
        sf::Vector2f menu_button_position(active_v * (cell_v_size) - 570,
                                          active_h * (cell_h_size) - 290);
        menu_button.setPosition(menu_button_position);
        menu_button.setOutlineThickness(2.f);
        menu_button.setOutlineColor(sf::Color(73, 103, 113));

        sf::Text menu_text;
        menu_text.setFont(text_font);
        menu_text.setString(" Menu");
        menu_text.setCharacterSize(30);
        menu_text.setFillColor(sf::Color::Black);
        menu_text.setStyle(sf::Text::Italic);
        menu_text.setPosition(menu_button_position);

        sf::Text player_text;
        player_text.setFont(text_font);
        player_text.setString(active_player.get_name());
        player_text.setCharacterSize(20);
        player_text.setFillColor(sf::Color::Blue);
        player_text.setStyle(sf::Text::Italic);
        player_text.setPosition(active_player_position);

        sf::Text teacher1_text;
        teacher1_text.setFont(text_font);
        teacher1_text.setString(teachers[0].get_name());
        teacher1_text.setCharacterSize(20);
        teacher1_text.setFillColor(sf::Color::Red);
        teacher1_text.setStyle(sf::Text::Italic);
        teacher1_text.setPosition(teacher1_position);

        sf::Text teacher2_text;
        teacher2_text.setFont(text_font);
        teacher2_text.setString(teachers[1].get_name());
        teacher2_text.setCharacterSize(20);
        teacher2_text.setFillColor(sf::Color::Red);
        teacher2_text.setStyle(sf::Text::Italic);
        teacher2_text.setPosition(teacher2_position);

        sf::Text teacher3_text;
        teacher3_text.setFont(text_font);
        teacher3_text.setString(teachers[2].get_name());
        teacher3_text.setCharacterSize(20);
        teacher3_text.setFillColor(sf::Color::Red);
        teacher3_text.setStyle(sf::Text::Italic);
        teacher3_text.setPosition(teacher3_position);

        sf::Vector2f active_view_position(active_v * (cell_v_size) + 100,
                                          active_h * (cell_h_size) + 100);
        sf::View player_view(sf::FloatRect(0, 0,
                                           window->getSize().x, window->getSize().y));
        player_view.setCenter(active_view_position);
        window->setView(player_view);

        target.draw(active_player_shape, states);
        target.draw(player_text, states);
        target.draw(teacher1_shape, states);
        target.draw(teacher1_text, states);
        target.draw(teacher2_shape, states);
        target.draw(teacher2_text, states);
        target.draw(teacher3_shape, states);
        target.draw(teacher3_text, states);
        if (displayed_items[0].get_displayed()) {
            target.draw(item1_shape, states);
        }
        if (displayed_items[1].get_displayed()) {
            target.draw(item2_shape, states);
        }
        target.draw(menu_button, states);
        target.draw(menu_text, states);
    }

} // namespace university_game