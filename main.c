#include <stdio.h>
#include <raylib.h>
#define ScreenWidth 800
#define ScreenHeight 600 

#define Ball_Radius 5 
#define PaddleHeight 70
#define PaddleWidth 10



typedef struct Paddle{

int width ;
int height ;
int x  ;
int y;

}Paddle;



typedef struct Ball{

int radius; 
int x; 
int y;

}Ball;




void initBoard(){
    
    Paddle Paddle_Left = {PaddleWidth, PaddleHeight, 0, 400};
    Paddle Paddle_Right = {PaddleWidth, PaddleHeight, ScreenWidth - PaddleWidth, 400};

    DrawRectangle(Paddle_Left.x, Paddle_Left.y, Paddle_Left.width, Paddle_Left.height, RAYWHITE);
    DrawRectangle(Paddle_Right.x, Paddle_Right.y, Paddle_Right.width, Paddle_Right.height, RAYWHITE);
}






int main(void){
   
 

    InitWindow(ScreenWidth, ScreenHeight, "Pong");

    SetTargetFPS(60);              
    while (!WindowShouldClose()) {
        
     
        BeginDrawing();
        initBoard();

            ClearBackground(BLACK);


        EndDrawing();
    
    }
    CloseWindow();    
    
    

    return 0;
}

//gcc -o game main.c -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo 