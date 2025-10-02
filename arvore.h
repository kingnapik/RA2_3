#ifndef ARVORE_H
#define ARVORE_H

#include <string>
#include <vector>

using namespace std;

struct NoArvore {
    string simbolo; //cada simbolo aqui, tipo ( MEM +
    vector<NoArvore*> filhos; //cria filhos
    bool ehTerminal; //e terminal?
    
    NoArvore(string s, bool terminal = false);
    ~NoArvore(); //mata criancas (⊙ _ ⊙ )
};

struct Derivacao {
    vector<string> passos; //steps
    NoArvore* raiz;
    bool sucesso; //deu?
    string mensagemErro; //msg de erro
    
    Derivacao();
    ~Derivacao();
};

// Funcoes da arvore
NoArvore* gerarArvore(Derivacao* derivacao);
void imprimirArvore(NoArvore* no, int nivel = 0);
void gerarHTML(NoArvore* raiz, int numeroLinha);
void salvarArvoreMarkdown(NoArvore* raiz, int numeroLinha);

#endif