#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int KMP(char *texto, char *padrao);
int kmp(char *texto, char *padrao); //novo
int* prefixo(char *padrao, int m);

int main(int argc, char **argv){ 

    if(argc != 3){
        exit(EXIT_FAILURE);
    }

    FILE *tex = fopen(argv[1], "rb");   //Abre binário
    if(tex == NULL){
        perror("Erro ao abrir arquivo texto_binario.");
    return 1;
    } 

    fseek(tex, 0, SEEK_END); //fseek deixa no último bite do arquivo
    size_t tamtex = ftell(tex)/sizeof(int); //ftell responde quantos bites tem no arquivo
    rewind(tex);

    int *texto = (int *)malloc(tamtex*sizeof(int)); //malloc recebe a quantidade de bites e reserva na memória
    if (texto == NULL) exit(EXIT_FAILURE);

    FILE *pad = fopen(argv[2], "rb");
    if(pad == NULL){
        perror("Erro ao abrir arquivo padrao_binario."); 
    return 1;
    }
    
    fseek(pad, 0, SEEK_END);
    size_t tampad = ftell(pad)/sizeof(int);
    rewind(pad);

    int *padrao = (int *)malloc(tampad*sizeof(int)); 
    if (padrao == NULL) exit(EXIT_FAILURE);
 
    fread(texto, 4, tamtex, tex);      //Precisa ler cada numero e separar com: / (usar for ou while?)
    fread(padrao, 4, tampad, pad);
    size_t i;
    for(i=0; i<tamtex; i++)
        printf("%d\t%d\n", i, texto[i]);
    //printf("%s\n FIM2 \n", padrao);                                        //Imprime o padrao

    kmp(texto, padrao);                                            //KMP

    fclose(tex);
    fclose(pad);
    return 0;
}

int kmp(char *texto, char *padrao){
    int n = strlen(texto), m = strlen(padrao);

    int *pi = prefixo(padrao, m);

    //for(int i=0; i<m; i++) printf("%d ", pi[i]); printf("\n");  //Imprime o pi

    FILE *res = fopen("result.txt", "w");
    if(res == NULL){
        perror("Erro ao abrir arquivo de resultados");
        return 1;
    }

    int j = 0, i = 0; 

    while (j < n) {
        if (padrao[i] == texto[j]) { //Se igual passa para a próxima comparação
            i++;
            j++;

            if (i == m) { // Quando a comparação chega ao final do padrão, ou seja, deu certo
                //TODO: escrever a saída em um arquivo
                printf("Padrão encontrado na posição %d\n", j - i);
                fprintf(res, "Padrão encontrado na posição %d\n", j-i); //Escreve no arquivo result.txt
                i = pi[i - 1];
            }
        } 
        else {
            if (i == 0) { 
                j++;
            } 
            else { //Define i<j para voltar a comparar
                i = pi[i - 1]; 
            }
        }
    }
    free(pi);
    return 0;
}

int* prefixo(char *padrao, int m){

    int *pi = (int *)malloc(m *sizeof(int));
    if (pi == NULL) exit(EXIT_FAILURE);

    int k = 0;  
    pi[0] = 0;  // O primeiro valor sempre é 0 porque não tem comparação

    for (int q = 1; q < m; q++){
        while (k > 0 && padrao[k] != padrao[q]){
            k = pi[k - 1];
        }
        if (padrao[q] == padrao[k]){
            k++;
        }
        pi[q] = k;
    }
    return pi;
}

int KMP(char *texto, char *padrao){ //ANTIGO
    int m = strlen(padrao), n = strlen(texto);

    int *pi = prefixo(padrao, m);

    for(int i=0; i<m; i++) printf("%d ", pi[i]); printf("\n");  //Imprime o pi

    FILE *res = fopen("result.txt", "w");
    if(res == NULL){
        perror("Erro ao abrir arquivo de resultados");
        return 1;
    }

    int q = 0;

    for (int i = 0; i < n; i++){
        while (q > 0 && texto[i] != padrao[q]){
            q = pi[q - 1];
        }
        if (texto[i] == padrao[q]){
            q++;
        }
        if (q == m){
            printf("Padrão encontrado no índice: %d", i-q+2);  //Imprime a posição encontrada
            fprintf(res, "Padrão encontrado no índice: %d\n", i-q+2); //Escreve no arquivo result.txt
            q = pi[q - 1];
        }
    }
    free(pi);
    return 0;
}
