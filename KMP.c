#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Digitar o arquivo text, padrão e o tipo do dado fornecido, resultado no arquivo result.txt*/
int primos[] = {0, 0, 1, 1, 0, 1, 0, 1};
int binarios[] = {0, 1, 1, 0, 1, 0, 0, 0, 1};

int kmp(char *text, char *pad, int tipo);
int padrao_regular (char *pad, int m, int tipo);
int* border(char *pad, int m, int tipo); 
int cmp(char text, char pad, int tipo);
int INDET(char text, int tipo);
int set_indety(int i, int j, int rigth_pos);
int compute_shift(bool indety, char *text, char *pad, int i, int j, int *borda, int l);
int* prefixo(char *compq);
char* substring(const char* str, int start, int end);
char* concatenar(const char* str1, const char* str2);

enum TIPO {REGULAR, PRIMOS, BINARIO};

int main(int argc, char **argv){ 

    if(argc != 4){ 
        exit(EXIT_FAILURE);
    }

    int tipo;
    tipo = atoi(argv[3]);
 
        FILE *tex = fopen(argv[1], "rb"); 
        if(tex == NULL){
            perror("Erro ao abrir arquivo text.");
        return 1;
        } 

        fseek(tex, 0, SEEK_END); //fseek deixa no último bite do arquivo
        size_t tamtex = ftell(tex); //ftell responde quantos bites tem no arquivo
        rewind(tex);

        char *text = (char *)malloc(tamtex+1); //malloc recebe a quantidade de bites
        if (text == NULL) exit(EXIT_FAILURE);

        FILE *pat = fopen(argv[2], "r");
        if(pat == NULL){
            perror("Erro ao abrir arquivo pad."); 
        return 1;
        }

        fseek(pat, 0, SEEK_END);
        size_t tampad = ftell(pat);
        rewind(pat);

        char *pad = (char *)malloc(tampad+1); 
        if (pad == NULL) exit(EXIT_FAILURE);

        fscanf(tex, "%s", text);
        fscanf(pat, "%s", pad);

        kmp(text, pad, tipo);              
        fclose(tex);
        fclose(pat);
    
    return 0;
}

int kmp(char *text, char *pad, int tipo){
    int n = strlen(text), m = strlen(pad);

    int l = padrao_regular(pad, m, tipo); // Funcao ate onde o pad é regular
    
    int *borda = border(pad, l, tipo);    // Calcula a borda

    FILE *res = fopen("result.txt", "w");
    if(res == NULL){
        perror("Erro ao abrir arquivo de resultados");
        return 1;
    }

    int i = 0, j = 0;
    bool indety = false;
    int rigth_pos = 0;

    while (i < n) {   
            
        if (cmp(pad[j], text[i], tipo)){ //Se for similar passa para a próxima comparação
            printf("Confere %d\n", i);
            if (INDET(text[i], tipo)){
                indety = true;
                rigth_pos = i;
            }
            j++;
            i++;

            if (j == m) { // Ocorre quando a comparação chega ao final do padrão
                printf("Padrao encontrado na posicao %d\n", i-j);
                fprintf(res, "Padrao encontrado na posicao %d\n", i-j);   //Escreve no arquivo result.txt
                j = compute_shift(indety, text, pad, i, j, borda, l);
                indety = set_indety(i, j, rigth_pos);
            }
        } 
        else{
            if (j == 0) { 
                i++;
            } 
            else{ //Define j<i para voltar a comparar
                j = compute_shift(indety, text, pad, i, j, borda, l);
                set_indety(i, j, rigth_pos); 
            }
        }
    }
    free(borda);
    return 0;
}

int padrao_regular (char *pad, int m, int tipo){

    if(tipo == REGULAR){
        return m; 
    }

    else if(tipo == PRIMOS){

        for(int i=0; i<m; i++){
            if(pad[i] > 7) return i;
            else
                if(primos[pad[i]]==0) return i;      
        }
        return m;
    }
    else if (tipo == BINARIO){
        for(int i=0; i<m; i++){
            if(pad[i] > 8) return i;
            else
                if(binarios[pad[i]]==0) return i; 
        }
        return m;
    }

    else perror("Tipo de dado inválido ou inexistente"); return 1;
}

int* border(char *pad, int m, int tipo){

    int *borda = (int *)malloc(m *sizeof(int));
    if (borda == NULL) exit(EXIT_FAILURE);

    int k = 0;  
    borda[0] = 0;  //O primeiro valor sempre é 0 porque não tem comparação

    for (int q = 1; q < m; q++){
        while (k > 0 && (cmp(pad[q], pad[k], tipo) == 0)){                   //pad[k] != pad[q]
            k = borda[k - 1];
        }
        if (cmp(pad[q], pad[k], tipo)==1){                                   //pad[q] == pad[k]
            k++;
        }
        borda[q] = k;
    }
    return borda;
}

int cmp(char text, char pad, int tipo){

    if(tipo==REGULAR){

        if(text == pad) return true;
        else return false;
    }

    else if(tipo == PRIMOS){
        while (text != 0){  //MDC
            int temp = text;
            text = pad % text;  
            pad = temp;  
        }

        if(pad > 1) return true;
        else return false;
    }

    else if(tipo == BINARIO){
        
        if((pad & text) != 0){
            return true;
        }
        else return false;
    }
}

int INDET(char simbolo, int tipo){
    if(tipo == PRIMOS){
        
        if(simbolo > 7) return true;
        else
            if(primos[simbolo]==0) return true;
        return false;
    }
    if(tipo == BINARIO){
        
        if(simbolo > 8) return true;
        else
            if(binarios[simbolo]==0) return true;
        return false;
    }
    return false;
}

int set_indety(int i, int j, int rigth_pos){

    int k = i-j;

    if (k < rigth_pos && j > rigth_pos) return true;
    else return false;
}

int compute_shift(bool indety, char *text, char *pad, int i, int j, int *borda, int l){
    int max = 0;

    if(indety || j<l){
        //compq = pad[0:j] + text[i-j+1:i];
        char* subPadrao = substring(pad, 0, j); 

        printf("Subpadrao\n");
        for(int i = 0; i<(int)strlen(subPadrao); i++) printf(" %c ", subPadrao[i]); printf("\n");

        printf("Subtexto\n");
        char* subTexto = substring(text, i-j+1, i); 
        for(int i = 0; i<(int)strlen(subTexto); i++) printf(" %c ", subTexto[i]); printf("\n");
        char* compq = concatenar(subPadrao, subTexto);

        printf("Comparacao q \n");
        for(int i = 0; i<(int)strlen(compq); i++) printf("%d ", compq[i]); printf("\n");  //Imprime o compq
        printf("FIM Compute_shift \n");
        
        if (compq == NULL) return 0;
        int* picompq = prefixo(compq);
        for(int i = 0; i<(int)strlen(compq); i++) printf("%d ", picompq[i]); printf("\n");  //Imprime o prefixo

        max = 0;
        for(int r = j; r<2*(j); r++){
            if (max < picompq[r] && picompq[r] == 2*j-r) max = picompq[r];
        j = max;
        }
    }
    else j = borda[j-1];
    return j;
}

int* prefixo(char *compq){
    int ind = 0, r = 1, tam = strlen(compq), j = 0;
    int* picompq = (int*)malloc(tam * sizeof(int));
    if (picompq == NULL) exit(EXIT_FAILURE);
    picompq[0] = tam;
        for (r; r<tam; r++){
            j = r;
            while (compq[j] == compq[ind]){
                picompq[r] = ind;    //iniciar picompq
                j++;
                ind++;
            }
            picompq[r] = ind;    //iniciar picompq
            ind = 0;
        }
    return picompq;
}

char* substring(const char* str, int start, int end){

    if (str == NULL) return NULL;

    // Função para extrair uma substring
    if (start > end || start < 0 || end >= (int)strlen(str)) return NULL;  // Se os índices forem inválidos
    
    char* sub = (char*)malloc((end - start + 2) * sizeof(char)); // +2 para o '\0'
    if (sub == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    
    strncpy(sub, str + start, end - start + 1); // Copia uma quantidade específica de caracteres de uma string
    sub[end - start + 1] = '\0'; // Adiciona '\0' como fim
    return sub;
}

char* concatenar(const char* str1, const char* str2){
    // Função para concatenar duas strings
    char* result = (char*)malloc(strlen(str1) + strlen(str2) + 1);
    if (result == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}