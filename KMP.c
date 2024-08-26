#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Digitar o arquivo texto, padrão e o tipo do dado fornecido */

//int KMP(char *texto, char *padrao); //antigo
int kmp(char *texto, char *padrao, int tipo);
int* prefixo(char *padrao, int m, int tipo); 
int cmp(char texto, char padrao, int tipo);
int INDET(char texto, char padrao, int tipo);

enum TIPO {REGULAR, PRIMOS, BINARIO};

int main(int argc, char **argv){ 

    if(argc != 4){ 
        exit(EXIT_FAILURE);
    }

    int tipo;
    tipo = atoi(argv[4]);
 
        FILE *tex = fopen(argv[1], "r");    //lendo apenas txt
        if(tex == NULL){
            perror("Erro ao abrir arquivo texto.");
        return 1;
        } 

        fseek(tex, 0, SEEK_END); //fseek deixa no último bite do arquivo
        size_t tamtex = ftell(tex); //ftell responde quantos bites tem no arquivo
        rewind(tex);

        char *texto = (char *)malloc(tamtex+1); //malloc recebe a quantidade de bites
        if (texto == NULL) exit(EXIT_FAILURE);

        FILE *pad = fopen(argv[2], "r");
        if(pad == NULL){
            perror("Erro ao abrir arquivo padrao."); 
        return 1;
        }

        fseek(pad, 0, SEEK_END);
        size_t tampad = ftell(pad);
        rewind(pad);

        char *padrao = (char *)malloc(tampad+1); 
        if (padrao == NULL) exit(EXIT_FAILURE);

        fscanf(tex, "%s", texto);
        fscanf(pad, "%s", padrao);

        kmp(texto, padrao, tipo);              
        fclose(tex);
        fclose(pad);
    
    return 0;
}

int kmp(char *texto, char *padrao, int tipo){
    int n = strlen(texto), m = strlen(padrao);
    
    int *pi = prefixo(padrao, m, tipo);

    //for(int i=0; i<m; i++) printf("%d ", pi[i]); printf("\n");  //Imprime o pi

    FILE *res = fopen("result.txt", "w");
    if(res == NULL){
        perror("Erro ao abrir arquivo de resultados");
        return 1;
    }

    int j = 0, i = 0;

    while (j < n) {        
        if (cmp(padrao[i], texto[j], tipo)) { //Se for similar passa para a próxima comparação
            i++;
            j++;

            if (i == m) { // Ocorre quando a comparação chega ao final do padrão
                printf("Padrão encontrado na posição %d\n", j-i);
                fprintf(res, "Padrão encontrado na posição %d\n", j-i);   //Escreve no arquivo result.txt
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

int* prefixo(char *padrao, int m, int tipo){

    int *pi = (int *)malloc(m *sizeof(int));
    if (pi == NULL) exit(EXIT_FAILURE);

    int k = 0;  
    pi[0] = 0;  // O primeiro valor sempre é 0 porque não tem comparação

    for (int q = 1; q < m; q++){
        while (k > 0 && (cmp(padrao[q], padrao[k], tipo) == 0)){                   //padrao[k] != padrao[q]
            k = pi[k - 1];
        }
        if (cmp(padrao[q], padrao[k], tipo)==1){                                      //padrao[q] == padrao[k]
            k++;
        }
        pi[q] = k;
    }
    return pi;
}

int cmp(char texto, char padrao, int tipo){

    INDET(texto, padrao, tipo) ? tipo = REGULAR : ;

    if(tipo==REGULAR){
        if(texto == padrao){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(tipo == PRIMOS){
        if(padrao % texto == 0 || texto % padrao == 0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(tipo == BINARIO){
        if(padrao & texto != 0){
            return 1;
        }
    }
}

int INDET(char texto, char padrao, int tipo){
    if(tipo == PRIMOS){
        int primos[] = {2, 3, 5, 7};    //TODO: não está conferindo direito ainda
        for (int i = 0; i < 3; i++){
            if (primos[i] == texto && primos[i] == padrao){
                return true;  // Retorna true se o caractere for encontrado
            }
    }
    return false;  // Retorna false se o caractere não for encontrado
}
    if(tipo == BINARIO){
        int binarios[] = {1, 2, 4, 8};    //TODO: não está conferindo direito ainda(alterar n no mapeamento binarios)
        for (int i = 0; i < 3; i++){
            if (binarios[i] == texto && binarios[i] == padrao){
                return true;  // Retorna true se o caractere for encontrado
            } 
    }
    return false;
}
    return true;  //Se for regular
}

/*
int KMP(char *texto, char *padrao){ // modelo ANTIGO
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
*/
