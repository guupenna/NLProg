#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../headers/caracteristicas.h"
#include "../headers/indiceDocs.h"
#include "../headers/documento.h"

struct caracteristicas {
    int posicao, frequencia;
    double tf_idf;
};

Caracteristicas * AlocaCaracteristicas()
{
    Caracteristicas *crts = (Caracteristicas *)malloc(sizeof(Caracteristicas));

    return crts;
}

Caracteristicas * InicializaCaracteristicas(Caracteristicas * crts, int pos, int freq, double tf_idf)
{
    crts = AlocaCaracteristicas();
    crts->posicao = pos;
    crts->frequencia = freq;
    crts->tf_idf = tf_idf;

    return crts;
}

Caracteristicas * SomaNaFrequencia(Caracteristicas *crts)
{
    crts->frequencia++;

    return crts;
}

int VerificaSeAddFrequencia(Caracteristicas * crts, int nDoc)
{
    if (crts->posicao == nDoc) 
    {
        return 1;
    }
    
    return 0;
}

void CalculaTf_idf(Caracteristicas *crts, int df, int n)
{
    double tf, idf;

    tf = crts->frequencia;
    idf = log((1+n)/(1+df))+1;

    crts->tf_idf = tf*idf;
}

void SalvaCaracteristicasBin(Caracteristicas *crts, FILE *f)
{
    fwrite(&crts->posicao, sizeof(int), 1, f);

    fwrite(&crts->frequencia, sizeof(int), 1, f);

    fwrite(&crts->tf_idf, sizeof(double), 1, f);
}

void ImprimeCaracteristicas(Caracteristicas *crts)
{
    printf("pos: %d - freq: %d - tf_idf: %.2lf\n", crts->posicao, crts->frequencia, crts->tf_idf);
}

void LiberaCaracteristicas(Caracteristicas *crts)
{
    free(crts);
}

void FinalizaCaracDocumentos_carac(Caracteristicas *crts, IndiceDocs *docs, int posPalavra)
{
    AtribuiCaracDoc(AchaDocumento(docs, crts->posicao), posPalavra, crts->frequencia, crts->tf_idf);
}