#include <stdio.h>
#include <stdlib.h>

typedef struct aluno {
    char nome[50];
    int idade;
}t_aluno;

// ARQUIVO DE REGISTRO EM C
void writeRegisterBin(t_aluno a1, t_aluno a2, t_aluno a3, char fileName[]) {
    FILE *file = fopen(fileName, "wb");
    if (file != NULL) {
        fwrite(&a1, sizeof(t_aluno), 1, file);
        fwrite(&a2, sizeof(t_aluno), 1, file);
        fwrite(&a3, sizeof(t_aluno), 1, file);
        fclose(file);
    }
    printf("Error ao abrir arquivo\n");
    exit(1);
}

void readBinRegister(char fileName[]) {
    FILE *file = fopen(fileName, "rb");
    if (file != NULL) {
        while (1) {
            t_aluno a;
            size_t qtd = fread(&a, sizeof(t_aluno), 1, file);
            if (qtd < 1) {
                break;
            } else {
                printf("Nome: %s\n", a.nome);
                printf("Idade: %i\n", a.idade);
            }
            fclose(file);
        }
    } else {
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }
}

int main() {

    t_aluno a1 = {"claudio", 26};
    printf("%s", a1.nome);

    return 0;
}
