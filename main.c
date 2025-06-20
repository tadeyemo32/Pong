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




void Menu(){
    



}











int main(void){
   
 

InitWindow(ScreenWidth, ScreenHeight, "Pong");
InitAudioDevice();
    

    while (!WindowShouldClose()) {
        
     
        BeginDrawing();
       

            ClearBackground(BLACK);

        EndDrawing();
    
    }
    CloseWindow();    
    
    

    return 0;
}

//gcc -o game main.c -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo 