#ifndef UNIVERSITY_GAME_TEACHER_H
#define UNIVERSITY_GAME_TEACHER_H

#include "../constants/constants.h"
#include "player.h"

namespace university_game {

    class teacher : public sf::Drawable, public sf::Transformable {
    private:
        std::string name;
        int id = 2;
        int active_v = 0;
        int active_h = 0;
        std::vector<std::string> phrases;
        std::string associated_quest_name;
        int quest_stage = 0;

    public:
        teacher() = default;

        explicit teacher(std::string name_, int id_, int active_v_, int active_h_,
                         std::vector<std::string> phrases_, std::string associated_quest_name_);

        [[nodiscard]] std::string get_name() const;

        [[nodiscard]] int get_v() const;

        [[nodiscard]] int get_h() const;

        [[nodiscard]] int get_id() const;

        [[nodiscard]] int get_quest_stage() const;

        [[nodiscard]] std::string get_associated_quest_name() const;

        void satisfy_quest(player &player_);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

} // namespace university_game

#endif // UNIVERSITY_GAME_TEACHER_H
