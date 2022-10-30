#include "LOGICS_TETRIS.h"

LOGICS_TETRIS::LOGICS_TETRIS() {
    srand(time(NULL));

    //создание массива поля
    field = (int**)calloc(M, sizeof(int*));
    for(i = 0; i < M; i++) {
        field[i] = (int*)calloc(N, sizeof(int));
    }

    for(i = 0; i < M; i++)
        for(j = 0; j < N; j++)
            field[i][j] = 0;

    //обнуление переменных
    for(i = 0; i < 4; i++) {
        a[i].x = -1;
        a[i].y = -1;
        b[i].x = -1;
        b[i].y = -1;
    }
    rot = 0;
    type = -1;
    typeNext = rand() % 7;

    status = 1;
    score = 0;
    line = 0;
    _score = NULL;

    //создание фигуры
    newFigure();
}

LOGICS_TETRIS::~LOGICS_TETRIS() {
    if(field) { //очистка массива поля
        for(i = 0; i < M; i++)
            if(field[i])
                free(field[i]);
        free(field);
    }
}

bool LOGICS_TETRIS::check() {
    for (i = 0; i < 4; i++)
        if(a[i].y >= 0)
            //сдвиг фигуры
            if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
            //возможность расположения фигуыр на поле
            else if (field[a[i].y][a[i].x]) return 0;

    return 1;
}

void LOGICS_TETRIS::newFigure() {
    //запись цвета и типа следующей фигуры в текущую
    color = colorNext;
    type = typeNext;

    //генерация цвета и типа следующей фигуры
    colorNext = 1 + rand() % 7;
    typeNext = rand() % 7;

    rot = 0; //позиция вращения фигуры

    //работа с координатами фигур
    for (i = 0; i < 4; i++) {
        a[i].x = figures[type][i] % 2 + 4;
        a[i].y = figures[type][i] / 2 - 4;
        nextFigure[i].x = figures[typeNext][i] % 2;
        nextFigure[i].y = figures[typeNext][i] / 2;
        b[i] = a[i];
    }

    //проверка на "конец" игры
    for (i = 3; i < 7; i++) {
        if(a[i].y <= 0) {
            if(field[0][i]) {
                status = 0;
                if(_score)
                    _score->add(score, line);
                return;
            }
        }
    }
}

void LOGICS_TETRIS::setFigure() {
    //установка фигуры но поле
    for (i = 0; i < 4; i++)
        if(b[i].y >= 0)
            field[b[i].y][b[i].x] = color;

    //чистка поля от полынх линий
    int k = M - 1, c;
    for (i = M - 1; i > 0; i--) {
        c = 0;
        for (j = 0; j < N; j++) {
            if (field[i][j]) c++;
            field[k][j] = field[i][j];
        }
        if (c < N) k--;
    }

    //прибавлени рекорда
    switch(k) {
        case 1: score += 100; break;
        case 2: score += 300; break;
        case 3: score += 700; break;
        case 4: score += 1500; break;
    }

    line += k;
}

void LOGICS_TETRIS::moveDownFigure() {
    if(status) {
        //сдвиг фигуры вниз
        for(i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].y += 1;
        }

        //проверка и возможная установка фигуры
        if(!check()) {
            setFigure();
            newFigure();
        }
    }
}

void LOGICS_TETRIS::moveRightFigure() {
    //сдвиг фигуры вправо
    for (i = 0; i < 4; i++) {
        b[i] = a[i];
        a[i].x += 1;
    }

    //проверка возможности сдвига и возможная отмена сдвига
    if (status && !check()) for (i = 0; i < 4; i++) a[i] = b[i];
}

void LOGICS_TETRIS::moveLeftFigure() {
    //сдвиг фигуры влево
    for (i = 0; i < 4; i++) {
        b[i] = a[i];
        a[i].x -= 1;
    }

    //проверка возможности сдвига и возможная отмена сдвига
    if (status && !check()) for (i = 0; i < 4; i++) a[i] = b[i];
}

int **LOGICS_TETRIS::getField() {
    return field;
}

POINT *LOGICS_TETRIS::getFigure() {
    return a;
}

char LOGICS_TETRIS::getColor() {
    return color;
}

POINT *LOGICS_TETRIS::getNextFigure() {
    return nextFigure;
}

char LOGICS_TETRIS::getNextColor() {
    return colorNext;
}

char LOGICS_TETRIS::getNextType() {
    return typeNext;
}

POINT LOGICS_TETRIS::getSize() {
    POINT temp;
    temp.x = M;
    temp.y = N;

    return temp;
}

int LOGICS_TETRIS::getScore() {
    return score;
}

int LOGICS_TETRIS::getLine() {
    return line;
}

bool LOGICS_TETRIS::getStatus() {
    return status;
}

void LOGICS_TETRIS::clearGame() {
    for(i = 0; i < M; i++)
        for(j = 0; j < N; j++)
            field[i][j] = 0;

    score = 0;
    line = 0;
    status = 1;

    newFigure();
}

void LOGICS_TETRIS::setPointerScore(SCORE *a) {
    _score = a;
}

void LOGICS_TETRIS::rotateFigure() {
    //если фигура куб то ничего не делаем
    if(type == 6) return;

    //значение переменной rot
    rot++;
    if(rot > 3) rot = 0;
    for (i = 0; i < 4; i++)
        b[i] = a[i];

    //работа с координатами
    switch(type) {
        case 0:
            switch(rot) {
                case 0:
                    a[0].x += 2;
                    a[0].y -= 1;
                    a[1].x += 1;
                    a[2].y += 1;
                    a[3].x -= 1;
                    a[3].y += 2;
                    break;

                case 1:
                    a[0].x += 1;
                    a[0].y += 2;
                    a[1].y += 1;
                    a[2].x -= 1;
                    a[3].x -= 2;
                    a[3].y -= 1;
                    break;

                case 2:
                    a[0].x -= 2;
                    a[0].y += 1;
                    a[1].x -= 1;
                    a[2].y -= 1;
                    a[3].x += 1;
                    a[3].y -= 2;
                    break;

                case 3:
                    a[0].x -= 1;
                    a[0].y -= 2;
                    a[1].y -= 1;
                    a[2].x += 1;
                    a[3].x += 2;
                    a[3].y += 1;
                    break;
            }
            break;

        case 1:
            switch(rot) {
                case 0:
                    a[0].x += 1;
                    a[0].y -= 1;
                    a[2].x += 1;
                    a[2].y += 1;
                    a[3].y += 2;
                    break;

                case 1:
                    a[0].x += 1;
                    a[0].y += 1;
                    a[2].x -= 1;
                    a[2].y += 1;
                    a[3].x -= 2;
                    break;

                case 2:
                    a[0].x -= 1;
                    a[0].y += 1;
                    a[2].x -= 1;
                    a[2].y -= 1;
                    a[3].y -= 2;
                    break;

                case 3:
                    a[0].x -= 1;
                    a[0].y -= 1;
                    a[2].x += 1;
                    a[2].y -= 1;
                    a[3].x += 2;
                    break;
            }
            break;

        case 2:
            switch(rot) {
                case 0:
                    a[0].x += 2;
                    a[1].x += 1;
                    a[1].y += 1;
                    a[3].x -= 1;
                    a[3].y += 1;
                    break;

                case 1:
                    a[0].y += 2;
                    a[1].x -= 1;
                    a[1].y += 1;
                    a[3].x -= 1;
                    a[3].y -= 1;
                    break;

                case 2:
                    a[0].x -= 2;
                    a[1].x -= 1;
                    a[1].y -= 1;
                    a[3].x += 1;
                    a[3].y -= 1;
                    break;

                case 3:
                    a[0].y -= 2;
                    a[1].x += 1;
                    a[1].y -= 1;
                    a[3].x += 1;
                    a[3].y += 1;
                    break;
            }
            break;

        case 3:
            switch(rot) {
                case 0:
                    a[0].x += 1;
                    a[0].y -= 1;
                    a[2].x -= 1;
                    a[2].y -= 1;
                    a[3].x -= 1;
                    a[3].y += 1;
                    break;

                case 1:
                    a[0].x += 1;
                    a[0].y += 1;
                    a[2].x += 1;
                    a[2].y -= 1;
                    a[3].x -= 1;
                    a[3].y -= 1;
                    break;

                case 2:
                    a[0].x -= 1;
                    a[0].y += 1;
                    a[2].x += 1;
                    a[2].y += 1;
                    a[3].x += 1;
                    a[3].y -= 1;
                    break;

                case 3:
                    a[0].x -= 1;
                    a[0].y -= 1;
                    a[2].x -= 1;
                    a[2].y += 1;
                    a[3].x += 1;
                    a[3].y += 1;
                    break;
            }
            break;

        case 4:
            switch(rot) {
                case 0:
                    a[0].y -= 2;
                    a[1].x += 1;
                    a[1].y -= 1;
                    a[3].x -= 1;
                    a[3].y += 1;
                    break;

                case 1:
                    a[0].x += 2;
                    a[1].x += 1;
                    a[1].y += 1;
                    a[3].x -= 1;
                    a[3].y -= 1;
                    break;

                case 2:
                    a[0].y += 2;
                    a[1].x -= 1;
                    a[1].y += 1;
                    a[3].x += 1;
                    a[3].y -= 1;
                    break;

                case 3:
                    a[0].x -= 2;
                    a[1].x -= 1;
                    a[1].y -= 1;
                    a[3].x += 1;
                    a[3].y += 1;
                    break;
            }
            break;

        case 5:
            switch(rot) {
                case 0:
                    a[0].x += 1;
                    a[0].y -= 1;
                    a[2].x -= 1;
                    a[2].y += 1;
                    a[3].x -= 2;
                    break;

                case 1:
                    a[0].x += 1;
                    a[0].y += 1;
                    a[2].x -= 1;
                    a[2].y -= 1;
                    a[3].y -= 2;
                    break;

                case 2:
                    a[0].x -= 1;
                    a[0].y += 1;
                    a[2].x += 1;
                    a[2].y -= 1;
                    a[3].x += 2;
                    break;

                case 3:
                    a[0].x -= 1;
                    a[0].y -= 1;
                    a[2].x += 1;
                    a[2].y += 1;
                    a[3].y += 2;
                    break;
            }
            break;
    }

    //проверка вращения и возможная отмена его
    if (status && !check()) {
        for (i = 0; i < 4; i++) a[i] = b[i];
        rot--;
    }
}
