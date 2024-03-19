#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <raylib.h>

#include "config.hpp"

class Player {
    private:
        int width = 130;
        int height = 20;
        int posX = GameConfig::SCREEN_WIDTH/2 - width/2;
        int posY = 7*GameConfig::SCREEN_HEIGHT/8;
        Color color = DARKBLUE;

    public:
        void draw_player();
        void update_position(int xIncrement);
        void return_to_start();

        Coordinates get_coordinates();
        int get_width();
};

#endif