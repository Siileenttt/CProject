#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#define WIDTH 900
#define HEIGHT 600
struct Circle
{
    double x;
    double y;
    double vx;
    double vy;
    double gravity;
    double radius;
    double dampening;
};
void update_position(struct Circle *pcircle)
{
    double new_x = pcircle->x + pcircle->vx;
    double new_y = pcircle->y + pcircle->vy;
    double new_vy = pcircle->vy- pcircle->gravity;
    pcircle->x = new_x;
    pcircle->y = new_y;
    pcircle->vy = new_vy;
    double radius = pcircle->radius;
    if (pcircle->x < 0+radius)
    {
        pcircle->x = radius;
        pcircle->vx = -pcircle->vx;
        pcircle->vx *= pcircle->dampening;
    }  
    if (pcircle->x > WIDTH + radius)
    {
        pcircle->x = WIDTH - radius;
        pcircle->vx = -pcircle->vx;
        pcircle->vx *= pcircle->dampening;
    }  
    if (pcircle->y < 0+radius)
    {
        pcircle->y = radius;
        pcircle->vy = -pcircle->vy;
        pcircle->vy *= pcircle->dampening;
    }  
    if (pcircle->y > HEIGHT - radius)
    {
        pcircle->y = HEIGHT - radius;
        pcircle->vy = -pcircle->vy;
        pcircle->vy *= pcircle->dampening;
    }  
}
void Draw_Circle(SDL_Renderer *prenderer, struct Circle *circle)
{
    SDL_SetRenderDrawColor(prenderer, 0x00, 0xff, 0x00, 0xff);
    double cx = circle->x;
    double cy = circle->y;
    double r = circle->radius;
    SDL_Point p0, p1, p2;
    p0.x = (int)(cx + r * cos(M_PI / 2));
    p0.y = (int)(cy + r * sin(M_PI / 2));
    p1.x = (int)(cx + r * cos(M_PI / 2 + 2 * M_PI / 3));
    p1.y = (int)(cy + r * sin(M_PI / 2 + 2 * M_PI / 3));
    p2.x = (int)(cx + r * cos(M_PI / 2 + 4 * M_PI / 3));
    p2.y = (int)(cy + r * sin(M_PI / 2 + 4 * M_PI / 3));
    int minX = fmin(fmin(p0.x, p1.x), p2.x);
    int maxX = fmax(fmax(p0.x, p1.x), p2.x);
    int minY = fmin(fmin(p0.y, p1.y), p2.y);
    int maxY = fmax(fmax(p0.y, p1.y), p2.y);
    float denom = (float)((p1.y - p2.y)*(p0.x - p2.x) + (p2.x - p1.x)*(p0.y - p2.y));
    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            float a = ((p1.y - p2.y)*(x - p2.x) + (p2.x - p1.x)*(y - p2.y)) / denom;
            float b = ((p2.y - p0.y)*(x - p2.x) + (p0.x - p2.x)*(y - p2.y)) / denom;
            float c = 1.0f - a - b;
            if (a >= 0 && b >= 0 && c >= 0)
                SDL_RenderDrawPoint(prenderer, x, y);
        }
    }
    SDL_RenderPresent(prenderer);
}
int main()
{
    printf("Hello World\n");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *pwindow = SDL_CreateWindow("Bouncing Circle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *prenderer = SDL_CreateRenderer(pwindow,0, 0);
    SDL_RenderClear(prenderer);
    SDL_Rect background_rect = (struct SDL_Rect) {0,0, WIDTH, HEIGHT};
    SDL_SetRenderDrawColor(prenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderFillRect(prenderer, &background_rect);
    
    int quit = 0;
    struct Circle circle = (struct Circle) {100,100,10,10,-10,60, 0.7};

    while( !quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) 
            {
                printf("Quit application\n"); 
                quit = 1;
            } 
        }
        SDL_SetRenderDrawColor(prenderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(prenderer);
        update_position(&circle);
        //   Draw Circle
        Draw_Circle(prenderer, &circle);
        SDL_Delay(20);
        
    }   


}
