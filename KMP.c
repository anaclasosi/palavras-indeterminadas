#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Digitar o arquivo text, padrão e o tipo do dado fornecido, resultado no arquivo result.txt*/
int primos[] = {0, 0, 1, 1, 0, 1, 0, 1};
int binarios[] = {0, 1, 1, 0, 1, 0, 0, 0, 1};

int kmp(char *text, char *pad, int tipo);
int* padrao_regular (char *pad, int m, int tipo);
int* border(char *pad, int m, int tipo); 
int cmp(char text, char pad, int tipo);
int INDET(char text, int tipo);
int set_indety(int i, int j, int rigth_pos);
int compute_shift(bool indety, char *text, char *pad, int i, int j, int *borda, int l);
int prefixo(char *compq);
char* substring(const char* str, int start, int end);
char* concatenar(const char* str1, const char* str2);

enum TIPO {REGULAR, PRIMOS, BINARIO};

int main(int argc, char **argv){ 

    if(argc != 4){ 
        exit(EXIT_FAILURE);
    }

    int tipo;
    tipo = atoi(argv[4]);
 
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

        FILE *pad = fopen(argv[2], "rb");
        if(pad == NULL){
            perror("Erro ao abrir arquivo pad."); 
        return 1;
        }

        fseek(pad, 0, SEEK_END);
        size_t tampad = ftell(pad);
        rewind(pad);

        char *pad = (char *)malloc(tampad+1); 
        if (pad == NULL) exit(EXIT_FAILURE);

        fscanf(tex, "%s", text);
        fscanf(pad, "%s", pad);

        kmp(text, pad, tipo);              
        fclose(tex);
        fclose(pad);
    
    return 0;
}

int kmp(char *text, char *pad, int tipo){
    int n = strlen(text), m = strlen(pad);

    char* ql = padrao_regular(pad, m, tipo); // funçao que vê até onde o pad é regular
    
    for(int j=0; j<m; j++) printf("%d ", ql[j]); printf("\n"); //Imprime o ql
    
    int l = strlen(ql);
    int *borda = border(ql, l, tipo); // alterar para receber ql

    for(int j=0; j<m; j++) printf("%d ", borda[j]); printf("\n");  //Imprime o borda

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
            if (INDET(text[i], tipo)){
                indety = true;
                rigth_pos = i;
            }
            j++;
            i++;

            if (j == m) { // Ocorre quando a comparação chega ao final do padrão
                printf("Padrão encontrado na posição %d\n", i-j);
                fprintf(res, "Padrão encontrado na posição %d\n", i-j);   //Escreve no arquivo result.txt
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
                indety = set_indety(i, j, rigth_pos); 
            }
        }
    }
    free(ql);
    free(borda);
    return 0;
}

int* padrao_regular (char *pad, int m, int tipo){
    int *ql = (int *)malloc(m *sizeof(int));
    if (ql == NULL) exit(EXIT_FAILURE);

    if(tipo == REGULAR){
        return pad; 
    }

    else if(tipo == PRIMOS){

        for(int i=0; i<m; i++){
            if(pad[i] > 7) return ql;
            else
                if(primos[pad[i]]==0) return ql;      
            ql[i] = pad[i];
        }
    }
    else if(tipo == BINARIO){
        for(int i=0; i<m; i++){
            if(pad[i] > 8) return ql;
            else
                if(binarios[pad[i]]==0) return ql; 
            ql[i] = pad[i];
        }
    }
    return ql;
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
        
        if((pad & text) != 0) return true;
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
    
    if (k < rigth_pos && j > rigth_pos) return true;
    else return false;
}

int compute_shift(bool indety, char *text, char *pad, int i, int j, int *borda, int l){
    int max = 0;

    if(indety || j<l){
        //compq = pad[1:j] + text[i-j+1:i];
        char* subPadrao = substring(pad, 0, j); 
        char* subTexto = substring(text, i-j+1, i); 
        char* compq = concatenar(subPadrao, subTexto);

        if (compq == NULL) return 0;
        int* picompq = prefixo(compq);
        max = 0;
        for(int r = j; r<2*(j-2)){
            if(max < picompq[r] && picompq[r] = 2*j-r-2) max = picompq[r];
        j = max;
        }
    }
    else j = borda[j-1];
    return j;
}

int* prefixo(char *compq){
    int ind = 0, r = 1, tam = strlen(compq), j;
    int* picompq = (int*)malloc(tam * sizeof(int));
    if (picompq == NULL) exit(EXIT_FAILURE);
    picompq[0] = tam;
        while (compq[j] == compq[ind]){
        j = r;
        while (compq[j] == compq[ind]){
        picompq[r] = ind;    //iniciar picompq
            j++;
        picompq[r] = ind;    //iniciar picompq
        ind = 0;
        }
    }
    return picompq;
}

char* substring(const char* str, int start, int end){
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