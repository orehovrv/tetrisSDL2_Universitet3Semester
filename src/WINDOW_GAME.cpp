#include "WINDOW_game.h"

WINDOW_GAME::WINDOW_GAME() {
    for(i = 0; i < 8; i++) {
        wayTiles[14] = i + '0';
        tile[i] = SDL_LoadBMP(wayTiles);
    }

    background = SDL_LoadBMP(wayBackground);
    frame = SDL_LoadBMP(wayFrame);

    type = -1;
}

WINDOW_GAME::~WINDOW_GAME() {

}

void WINDOW_GAME::start(char *name, int x, int y, int w, int h, LOGICS_TETRIS *a) {
    setName(name);
    setPosition(x, y);
    setSize(w, h);
    recreateWindow();

    type = 0;

    game = a;
    POINT temp = game->getSize();
    M = temp.x;
    N = temp.y;

    game->clearGame();
    game->newFigure();
}

void WINDOW_GAME::setType(char input) {
    type = input;
}

void WINDOW_GAME::drawBackground() {
    drawSurface(background, 0, 0);

    drawText("Next:", 282, 0, 32, 255, 255, 255);
    drawText("Score:", 278, 200, 32, 255, 255, 255);
    drawText("Lines:", 278, 300, 32, 255, 255, 255);
}

void WINDOW_GAME::drawMenu() {
    drawBackground();

    for(i = 0; i < 3; i++)
        for(j = 0; j < 6; j++)
            drawSurface(tile[0], j * scale + scale * 3, i * scale + 80);
    drawText("Play", 75, 65, 48, 255, 255, 255);

    for(i = 0; i < 3; i++)
        for(j = 0; j < 6; j++)
            drawSurface(tile[0], j * scale + scale * 3, i * scale + 180);
    drawText("Help", 70, 165, 48, 255, 255, 255);

    for(i = 0; i < 3; i++)
        for(j = 0; j < 6; j++)
            drawSurface(tile[0], j * scale + scale * 3, i * scale + 280);
    drawText("About", 78, 268, 32, 255, 255, 255);
    drawText("author", 74, 294, 32, 255, 255, 255);

    for(i = 0; i < 3; i++)
        for(j = 0; j < 6; j++)
            drawSurface(tile[0], j * scale + scale * 3, i * scale + 380);
    drawText("Exit", 78, 366, 48, 255, 255, 255);

    if(getFocus()) {
        POINT pos = getMousePos();
        if(pos.x >= 60 && pos.x <= 180 && pos.y >= 80 && pos.y <= 140)
            drawSurface(frame, 57, 77);
        else if(pos.x >= 60 && pos.x <= 180 && pos.y >= 180 && pos.y <= 240)
            drawSurface(frame, 57, 177);
        else if(pos.x >= 60 && pos.x <= 180 && pos.y >= 280 && pos.y <= 340)
            drawSurface(frame, 57, 277);
        else if(pos.x >= 60 && pos.x <= 180 && pos.y >= 380 && pos.y <= 440)
            drawSurface(frame, 57, 377);
    }
}

void WINDOW_GAME::drawGame() {
    int **field = game->getField();
    POINT *figure = game->getFigure();
    POINT *nextFigure = game->getNextFigure();
    POINT temp;

    char color = game->getColor();
    char colorNext = game->getNextColor();

    drawBackground();

    for(i = 0; i < M; i++)
        for(j = 0; j < N; j++) {
            if(field[i][j] == 0) continue;
            drawSurface(tile[field[i][j]], j * scale + scale, i * scale);
        }

    for(i = 0; i < 4; i++) {
        drawSurface(tile[color], figure[i].x * scale + scale, figure[i].y * scale);
        switch(game->getNextType()) {
            case 0:
                temp.x = nextFigure[i].x * scale + 290;
                temp.y = nextFigure[i].y * scale + 80;
                break;
            case 1:
                temp.x = nextFigure[i].x * scale + 300;
                temp.y = nextFigure[i].y * scale + 70;
                break;
            case 2:
                temp.x = nextFigure[i].x * scale + 300;
                temp.y = nextFigure[i].y * scale + 70;
                break;
            case 3:
                temp.x = nextFigure[i].x * scale + 300;
                temp.y = nextFigure[i].y * scale + 70;
                break;
            case 4:
                temp.x = nextFigure[i].x * scale + 300;
                temp.y = nextFigure[i].y * scale + 70;
                break;
            case 5:
                temp.x = nextFigure[i].x * scale + 300;
                temp.y = nextFigure[i].y * scale + 70;
                break;
            case 6:
                temp.x = nextFigure[i].x * scale + 300;
                temp.y = nextFigure[i].y * scale + 80;
                break;
        }
        drawSurface(tile[colorNext], temp.x, temp.y);
    }

    itoa(game->getScore(), number, 10);
    drawText(number, 278, 232, 32, 255, 255, 255);
    itoa(game->getLine(), number, 10);
    drawText(number, 278, 332, 32, 255, 255, 255);

    if(!game->getStatus())
        type = 2;
}

void WINDOW_GAME::drawEnd() {
    drawSurface(background, 0, 0);

    for(i = 0; i < M; i++)
        for(j = 0; j < N; j++)
            drawSurface(tile[0], j * scale + scale, i * scale);
    drawText("The End", 47, 226, 40, 255, 255, 255);

    drawText("Next:", 282, 0, 32, 255, 255, 255);
    drawText("Score:", 278, 200, 32, 255, 255, 255);
    itoa(game->getScore(), number, 10);
    drawText(number, 278, 232, 32, 255, 255, 255);
    drawText("Lines:", 278, 300, 32, 255, 255, 255);
    itoa(game->getLine(), number, 10);
    drawText(number, 278, 332, 32, 255, 255, 255);
}

void WINDOW_GAME::drawHelp() {
    drawText("                Tetris", 10, 0, 32, 128, 255, 128);
    drawText("  You die if the new figure", 10, 30, 32, 255, 255, 255);
    drawText("cannot move down", 10, 60, 32, 255, 255, 255);

    drawText("  100 points are awarded", 10, 120, 32, 255, 255, 255);
    drawText("for cleaning 1 linney", 10, 150, 32, 255, 255, 255);
    drawText("  300 points are awarded", 10, 180, 32, 255, 255, 255);
    drawText("for cleaning 2 linney", 10, 210, 32, 255, 255, 255);
    drawText("  700 points are awarded", 10, 240, 32, 255, 255, 255);
    drawText("for cleaning 3 linney", 10, 270, 32, 255, 255, 255);
    drawText("  1500 points are awarded", 10, 300, 32, 255, 255, 255);
    drawText("for cleaning 4 linney", 10, 330, 32, 255, 255, 255);

    drawText("  w - rotate figure", 10, 390, 32, 255, 255, 255);
    drawText("  a/d - move figure", 10, 425, 32, 255, 255, 255);
    drawText("  s - acceleration figure", 10, 455, 32, 255, 255, 255);
    drawText("  esc - exit in menu", 10, 485, 32, 255, 255, 255);
}

void WINDOW_GAME::drawAbout() {
    drawSurface(background, 0, 0);

    drawText("Veselov", 66, 100, 32, 255, 255, 255);
    drawText("Maxim", 72, 130, 32, 255, 255, 255);
    drawText("I596", 88, 160, 32, 255, 255, 255);

    drawText("Variant: 7", 52, 220, 32, 255, 255, 255);
}

void WINDOW_GAME::drawAll() {
    clearRender();
    clearTempSurface();

    static char countEnd = 0;

    switch(type) {
        case 0:
            drawMenu();
            break;

        case 1:
            drawGame();
            break;

        case 2:
            drawEnd();
            countEnd++;

            if(countEnd > 75) {
                game->clearGame();
                type = 0;
                countEnd = 0;
            }
            break;
        case 3:
            drawHelp();
            break;

        case 4:
            drawAbout();
            break;
    }

    updateWindow();
}

void WINDOW_GAME::pressLeftButton() {
    POINT pos = getMousePos();
    if(pos.x >= 60 && pos.x <= 180 && pos.y >= 80 && pos.y <= 140) {
        game->clearGame();
        setType(1);
    } else if(pos.x >= 60 && pos.x <= 180 && pos.y >= 180 && pos.y <= 240)
        setType(3);
    else if(pos.x >= 60 && pos.x <= 180 && pos.y >= 280 && pos.y <= 340)
        setType(4);
    else if(pos.x >= 60 && pos.x <= 180 && pos.y >= 380 && pos.y <= 440)
        SDL_Quit();
}
