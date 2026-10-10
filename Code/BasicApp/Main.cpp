#include "raylib.h"
#include "Program.hpp"

int main(){


    int screenWidth = 800;
    int screenHeight = 600;


    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Basic App for ESP");

    SetTargetFPS(60);

    std::cout << "Starting" << std::endl;


    int ClickCount = 0;
    int Roboto1FontSize = 40;

    Font Roboto1 = LoadFontEx("Roboto1.ttf", Roboto1FontSize, 0, 0);

    ESP32_Program esp32;
    bool ok = esp32.connect("COM2");
    //Ill Modify the COM Port later when ill get the ESP32

    bool isLedOn = false;
    Rectangle LedButton = { 300, 200, 250, 150 };
    Rectangle ExitButton = { 680, 30, 100, 50 };
    Rectangle ReconnectButton = { 620, 500, 150, 75 };
    

    bool isReconnecting = false;
    float ReconnectTimer = 0.0f;

    while(!WindowShouldClose()){


        Vector2 MousePos = GetMousePosition();
        bool isHoveringButton = CheckCollisionPointRec(MousePos, LedButton);
        bool isHoveringExit = CheckCollisionPointRec(MousePos, ExitButton);
        bool isHoveringReconnect = CheckCollisionPointRec(MousePos, ReconnectButton);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isHoveringButton){


            isLedOn = !isLedOn;
            esp32.setLed(isLedOn);
            ClickCount++;

        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isHoveringExit){

            CloseWindow();

            std::cout << "Exiting" << std::endl;

        }

        if(isHoveringReconnect && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            esp32.connect("COM2");
            //Same here ill modify the com port later
            esp32.setLed(isLedOn);
            isReconnecting = true;
            ReconnectTimer = 1.0f;

            std::cout << "Trying to reconnect..." << std::endl;

        }
    

        if(isReconnecting){
            ReconnectTimer -= GetFrameTime();
            if(ReconnectTimer <= 0.0f){
                isReconnecting = false;
            }
        }

        BeginDrawing();

        ClearBackground(Color{25,28,40,225});



        Color ButtonColor = DARKGRAY;
        if(isHoveringButton){
            ButtonColor = GRAY;
        }

        Color ExitButtonColor = RED;
        if(isHoveringExit){
            ExitButtonColor = MAROON;
        }

        Color ReconnectButtonColor = RED;
        if(isHoveringReconnect){
            ReconnectButtonColor = MAROON;
        }

        DrawTextEx(Roboto1, "ESP32 Led Test App", { 300, 20 }, Roboto1FontSize, 2, RAYWHITE);

        DrawRectangleRounded(LedButton,0.5f, 16, ButtonColor);


        DrawRectangleRounded(ExitButton, 0.5f, 16, ExitButtonColor);
        DrawTextEx(Roboto1, "Exit", { 700, 40 }, Roboto1FontSize, 2, RAYWHITE);

        DrawRectangleRounded(ReconnectButton, 0.5f, 16, ReconnectButtonColor);
        DrawTextEx(Roboto1, "Reconnect", { 630, 520 }, 30, 2, RAYWHITE);

        DrawCircle(50, 50, 40, isLedOn ? GREEN : GRAY);

        DrawTextEx(Roboto1, isLedOn ? "LED ON" : "LED OFF", { 350, 100 }, Roboto1FontSize, 2, isLedOn ? GREEN : RED);

        DrawTextEx(Roboto1, esp32.isConnected() ? "Connected" : "Disconnected", { 320, 400 }, Roboto1FontSize, 2, esp32.isConnected() ? GREEN : RED);
        
        DrawTextEx(Roboto1, "Turn Led On/Off", { 320, 250 }, 35, 2, isLedOn ? GREEN : RED);

        DrawTextEx(Roboto1, TextFormat("Click Count: %i", ClickCount), { 30, 550 }, 30, 2, RAYWHITE);

        if(isReconnecting){
            DrawTextEx(Roboto1, "Reconnecting...", { 400, 500 }, 30, 2, YELLOW);
        }



        EndDrawing();

        
        
    }

    CloseWindow();

    std::cout << "Exiting" << std::endl;

    return 0;


}