#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <stdlib.h>

#include "POINT.h"

struct NODE { //структура с рекордом
    int lines; //кол-во линий
    int lengLines; //длина числа lines (нужно для отрисоки)
    int score; //рекорд
    int lengScore; //длина числа score (нужно для отрисоки)
};

class SCORE {
    private:
        char *wayFile = "score.bin"; //название файла
        NODE mass[7]; //массив с рекордами
        FILE *file; //вспомогательная переменная для работы с файлом

        int i, j; //вспомогательные переменные

        int lengNumber(int); //функция возвращающая длину числа

        void viewMass(); //вспомогатлеьная функция для отладки
        void sortMass(); //сортировка массива

    public:
        SCORE();
        ~SCORE();

        void clear(); //очистка файла
        void load(); //загрузка файла
        void save(); //сохранения файла
        void add(int, int); //добавление рекорда

        NODE *getMass(); //получения указателлся на массив
};

#endif // SCORE_H
