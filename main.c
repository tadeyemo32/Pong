#include <stdio.h>
#include <raylib.h>
#define ScreenWidth 800
#define ScreenHeight 600 
#define PaddleWidth 25
#define PaddleHeight 100
#define PaddleSpeed 3


int SCORE =0; 

typedef enum {
    STATE_MENU,
    STATE_PLAYING
} GameState;
GameState gameState = STATE_MENU;





typedef struct Paddle{

float x ;
float y ;

}Paddle;

void Menu(Sound fxButton) {

    int x  = (ScreenWidth - 80)/2;
    int y = (ScreenHeight - 30)/2;
    Rectangle start = {x, y, 100, 30};
    DrawRectangleRec(start, DARKGRAY);
    DrawText("START", x + 15, y + 10, 20, RAYWHITE);

    char buffer[16];
    sprintf(buffer, "%d", SCORE);  
    DrawText(buffer, 10, 10, 20, WHITE);



    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), start)) {
        PlaySound(fxButton);        
        gameState = STATE_PLAYING;  
    }


}


void update(Paddle *left, Paddle *right,float deltaTime ){

    char buffer[16];
    sprintf(buffer, "%d", SCORE);  
    DrawText(buffer, 10, 10, 20, WHITE);

    DrawRectangle((int)left->x, (int)left->y, PaddleWidth, PaddleHeight, RAYWHITE);
    DrawRectangle((int)right->x, (int)right->y, PaddleWidth, PaddleHeight, RAYWHITE);
    


    if (IsKeyDown(KEY_W)) left->y -= PaddleSpeed * deltaTime * 200;
    if (IsKeyDown(KEY_S)) left->y += PaddleSpeed * deltaTime * 200;
    if (IsKeyDown(KEY_UP)) right->y -= PaddleSpeed * deltaTime * 200;
    if (IsKeyDown(KEY_DOWN)) right->y += PaddleSpeed * deltaTime * 200;
    // Clamp left paddle
if (left->y < 0) left->y = 0;
if (left->y + PaddleHeight > ScreenHeight) left->y = ScreenHeight - PaddleHeight;

// Clamp right paddle
if (right->y < 0) right->y = 0;
if (right->y + PaddleHeight > ScreenHeight) right->y = ScreenHeight - PaddleHeight;

  


}


int main(void){
    
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);  // ✅ This fixes the scaling on macOS
InitWindow(ScreenWidth, ScreenHeight, "Pong");
InitAudioDevice();
    Sound fxButton = LoadSound("assets/button.wav");
  
    Paddle left = {0, (ScreenHeight - PaddleHeight) / 2};
    Paddle right = {ScreenWidth - PaddleWidth, (ScreenHeight - PaddleHeight) / 2};
    


    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();


        BeginDrawing();
            ClearBackground(BLACK);
          
            if (gameState == STATE_MENU) {
                Menu(fxButton);
            } else if (gameState == STATE_PLAYING) {
                //Game Logic 
                update(&left,&right,deltaTime);
            

            }

        EndDrawing();
    
    }
    CloseWindow();    
    
    

    return 0;
}

//    gcc -o game main.c -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo 
