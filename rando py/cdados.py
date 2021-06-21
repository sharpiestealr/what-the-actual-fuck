import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

import os

filename = 'dados.xlsx'
if filename in os.listdir():
    print(f'Encontrei o arquivo {filename}, tudo certo para prosseguir com a prova!')
else:
    print(f'Não encontrei o arquivo {filename} aqui no diretório {os.getcwd()}, será que você não baixou o arquivo?')

train = pd.read_excel(filename)
train.head(5)

test = pd.read_excel(filename, sheet_name = 'Teste')
test.head(5)

quer=''
naoquer=''
for i in range(len(train.Relevancia)):
    if train.Relevancia[i] == 1:
        quer=quer+train.Treinamento[i]

for i in range(len(train.Relevancia)):
    if train.Relevancia[i] == 0:
        naoquer=naoquer+train.Treinamento[i]

import re 
def cleanup(text):
    """
        Função de limpeza muito simples que troca alguns sinais básicos por espaços
    """
    #import string
    punctuation = '[!-.:?;,(\n)('')("")/@(rt)(\)]' # Note que os sinais [] são delimitadores de um conjunto.
    pattern = re.compile(punctuation)
    text_subbed = re.sub(pattern, '', text)
    return text_subbed

#limpa o texto
quer_limpo=cleanup(quer.lower())
naoquer_limpo=cleanup(naoquer.lower())

#espaçamento correto #não conseguimos ;-;😭
alfabeto = ['a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' , 'j', 'k' , 'l', 'm' , 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0']
def limpa(x):
    lista=list(x)
    x=' '
    for i in range(len(lista)):
        if lista[i] not in alfabeto:
            lista[i]= ' ' + lista[i] + ' '
        elif lista[i] in alfabeto:
            lista[i]=lista[i]
    x =''.join(lista)
#tranforma em um conjunto de palavras
palavras_quer=quer_limpo.split()
palavras_naoquer=naoquer_limpo.split()

#gera uma planilha
serie_quer=pd.Series(palavras_quer)
serie_naoquer=pd.Series(palavras_naoquer)

#conta as quantidades
tabela_quer=serie_quer.value_counts()
tabela_naoquer=serie_naoquer.value_counts()

#faz as quantidades relativas
relativo_quer=serie_quer.value_counts(True)
relativo_naoquer=serie_naoquer.value_counts(True)

#definindo variaveis
probquer = len(serie_quer)/(len(serie_quer)+len(serie_naoquer))
probnaoquer = len(serie_naoquer)/(len(serie_quer)+len(serie_naoquer))

def classifica(x):
    x.insert(2,"treinado",'')
1    for i in range(len(x.Teste)):
        x2=''
        x2=x.Teste[i]
    
        x2=cleanup(x2.lower())
        x3=x2.split()

        probFraseDadoq= 1
        probFraseDadon= 1

        for i in range(len(x3)):
            if x3[i] in relativo_quer:
                probFraseDadoq= probFraseDadoq *relativo_quer[x3[i]]
                if x3[i] in relativo_naoquer:
                    probFraseDadon=probFraseDadon *relativo_naoquer[x3[i]]

            elif x3[i] in relativo_naoquer:
                probFraseDadon= probFraseDadon *relativo_naoquer[x3[i]]
                if x3[i] in relativo_quer:
                    probFraseDadoq= probFraseDadoq *relativo_quer[x3[i]]

        probFraseDadoq=probFraseDadoq*probquer
        probFraseDadon=probFraseDadon*probnaoquer

        if (probFraseDadoq/probFraseDadon) > (probFraseDadon/probFraseDadoq) :
            x.treinado[i]=1
        elif (probFraseDadoq/probFraseDadon) < (probFraseDadon/probFraseDadoq) :
            x.treinado[i]=0
classifica(test)
test.treinado.value_counts()