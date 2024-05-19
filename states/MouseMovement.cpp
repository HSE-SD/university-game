#include "Application.cpp"

void onMouseMovementLeft(university_game::Application& app, sf::Event& event){
    if (event.mouseButton.x > 490 && event.mouseButton.x < 790
        && event.mouseButton.y > 195 && event.mouseButton.y < 245 &&
        !app.state.settings_opened) { // start new game

        app.state.game_started = true;
        app.state.game_started_ever = true;

        university_game::game new_game(&app.window, app.buttons.text_font, app.player_1);
        new_game.load_textures();
        app.my_game = new_game;
        app.my_game.setPosition(40.f, 40.f);

        app.my_game.get_teachers()[0] = app.teacher_1;
        app.my_game.get_teachers()[1] = app.teacher_2;
        app.my_game.get_teachers()[2] = app.teacher_3;
        app.first_required.set_displayed(true);
        app.my_game.get_displayed_items()[0] = app.first_required;
        app.third_required.set_displayed(true);
        app.my_game.get_displayed_items()[1] = app.third_required;
    }
    if (event.mouseButton.x > 490 && event.mouseButton.x < 790 && event.mouseButton.y > 295 &&
        event.mouseButton.y < 345 && !app.state.settings_opened && app.state.game_started_ever) { // load game
        app.state.game_started = true;
    }
    if (event.mouseButton.x > 490 && event.mouseButton.x < 790
        && event.mouseButton.y > 395 && event.mouseButton.y < 445 && !app.state.settings_opened) {
        app.state.settings_opened = true;
    }
    if (event.mouseButton.x > 590 && event.mouseButton.x < 690
        && event.mouseButton.y > 595 && event.mouseButton.y < 645 && app.state.settings_opened) {
        app.state.settings_opened = false;
    }
}