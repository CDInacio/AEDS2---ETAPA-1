#include <stdio.h>
#include <stdlib.h>

// Menu
int menu(){
    int opc;

    printf("##### SEJA BEM-VINDO #####\n");
    printf("Escolha uma das opcoes abaixo\n\n");
    printf("1: Escrever arquivo de texto\n");
    printf("2: Escrever arquivo binario\n");
    printf("3: Ler arquivo de texto\n");
    printf("4: Ler arquivo binario\n");
    printf("5: Escrever matriz de inteiros\n");
    fflush(stdin);
    scanf("%d", &opc);

    return opc;
}

//Acesso sequencial -> escrever arquivo txt
void writeTextFile1(char text[], char file_name[]){
    FILE *file = fopen(file_name, "w");
    fprintf(file, "%s", text);
    fclose(file);
}

//Acesso sequencial -> escrever arquivo txt
void writeTextFile2 (char file_name[]){
    int nums[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    FILE *file = fopen(file_name, "w");
    for (int i = 0; i < 10; i ++){
        fprintf(file, "%d \n", nums[i]);
    }
    fclose(file);
}

//Acesso sequencial -> l  arquivo txt
void readTextFile(char file_name[]){
    char c;
    FILE *file = fopen(file_name, "r");
    if (file != NULL){
        while((fscanf(file, "%c", &c)) != EOF){
            printf("%c", c);
        }
    }
    fclose(file);
}

//Acesso sequencial -> escrever arquivo binario
void writeBinaryFile(char file_name[]){
    FILE *file = fopen(file_name, "wb");
    int nums [3] = {1, 2, 3};
    if (file != NULL){
        fwrite(nums, sizeof(int), 3, file);
    }
    fclose(file);
}

//Acesso sequencial -> l  arquivo binario
void readBinaryFile(char file_name[]){
    FILE *file = fopen(file_name, "rb");
    char nums[3];
    int i = 0;
    if (file != NULL) {
        while(fread(&nums[i], sizeof(int), 1, file) == 1) {
            printf("%d\n", nums[i]);
            i++;
        }
    }
    fclose(file);
}

// Retorna o n mero de espa os em branco em um arquivo
int countBlackSpaces(char file_name[]) {
    FILE *file = fopen(file_name, "r");
    int count = 0;
    char c;
    while(!feof(file)) {
        c = fgetc(file);
        if (c  == ' ') count ++;
    }
    return c;
}

//Escreve matriz de inteiros
void writeMatrix(int matrix[4][4], int m, int n, char file_name[]) {
    FILE *file = fopen(file_name, "w");

    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            fprintf(file, "%d", i+j);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}


int main() {

    menu();


    return 0;
}





















