#ifndef UNIVERSITY_GAME_ITEM_H
#define UNIVERSITY_GAME_ITEM_H

#include "../constants/constants.h"

namespace university_game {

    class item {
    private:
        std::string name;
        std::string usage;
        int active_v = 0;
        int active_h = 0;
        bool displayed = false;

    public:
        item() = default;

        explicit item(std::string name_, std::string usage_, int active_v_, int active_h_)
                : name(std::move(name_)),
                  usage(std::move(usage_)),
                  active_v(active_v_),
                  active_h(active_h_) {}

        [[nodiscard]] std::string get_name() const {
            return name;
        }

        [[nodiscard]] std::string get_usage() const {
            return usage;
        }

        [[nodiscard]] std::string get_info() const {
            return "Name: " + get_name() + "\nUsage: " + get_usage() + "\n\n";
        }

        [[nodiscard]] int get_v() const {
            return active_v;
        }

        [[nodiscard]] int get_h() const {
            return active_h;
        }

        [[nodiscard]] bool get_displayed() const {
            return displayed;
        }

        void set_displayed(bool condition) {
            displayed = condition;
        }
    };

} // namespace university_game

#endif // UNIVERSITY_GAME_ITEM_H
