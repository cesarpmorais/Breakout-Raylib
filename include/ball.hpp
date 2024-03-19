#ifndef BALL_HPP
#define BALL_HPP

#include <raylib.h>
#include <cstdlib>
#include <ctime>

#include "config.hpp"

class Ball {
    private:
        int radius = 8;
        int centerX = GameConfig::SCREEN_WIDTH/2;
        int centerY = 7*GameConfig::SCREEN_HEIGHT/8 - 20;

        int speedX = 0;
        int speedY = 2;

        Color color = DARKGREEN;
    public:
        void draw_ball();

        bool check_wall_collision(Coordinates player_coordinates);
        bool check_player_collision(Coordinates player_coordinates, int player_width);
        bool check_brick_collision(Coordinates brick_coordinates);
        
        void change_direction();
        void increase_speed();
        void return_to_start();

        int get_y_coordinate();
};

#endif