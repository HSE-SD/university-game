#ifndef UNIVERSITY_GAME_PLAYER_H
#define UNIVERSITY_GAME_PLAYER_H

#include "../constants/constants.h"
#include "../quest/quest.h"
#include "../inventory/item.h"

namespace university_game {

    class player : public sf::Drawable, public sf::Transformable {
    private:
        std::string name;
        int level = 1;
        std::vector<quest> list_of_quests;
        std::vector<item> inventory;
        double active_v = v_table / 2;
        double active_h = h_table / 2;
        int active_v_compare = v_table / 2;
        int active_h_compare = h_table / 2;
        std::string quest_taken;
        int direction = 4;
        int graphic_phase = 0;

    public:
        player() = default;

        explicit player(std::string name_,
                        std::vector<quest> &list_of_quests_,
                        std::vector<item> &inventory_);

        void set_name(std::string new_name);

        [[nodiscard]] std::string get_name() const;

        [[nodiscard]] int get_level() const;

        [[nodiscard]] std::vector<quest> &get_list_of_quests();

        [[nodiscard]] double get_v() const;

        [[nodiscard]] double get_h() const;

        [[nodiscard]] int get_v_compare() const;

        [[nodiscard]] int get_h_compare() const;

        [[nodiscard]] std::string get_quest_taken() const;

        [[nodiscard]] std::vector<item> get_inventory() const;

        [[nodiscard]] int get_direction() const;

        [[nodiscard]] int get_graphic_phase() const;

        void set_graphic_phase(int new_graphic_phase);

        void set_direction(int new_direction);

        void set_quest_taken(const std::string &new_quest_name);

        void set_v(double new_v);

        void set_h(double new_h);

        void set_v_compare(int new_v);

        void set_h_compare(int new_h);

        void add_to_inventory(const item &new_item);

        void set_inventory(std::vector<item> new_inventory);

        void check_for_level_up();

        [[nodiscard]] std::string display_available_quests() const;

        [[nodiscard]] std::string show_inventory() const;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

} // namespace university_game

#endif //UNIVERSITY_GAME_PLAYER_H
