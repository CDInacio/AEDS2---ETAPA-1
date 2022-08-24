#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Employee { 
    int code;
    char name[30];
    char cpf[11];
    char birthday[11];
    double wage;
}TEmployee;

void save(TEmployee *employee, FILE *out) {
    fwrite(&employee->code, sizeof(int), 1, out);
    fwrite(employee->name, sizeof(char), sizeof(employee->name), out);
    fwrite(employee->cpf, sizeof(char), sizeof(employee->cpf), out);
    fwrite(employee->birthday, sizeof(char), sizeof(employee->birthday), out);
    fwrite(&employee->wage, sizeof(double), 1, out);
}

TEmployee *read(FILE *in) {
    TEmployee *emp = (struct Employee *) malloc(sizeof(struct Employee));
    if (fread(&emp->code, sizeof(int), 1, in) <= 0) {
        free(emp);
        return NULL;
    }

    fread(emp->name, sizeof(char), sizeof(emp->name), in);
    fread(emp->cpf, sizeof(char), sizeof(emp->cpf), in);
    fread(emp->birthday, sizeof(char), sizeof(emp->birthday), in);
    fread(&emp->wage, sizeof(double), 1, in);

    return emp;
}

// (A)
// Crie uma base de dados contendo 100 registros de funcionários,
// armazenados em um arquivo binário.
void createDataSet(FILE *file, int empQty) {
    for (int i = 1; i <= empQty; i++) {
        TEmployee emp;
        emp.code = i;
        sprintf(emp.name, "Employee %d", i);
        sprintf(emp.cpf, "111.111.111 - 11");
        sprintf(emp.birthday, "20/08/1990");
        emp.wage = 1000;
        fseek(file, (i-1)*sizeof(struct Employee), SEEK_SET);
        save(&emp, file);
    }
}

// (B)
// Realize uma busca sequencial por um funcionário específico. Considerar 
// como chave de busca o código do funcionário. Informe o total de compar
// ações feitas até encontrar o funcionário em questão, bem como o tempo 
// gasto na busca.
void sequencialSearch (int code, FILE *file) {
    for (int i = 1; i <= 100; i++) {
        fseek(file, i*sizeof(TEmployee), SEEK_SET);
        TEmployee *emp = read(file);
        if (code == emp->code) {
            printf("ENCONTRADO");
            exit(1);
        }
    }
    printf("NÃO ENCONTRADO");
}

void keySort(int code, FILE *file) {
    
}

// (D)
// Realize a busca pelo mesmo funcionário escolhido na letra b. Utilize agora a busca
// binária no arquivo ordenado. Informe o total de comparações feitas até encontrar o
// funcionário em questão, bem como o tempo gasto na busca.
TEmployee *binarySearch (int code, FILE *file, int size) {
    int left = 0, right =  size - 1;
    while(left <= right) {
        int middle = (left + right) / 2;
        fseek(file, middle*sizeof(struct Employee), SEEK_SET);
        TEmployee *emp = read(file);
        if (code == emp->code) {
            return emp;
        } else if (emp->code < code) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return NULL;
}

int main() {
    FILE *file = fopen("prova1.dat", "wb+");
    if (file == NULL) {
        printf("Unable to open the file! \n");
        return 1;
    }

    int empQty = 100;
    // createData(file, empQty);
    sequencial_search(10, &file);
    

    return 0;
}
    // TEmployee *emp = binary_search(8, file, empQty);
