#include <stdio.h>
#include <stdlib.h>

int countDiamonds(char* line);

int main(){

    int i, N;
    char line[1001];

    scanf('%d', &N);
    getchar();

    for (i = 0; i < N; i++) {
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0;
        printf("%d\n", countDiamonds(line));
    }

    return 0;
}

int countDiamonds(char* line){
    int i,count = 0;
    int open = 0;

    for (i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '<') {
            open++; 
        } else if (linha[i] == '>' && open > 0) {
            count++;
            open--; 
        }
    }

    return count;
}