#include "SCORE.h"

SCORE::SCORE() {

}

SCORE::~SCORE() {

}

void SCORE::clear() {
    for(i = 0; i < 7; i++) {
        mass[i].score = 0;
        mass[i].lengScore = 1;
        mass[i].lines = 0;
        mass[i].lengLines = 1;
    }
    save();
}

int SCORE::lengNumber(int num) {
    int temp = 1;
    while(num /= 10) temp++;
    return temp;
}

void SCORE::load() {
    file = fopen(wayFile, "rb");

    if(file) {
        i = 0;
        while(fread(mass + i, 1, sizeof(NODE), file)) {
            mass[i].lengLines = lengNumber(mass[i].lines);
            mass[i].lengScore = lengNumber(mass[i].score);
            i++;
        }
    }

    fclose(file);
    sortMass();
}

void SCORE::save() {
    file = fopen(wayFile, "wb");

    if(file) {
        for(i = 0; i < 7; i++)
            fwrite(mass + i, 1, sizeof(NODE), file);
    }

    fclose(file);
}

void SCORE::viewMass() {
    for(i = 0; i < 7; i++)
        printf("lines: %3d lengLines: %2d score: %6d lengScore: %2d\n", mass[i].lines, mass[i].lengLines, mass[i].score, mass[i].lengScore);
}

void SCORE::sortMass() {
    for (i = 0; i < 6; i++)
        for (j = 6; j > i; j--)
            if (mass[j - 1].score < mass[j].score || (mass[j - 1].score == mass[j].score && mass[j - 1].lines > mass[j].lines)) {
                NODE temp = mass[j - 1];
                mass[j - 1] = mass[j];
                mass[j] = temp;
            }
}

void SCORE::add(int score, int lines) {
    NODE a;

    a.score = score;
    a.lengScore = lengNumber(score);
    a.lines = lines;
    a.lengLines = lengNumber(lines);

    mass[6] = a;
    sortMass();
}

NODE *SCORE::getMass() {
    return mass;
}
