#include "Application.cpp"

void onDrawingStarted(university_game::Application& app){
    app.window.clear();
    app.window.draw(app.my_game);
    if (app.state.inventory_and_quests_opened) {
        app.window.draw(app.my_game.get_player());
    }
    if (app.state.teacher_speaking) {
        const sf::Time freezeLength{sf::seconds(3.f)};
        sf::Clock freezeClock;
        while (freezeClock.getElapsedTime() < freezeLength) {
            app.window.draw(app.my_game.get_teachers()[app.state.id - 2]);
            app.window.display();
        }
        app.state.teacher_speaking = false;
        app.my_game.get_teachers()[app.state.id - 2].satisfy_quest(app.my_game.get_player());
    }
    app.window.display();
}