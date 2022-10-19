#include <stdio.h>
#include <stdlib.h>

void printSequence(int start, int end, int step) {
    for (int i = start; i < end; i += step) {
        printf("%d\n", i);
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Help:\n");
        printf("./range N     => [0, 1, ... N-1]\n");
        printf("./range N M   => [M, M+1, … N-1]\n");
        printf("./range N M S => [M, M+S, M+2S, … N-1]\n");
    } else if (argc == 2) {
        printSequence(0, atoi(argv[1]), 1);
    } else if (argc == 3) {
        printSequence(atoi(argv[1]), atoi(argv[2]), 1);
    } else if (argc == 4) {
        printSequence(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    } else {
        printf("Invalid arguments!\n");
    }

    return 0;
}