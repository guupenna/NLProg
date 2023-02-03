#ifndef INDICEDOCS_H
#define INDICEDOCS_H

#include "documento.h"

typedef struct indiceDocs IndiceDocs;

IndiceDocs * AtribuiNomeClasseIndiceDocs(IndiceDocs *docs, char *caminho, char *classe);

IndiceDocs * InicializaIndiceDocs(IndiceDocs *docs);

int ObtemQtdDocumentos(IndiceDocs *docs);

void ImprimeDocs(IndiceDocs *docs);

Documento * AchaDocumento(IndiceDocs *docs, int posDocumento);

void SalvaIndiceDocsBin(IndiceDocs *docs, FILE *f);

IndiceDocs * CarregaIndiceDocsBin(IndiceDocs *docs, FILE *f);

void LiberaIndiceDocs(IndiceDocs *docs);

double * CriaArrayCossenos(IndiceDocs *docs, Documento *doc);

void AtribuiArrayDouble(double *a, double *b, int tam);

int OrdenaCossenos(const void *a, const void *b);

int OrdenaStrings(const void *a, const void *b);

char * ClassificaNoticia(double *cossenos, IndiceDocs *docs, int K);

IndiceDocs * CopiaIndiceDocs(IndiceDocs *docs, IndiceDocs *Rdocs);

void AtribuiSomaDasFrequencias_Indice(IndiceDocs *docs, IndiceDocs *Rdocs);

void OrdenaRelatorioDocs(IndiceDocs *Rdocs, int flagOrdem);

void ImprimeRelatorioDocs(IndiceDocs *Rdocs, int flagOrdem);

void ImprimeDocsPorIndice(IndiceDocs *docs, int *arrayIndicesInt);

char ** CriaArrayClassesDeduzidas(IndiceDocs *docsTrain, IndiceDocs *docsTeste, int K);

char ** CriaArrayClassesVerdadeiras(IndiceDocs *docsTeste, int K);

char ** ObtemClassesUnicas(char **classesUnicas, char **classesVerdadeiras, int qtdDocs, int *qtdClasses);

int ObtemPosicaoClasse(char *classe, char **classesUnicas, int qtdClasses);

#endif