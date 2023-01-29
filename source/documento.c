#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/documento.h"
#include "../headers/caracteristicas.h"

struct documento {
    char *nome, *classe;
    Caracteristicas **crts;
    int qtdPalavras;
};

Documento * AlocaDocumento(int tamNome, int tamClasse)
{
    Documento *doc = (Documento *)malloc(sizeof(Documento));

    doc->nome = (char *)malloc(tamNome*sizeof(char));
    doc->classe = (char *)malloc(tamClasse*sizeof(char));
    doc->crts = NULL;
    doc->qtdPalavras = 0;

    return doc;
}

Documento * AtribuiNomeClasse(Documento *doc, char *nome, char *classe)
{
    int tamNome = strlen(nome)+1;
    int tamClasse = strlen(classe)+1;

    doc = AlocaDocumento(tamNome, tamClasse);

    strncpy(doc->nome, nome, tamNome);
    strncpy(doc->classe, classe, tamClasse);

    return doc;
}

void AtribuiCaracDoc(Documento *doc, int posPalavra, int freqPalavra, double tf_idf)
{
    doc->qtdPalavras++;
    doc->crts = (Caracteristicas **)realloc(doc->crts, doc->qtdPalavras*sizeof(Caracteristicas *));

    doc->crts[doc->qtdPalavras-1] = InicializaCaracteristicas(doc->crts[doc->qtdPalavras-1], posPalavra, freqPalavra, tf_idf);
}

void SalvaDocBin(Documento *doc, FILE *f)
{
    int tamNome = strlen(doc->nome)+1;
    int tamClasse = strlen(doc->classe)+1;

    fwrite(&tamNome, sizeof(int), 1, f); // TAMANHO NOME
    fwrite(&tamClasse, sizeof(int), 1, f); // TAMANHO CLASSE

    for (int i = 0; i < tamNome; i++)
    {
        fwrite(&doc->nome[i], sizeof(char), 1, f); // NOME
    }
    for (int i = 0; i < tamClasse; i++)
    {
        fwrite(&doc->classe[i], sizeof(char), 1, f); // CLASSE
    }

    fwrite(&doc->qtdPalavras, sizeof(int), 1, f); // QTD_PALAVRAS

    for (int i = 0; i < doc->qtdPalavras; i++)
    {
        SalvaCaracteristicasBin(doc->crts[i], f); // CARACTERISTICAS
    }
}

Documento * CarregaDocBin(Documento *doc, FILE *f)
{
    int tamNome=0, tamClasse=0;

    fread(&tamNome, sizeof(int), 1, f); // TAMANHO NOME
    fread(&tamClasse, sizeof(int), 1, f); // TAMANHO CLASSE

    doc = AlocaDocumento(tamNome, tamClasse);

    // Lendo o nome
    for (int i = 0; i < tamNome; i++)
    {
        fread(&doc->nome[i], sizeof(char), 1, f); // NOME
    }

    // Lendo a classe
    for (int i = 0; i < tamClasse; i++)
    {
        fread(&doc->classe[i], sizeof(char), 1, f); // CLASSE
    }

    fread(&doc->qtdPalavras, sizeof(int), 1, f); // QTD_PALAVRAS

    doc->crts = (Caracteristicas **)malloc(doc->qtdPalavras*sizeof(Caracteristicas *));

    for (int i = 0; i < doc->qtdPalavras; i++)
    {
        doc->crts[i] = CarregaCaracteristicasBin(doc->crts[i], f); // CARACTERISTICAS
    }

    return doc;
}

void ImprimeDoc(Documento *doc) 
{
    // int i;

    printf("nome: %s - classe: %s\n", doc->nome, doc->classe);
 
    // for (i = 0; i < doc->qtdPalavras; i++)
    // {
    //     ImprimeCaracteristicas(doc->crts[i]);
    // }
}

void LiberaDoc(Documento *doc)
{
    for (int i = 0; i < doc->qtdPalavras; i++)
    {
        LiberaCaracteristicas(doc->crts[i]);
    }
    
    free(doc->crts);
    free(doc->nome);
    free(doc->classe);

    free(doc);
}

int DocsSaoIguais(Documento *doc1, Documento *doc2)
{
    if (doc1 == doc2)
    {
        return 1;
    }

    return 0;
}