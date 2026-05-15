#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>

int main()
{
    FILE *in = stdin;
    char *pthroway = calloc(1000, sizeof(char));
    // Read first line (specifier P3 or P6 - ignore here)
    fgets(pthroway, 1000, in);
    // Read second line (comment)
    fgets(pthroway, 1000, in);
    // Read third line (dimensions: width / height)
    char *pdimensions = calloc(1000, sizeof(char));
    fgets(pdimensions, 1000, in);
    // Read fourth line (max color value - ignore it)
    fgets(pthroway, 1000, in);
    free(pthroway);

    int width = -1;
    int height = -1;
    sscanf(pdimensions, "%d %d\n", &width, &height);
    free(pdimensions);
    printf("width=%d, height=%d\n", width, height);
    
    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow); 


    SDL_Rect pixel = (SDL_Rect){0,0,1,1};
    Uint32 color = 0;
    for (int y=0; y<height; y++)
    {
        for(int x=0; x<width; x++)
        {
            Uint8 r,g,b;
            r = (char) getchar();
            g = (char) getchar();
            b = (char) getchar();
            color = SDL_MapRGB(psurface->format,r,g,b);
            pixel.x=x;
            pixel.y=y;
            SDL_FillRect(psurface, &pixel, color);
        }
    }
    SDL_UpdateWindowSurface(pwindow);
   
    int app_running = 1; 
    while (app_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {  
            if(event.type == SDL_QUIT)
            {
                app_running = 0;
            }
        }
        SDL_Delay(100);
    }
}
