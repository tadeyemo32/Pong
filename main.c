#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#define ScreenWidth 800
#define ScreenHeight 600 
#define PaddleWidth 30
#define PaddleHeight 100
#define PaddleSpeed 3
#define BallRadius 15

int SCORE =0; // score count 
int HighScore= 0; // highest score 
int gamesPlayed = 0;  // track num of games played 

typedef enum {
    // track game state 
    STATE_MENU,
    STATE_PLAYING
} GameState;

GameState gameState = STATE_MENU; // Set game state to Menu at the start of the game 



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




void Menu(Sound fxButton) { // Menu code runs when game state is set to Menu 
        int x  = (ScreenWidth - 80)/2;
        int y = (ScreenHeight - 30)/2;

        Rectangle start = {x, y, PaddleHeight, PaddleWidth};
        DrawRectangleRec(start, DARKGRAY);
        DrawText("START", x + 15, y + 10, 20, RAYWHITE);
    
        char scoreBuffer[32];
        sprintf(scoreBuffer, "Score: %d", SCORE);  
        DrawText(scoreBuffer, 10, 10, 20, WHITE);
    
        if (gamesPlayed > 0) {// if the game has been played we want to store and display the highscore
            char highScoreBuffer[32];
            sprintf(highScoreBuffer, "High Score: %d", HighScore);  
            DrawText(highScoreBuffer, 10, 40, 20, WHITE);
            if(SCORE>=HighScore){
            HighScore = SCORE;
            }
            
        }
    
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), start)) {// Chech if we clicked the Menu button 
            PlaySound(fxButton); // Play sound effect         
            gameState = STATE_PLAYING;// change game state 
    
            // Update high score before resetting score
            if (SCORE > HighScore) {
                HighScore = SCORE;
            }
    
            SCORE = 0; // set score back to 0 after each game 
            gamesPlayed++; // incrmenet games played count 
        }
    }
    

void resetBall(Ball *ball){// bring ball to center position 

    ball->x =400 ;
    ball->y =300;

}

void resetPaddle(Paddle *paddle_left ,Paddle *paddle_right){ // Bring paddles to center position
    paddle_left->x =0 ;
    paddle_left->y = (ScreenHeight - PaddleHeight) / 2;

    paddle_right->x =ScreenWidth - PaddleWidth ;
    paddle_right->y =(ScreenHeight - PaddleHeight) / 2 ;


}


void update(Ball *ball, Paddle *left, Paddle *right, float deltaTime) { // main game logic 
    char buffer[16];
    sprintf(buffer, "%d", SCORE);
    DrawText(buffer, 400, 10, 20, WHITE);// display the score 

    DrawRectangle((int)left->x, (int)left->y, PaddleWidth, PaddleHeight, RAYWHITE);// draw left paddle 
    DrawRectangle((int)right->x, (int)right->y, PaddleWidth, PaddleHeight, RAYWHITE);// draw right paddle 
    DrawCircle((int)ball->x, (int)ball->y, BallRadius, RAYWHITE);// draw ball 

    // Paddle movement
    if (IsKeyDown(KEY_W)) left->y -= PaddleSpeed * deltaTime * 200; 
    if (IsKeyDown(KEY_S)) left->y += PaddleSpeed * deltaTime * 200;
    if (IsKeyDown(KEY_UP)) right->y -= PaddleSpeed * deltaTime * 200;
    if (IsKeyDown(KEY_DOWN)) right->y += PaddleSpeed * deltaTime * 200;

    // Clamp paddles
    if (left->y < 0) left->y = 0;
    if (left->y + PaddleHeight > ScreenHeight) left->y = ScreenHeight - PaddleHeight;
    if (right->y < 0) right->y = 0;
    if (right->y + PaddleHeight > ScreenHeight) right->y = ScreenHeight - PaddleHeight;

    // Update ball position
    ball->x += ball->xv * deltaTime * 200;
    ball->y += ball->yv * deltaTime * 200;

    if (ball->y - BallRadius < 0) {//if the ball collides with floor it bounces 
        ball->y = BallRadius; 
        ball->yv *= -1;
    }
    if (ball->y + BallRadius > ScreenHeight) { // if the ball collides with roof it bounces 
        ball->y = ScreenHeight - BallRadius;
        ball->yv *= -1;
    }

    if (ball->x - BallRadius < 0 || ball->x + BallRadius > ScreenWidth) {// if it goes out of bounds we change back to the menu and reset assets 
        resetBall(ball);
        resetPaddle(left, right);
        gameState = STATE_MENU;
        return;
    }

    // Paddle collision
    Vector2 center = { ball->x, ball->y };

    Rectangle leftRec = { left->x, left->y, PaddleWidth, PaddleHeight };
    Rectangle rightRec = { right->x, right->y, PaddleWidth, PaddleHeight };

    if (CheckCollisionCircleRec(center, BallRadius, leftRec)) {
        ball->x = left->x + PaddleWidth + BallRadius; // push ball away
        ball->xv *= -1;
        SCORE++;
    }
    if (CheckCollisionCircleRec(center, BallRadius, rightRec)) {
        ball->x = right->x - BallRadius; // push ball away
        ball->xv *= -1;
        SCORE++;
    }
}



int main(void){
    
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);  
    InitWindow(ScreenWidth, ScreenHeight, "Pong");
    InitAudioDevice();
    
    // generate game items 
    Sound fxButton = LoadSound("assets/button.wav");
    Paddle left = {0, (ScreenHeight - PaddleHeight) / 2};
    Paddle right = {ScreenWidth - PaddleWidth, (ScreenHeight - PaddleHeight) / 2};
    Ball ball = {400.0,300.0,0.8,0.7};


    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();


        BeginDrawing();
        ClearBackground(BLACK);

        if(gameState == STATE_MENU) { // 
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

