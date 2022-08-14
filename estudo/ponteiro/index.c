#include <stdio.h>
#include <stdlib.h>

void basicoDePonteiro1() {
    int value = 17;
    int *ptr;
    // int *ptr = &value;
    ptr = &value;

    printf("Conteudo da variavel ptr: %d\n", value);
    printf("Endereco da variavel value: %d\n", &value);
    printf("Endereco da variavel ptr: %d", ptr);
}

void basicoDePonteiro2() {
    int x = 10;
    int y = 100;
    char z = 'a';

    int *pX = &x;
    int *pY = &y;
    char *pZ = &z;

    double soma = *pX + *pY;

    printf("Endereco de X: %i - valor de X: %i\n", pX, *pX);
    printf("Soma: %f", soma);

}

typedef struct {
    int hora;
    int minuto;
    int segundo;
}Horario;

void ponteiroEstrutura() {
    Horario agora, *depois;
    depois = &agora;    

    depois->hora = 23;
    depois->minuto = 20;
    depois->segundo = 59;
 
    printf("%i:%i:%i\n", agora.hora, agora.minuto, agora.segundo);

    int somatorio = 100;

    Horario antes;
    // valores da estrutura depois sendo atribuidos para os valores da estrutura antes
    antes.hora = somatorio + depois->hora;
    antes.minuto = somatorio + depois->minuto;
    antes.segundo = somatorio + depois->segundo;

    printf("%i:%i:%i\n", antes.hora, antes.minuto, antes.segundo);
}

typedef struct {
    int *pHora;
    int *pMinuto;
    int *pSegundo;
}HorarioP;

void estruturaQueContemPonteiro() {
    HorarioP hoje;
    
    int hora = 10;
    int minuto = 20;
    int segundo = 30;

    hoje.pHora = &hora;
    hoje.pMinuto = &minuto;
    hoje.pSegundo = &segundo;

    printf("Hora: %i \n", *hoje.pHora);
    printf("Minuto: %i \n", *hoje.pMinuto);
    printf("Segundo: %i \n", *hoje.pSegundo);

    *hoje.pSegundo = 100;
    printf("Segundo: %i \n", *hoje.pSegundo);
}

// recebe um endereço de memória como parametro
void ponteiroComoParametroDeFuncao(int *pX) {
    ++*pX;
}

void testeVariavel(int x) {
    ++x;
}

int main() {
    int teste = 10;
    int *pTeste = &teste;

    // testeVariavel(teste);
    ponteiroComoParametroDeFuncao(pTeste);

    printf("%i\n", teste);

    return 0;
}