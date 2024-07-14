#include "include/SDL2/SDL.h"
#include <cmath>
#include <stdio.h>

bool init();
void clear();
void logic();
void getNet();

void timer() {SDL_Delay(500);}

float mFunc(float x);
bool accessToReflection = 0;

float scaleOfCell = 70.0f;
float quality = 0.0005f;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;

int main() {
  if (!init())
    return -1;
  getNet();
  logic();
  SDL_RenderPresent(gRenderer);

  bool quit = 0;
  SDL_Event e;
  while (!quit) {
    SDL_GetWindowSize(gWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    while (SDL_PollEvent(&e))
      if (e.type == SDL_QUIT)
        quit = 1;
      else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_w:
          printf("Scale of cell: %f\n", scaleOfCell + 5);
          for(int i = 0; i < 5; i++) {
            scaleOfCell++;
            getNet();
            logic();
            SDL_RenderPresent(gRenderer);
          }
          break;
        case SDLK_s:
          if(scaleOfCell - 5 <= 0)
              break;
          printf("Scale of cell: %f\n", scaleOfCell - 5);
          for(int i = 0; i < 5; i++) {
            scaleOfCell--;
            getNet();
            logic();
            SDL_RenderPresent(gRenderer);
          }
          getNet();
          logic();
          SDL_RenderPresent(gRenderer);
          break;
        case SDLK_e:
          quality += 0.0005;
          printf("Quality: %f\n", quality);
          getNet();
          logic();
          SDL_RenderPresent(gRenderer);
          break;
        case SDLK_d:
          if(quality -0.0005 < 0.0005)
              break;
          quality -= 0.0005;
          printf("Quality: %f\n", quality);
          getNet();
          logic();
          SDL_RenderPresent(gRenderer);
          break;
        case SDLK_r:
          accessToReflection = accessToReflection ? 0 : 1;
          printf("Access to reflection: %s\n", accessToReflection ? "true" : "false");
          getNet();
          logic();
          SDL_RenderPresent(gRenderer);
          break;
        }
      }
  }

  clear();
  return 0;
}

bool init() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &gWindow,
                              &gRenderer);
  SDL_RenderSetScale(gRenderer, 1, 1);

  printf("Initialization successed!\n");
  return 1;
}

void clear() {
  SDL_DestroyWindow(gWindow);
  SDL_DestroyRenderer(gRenderer);
  SDL_Quit();
  printf("Session ended successfully!\n");
}

void logic() {
  SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);

  float x, y;

  for (x = float(SCREEN_WIDTH) / 2 * -1; x <= float(SCREEN_WIDTH) / 2;
       x += quality) {
    y = mFunc(x);

    if (y * -1 + float(SCREEN_HEIGHT) / 2 < 0 ||
        y * -1 + float(SCREEN_HEIGHT) / 2 > SCREEN_HEIGHT) {
      continue;
    }

    if(accessToReflection)
      SDL_RenderDrawPointF(gRenderer, x * scaleOfCell + float(SCREEN_WIDTH) / 2, y * scaleOfCell + float(SCREEN_HEIGHT) / 2);
    SDL_RenderDrawPointF(gRenderer, x * scaleOfCell + float(SCREEN_WIDTH) / 2, y * scaleOfCell * -1 + float(SCREEN_HEIGHT) / 2);
  }
}

void getNet() {
  SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
  SDL_RenderClear(gRenderer);

  SDL_SetRenderDrawColor(gRenderer, 128, 128, 128, 128);
  for (int i = SCREEN_WIDTH / 2; i <= SCREEN_WIDTH;
       i += (scaleOfCell >= 1 ? scaleOfCell : 1 / scaleOfCell)) {
    SDL_RenderDrawLine(gRenderer, i, 0, i, SCREEN_HEIGHT);
  }
  for (int i = SCREEN_WIDTH / 2; i >= 0;
       i -= (scaleOfCell >= 1 ? scaleOfCell : 1 / scaleOfCell)) {
    SDL_RenderDrawLine(gRenderer, i, 0, i, SCREEN_HEIGHT);
  }
  for (int i = SCREEN_HEIGHT / 2; i <= SCREEN_HEIGHT;
       i += (scaleOfCell >= 1 ? scaleOfCell : 1 / scaleOfCell)) {
    SDL_RenderDrawLine(gRenderer, 0, i, SCREEN_WIDTH, i);
  }
  for (int i = SCREEN_HEIGHT / 2; i >= 0;
       i -= (scaleOfCell >= 1 ? scaleOfCell : 1 / scaleOfCell)) {
    SDL_RenderDrawLine(gRenderer, 0, i, SCREEN_WIDTH, i);
  }

  SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
  SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH,
                     SCREEN_HEIGHT / 2);
  SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2 - 1, SCREEN_WIDTH,
                     SCREEN_HEIGHT / 2 - 1);
  SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2 + 1, SCREEN_WIDTH,
                     SCREEN_HEIGHT / 2 + 1);
  SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2,
                     SCREEN_HEIGHT);
  SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 2 - 1, 0, SCREEN_WIDTH / 2 - 1,
                     SCREEN_HEIGHT);
  SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 2 + 1, 0, SCREEN_WIDTH / 2 + 1,
                     SCREEN_HEIGHT);
}

float mFunc(float x) { 
  return pow(M_E, sin(x));
}
