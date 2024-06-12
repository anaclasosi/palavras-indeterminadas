'''O programa recebe uma palavra indeterminada e a converte para números binários'''
import sys
nucleotideos = {"a":1, "c":2, "g":4, "t":8, "n":16,  "A":1, "C":2, "G":4, "T":8, "N":16}

def main():
    arq = abrir_arquivo(sys.argv[1])
    str_bin, lista_bin = num_binario(arq)
    escrever_arquivo_bin(lista_bin, sys.argv[2])
    escrever_arquivo_texto(str_bin, sys.argv[3])
    str_bin_tex = decodificar_binario(sys.argv[2])
    escrever_arquivo_texto(str_bin_tex, sys.argv[4])
    
def abrir_arquivo(nome):
    """Recebe um arquivo e abre para a leitura"""
    try:
        arq = open(nome, 'r')
        return arq.read()
    except:
        print("abrir_arquivo: Não foi possivel abrir o arquivo")   

def num_binario(arq):
    str_bin = ""
    lista_bin = []
    
    acc = 0
    for i in range(len(arq)):
        if arq[i] == "/":
            str_bin += str(acc) + "/"
            lista_bin.append(acc)
            acc = 0
        else:
            acc = acc + nucleotideos[arq[i]]
    
    return str_bin, lista_bin 

def escrever_arquivo_texto (mapeamento, nome_arquivo):
    """Escreve no arquivo a string final"""
    arquivo = open(nome_arquivo, 'w')
    return arquivo.write(mapeamento)

def escrever_arquivo_bin (lista_primos, nome_arquivo):
    try:
        arq = open(nome_arquivo, 'wb')
        for item in lista_primos:
            arq.write(item.to_bytes(4, byteorder='little', signed=True))
    except:
        print("escrever_arquivo_bin: Não foi possivel abrir o arquivo")

def decodificar_binario(binario):
    try:
        bin = open(binario,'rb')
        str_bin_tex = ""
    except:
        print("decodificar_binario: erro ao abrir arquivo")
    x = bin.read(4)
    while True:
        y = int.from_bytes(x, byteorder='little', signed=True) 
        str_bin_tex += str(y) + "/"
        x = bin.read(4)
        if not x:
            break
    bin.close()
    '''
    for item in bin: # seleciona uma linha de binarios do arquivo
        for num in item: # seleciona um byte da linha
            str_bin_tex += str(num) + "/"
    '''
    return str_bin_tex

if __name__ == "__main__":
    main()