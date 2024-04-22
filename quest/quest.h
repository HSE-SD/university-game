#ifndef UNIVERSITY_GAME_QUEST_H
#define UNIVERSITY_GAME_QUEST_H

#include "../constants/constants.h"
#include "../inventory/item.h"

namespace university_game {

    class quest {
    private:
        std::string name;
        std::string description;
        int required_level = 1;
        int is_completed = 0;
        item required_item;
        item award;

    public:
        quest() = default;

        explicit quest(std::string name_,
                       std::string description_,
                       int required_level_,
                       item required_item_,
                       item award_)
                : name(std::move(name_)),
                  description(std::move(description_)),
                  required_level(required_level_),
                  required_item(std::move(required_item_)),
                  award(std::move(award_)) {}

        [[nodiscard]] int get_required_level() const {
            return required_level;
        }

        [[nodiscard]] std::string get_name() const {
            return name;
        }

        [[nodiscard]] std::string get_description() const {
            return description;
        }

        [[nodiscard]] item get_required_item() const {
            return required_item;
        }

        [[nodiscard]] item get_award() const {
            return award;
        }

        [[nodiscard]] std::string get_condition() const {
            if (is_completed == 0) {
                return "NOT COMPLETED";
            }
            if (is_completed == 1) {
                return "IN PROGRESS";
            }
            if (is_completed == 2) {
                return "COMPLETED";
            }
            return "";
        }

        void mark_as_completed() {
            is_completed = 2;
        }

        void mark_as_in_progress() {
            is_completed = 1;
        }

        [[maybe_unused]] void create_from_json(const std::string &filename) {
            std::ifstream infile("../quest/quest_artifacts/" + filename);
            std::string input;
            std::getline(infile, input);

            rapidjson::Document d;
            d.Parse(input.c_str());

            required_item = item(d["required_item_name"].GetString(), d["required_item_usage"].GetString(),
                                 d["required_item_v"].GetInt(), d["required_item_h"].GetInt());
            award = item(d["award_item_name"].GetString(), d["award_item_usage"].GetString(),
                         d["award_item_v"].GetInt(), d["award_item_h"].GetInt());
            name = d["quest_name"].GetString();
            description = d["quest_description"].GetString();
            required_level = d["required_level"].GetInt();
            infile.close();
        }
    };

} // namespace university_game

#endif //UNIVERSITY_GAME_QUEST_H
