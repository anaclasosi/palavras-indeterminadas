'''O programa recebe os arquivos e cria palavras indeterminadas separadas por '/' '''
import sys
simbolos = {'a','c','g','t','n', 'A','C','G','T','N'}

def main():

    a = len(sys.argv)   # Recebe na linha de comando os argumentos
    t = a-2

    arq = []    # Lista com o nome dos arquivos
    for i in range(1,a):
        arq.append(str(sys.argv[i]))

    s = []      # Lista com o conteudo dos arquivos
    for i in range(a-2):
        s.append(abrir_arquivo(arq[i]))

    tam = maior_arquivo_texto(t,s)
    print("O tamanho do maior texto é:", tam)

    nova_string  = comparar_strings_set(s, tam)    # Funcao para comparacao dos arquivos
        
    arquivo_saida = str(sys.argv[a-1])
    escrever_arquivo (nova_string , arquivo_saida) # Escreve no arquivo
    print("String escrita com sucesso no arquivo de saída!")

def abrir_arquivo(nome):
    """Recebe um arquivo e abre para a leitura"""
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
    '''Compara o conteudo dos arquivos em cada indice'''
    str_saida = ""
    aux = set()
    vazio = set()
    
    for i in range(tam):            # Percorre as strings
        for j in range(len(s)):     # Percorre os índices da lista
            try:       
                if(s[j][i] not in simbolos): 
                    continue
                else:
                    aux.add(s[j][i])
            except:        # Quando um índice não puder ser acessado
                continue
        if aux == vazio:   # Caso em que em todas as strings não tem um s[j][i] pertencente aos simbolos
            continue
        else:
            lista = list(aux)
            lista.sort()   # Coloca a lista em ordem alfabetica
            if 'N' in lista:
                str_saida = 'N'
            elif 'n' in lista:
                str_saida = 'n'
            else:
                for base in lista:
                    str_saida += base
            
            str_saida += "/"
            aux.clear()

    return str_saida

def escrever_arquivo (nova_string, nome_arquivo):
    """Escreve no arquivo a string final"""
    arquivo = open(nome_arquivo, 'w')
    return arquivo.write(nova_string)

if __name__ == "__main__":
    main()