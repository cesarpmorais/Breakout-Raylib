#include "brick.hpp"

void Brick::draw_brick() {
    if (this->active)
        DrawRectangleLines(this->posX, this->posY, this->width, this->height, this->color);
}

void Brick::set_coordinates(int x, int y) {
    this->posX = x;
    this->posY = y;
}

void Brick::deactivate() {
    this->active = false;
}

Coordinates Brick::get_coordinates() {
    return Coordinates(this->posX, this->posY);
}

int Brick::get_width() {
    return this->width;
}

bool Brick::is_active() {
    return this->active;
}

void Brick::set_to_active() {
    this->active = true;
}

Brick::~Brick() {}