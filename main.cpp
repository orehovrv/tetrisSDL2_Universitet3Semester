#include <SDL2/SDL.h>
#include "SDL_ttf.h"

#include <stdio.h>
#include <stdlib.h>
#undef main

#include "SCORE.h"
#include "LOGICS_TETRIS.h"

#include "WINDOW_GAME.h"
#include "WINDOW_SCORE.h"

Uint32 ttFunk1(Uint32, void*); //Функция для таймера 1
Uint32 ttFunk2(Uint32, void*); //Функция для таймера 2

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();

    SDL_Event event;
    SDL_TimerID updateImage, step;

    updateImage = SDL_AddTimer(30, ttFunk1, 0); //таймер для обновления картинки
    step = SDL_AddTimer(300, ttFunk2, 0); //таймер для "шага" в тетрисе

    SCORE score; //реорды
    score.load(); //загрузка рекордов

    LOGICS_TETRIS game; //логика игры
    game.setPointerScore(&score); //связка логики игры и рекордов
    game.clearGame(); //обнуление игры

    WINDOW_GAME windowGame; //окно с игрой и главное меню
    windowGame.start("Tetris", 300, 100, 400, 540, &game);

    WINDOW_SCORE windowScore; //окно с рекордами
    windowScore.start("Leaderboard", 750, 100, 220, 540, &score);

    bool flag = 1; //вспомогательная переменная для ускорения фигур
    bool KEYS[322] = {0}; //текущее состояние клавиатуры
    int lines = 0, lastCountLines = 0, speedStep = 300; //вспомогательные переменные

    while (SDL_WaitEvent(&event)) {
        switch(event.type) {
            case SDL_USEREVENT:
                switch(event.user.code) {
                    case 1: //обновление картинки
                        windowGame.drawAll();
                        windowScore.drawAll();
                        break;

                    case 2: //движение фигур и ускорение фигур
                        game.moveDownFigure(); //сдвиг фигуры

                        lines = game.getLine(); //изменение скорости сдвига фигур
                        if(lastCountLines != lines) {
                            lastCountLines = lines;
                            if(speedStep > 50) {
                                speedStep = 300 - lines * 2;
                                SDL_RemoveTimer(step);
                                step = SDL_AddTimer(speedStep, ttFunk2, 0);
                            }
                        }

                        break;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button) {
                    case SDL_BUTTON_LEFT:
                        switch(event.window.windowID) {
                            case 1: //левый клик по 1 окну
                                windowGame.pressLeftButton();
                                break;

                            case 2: //левый клик по 2 окну
                                windowScore.pressLeftButton();
                                break;
                        }
                        break;

                    case SDL_BUTTON_RIGHT:
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                switch(event.window.windowID) {
                    case 1: //запись позиции курсора на 1 окне
                        windowGame.setMousePos(event.motion.x, event.motion.y);
                        break;

                    case 2: //запись позиции курсора на 2 окне
                        windowScore.setMousePos(event.motion.x, event.motion.y);
                        break;
                }
                break;

            //обработка нажатий на клавиатуре
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_w: //вращение фигуры
                        switch(event.window.windowID) {
                            case 1:
                                game.rotateFigure();
                                break;
                        }
                        break;

                    case SDLK_d: //сдвиг фигуры вправо
                        switch(event.window.windowID) {
                            case 1:
                                game.moveRightFigure();
                                break;
                        }
                        break;

                    case SDLK_a: //сдвиг фигуры влево
                        switch(event.window.windowID) {
                            case 1:
                                game.moveLeftFigure();
                                break;
                        }
                        break;

                    case SDLK_s: //ускорение сдвига фигуры вниз
                        switch(event.window.windowID) {
                            case 1:
                                if(flag) {
                                    SDL_RemoveTimer(step);
                                    step = SDL_AddTimer(50, ttFunk2, 0);
                                    flag = 0;
                                }
                                break;
                        }
                        break;

                    case SDLK_ESCAPE: //выход в главное меню
                        switch(event.window.windowID) {
                            case 1:
                                windowGame.setType(0);
                                game.clearGame();
                                break;
                            case 2:
                                windowScore.setFlag(0);
                                break;
                        }
                        break;
                }
                KEYS[event.key.keysym.sym] = 1;
                break;

            case SDL_KEYUP:
                switch(event.key.keysym.sym) {
                    case SDLK_s: //установка стандартной скорости сдвига фигуры вниз
                        switch(event.window.windowID) {
                            case 1:
                                if(!flag) {
                                    SDL_RemoveTimer(step);
                                    step = SDL_AddTimer(speedStep, ttFunk2, 0);
                                    flag = 1;
                                }
                                break;
                        }
                        break;
                }
                KEYS[event.key.keysym.sym] = 0;
                break;

            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_CLOSE: //реакция на закрытие окна
                        SDL_Quit();
                        break;

                    //установка фокуса на разных окнах
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        switch(event.window.windowID) {
                            case 1:
                                windowGame.setFocus(1);
                                break;
                            case 2:
                                windowScore.setFocus(1);
                                break;
                        }
                        break;

                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        switch(event.window.windowID) {
                            case 1:
                                windowGame.setFocus(0);
                                break;
                            case 2:
                                windowScore.setFocus(0);
                                break;
                        }
                        break;
                }
                break;

            case SDL_QUIT:
                break;
        }
    }

    score.save(); //сохранение рекордов

    TTF_Quit();
    SDL_Quit();
    return 0;
}

Uint32 ttFunk1(Uint32 interval, void *param){
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 1;
    userevent.data1 = 0;
    userevent.data2 = 0;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

Uint32 ttFunk2(Uint32 interval, void *param){
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 2;
    userevent.data1 = 0;
    userevent.data2 = 0;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}
