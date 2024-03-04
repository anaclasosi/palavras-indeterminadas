#Fechar todos n arquivos
import sys
simbolos = {'a','c','g','t','n'}

def main():

    a = len(sys.argv)   #Recebe na linha de comando os argumentos
    t = a-2

    arq = []    #Lista com o nome dos arquivos
    for i in range(1,a):
        arq.append(str(sys.argv[i]))

    s = []      #Lista com o conteudo dos arquivos
    for i in range(a-1):
        s.append(abrir_arquivo(arq[i]))

    tam = maior_arquivo_texto(t,s)
    print("O tamanho do maior texto é:", tam)

    nova_string  = comparar_strings_set(s, tam)  #Comparacao dos arquivos
        
    arquivo_saida = str(sys.argv[a-1])
    escrever_arquivo (nova_string , arquivo_saida) #Escreve no arquivo
    print("String escrita com sucesso no arquivo de saída!")

def abrir_arquivo(nome):
    """Recebe um arquivo e abre para a escrita"""
    try:
        arq = open(nome, 'r')
        return arq.read()
    except:
        print("Não foi possivel abrir o arquivo")

def maior_arquivo_texto(t, s):
    """Encotra o maior índice exluindo o último argumento do argv"""
    acc = 0
    for i in range(t):
        if len(s[i]) > acc:
            acc = len(s[i])
                
    return acc
        
def comparar_strings_set(s, tam):
    str_saida = ""
    aux = set()
    
    for i in range(tam):            # Percorre as strings
        for j in range(len(s)):     # Percorre os índices da lista
            try:       
                if(s[j][i] not in simbolos): 
                    continue
                else:
                    aux.add(s[j][i])
            except:     # Quando um índice não puder ser acessado
                continue
        if aux == {}:   # Caso em que em todas as strings não tem um s[j][i] pertencente aos simbolos
            continue
        else:
            for base in aux:
                str_saida += base
            str_saida += "/"
            aux.clear()

    return str_saida


def comparar_strings(str1, str2):   #Antigo
    """Realiza a comparação de duas strings"""

    str_saida = ""
    
    if(len(str1) < len(str2)):
         a = str1
         b = str2
    else:
         a = str2
         b = str1

    i = 0
    tam = len(a)
    while(i < tam):
        if(a[i] not in simbolos and b[i] not in simbolos ): 
            i+=1
            continue

        if(a[i] not in simbolos and b[i] in simbolos ):
            str_saida += "/" + b[i]
            i+=1
            continue #ou else if
        if(a[i] in simbolos and b[i] not in simbolos ):
            str_saida += "/" + a[i]
            i+=1
        else:
            if a[i] == b[i]:
                    str_saida += "/" +  a[i]  
            else:
                    str_saida += "/" + a[i] + b[i] 
            i+=1
    
    tam = len(b)
    while(i<tam):
        str_saida += "/" +  b[i]  
        i+=1

    str_saida += "/"
    
    print(str_saida)

    return str_saida

def escrever_arquivo (nova_string, nome_arquivo):
    """Escreve no arquivo a string final"""
    arquivo = open(nome_arquivo, 'w')
    return arquivo.write(nova_string)

if __name__ == "__main__":
    main()