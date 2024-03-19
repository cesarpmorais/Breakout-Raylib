#include "player.hpp"

void Player::draw_player() {
    DrawRectangle(this->posX, this->posY, this->width, this->height, this->color);
}

void Player::update_position(int xIncrement) {
    this->posX += xIncrement;

    if (this->posX < 0)
        this->posX = 0;
    if (this->posX > GameConfig::SCREEN_WIDTH - this->width)
        this->posX = GameConfig::SCREEN_WIDTH - this->width;
}

void Player::return_to_start() {
    this->posX = GameConfig::SCREEN_WIDTH/2 - width/2;
    this->posY = 7*GameConfig::SCREEN_HEIGHT/8;
}

Coordinates Player::get_coordinates() {
    return Coordinates(this->posX, this->posY);
}

int Player::get_width() {
    return this->width;
}