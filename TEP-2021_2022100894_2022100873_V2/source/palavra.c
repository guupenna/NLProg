#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../headers/palavra.h"
#include "../headers/caracteristicas.h"
#include "../headers/indiceDocs.h"
#include "../headers/arrayBusca.h"

#define FREQ_INICIAL 1
#define TF_IDF_PADRAO 0

struct palavra {
    char *palavra;
    Caracteristicas **crts;
    int qtdAparicoes;
};

Palavra * AlocaPalavra(int tamPalavra)
{
    Palavra *p = (Palavra *)malloc(sizeof(Palavra));

    p->crts = (Caracteristicas **)malloc(sizeof(Caracteristicas *));
    p->palavra = (char *)malloc(tamPalavra*sizeof(char));
    p->qtdAparicoes = 0;

    return p;
}

Palavra * AlocaPalavra_auxBusca(char *palavra)
{
    Palavra *p = (Palavra *)malloc(sizeof(Palavra));

    int tamPalavra=strlen(palavra)+1;
    p->palavra = (char *)malloc(tamPalavra*sizeof(char));

    strncpy(p->palavra, palavra, tamPalavra);

    return p;
}

void LiberaPalavra_auxBusca(Palavra *p)
{
    free(p->palavra);
    free(p);
}

Palavra * InicializaPalavra(Palavra *p, char *palavra, int nDoc)
{
    int tamPalavra = strlen(palavra)+1;
    
    p = AlocaPalavra(tamPalavra);

    p->crts[0] = InicializaCaracteristicas(p->crts[0], nDoc, FREQ_INICIAL, TF_IDF_PADRAO);

    strncpy(p->palavra, palavra, tamPalavra); // Atribui a palavra (string) na struct

    p->qtdAparicoes = 1;

    return p;
}

Palavra * AdicionaFrequencia(Palavra *p, int nDoc)
{
    int i = 0;

    for (i = 0 ; i < p->qtdAparicoes; i++)
    {
        if (VerificaSeAddFrequencia(p->crts[i], nDoc))
        {
            p->crts[i] = SomaNaFrequencia(p->crts[i]);
            return p;
        }
    }
    
    p->qtdAparicoes++;
            
    p->crts = (Caracteristicas **)realloc(p->crts, p->qtdAparicoes*sizeof(Caracteristicas *));
    p->crts[p->qtdAparicoes-1] = InicializaCaracteristicas(p->crts[p->qtdAparicoes-1], nDoc, FREQ_INICIAL, TF_IDF_PADRAO);
    
    return p;
}

int ComparaPalavras(Palavra *p, char *palavra)
{
    if (!strcmp(p->palavra, palavra))
    {
        return 1;
    }
    
    return 0;
}

int PelaPalavra(const void *a, const void *b)
{
    const Palavra **p1 = (const Palavra **)a;
    const Palavra **p2 = (const Palavra **)b;

    return strcmp((*p1)->palavra, (*p2)->palavra);
}

void AtribuiTf_idfPalavra(Palavra *p, IndiceDocs *docs, int flagClassificador)
{
    int i = 0, docsTotais = 0, docsAparicao = 0;
    double idf = 0;

    if (flagClassificador)
    {
        docsTotais = ObtemQtdDocumentos(docs) + 1;
        docsAparicao = p->qtdAparicoes + 1;
    }

    idf = log(((double)(1+docsTotais))/((double)(1+docsAparicao))) + 1;

    for (i = 0; i < p->qtdAparicoes; i++)
    {
        CalculaTf_idf(p->crts[i], idf);
    }
}

void FinalizaCaracDocumentos_palavras(Palavra *p, IndiceDocs *docs, int posPalavra)
{
    int i;

    for (i = 0; i < p->qtdAparicoes; i++)
    {
        FinalizaCaracDocumentos_carac(p->crts[i], docs, posPalavra);
    }
}

void SalvaPalavraBin(Palavra *p, FILE *f)
{
    int tamPalavra=strlen(p->palavra)+1;

    fwrite(&tamPalavra, sizeof(int), 1, f); // TAMANHO
    
    // Salvando a palavra
    for (int i = 0 ; i < tamPalavra; i++)
    {
        fwrite(&p->palavra[i], sizeof(char), 1, f); // PALAVRA
    }

    fwrite(&p->qtdAparicoes, sizeof(int), 1, f); // APARI????ES

    for (int i = 0; i < p->qtdAparicoes; i++)
    {
        SalvaCaracteristicasBin(p->crts[i], f); // CARACTERISTICAS
    }
}

Palavra * CarregaPalavraBin(Palavra *p, FILE *f)
{
    int tamPalavra=0;
    
    p = (Palavra *)malloc(sizeof(Palavra));

    fread(&tamPalavra, sizeof(int), 1, f); // TAMANHO

    p->palavra = (char *)malloc(tamPalavra*sizeof(char));
    
    // Lendo a palavra
    for (int i = 0 ; i < tamPalavra; i++)
    {
        fread(&p->palavra[i], sizeof(char), 1, f); // PALAVRA
    }

    fread(&p->qtdAparicoes, sizeof(int), 1, f); // APARI????ES

    p->crts = (Caracteristicas **)malloc(p->qtdAparicoes*sizeof(Caracteristicas *));

    for (int i = 0; i < p->qtdAparicoes; i++)
    {
        p->crts[i] = CarregaCaracteristicasBin(p->crts[i], f); // CARACTERISTICAS
    }

    return p;
}

void ImprimePalavra(Palavra *p)
{
    int i;

    printf("%s\n", p->palavra);

    for (i = 0; i < p->qtdAparicoes; i++)
    {
        ImprimeCaracteristicas(p->crts[i]);
    }

}

void LiberaPalavra(Palavra *p)
{
    for (int i = 0; i < p->qtdAparicoes; i++)
    {
        LiberaCaracteristicas(p->crts[i]);
    }  

    free(p->crts); 
    free(p->palavra);
    free(p);
}

void CriaArrayDeBusca_Palavra(Palavra *p, ArrayBusca *arrayB, IndiceDocs *docs)
{
    for (int i = 0; i < p->qtdAparicoes; i++)
    {
        CriaArrayDeBusca_Carac(p->crts[i], arrayB, docs);
    }
}

int ObtemQtdAparicoes(Palavra *p)
{
    return p->qtdAparicoes;
}

char * ObtemPalavra(Palavra *p)
{
    return p->palavra;
}

void CriaDoc_classificador_palavra(Palavra *p, Documento *doc, int indicePalavra)
{
    CriaDoc_classificador_carac(p->crts[p->qtdAparicoes-1], doc, indicePalavra);
}

int StringIgualPalavra(Palavra *p, char *palavra)
{
    return !strncmp(p->palavra, palavra, strlen(palavra)+1);
}

void RelatorioPalavra(Palavra *p, char *palavra, int *arrayIndicesInt)
{
    Palavra *Rp = AlocaPalavra(strlen(palavra)+1);

    Rp = CopiaPalavra(p, Rp);

    qsort(Rp->crts, Rp->qtdAparicoes, sizeof(Caracteristicas *), PelaFrequencia);

    int i = 0;
    while (i < 10 && i < Rp->qtdAparicoes)
    {
        arrayIndicesInt[i] = RetornaPosicao(Rp->crts[i]);
        i++;
    }
    if (i != 10) arrayIndicesInt[i] = -1;

    printf("\nN??mero de documentos em que ""%s"" aparece: %d\n", Rp->palavra, Rp->qtdAparicoes);

    LiberaPalavra(Rp);
}

Palavra * CopiaPalavra(Palavra *p, Palavra *Rp)
{
    strncpy(Rp->palavra, p->palavra, strlen(p->palavra)+1);

    for (int i = 1; i <= p->qtdAparicoes; i++)
    {
        Rp->qtdAparicoes++;

        Rp->crts = (Caracteristicas **)realloc(Rp->crts, Rp->qtdAparicoes*sizeof(Caracteristicas *));

        Rp->crts[i-1] = CopiaCarac(p->crts[i-1], Rp->crts[i-1]);
    }

    return Rp;
}