#ifndef LOGICS_TETRIS_H
#define LOGICS_TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SCORE.h"
#include "POINT.h"

class LOGICS_TETRIS {
    private:
        //размеры поля
        int M = 26;
        int N = 10;

        int **field; //указатель на массив с полем

        //переменные для работы с фигурами
        POINT a[4], b[4], nextFigure[4]; //a - cur, b - prev
        char color, colorNext, type, typeNext, rot;

        int figures[7][4] = {{1, 3, 5, 7},
                             {2, 4, 5, 7},
                             {3, 5, 4, 6},
                             {3, 5, 4, 7},
                             {2, 3, 5, 7},
                             {3, 5, 7, 6},
                             {2, 3, 4, 5}};

        //переменные нужные для работы с рекордами
        int score;
        int line;

        SCORE *_score;

        //вспомогательные переменные
        int i, j;
        bool status;

    public:
        LOGICS_TETRIS();
        ~LOGICS_TETRIS();

        bool check(); //проверка возможности расположение фигуры

        void newFigure(); //генерация новой фигуры
        void setFigure(); //установка фигуры на поле

        void moveDownFigure(); //сдвиг фигуры вниз
        void moveRightFigure(); //сдвиг фигуры вправо
        void moveLeftFigure(); //сдвиг фигуры влево
        void rotateFigure(); //поворот фигуры

        int **getField(); //получение указателя на поле
        POINT getSize(); //получение размера поля
        POINT *getFigure(); //получение указателя на массив с координами фигуры
        char getColor(); //получение цвета фигуры

        POINT *getNextFigure(); //получение указателя на массив с координами следующей фигуры
        char getNextColor(); //получение цвета следующей фигуры
        char getNextType(); //получение типа следующей фигуры

        int getScore(); //получение значения рекорда
        int getLine(); //получение кол-во удаленных линий
        bool getStatus(); //получение статуса игры (проиграл/не проиграл)

        void clearGame(); //обнудение игры
        void setPointerScore(SCORE*); //связка рекордов и логики
};

#endif // LOGICS_TETRIS_H
