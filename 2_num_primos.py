#Cria arquivo com numeros primos e binário 
import sys
nucleotideos = {"a":2, "c":3, "g":5, "t":7, "n":210,  "A":2, "C":3, "G":5, "T":7, "N":210}

#quando N --> entrada == /a,c,g,t/ == /210/

def main():
    s = abrir_arquivo(sys.argv[1])
    str_primos, lista_primos = num_primo(s) # Resultado
    escrever_arquivo_bin(lista_primos, sys.argv[2])
    escrever_arquivo_texto(str_primos, sys.argv[3])
    str_bin_tex = decodificar_binario(sys.argv[2]) # Abre e decodifica o binario
    escrever_arquivo_texto(str_bin_tex, sys.argv[4])

def abrir_arquivo(nome):
    """Recebe um arquivo e abre para a leitura"""
    try:
        arq = open(nome, 'r')
        return arq.read()
    except:
        print("abrir_arquivo: Não foi possivel abrir o arquivo")

def num_primo(s):
    str_primos = ""
    lista_primos = []
    acc = 1
    for i in range(len(s)):
        if s[i] == "/":
            str_primos += str(acc) + "/"
            lista_primos.append(acc)
            acc = 1
        else:

            acc = acc*nucleotideos[s[i]]
    return str_primos, lista_primos

def escrever_arquivo_texto (primos, nome_arquivo):
    """Escreve no arquivo a string final"""
    arquivo = open(nome_arquivo, 'w')
    return arquivo.write(primos)

def escrever_arquivo_bin (lista_primos, nome_arquivo):
    try:
        arq = open(nome_arquivo, 'wb')
        for item in lista_primos:
            arq.write(item.to_bytes(1, byteorder='little', signed=True))
    except:
        print("escrever_arquivo_bin: Não foi possivel abrir o arquivo")

def decodificar_binario(binario):
    try:
        bin = open(binario,'rb')
        str_bin_tex = ""
    except:
        print("decodificar_binario: erro ao abrir arquivo")
    x = bin.read(1)
    while True:
        y = int.from_bytes(x, byteorder='little', signed=True) 
        str_bin_tex += str(y) + "/"
        x = bin.read(4)
        if not x:
            break
    bin.close()

    return str_bin_tex
        
if __name__ == "__main__":
    main()