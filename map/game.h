#ifndef UNIVERSITY_GAME_GAME_H
#define UNIVERSITY_GAME_GAME_H

#include "../constants/constants.h"
#include "../entities/player.h"
#include "../entities/teacher.h"

namespace university_game {

    class game : public sf::Drawable, public sf::Transformable {
    private:
        sf::RenderWindow *window = nullptr;
        sf::Font text_font;
        player active_player;
        std::vector<std::vector<int>> map;
        std::vector<teacher> teachers;
        std::vector<item> displayed_items;

    public:
        game(sf::RenderWindow *window_, const sf::Font &text_font_param, player new_player) :
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

        [[nodiscard]] int check_presence_of_teacher() {
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

        void take_item_if_possible() {
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

        bool move(int direction, int iteration) {
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

        [[nodiscard]] player &get_player() {
            return active_player;
        }

        [[nodiscard]] std::vector<teacher> &get_teachers() {
            return teachers;
        }

        [[nodiscard]] std::vector<std::vector<int>> &get_map() {
            return map;
        }

        [[nodiscard]] std::vector<item> &get_displayed_items() {
            return displayed_items;
        }

        void load_textures();

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

} // namespace university_game

#endif //UNIVERSITY_GAME_GAME_H
