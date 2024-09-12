'''Compara os arquivos'''
import sys

def main():
    arq = []
    for i in range(1, len(sys.argv)):
        arq.append(abrir_arquivo(sys.argv[i]))
    q_texto = len(sys.argv)
    t_texto = len(arq[1])
    comparar_arq(arq, q_texto, t_texto)

def abrir_arquivo(nome):
    """Recebe um arquivo e abre para a leitura"""
    try:
        arq = open(nome, 'r')
        return arq.read()
    except:
        print("abrir_arquivo: Não foi possivel abrir o arquivo")

def comparar_arq(arq, q_texto, t_texto):
    for i in range(0, q_texto-2): # Confere se os tamanhos são iguais
        if len(arq[i]) == len(arq[i+1]):
            print("Os tamanhos são iguais!")
            x = True
        else:
            print("Os tamanhos são diferentes")
            x = False
            break
    if x == True: # Se os tamanhos forem iguais continua para a comparação por índice
        for i in range(0,q_texto-2): 
            for j in range(t_texto):
                if arq[i][j] != arq[i+1][j]:
                    print("Os arquivos não são iguais na posição: ", j)
                    print("Onde {} diferente de {}" .format(arq[i][j], arq[i+1][j]))
                    x = False
                    break
            if x == True:
                print("Os arquivos são iguais!")

if __name__ == "__main__":
    main()