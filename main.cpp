#include <SFML/Graphics.hpp>
#include "states/Application.cpp"
#include "states/OnKeyPressed.cpp"
#include "states/DrawingStarted.cpp";
#include "states/MouseMovement.cpp";

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "University game");
    university_game::Application app(window, university_game::game(nullptr, sf::Font(), university_game::player()));



    university_game::player player_1("You", app.initial_quests, app.initial_items);
    university_game::teacher teacher_1("Mr. Antipoff", 2, 1, 1,
                                       {"Hey! Wanna mark? Bring me my algebra book.",
                                        "Did you actually find it?", "Alright, here we go."}, app.quests[0].get_name());
    university_game::teacher teacher_2("Mr. Khrabroff", 3, 12, 5,
                                       {"Hey!",
                                        "I've heard that you're a trickster now.",
                                        "Good job! See you later."}, app.quests[1].get_name());
    university_game::teacher teacher_3("Pashok", 4, 22, 2,
                                       {"Yo! Find a wall, where I've hidden money.",
                                        "You've found it, right?",
                                        "Thank you, man. Appreciate that."}, app.quests[2].get_name());
    app.teacher_1 = teacher_1;
    app.teacher_2 = teacher_2;
    app.teacher_3 = teacher_3;


    while (window.isOpen()) {
        if (app.state.game_started) {
            sf::Event event{};
            while (app.window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    app.window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    university_game::OnKeyPressed onKeyPressed(event, app);
                    onKeyPressed.action();
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (event.mouseButton.x > 0
                        && event.mouseButton.x < 110
                        && event.mouseButton.y > 0
                        && event.mouseButton.y < 50
                        && !app.state.something_extra_opened) {
                        app.state.game_started = false;
                        window.setView(app.standard_view);
                    }
                }
            }

            if (app.state.game_started) { // drawing process starts here
                onDrawingStarted(app);
            }
        } else {
            sf::Event event{};
            while (app.window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    app.window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        app.window.close();
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    onMouseMovementLeft(app, event);
                }
            }
            app.window.clear();
            app.buttons.draw(window, app.state.settings_opened);
        }
    }

    return 0;
}