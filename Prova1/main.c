#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct Employee{
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
void createDataBase(FILE *file, int empQty) {
    for (int i = 1; i <= empQty; i++) {
        TEmployee emp;
        emp.code = rand()%1000;
        sprintf(emp.name, "Employee %d", i);
        sprintf(emp.cpf, "111.111.111 - 11");
        sprintf(emp.birthday, "20/08/1990");
        emp.wage = 1000;
        fseek(file, (i-1)*sizeof(struct Employee), SEEK_SET);
        save(&emp, file);
    }
}

// (B)
// Realize uma busca sequencial por um funcionário específico. Considerar como
// chave de busca o código do funcionário. Informe o total de comparações feitas até encontrar o
// funcionário em questão, bem como o tempo gasto na busca.
TEmployee *sequencial_search(int code, FILE *file) {
    int i = 0;
    while (i < 100) {
        fseek(file, sizeof(struct Employee), SEEK_SET);
        TEmployee *emp = read(file);
        if (code == emp->code) {
            return emp;
        } else {
            printf("Employee register not found!! \n");
            return NULL;
        }
        i++;
    }   
    return NULL;
}


// (D)
// Realize a busca pelo mesmo funcionário escolhido na letra b. Utilize agora a busca
// binária no arquivo ordenado. Informe o total de comparações feitas até encontrar o funcionário
// em questão, bem como o tempo gasto na busca.
TEmployee *binary_search(int code, FILE *file, int size) {
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

void insertionSort(FILE *file, int size) {
    fseek(file, 0, SEEK_SET);
    int i;
    for (int j = 2; j <= size; j++) {
        fseek(file, (j-1) * registerSize(), SEEK_SET);
        TFunc *fj = read(file);
        i = j - 1;
        fseek(file, (i-1) * registerSize(), SEEK_SET);
        do{
            TFunc *fi = read(file);
            if( (fi->cod < fj->cod)){
                break;
            }
            fseek(file, i * registerSize(), SEEK_SET);
            save(fi, file);
            i = i - 1;
            fseek(file, (i-1) * registerSize(), SEEK_SET);
            free(fi);
        }while ((i > 0) );
        fseek(file, (i) * registerSize(), SEEK_SET);
        save(fj, file);
        free(fj);
    }
    fflush(file);
}

int main() {
    clock_t start, end;

    FILE *file = fopen("prova1.dat", "wb+");
    if (file == NULL) {
        printf("Unable to open the file! \n");
        return 1;
    }

    int empQty = 100;
    createDataBase(file, empQty);
    // TEmployee *emp = binary_search(8, file, empQty);
    TEmployee *emp = sequencial_search(8, file);

    if (emp != NULL) {
        printf("### EMPLOYEE REGISTER FOUND!!! ### \n\n");
        printf("Code: %d \n", emp->code);
        printf("Name: %s \n", emp->name);
        printf("Cpf: %s \n", emp->cpf);
        printf("Birthday: %s \n", emp->birthday);
        printf("Wage: %.2f \n", emp->wage);
    } else {
        printf("Employee register not found! \n");
        return 1;
    }

    free(emp);
    fclose(file);
    return 0;
}
