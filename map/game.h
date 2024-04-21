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
        game(sf::RenderWindow *window_, const sf::Font &text_font_param, player new_player);

        [[nodiscard]] int check_presence_of_teacher();

        void take_item_if_possible();

        bool move(int direction, int iteration);

        [[nodiscard]] player &get_player();

        [[nodiscard]] std::vector<teacher> &get_teachers();

        [[nodiscard]] std::vector<std::vector<int>> &get_map();

        [[nodiscard]] std::vector<item> &get_displayed_items();

        static void load_textures();

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

} // namespace university_game

#endif //UNIVERSITY_GAME_GAME_H
