namespace university_game {
    struct state {
        bool game_started = false;
        bool settings_opened = false;
        bool inventory_and_quests_opened = false;
        bool teacher_speaking = false;
        bool something_extra_opened = false; // true if inventory opened
        bool game_started_ever = false;
        int executing_id = 0;
        int id = 0;
    };
}