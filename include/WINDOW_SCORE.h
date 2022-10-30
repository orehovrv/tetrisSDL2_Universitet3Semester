#ifndef WINDOW_SCORE_H
#define WINDOW_SCORE_H

#include <SDL2\SDL.h>
#include "SDL_ttf.h"

#include "WINDOW.h"
#include "SCORE.h"
#include "POINT.h"

#define scale 20

class WINDOW_SCORE : public WINDOW {
    private:
        SCORE *score;

        SDL_Surface *background[2]; //массив поверхностей с фономами
        SDL_Surface *frame; //поверхность с рамкой для обвода кнопки

        char wayBackground[30] = ".\\images\\scoreBackground*.bmp"; //путь к картинке с фоном
        char *wayFrame = ".\\images\\frame.bmp"; //путь к картинке с рамкой

        int i, j;
        bool flag; //определяет что отрисовывать
        char number[10]; //вспомогательный массив для перевода числа в строку

        void drawScore(); //отрисовка рекордов
        void drawClear(); //отрисовка окна с вопросом об очистке

    public:
        WINDOW_SCORE();
        virtual  ~WINDOW_SCORE();

        void start(char*, int, int, int, int, SCORE*); //"запуск" окна
        void drawAll(); //отрисовка окна
        void setFlag(bool); //что отрисовывать

        void pressLeftButton();//определение чего отрисовывать
};

#endif // WINDOW_SCORE_H
