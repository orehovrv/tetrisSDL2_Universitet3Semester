#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2\SDL.h>
#include "SDL_ttf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "POINT.h"

class WINDOW {
    private:
        //основные объекты для работы окна
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        //вспомагательная поверхность для отрисовки
        SDL_Surface *temp_surface;

        //объекты для хранения размеров и координат
        SDL_Rect info, dst;

        //вспомогательные объеты для отрисовки текста
        TTF_Font *font;
        SDL_Color color;
        SDL_Surface *text_surface;

        char name[30] = {0}; //название окна
        POINT pos; //координаты окна
        POINT lastPosMouse; //координаты позиции мышки
        bool focus; //фокус окна

    public:
        WINDOW();
        virtual ~WINDOW();

        void setPosition(int, int); //установка позиции окна
        void setSize(int, int); //установка размеров окна
        void setName(char*); //установка названия окна
        void recreateWindow(); //создание окна

        void centerWindow(); //возврат окна на координаты POS

        void clearRender(); //очистка render
        void clearTempSurface(); //очистка временной поверхности

        void updateWindow(); //обновление картинки на рабочем окне

        //отрисовка поверхности на опред. координатах
        void drawSurface(SDL_Surface*, int, int);
        //отрисовка текста
        void drawText(char*, int, int, int, unsigned char, unsigned char, unsigned char);

        void setMousePos(int, int); //запись координат курсора в переменную
        POINT getMousePos(); //получение координат курсора
        void setFocus(bool); //установка фокуса
        bool getFocus(); //получение фокуса

        virtual void pressLeftButton() {} //обработка левого щелчка мышки
};

#endif // WINDOW_H
