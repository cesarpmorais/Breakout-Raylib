#ifndef BRICK_HPP
#define BRICK_HPP

#include <raylib.h>

#include "config.hpp"

class Brick {
    private:
        int width = GameConfig::BRICK_WIDTH;
        int height = GameConfig::BRICK_HEIGHT;
        Color color = BLACK;

        int posX = GameConfig::SCREEN_WIDTH/2 - 40;
        int posY = 4*GameConfig::SCREEN_HEIGHT/8;
        bool active = true;
        
    public:
        Brick() {}
        void draw_brick();
        void set_coordinates(int x, int y);
        void deactivate();


        Coordinates get_coordinates();
        int get_width();

        bool is_active();
        void set_to_active();

        ~Brick();
};

#endif