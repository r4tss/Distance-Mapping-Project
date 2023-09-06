#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define ARRAYSIZE(x) (sizeof(x)/sizeof(*x))

struct point {
    int x;
    int y;
};

int main() {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  window = SDL_CreateWindow("Distance Mapping", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 576, SDL_WINDOW_OPENGL);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  bool quit = true;
  int start_frame, fps = 30, ticks_per_frame = 1000/fps, tar_h = 16, tar_w = 16, points_n;

  SDL_Surface *Surface = SDL_LoadBMP("./dot.bmp");
  SDL_Texture *Texture = SDL_CreateTextureFromSurface(renderer, Surface);
  SDL_Rect target;
  target.h = tar_h;
  target.w = tar_w;

  SDL_Point points[points_n];

  time_t t;
  srand((unsigned) time(&t));
  for(int i = 0;i < (int)ARRAYSIZE(points);i++)
  {
    points[i].x = (rand() % 1024);
    points[i].y = (rand() % 576);
  }

  while(!quit)
  {
    start_frame = SDL_GetTicks();
    SDL_RenderClear(renderer);

    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym)
          {
            case SDLK_SPACE:
              for(int i = 0;i < (int)ARRAYSIZE(points);i++)
              {
                points[i].x = (rand() % 1024);
                points[i].y = (rand() % 576);
              }
              break;
          }
          break;
        case SDL_QUIT:
          quit = true;
          break;
      }
    }

    for(int i = 0;i < (int)ARRAYSIZE(points);i++)
    {
      target.x = points[i].x - (tar_w / 2);
      target.y = points[i].y - (tar_h / 2);

      SDL_SetTextureColorMod(Texture, i*4 + 55, 0, 0);
      SDL_RenderCopy(renderer, Texture, NULL, &target);
    }

    SDL_RenderPresent(renderer);
    int ticks = start_frame - SDL_GetTicks();
    if(ticks < ticks_per_frame)
      SDL_Delay(ticks_per_frame - ticks);
  }

  TTF_Quit();
  SDL_Quit();
}
