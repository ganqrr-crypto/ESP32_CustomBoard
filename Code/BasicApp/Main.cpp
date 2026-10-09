#include "raylib.h"
#include "Program.hpp"

int main(){


    InitWindow(800,600, "Basic App for ESP");

    SetTargetFPS(60);

    ESP32_Program esp32;
    bool ok = esp32.connect("COM2");


    bool isLedOn = false;
    Rectangle LedButton = { 300, 200, 250, 150 };


    while(!WindowShouldClose()){



        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            Vector2 MousePos = GetMousePosition();

            if(CheckCollisionPointRec(MousePos, LedButton)){

                isLedOn = !isLedOn;
                esp32.setLed(isLedOn);

            }

        }


        BeginDrawing();

        ClearBackground(RAYWHITE);


        DrawRectangleRec(LedButton, DARKGRAY);

        DrawText(isLedOn ? "LED ON" : "LED OFF", 350, 100, 20, isLedOn ? GREEN : RED);

        DrawText(esp32.isConnected() ? "Connected" : "Disconnected", 350, 400, 20, esp32.isConnected() ? GREEN : RED);

        EndDrawing();

        
        
    }

    CloseWindow();

    return 0;


}