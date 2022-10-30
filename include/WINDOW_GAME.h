#ifndef WINDOW_GAME_H
#define WINDOW_GAME_H

#include <SDL2\SDL.h>
#include "SDL_ttf.h"

#include "WINDOW.h"
#include "LOGICS_TETRIS.h"
#include "POINT.h"

#define scale 20

class WINDOW_GAME : public WINDOW {
    private:
        LOGICS_TETRIS *game;

        SDL_Surface *tile[8]; //поверхности с кубиками
        SDL_Surface *background; //поверхность с фоном
        SDL_Surface *frame; //поверхность с рамкой для обвода кнопки

        char wayTiles[30] = ".\\images\\tiles*.bmp"; //путь к картинке с кубиками
        char *wayBackground = ".\\images\\gameBackground.bmp"; //путь к картинке с фоном
        char *wayFrame = ".\\images\\frame.bmp"; //путь к картинке с рамкой

        int i, j, M, N;
        char number[10]; //вспомогательный массив для перевода числа в строку

        char type; //определяет что отрисовывать

        void drawBackground(); //отрисовка фона
        void drawMenu(); //отрисовка меню
        void drawGame(); //отрисовка игры
        void drawEnd(); //отрисовка конца игры
        void drawHelp();
        void drawAbout();

    public:
        WINDOW_GAME();
        virtual ~WINDOW_GAME();

        void start(char*, int, int, int, int, LOGICS_TETRIS*); //"запуск" окна
        void drawAll(); //отрисовка окна
        void pressLeftButton(); //обработка нажатия левой кнопки мышки

        void setType(char); //определение чего отрисовывать
};

#endif // WINDOW_GAME_H
