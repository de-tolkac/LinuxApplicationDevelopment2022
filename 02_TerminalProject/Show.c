#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>

#define DX 3

int getFileSize(FILE* fp) {
    fseek(fp, 0L, SEEK_END);
    int fileSize = ftell(fp);
    rewind(fp);

    return fileSize;
}

int countLinesInFile(FILE* fp) {
    int lines = 1;

    for (char c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') {
            lines += 1;
        }
    }

    rewind(fp);

    return lines;
}

void readFile(char*** data, char* fileName, int* fileSize, int* linesNumber) {
    FILE* fp = fopen(fileName, "r");

    if (fp == NULL) {
        return;
    }

    *fileSize = getFileSize(fp);
    *linesNumber = countLinesInFile(fp);
    
    if (*fileSize != 0) {
        *data = malloc(*linesNumber * sizeof(char*));

        for (int i = 0; i < *linesNumber; ++i) {
            (*data)[i]  = '\0';
            (*data)[i] = malloc(256 * sizeof(char));
            fgets((*data)[i], 256, fp);
        }
    }

    fclose(fp);
}

void freeMemory(char** data, int linesNumber) {
    for (int i = 0; i < linesNumber; ++i) {
        if (data[i] != NULL) {
            free(data[i]);
        }
    }

    if (data != NULL) {
        free(data);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Invalid number of parameters provided!\nExpected 2, but received %d", argc);
        return 0;
    }

    char** data = NULL;
    int fileSize = -1;
    int linesNumber = -1;

    readFile(&data, argv[1], &fileSize, &linesNumber);

    if (fileSize == -1) {
        printf("File %s invalid or doesnt exists!\n", argv[1]);
        return  0;
    }

    WINDOW *win;
    int c = 0;

    initscr();
    noecho();
    cbreak();
    printw("File: %s; size: %d; total lines: %d", argv[1], fileSize, linesNumber);
    refresh();

    win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    for (int i = 0; i < linesNumber; ++i) {
        wprintw(win, "  %d: %s\n", i + 1, data[i]);
    }

    box(win, 0, 0); 
    wmove(win, 1, 0); 
    while((c = wgetch(win)) != 27) {
            for (int i = 0; i < linesNumber; ++i) {
                wprintw(win, "  %d: %s\n", i + 1, data[i]);
            }
            box(win, 0, 0); 
            wrefresh(win);
    }
    endwin();

    freeMemory(data, linesNumber);
}