#include "ball.hpp"
#include <iostream>

void Ball::draw_ball() {
    this->centerX += this->speedX;
    this->centerY += this->speedY;

    DrawCircle(this->centerX, this->centerY, this->radius, this->color);
}

//Returns false if game over
bool Ball::check_wall_collision(Coordinates player_coordinates) {
    if (this->centerY + this->radius > player_coordinates.y + 40)
        return false;
    // If if reaches ceiling
    if (this->centerY - this->radius <= GameConfig::HEADER_SIZE) {
        this->speedY = -this->speedY;
    }
    if (this->centerX + this->radius >= GameConfig::SCREEN_WIDTH || this->centerX - this->radius <= 0)
        this->speedX = -this->speedX;

    return true;
}

bool Ball::check_player_collision(Coordinates player_coordinates, int player_width) {
    if (this->centerY + this->radius >= player_coordinates.y) {
        if (this->centerX - this->radius <= player_coordinates.x + player_width && this->centerX + this->radius >= player_coordinates.x) {
            // Add randomized speed increase/direction change
            this->speedY = -this->speedY;
            this->speedX = -this->speedX;
            return true;
        }
    }
    return false;
}

bool Ball::check_brick_collision(Coordinates brick_coordinates) {
    // Collision from above or below
    if (this->centerY - this->radius <= brick_coordinates.y + GameConfig::BRICK_HEIGHT &&
    this->centerY + this->radius >= brick_coordinates.y &&
    !(this->centerX + this->radius < brick_coordinates.x || 
    this->centerX - this->radius > brick_coordinates.x + GameConfig::BRICK_WIDTH)
    ) {
        this->speedY = -this->speedY;
        return true;
    }

    return false;
}

void Ball::change_direction() {
    int random_number = std::rand() % 10 + 1;

    if (random_number > 1) {
        int new_direction = std::rand() % 7;
        if (this->speedX > 0)
            this->speedX -= new_direction;
        else
            this->speedX += new_direction;
    }
}

void Ball::increase_speed() {
    if (this->speedY > 0)
        speedY++;
    else
        speedY--;
}

int Ball::get_y_coordinate() {
    return this->centerY - this->radius;
}