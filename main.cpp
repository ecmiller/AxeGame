#include "raylib.h"
#include <cstdio>

int main() {
    // Window dimensions
    int window_width { 1280 };
    int window_height { 720 };

    // Game Over message settings
    int game_over_x { window_width / 2 };
    int game_over_y { window_height / 2 };
    int game_over_fontsize { 20 };

    // Circle coordinates
    int circle_x { window_width / 2 };
    int circle_y { window_height / 2 };
    int circle_radius { 25 };

    // Circle hitbox edges
    int l_circle_x { circle_x - circle_radius }; // Left edge
    int r_circle_x { circle_x + circle_radius }; // Right edge
    int u_circle_y { circle_y - circle_radius }; // Upper edge
    int b_circle_y { circle_y + circle_radius }; // Bottom edge

    // Axe coordinates
    int axe_x { (window_width / 2) + (window_width / 4) };
    int axe_y { 0 };
    int axe_length { 50 };

    // Axe movement direction
    int direction = 10;

    // Axe hitbox edges
    int l_axe_x { axe_x}; // Left edge
    int r_axe_x { axe_x + axe_length }; // Right edge
    int u_axe_y { axe_y}; // Upper edge
    int b_axe_y { axe_y + axe_length }; // Bottom edge

    bool collision_with_axe =
            (b_axe_y >= u_circle_y) && // Bottom axe edge overlaps with upper circle edge
            (u_axe_y <= b_circle_y) && // Upper axe edge overlaps with bottom circle edge
            (r_axe_x >= l_circle_x) && // Right axe edge overlaps with left circle edge
            (l_axe_x <= r_circle_x); // Left axe edge overlaps with right circle edge

    // Movement distance
    int horizontal_move_distance { 10 };

    SetTargetFPS(60.0f);
    InitWindow(window_width, window_height, "Window Title");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);

        if(collision_with_axe)
        {
            DrawText("Game Over!", game_over_x, game_over_y, game_over_fontsize, RED);
        }
        else 
        {
            // Game logic begins

            // Update circle edges
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;

            // Update axe edges
            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_length;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_length;

            // Collision detection
            collision_with_axe = 
                (b_axe_y >= u_circle_y) && 
                (u_axe_y <= b_circle_y) &&
                (r_axe_x >= l_circle_x) &&
                (l_axe_x <= r_circle_x);

            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            // Move the axe (vertically)
            if (axe_y < 0 || axe_y > window_height)
            {
                direction *= -1;
            }
            
            axe_y += direction;

            // Button detection and window bounds check
            if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && (circle_x <= window_width))
            {
                circle_x += horizontal_move_distance;
            } 
            else if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && (circle_x >= 0))
            {
                circle_x -= horizontal_move_distance;
            }
            // Game logic ends
        }
        EndDrawing();
    }
    return 0;
}