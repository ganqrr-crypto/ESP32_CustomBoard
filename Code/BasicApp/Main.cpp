#include "raylib.h"
#include "Program.hpp"

int main(){


    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Basic App for ESP");

    SetTargetFPS(60);



    int Roboto1FontSize = 40;

    Font Roboto1 = LoadFontEx("Roboto1.ttf", Roboto1FontSize, 0, 0);

    ESP32_Program esp32;
    bool ok = esp32.connect("COM2");


    bool isLedOn = false;
    Rectangle LedButton = { 300, 200, 250, 150 };


    while(!WindowShouldClose()){


        Vector2 MousePos = GetMousePosition();
        bool isHoveringButton = CheckCollisionPointRec(MousePos, LedButton);
   


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isHoveringButton){


            isLedOn = !isLedOn;
             esp32.setLed(isLedOn);

        }


    

        BeginDrawing();

        ClearBackground(Color{25,28,40,225});



        Color ButtonColor = DARKGRAY;

        if(isHoveringButton){
            ButtonColor = GRAY;
        }

        DrawTextEx(Roboto1, "ESP32 Led Test App", { 300, 20 }, Roboto1FontSize, 2, RAYWHITE);

        DrawRectangleRounded(LedButton,0.5f, 16, ButtonColor);

        DrawTextEx(Roboto1, isLedOn ? "LED ON" : "LED OFF", { 350, 100 }, Roboto1FontSize, 2, isLedOn ? GREEN : RED);

        DrawTextEx(Roboto1, esp32.isConnected() ? "Connected" : "Disconnected", { 320, 400 }, Roboto1FontSize, 2, esp32.isConnected() ? GREEN : RED);
        
        DrawTextEx(Roboto1, "Turn Led On/Off", { 320, 250 }, 35, 2, isLedOn ? GREEN : RED);




        EndDrawing();

        
        
    }

    CloseWindow();

    return 0;


}