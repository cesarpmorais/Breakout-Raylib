#include "raylib.h"
#include <array>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "include/config.hpp"
#include "include/player.hpp"
#include "include/ball.hpp"
#include "include/brick.hpp"

typedef enum GameScreen { TITLE = 0, GAMEPLAY, GAME_OVER, WIN } GameScreen;

int main(void) {
    // Init
    InitWindow(GameConfig::SCREEN_WIDTH, GameConfig::SCREEN_HEIGHT, "Breakout!");
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Variables
    Player player;
    Ball ball;
    int score = 0;
    bool speed_increased = true;

    GameScreen current_screen = TITLE;
    bool game_has_started = true;
   
    int start_button_width = MeasureText(TextFormat("START"), 70);
    int start_button_height = 70;
    Rectangle start_button = { (GameConfig::SCREEN_WIDTH - start_button_width)/2, 300, start_button_width, start_button_height };

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
        // Update variables
        switch(current_screen) {
            case TITLE:
            case GAME_OVER:
            case WIN:
            {
                bool mouse_inside_start_button = CheckCollisionPointRec(GetMousePosition(), start_button);
                if (IsGestureDetected(GESTURE_TAP) && mouse_inside_start_button) {
                    current_screen = GAMEPLAY;
                    game_has_started = true;
                }
            } break;
            case GAMEPLAY: {
                if (game_has_started) {
                    //Return to original state
                    score = 0;
                    speed_increased = true;
                    player.return_to_start();
                    ball.return_to_start();

                    //Set bricks to active
                    for (int i = 0; i < size_grid_x; i++) {
                        for (int j = 0; j < size_grid_y; j++)
                            brick_grid[i][j].set_to_active();
                    }

                    game_has_started = false;
                }

                // Move player
                if (IsKeyDown(KEY_D))
                    player.update_position(GameConfig::PLAYER_SPEED);
                if (IsKeyDown(KEY_A))
                    player.update_position(-GameConfig::PLAYER_SPEED);

                // Check game over and win
                if(!ball.check_wall_collision(player.get_coordinates()))
                    current_screen = GAME_OVER;
                if(score >= 6*15)
                    current_screen = WIN;
                    
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

            } break;
            default: break;
        }

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);

            switch(current_screen) {
                case TITLE: {
                    // Title
                    int title_width = MeasureText(TextFormat("BREAKOUT!"), 100);
                    DrawText(TextFormat("BREAKOUT!"), (GameConfig::SCREEN_WIDTH - title_width)/2, 80, 100, BLACK);
                    
                    // Subtitle
                    int subtitle_width = MeasureText(TextFormat("A game by Cesar Morais"), 35);
                    DrawText(TextFormat("A game by Cesar Morais"), (GameConfig::SCREEN_WIDTH - subtitle_width)/2, 180, 35, DARKBLUE);

                    // Start Button
                    DrawText(TextFormat("START"), (GameConfig::SCREEN_WIDTH - start_button_width)/2, 300, 70, BLACK);
                } break;
                case GAMEPLAY: {
                    // Draw Header
                    int score_width = MeasureText(TextFormat("Score: %02i", score), 70);
                    DrawText(TextFormat("Score: %02i", score), (GameConfig::SCREEN_WIDTH - score_width)/2, 0, 70, BLACK);
                    DrawRectangle(0, GameConfig::HEADER_SIZE-5, GameConfig::SCREEN_WIDTH, 5, BLACK);

                    player.draw_player();
                    ball.draw_ball();
                    // Draw bricks
                    for (int i = 0; i < size_grid_x; i++) {
                        for (int j = 0; j < size_grid_y; j++)
                            brick_grid[i][j].draw_brick();
                    }
                } break;
                case GAME_OVER: {
                    int game_over_width = MeasureText(TextFormat("GAME OVER!"), 100);
                    DrawText(TextFormat("GAME OVER!"), (GameConfig::SCREEN_WIDTH - game_over_width)/2, 80, 100, RED);
                    DrawText(TextFormat("START"), (GameConfig::SCREEN_WIDTH - start_button_width)/2, 300, 70, BLACK);
                } break;
                case WIN: {
                    int win_width = MeasureText(TextFormat("YOU WIN!"), 100);
                    DrawText(TextFormat("YOU WIN!"), (GameConfig::SCREEN_WIDTH - win_width)/2, 80, 100, DARKGREEN);
                    DrawText(TextFormat("START"), (GameConfig::SCREEN_WIDTH - start_button_width)/2, 300, 70, BLACK);
                
                } break;
                default: break;
            }
        EndDrawing(); 
        
    }
    CloseWindow();

    return 0;
}