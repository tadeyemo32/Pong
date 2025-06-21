#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#define ScreenWidth 800
#define ScreenHeight 600 
#define PaddleWidth 30
#define PaddleHeight 100
#define PaddleSpeed 3
#define BallRadius 15

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



typedef struct Ball{

    float x ;
    float y ;
    float xv; 
    float yv;
    }Ball;

void Menu(Sound fxButton) {
    int x  = (ScreenWidth - 80)/2;
    int y = (ScreenHeight - 30)/2;
    Rectangle start = {x, y, PaddleHeight, PaddleWidth};
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

void resetBall(Ball *ball){


ball->x =400 ;
ball->y =300;

}
void resetPaddle(Paddle *paddle_left ,Paddle *paddle_right){
paddle_left->x =0 ;
paddle_left->y = (ScreenHeight - PaddleHeight) / 2;

paddle_right->x =ScreenWidth - PaddleWidth ;
paddle_right->y =(ScreenHeight - PaddleHeight) / 2 ;


}
void update(Ball *ball,Paddle *left, Paddle *right,float deltaTime ){

    char buffer[16];
    sprintf(buffer, "%d", SCORE);  
    DrawText(buffer, 400, 10, 20, WHITE);

    DrawRectangle((int)left->x, (int)left->y, PaddleWidth, PaddleHeight, RAYWHITE);
    DrawRectangle((int)right->x, (int)right->y, PaddleWidth, PaddleHeight, RAYWHITE);
    DrawCircle((int)ball->x,(int)ball->y,BallRadius,RAYWHITE);


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

ball->x +=ball->xv*deltaTime*200;
ball->y += ball->yv*deltaTime*200;
 
if (ball->y - BallRadius < 0) {
    ball->y = BallRadius;
    ball->yv *= -1;
}

if (ball->x - BallRadius < 0) {
    printf("Ball out of Boundw");
    resetBall(ball);
    resetPaddle(left,right);
  gameState = STATE_MENU;
}

if (ball->x + BallRadius > ScreenWidth) {
    printf("Ball out of Boundw");
resetBall(ball);
resetPaddle(left,right);

  gameState = STATE_MENU;
  }

if (ball->y + BallRadius > ScreenHeight) {
    ball->y = ScreenHeight - BallRadius;
    ball->yv *= -1;
}


if (ball->y + BallRadius > left->x) {
    ball->y = ScreenHeight - BallRadius;
    ball->yv *= -1;
}
Vector2 center = {ball->x,ball->y};
Rectangle leftRec = {left->x, left->y, PaddleHeight, PaddleWidth};
if (CheckCollisionCircleRec(center,BallRadius,leftRec)){
printf("Collsion Detecte");

}




}


int main(void){
    
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);  
InitWindow(ScreenWidth, ScreenHeight, "Pong");
InitAudioDevice();
    Sound fxButton = LoadSound("assets/button.wav");
  
    Paddle left = {0, (ScreenHeight - PaddleHeight) / 2};
    Paddle right = {ScreenWidth - PaddleWidth, (ScreenHeight - PaddleHeight) / 2};
    Ball ball = {400,300,-1,0};


    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();


        BeginDrawing();
            ClearBackground(BLACK);
          
            if (gameState == STATE_MENU) {
                Menu(fxButton);
            } else if (gameState == STATE_PLAYING) {
                //Game Logic 
                update(&ball,&left,&right,deltaTime);

            }

        EndDrawing();
    
    }
 
    CloseWindow();    
    
    

    return 0;
}

//    gcc -o game main.c -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo 
