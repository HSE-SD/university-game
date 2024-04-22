#ifndef UNIVERSITY_GAME_CONSTANTS_H
#define UNIVERSITY_GAME_CONSTANTS_H

#include <cmath>
#include <fstream>
#include <set>
#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <random>
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include <cstdio>

#ifdef __APPLE__
#define path_to_font ("../fonts/arial_mac.ttf")
#else
#define path_to_font ("../fonts/arial_unix.ttf")
#endif

namespace university_game {

    const int v_table = 28;
    const int h_table = 6;
    const int cell_v_size = 90;
    const int cell_h_size = 125;

}  // namespace university_game

#endif // UNIVERSITY_GAME_CONSTANTS_H