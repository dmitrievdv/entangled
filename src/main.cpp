#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <charconv>

#include "defs.h"
#include "draw.h"

int WINDOW_WIDTH;
int WINDOW_HEIGHT;

using namespace std;

//For SDL, you should have the following main method:
int main(int argc, char** args)
{
    SDL_Init(SDL_INIT_EVERYTHING); //Initialize all the systems of SDL
	
    TTF_Init(); // Initialize text-to-font
    
    SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,  //Create a window with a title, "Getting Started", in the centre
        SDL_WINDOWPOS_UNDEFINED, 350, 600, SDL_WINDOW_SHOWN);   //(or undefined x and y positions), with dimensions of 800 px width
                                                                                       //and 600 px height and force it to be shown on screen
    SDL_GetWindowSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); //Create a renderer for the window created above, with the first display driver present
                                                                //and with no additional settings
    SDL_Event input; //Struct for handling events

    	
    TTF_Font* font = TTF_OpenFont("resources/arial.ttf", 25); // Font

    SDL_Color SDLColorWhite = {255, 255, 255};

    //Boolean to find out whether the game is stopped or not
    //Of course, it will be false at start
    bool quit = false;
    int mainState = 1; // 1 -- Game
    int statesNumber = 2;
    char stateString[4];

    int gameField[7][7][6] = {0};

    gameField[0][0][0] = -1;
    gameField[1][0][0] = -1;
    gameField[1][1][0] = -1;
    gameField[0][2][0] = -1;
    gameField[2][0][0] = -1;
    gameField[0][1][0] = -1;

    gameField[6][6][0] = -1;
    gameField[5][6][0] = -1;
    gameField[6][5][0] = -1;
    gameField[6][4][0] = -1;
    gameField[5][5][0] = -1;
    gameField[4][6][0] = -1;

    gameField[3][3][0] = -1;

    SDL_Texture **stateIDText;
    stateIDText = new SDL_Texture*[statesNumber];

    SDL_Texture *textTest;
    SDL_Surface *temp = TTF_RenderText_Solid(font, "Test", SDLColorWhite);
    textTest = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);

    for (int i = 0; i < statesNumber; i++) {
        memset(stateString, '\0', 4);
        to_chars(stateString, stateString + 3, i);
        cout << stateString << endl;
        SDL_Surface *temp = TTF_RenderText_Solid(font, stateString, SDLColorWhite);
        stateIDText[i] = SDL_CreateTextureFromSurface(renderer, temp);
        SDL_FreeSurface(temp);
    }

    SDL_Rect windowRect; //'windowRect' defines the dimensions of the rendering sprite on window
    windowRect.x = 0;
    windowRect.y = 0;
    windowRect.w = 140;
    windowRect.h = 200;

    SDL_Rect textRect;
    textRect.x = WINDOW_WIDTH - 50;
    textRect.y = 50;
    textRect.w = 20;
    textRect.h = 40;

    //For selecting renderer's draw color
    int r = 0, g = 255, b = 0;

    while (!quit) { //Same as while(quit == false)
        // SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        //---Event polling method---
        //It runs until the number of events to be polled gets to zero
        while (SDL_PollEvent(&input) > 0) {
            //If the user did something which should
            //result in quitting of the game then...
            if (input.type == SDL_QUIT) {
                //...go out of the while loop
                quit = true;
            }
            //If the user pressed any key then...
            else if (input.type == SDL_KEYDOWN) {
                if (input.key.keysym.scancode == SDL_SCANCODE_S) {
                    mainState = (mainState + 1) % 2;
                }
                if (input.key.keysym.scancode == SDL_SCANCODE_C) {
                    r = rand() % 255;
                    g = rand() % 255;
                    b = rand() % 255;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderClear(renderer);

        switch (mainState)
        {
        case 1:
            drawgame(renderer, gameField);
            break;
        default:
            SDL_RenderCopy(renderer, textTest, NULL, &windowRect);
            break;
        }
        SDL_RenderCopy(renderer, stateIDText[mainState], NULL, &textRect);
        

        SDL_RenderPresent(renderer);
    }

    for (int i = 0; i < statesNumber; i++) {
        SDL_DestroyTexture(stateIDText[i]);
    }
    delete[] stateIDText;

    SDL_DestroyTexture(textTest);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    	
    TTF_Quit();
    SDL_Quit();

    return 0;
}