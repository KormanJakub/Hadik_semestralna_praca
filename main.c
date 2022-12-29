#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//zvazujem ci nebude treba nejaku upravu podla mnozstva maximalneho ale nie som si ista
int main(int argc, char** argv) {



    printf("Vitajte v hre 'Hadik'!\n");
    int i, j, height = 20;
    int width = 100;
    int xOvocie = rand() % width + 1;
    int yOvocie = rand() % height + 1;

    for ( i = 0; i < height; ++i) {
        for ( j = 0; j < width; ++j) {

            if (i == 0 || i == height -1){
                printf("-");
            } else if( j == 0 || j == width - 1){
                printf("|");
            } else if( xOvocie == j && yOvocie == i){
                printf("*");
            }
            else{
                printf(" ");
            }

        }
        printf("\n");
    }


    return 0;
}
