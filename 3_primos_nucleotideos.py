# muda de primos para nucleotídeos
import sys

def main():
    arq = abrir_arquivo(sys.argv[1])
    str_nuc = converte_nucleotideos(arq)
    escrever_arquivo_texto (str_nuc, sys.argv[2])

def abrir_arquivo(nome):
    """Recebe um arquivo e abre para a leitura"""
    try:
        arq = open(nome, 'r')
        return arq.read()
    except:
        print("abrir_arquivo: Não foi possivel abrir o arquivo")

def converte_nucleotideos(arq):
    num = ""
    str_nuc = ""
    
    for i in range(len(arq)):
        if arq[i] != "/":
            num += str(arq[i])
        else:
            inum = int(num)
            num = ""
            if inum%2 == 0:
                str_nuc += "a"
            if inum%3 == 0:
                str_nuc += "c"
            if inum%5 == 0:
                str_nuc += "g"
            if inum%11 == 0:
                str_nuc += "n"
            if inum%7 == 0:
                str_nuc += "t" 
            str_nuc += "/"
        
    return str_nuc

def escrever_arquivo_texto (resultado, nome_arquivo):
    """Escreve no arquivo a string final"""
    arquivo = open(nome_arquivo, 'w')
    return arquivo.write(resultado)                  

if __name__ == "__main__":
    main()