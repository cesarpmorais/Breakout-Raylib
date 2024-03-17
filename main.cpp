#include "raylib.h"
#include <array>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "include/config.hpp"
#include "include/player.hpp"
#include "include/ball.hpp"
#include "include/brick.hpp"

int main(void) {
    // Init
    InitWindow(GameConfig::SCREEN_WIDTH, GameConfig::SCREEN_HEIGHT, "Breakout!");
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Variables

    Player player;
    Ball ball;

    int score = 0;
    bool speed_increased = true;

    // Create brick grid
    int size_grid_x = 15;
    int size_grid_y = 6;

    int upper_y_blocks = GameConfig::HEADER_SIZE + 2*GameConfig::BRICK_HEIGHT;
    std::array<std::array<Brick, 6>, 15> brick_grid;
    int x_position = 0;
    for (int i = 0; i < size_grid_x; i++) {
        int y_position = upper_y_blocks;
        for (int j = 0; j < size_grid_y; j++) {
            brick_grid[i][j].set_coordinates(x_position, y_position);
            y_position += GameConfig::BRICK_HEIGHT;
        }
        x_position += GameConfig::BRICK_WIDTH;
    }

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Move player
        if (IsKeyDown(KEY_D))
            player.update_position(GameConfig::PLAYER_SPEED);
        if (IsKeyDown(KEY_A))
            player.update_position(-GameConfig::PLAYER_SPEED);

        // Check collisions
        if(!ball.check_wall_collision(player.get_coordinates())) {
            std::cout << "Game over!" << std::endl;
            break;
        }
            
        // Player or bricks
        if (ball.get_y_coordinate() > (size_grid_y*GameConfig::BRICK_HEIGHT + upper_y_blocks)) {
            if(ball.check_player_collision(player.get_coordinates(), player.get_width())) 
                ball.change_direction();
        }
        else {
            bool collision_detected = false;
            for (int i = 0; i < size_grid_x; i++) {
                for (int j = 0; j < size_grid_y; j++) {
                    if (!brick_grid[i][j].is_active())
                        continue;

                    if(ball.check_brick_collision(brick_grid[i][j].get_coordinates())) {
                        brick_grid[i][j].deactivate();
                        collision_detected = true;
                        score++;
                        break;
                    }
                }
                if (collision_detected)
                    break;
            }
        }

        // Increase speed based on score
        if (score % 6 == 0 && !speed_increased) {
            ball.increase_speed();
            speed_increased = true;
        }
        else if (score % 6 != 0)
            speed_increased = false;
            
        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Draw Header
            int score_width = MeasureText(TextFormat("Score: %03i", score), 70);
            DrawText(TextFormat("Score: %03i", score), (GameConfig::SCREEN_WIDTH - score_width)/2, 0, 70, BLACK);
            DrawRectangle(0, GameConfig::HEADER_SIZE-5, GameConfig::SCREEN_WIDTH, 5, BLACK);

            player.draw_player();
            ball.draw_ball();
            // Draw bricks
            for (int i = 0; i < size_grid_x; i++) {
                for (int j = 0; j < size_grid_y; j++)
                    brick_grid[i][j].draw_brick();
            }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}