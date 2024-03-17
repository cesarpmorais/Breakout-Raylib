#ifndef CONFIG_HPP
#define CONFIG_HPP

// Interface for player/brick coordinates
struct Coordinates {
    int x;
    int y;

    Coordinates(int x, int y) : x(x), y(y) {}
};

class GameConfig {
    public:
    // Static global variables
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;

        static int HEADER_SIZE;

        static int PLAYER_SPEED;

        static int BRICK_WIDTH;
        static int BRICK_HEIGHT;
};

#endif