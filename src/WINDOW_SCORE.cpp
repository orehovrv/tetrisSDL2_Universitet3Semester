#include "WINDOW_SCORE.h"

WINDOW_SCORE::WINDOW_SCORE() {
    wayBackground[24] = '1';
    background[0] = SDL_LoadBMP(wayBackground);
    wayBackground[24] = '2';
    background[1] = SDL_LoadBMP(wayBackground);
    frame = SDL_LoadBMP(wayFrame);

    flag = 0;
}

WINDOW_SCORE::~WINDOW_SCORE() {

}

void WINDOW_SCORE::start(char *name, int x, int y, int w, int h, SCORE *a) {
    setName(name);
    setPosition(x, y);
    setSize(w, h);
    recreateWindow();

    score = a;
}

void WINDOW_SCORE::drawScore() {
    POINT pos = getMousePos();
    drawSurface(background[0], 0, 0);

    drawText("Leaderboard", 11, -1, 36, 255, 255, 255);
    drawText("Clear", 94, 456, 40, 255, 255, 255);

    drawText("Lines", 23, 55, 24, 255, 255, 255);
    drawText("Score", 120, 55, 24, 255, 255, 255);

    NODE *temp = score->getMass();

    for(i = 0; i < 6; i++) {
        itoa(temp[i].lines, number, 10);
        switch(temp[i].lengLines) {
            case 1:
                drawText(number, 42, 80 + i * 60, 32, 255, 255, 255);
                break;
            case 2:
                drawText(number, 30, 80 + i * 60, 32, 255, 255, 255);
                break;
            case 3:
                drawText(number, 23, 80 + i * 60, 32, 255, 255, 255);
                break;
        }

        itoa(temp[i].score, number, 10);
        switch(temp[i].lengScore) {
            case 1:
                drawText(number, 141, 80 + i * 60, 32, 255, 255, 255);
                break;
            case 3:
                drawText(number, 123, 80 + i * 60, 32, 255, 255, 255);
                break;
            case 4:
                drawText(number, 113, 80 + i * 60, 32, 255, 255, 255);
                break;
            case 5:
                drawText(number, 105, 80 + i * 60, 32, 255, 255, 255);
                break;
        }
    }
    if(getFocus()){
        if(pos.x >= 80 && pos.x <= 200 && pos.y >= 460 && pos.y <= 520)
            drawSurface(frame, 77, 457);
    }
}

void WINDOW_SCORE::drawClear() {
    POINT pos = getMousePos();
    drawSurface(background[1], 0, 0);

    drawText("Really?", 50, 100, 40, 255, 255, 255);
    drawText("Yes", 78, 185, 40, 255, 255, 255);
    drawText("No", 84, 285, 40, 255, 255, 255);

    if(getFocus()){
        if(pos.x >= 50 && pos.x <= 170 && pos.y >= 160 && pos.y <= 250)
            drawSurface(frame, 46, 187);
        else if(pos.x >= 50 && pos.x <= 170 && pos.y >= 290 && pos.y <= 350)
            drawSurface(frame, 46, 287);
    }
}

void WINDOW_SCORE::drawAll() {
    clearRender();
    clearTempSurface();

    switch(flag) {
        case 0:
            drawScore();
            break;
        case 1:
            drawClear();
            break;
    }

    updateWindow();
}

void WINDOW_SCORE::pressLeftButton() {
    POINT pos = getMousePos();

    switch(flag) {
        case 0:
            if(pos.x >= 80 && pos.x <= 200 && pos.y >= 460 && pos.y <= 520)
                flag = 1;
            break;

        case 1:
            if(pos.x >= 50 && pos.x <= 170 && pos.y >= 160 && pos.y <= 250) {
                score->clear();
                flag = 0;
            }
            else if(pos.x >= 50 && pos.x <= 170 && pos.y >= 290 && pos.y <= 350)
                flag = 0;
            break;
    }
}

void WINDOW_SCORE::setFlag(bool a) {
    flag = a;
}
