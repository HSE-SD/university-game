#include "teacher.h"

namespace university_game {

    teacher::teacher(std::string name_, int id_, int active_v_, int active_h_,
                              std::vector<std::string> phrases_, std::string associated_quest_name_)
            : name(std::move(name_)),
              id(id_),
              active_v(active_v_),
              active_h(active_h_),
              phrases(std::move(phrases_)),
              associated_quest_name(std::move(associated_quest_name_)) {}

    [[nodiscard]] std::string teacher::get_name() const {
        return name;
    }

    [[nodiscard]] int teacher::get_v() const {
        return active_v;
    }

    [[nodiscard]] int teacher::get_h() const {
        return active_h;
    }

    [[nodiscard]] int teacher::get_id() const {
        return id;
    }

    [[nodiscard]] int teacher::get_quest_stage() const {
        return quest_stage;
    }

    [[nodiscard]] std::string teacher::get_associated_quest_name() const {
        return associated_quest_name;
    }

    void teacher::satisfy_quest(player &player_) {
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
