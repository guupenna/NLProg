#ifndef INDICEPALAVRAS_H
#define INDICEPALAVRAS_H

typedef struct indicePalavras IndicePalavras;

IndicePalavras * InicializaIndicePalavras(IndicePalavras *palavras);

IndicePalavras * AtribuiIndicePalavras(IndicePalavras *p, char *caminhoAux);

void LiberaIndicePalavras(IndicePalavras *p);

void ImprimePalavras(IndicePalavras *p);

#endif