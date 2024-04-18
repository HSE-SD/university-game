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
                         std::vector<std::string> phrases_, std::string associated_quest_name_)
                : name(std::move(name_)),
                  id(id_),
                  active_v(active_v_),
                  active_h(active_h_),
                  phrases(std::move(phrases_)),
                  associated_quest_name(std::move(associated_quest_name_)) {}

        [[nodiscard]] std::string get_name() const {
            return name;
        }

        [[nodiscard]] int get_v() const {
            return active_v;
        }

        [[nodiscard]] int get_h() const {
            return active_h;
        }

        [[nodiscard]] int get_id() const {
            return id;
        }

        [[nodiscard]] int get_quest_stage() const {
            return quest_stage;
        }

        [[nodiscard]] std::string get_associated_quest_name() const {
            return associated_quest_name;
        }

        void satisfy_quest(player &player_) {
            if (!(player_.get_quest_taken().empty()
                  || player_.get_quest_taken() == associated_quest_name)) {
                return;
            }
            for (auto &quest: player_.get_list_of_quests()) {
                if (quest.get_name() != associated_quest_name) {
                    continue;
                }
                if (quest.get_condition() == "NOT COMPLETED") {
                    quest.mark_as_in_progress();
                    quest_stage++;
                    player_.set_quest_taken(associated_quest_name);
                } else if (quest.get_condition() == "IN PROGRESS") {
                    if (quest.get_required_item().get_name() == "none") {
                        quest_stage++;
                        quest.mark_as_completed();
                        return;
                    }
                    for (auto &item_: player_.get_inventory()) {
                        if (item_.get_name() != quest.get_required_item().get_name()) {
                            continue;
                        }
                        std::vector<item> new_items;
                        for (auto &new_item_: player_.get_inventory()) {
                            if (new_item_.get_name() != quest.get_required_item().get_name()) {
                                new_items.push_back(new_item_);
                            }
                        }
                        player_.set_inventory(new_items);
                        quest_stage++;
                        quest.mark_as_completed();
                        break;
                    }
                } else if (quest.get_condition() == "COMPLETED") {
                    quest_stage++;
                    bool flag = false;
                    if (quest.get_award().get_name() == "none") {
                        flag = true;
                    } else {
                        for (auto &new_item_: player_.get_inventory()) {
                            if (new_item_.get_name() == quest.get_award().get_name()) {
                                flag = true;
                                break;
                            }
                        }
                    }
                    if (!flag) {
                        player_.add_to_inventory(quest.get_award());
                    }
                    player_.check_for_level_up();
                    player_.set_quest_taken("");
                }
                break;
            }
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

} // namespace university_game

#endif // UNIVERSITY_GAME_TEACHER_H
