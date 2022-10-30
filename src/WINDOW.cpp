#include "WINDOW.h"

WINDOW::WINDOW() {
    window = NULL;
    renderer  = NULL;
    texture  = NULL;
    temp_surface  = NULL;
    font  = NULL;
    text_surface  = NULL;

    info.x = 0;
    info.y = 0;
    info.h = 0;
    info.w = 0;

    dst.x = 0;
    dst.y = 0;
    dst.h = 0;
    dst.w = 0;
}

WINDOW::~WINDOW() {
    if(window)
        SDL_DestroyWindow(window);
    if(renderer)
        SDL_DestroyRenderer(renderer);
    if(texture)
        SDL_DestroyTexture(texture);
    if(temp_surface)
        SDL_FreeSurface(temp_surface);

    if(font)
        TTF_CloseFont(font);
    if(text_surface)
        SDL_FreeSurface(text_surface);
}

void WINDOW::setPosition(int x, int y) {
    pos.x = x;
    pos.y = y;
}

void WINDOW::setSize(int w, int h) {
    info.h = h;
    info.w = w;
}

void WINDOW::setName(char *way) {
    strcpy(name, way);
}

void WINDOW::recreateWindow() {
    window = SDL_CreateWindow(name, pos.x, pos.y, info.w, info.h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    temp_surface = SDL_CreateRGBSurface(0, info.w, info.h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    printf("Create window\nposition: %d %d\nsize: %d %d\n=============\n\n", pos.x, pos.y, info.h, info.w);
}

void WINDOW::centerWindow() {
    SDL_SetWindowPosition(window, pos.x, pos.y);
}

void WINDOW::clearRender() {
    SDL_RenderClear(renderer);
}

void WINDOW::clearTempSurface() {
    SDL_FillRect(temp_surface, NULL, 0x00000000);
}

void WINDOW::updateWindow() {
    SDL_DestroyTexture(texture);
    texture = SDL_CreateTextureFromSurface(renderer, temp_surface);

    SDL_RenderCopy(renderer, texture, NULL, &info);
    SDL_RenderPresent(renderer);
}

void WINDOW::drawSurface(SDL_Surface *img, int x, int y) {
    if(img) { //если есть поверхность
        dst.x = x; //запись координат
        dst.y = y;
        dst.h = img -> h; //запись размеров
        dst.w = img -> w;

        //отрисовка поверхности
        SDL_BlitSurface(img, NULL, temp_surface, &dst);
    }
}

void WINDOW::drawText(char *text, int x, int y, int h, unsigned char r, unsigned char g, unsigned char b) {
    font = TTF_OpenFont("CharisSILR.ttf", h); //создание шрифта размера h
    if(font) {
        color = {r, g, b}; //цвет
        //создание поверхности с текстом
        text_surface = TTF_RenderUTF8_Solid(font, text, color);
        if(text_surface) { //если создалось
            dst.x = x;
            dst.y = y;
            dst.h = text_surface -> h;
            dst.w = text_surface -> w;
            //отрисовать
            SDL_BlitSurface(text_surface, NULL, temp_surface, &dst);

            //очистить память
            SDL_FreeSurface(text_surface);
            text_surface = NULL;
        }
        //очистить шрифт
        TTF_CloseFont(font);
        font = NULL;
    }
}

void WINDOW::setMousePos(int x, int y) {
    lastPosMouse.x = x;
    lastPosMouse.y = y;
}

POINT WINDOW::getMousePos() {
    return lastPosMouse;
}

void WINDOW::setFocus(bool a) {
    focus = a;
}

bool WINDOW::getFocus() {
    return focus;
}
