#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

void menu(Matriz* m);
int ler_int(const char* msg);
void ler_coordenadas(int* x, int* y);

int main() {
    Matriz* m = NULL;
    int opcao;

    do {
        menu(m);
        opcao = ler_int("");

        if (!m) {
            switch (opcao) {
                case 1: {
                    int linhas = ler_int("Digite o numero de linhas: ");
                    int colunas = ler_int("Digite o numero de colunas: ");
                    m = cria_matriz(linhas, colunas);
                    if (m) {
                        printf("Matriz %dx%d criada com sucesso!\n", linhas, colunas);
                        imprime_matriz(m);
                    } else {
                        printf("Erro: dimensoes invalidas.\n");
                    }
                    break;
                }
                case 0: printf("Saindo...\n"); break;
                default: printf("Opcao invalida. Crie uma matriz primeiro.\n"); break;
            }
        } else {
            int x, y, valor, valor_lido;
            Elemento* no_encontrado;

            switch (opcao) {
                case 1:
                    ler_coordenadas(&x, &y);
                    valor = ler_int("Digite o valor: ");
                    if (insere_matriz(m, valor, x, y))
                        printf("Valor %d inserido em (%d, %d).\n", valor, x, y);
                    else
                        printf("Erro: posicao (%d, %d) fora dos limites.\n", x, y);
                    break;
                case 2:
                    ler_coordenadas(&x, &y);
                    if (remove_especifico(m, x, y))
                        printf("Valor em (%d, %d) removido (0).\n", x, y);
                    else
                        printf("Erro: posicao (%d, %d) fora dos limites.\n", x, y);
                    break;
                case 3:
                    ler_coordenadas(&x, &y);
                    if (consulta_valor(m, x, y, &valor_lido))
                        printf("Valor em (%d, %d) = %d\n", x, y, valor_lido);
                    else
                        printf("Erro: posicao (%d, %d) fora dos limites.\n", x, y);
                    break;
                case 4:
                    valor = ler_int("Digite o valor a ser buscado: ");
                    no_encontrado = busca_valor(m, valor);
                    printf(no_encontrado ? "O valor %d foi encontrado.\n" 
                                         : "O valor %d nao foi encontrado.\n", valor);
                    break;
                case 5:
                    ler_coordenadas(&x, &y);
                    imprime_vizinhos(m, x, y);
                    break;
                case 6:
                    imprime_matriz(m);
                    break;
                case 7:
                    printf("\tDados da Matriz\n");
                    printf("Dimensoes: %d x %d\n", m->linhas, m->colunas);
                    printf("Nos totais: %d\n", tamanho_total(m));
                    printf("Nos usados: %d\n", tamanho_usado(m));
                    printf("Matriz vazia? %s\n", matriz_vazia(m) ? "Sim" : "Nao");
                    printf("Matriz cheia? %s\n", matriz_cheia(m) ? "Sim" : "Nao");
                    break;
                case 8:
                    libera_matriz(m);
                    m = NULL;
                    printf("Matriz liberada.\n");
                    break;
                case 0:
                    libera_matriz(m);
                    printf("Saindo e liberando memoria...\n");
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
            }
        }
        printf("\nPressione ENTER para continuar...");
        getchar(); getchar();  // pausa
    } while (opcao != 0);

    return 0;
}

void menu(Matriz* m) {
    printf("\n\tMenu\n");
    if (!m) {
        printf("1 - Criar Matriz\n0 - Sair\n");
    } else {
        printf("1 - Inserir\n2 - Remover\n3 - Consultar\n4 - Buscar\n5 - Vizinhos\n6 - Imprimir\n7 - Estatisticas\n8 - Liberar\n0 - Sair\n");
    }
    printf("Escolha uma opcao: ");
}

int ler_int(const char* msg) {
    int valor;
    if (msg[0]) printf("%s", msg);
    scanf("%d", &valor);
    return valor;
}

void ler_coordenadas(int* x, int* y) {
    *x = ler_int("Digite a linha (x): ");
    *y = ler_int("Digite a coluna (y): ");
}
