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
                        std::vector<item> &inventory_)
                : name(std::move(name_)),
                  list_of_quests(list_of_quests_),
                  inventory(inventory_),
                  active_v(v_table / 2),
                  active_h(h_table / 2),
                  active_v_compare(v_table / 2),
                  active_h_compare(h_table / 2) {}

        void set_name(std::string new_name) {
            name = std::move(new_name);
        }

        [[nodiscard]] std::string get_name() const {
            return name;
        }

        [[nodiscard]] int get_level() const {
            return level;
        }

        [[nodiscard]] std::vector<quest> &get_list_of_quests() {
            return list_of_quests;
        }

        [[nodiscard]] double get_v() const {
            return active_v;
        }

        [[nodiscard]] double get_h() const {
            return active_h;
        }

        [[nodiscard]] int get_v_compare() const {
            return active_v_compare;
        }

        [[nodiscard]] int get_h_compare() const {
            return active_h_compare;
        }

        [[nodiscard]] std::string get_quest_taken() const {
            return quest_taken;
        }

        [[nodiscard]] std::vector<item> get_inventory() const {
            return inventory;
        }

        [[nodiscard]] int get_direction() const {
            return direction;
        }

        [[nodiscard]] int get_graphic_phase() const {
            return graphic_phase;
        }

        void set_graphic_phase(int new_graphic_phase) {
            graphic_phase = new_graphic_phase;
        }

        void set_direction(int new_direction) {
            direction = new_direction;
        }

        void set_quest_taken(const std::string &new_quest_name) {
            quest_taken = new_quest_name;
        }

        void set_v(double new_v) {
            active_v = new_v;
        }

        void set_h(double new_h) {
            active_h = new_h;
        }

        void set_v_compare(int new_v) {
            active_v_compare = new_v;
        }

        void set_h_compare(int new_h) {
            active_h_compare = new_h;
        }

        void add_to_inventory(const item &new_item) {
            inventory.push_back(new_item);
        }

        void set_inventory(std::vector<item> new_inventory) {
            inventory = std::move(new_inventory);
        }

        void check_for_level_up() {
            for (const auto &m_quest: list_of_quests) {
                if (m_quest.get_required_level() <= get_level() && m_quest.get_condition() == "NOT COMPLETED") {
                    return;
                }
            }
            level++;
        }

        [[nodiscard]] std::string display_available_quests() const {
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

        [[nodiscard]] std::string show_inventory() const {
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

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

} // namespace university_game

#endif //UNIVERSITY_GAME_PLAYER_H
