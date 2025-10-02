// Guilherme Knapik - kingnapik
// Analisador Sintatico LL(1) - Fase 2

#include "gramatica.h"
#include "parser.h"
#include "arvore.h"
#include "leitor.h"
#include <iostream>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {//verifica argumentos de entrada
    if (argc < 2) {
        cerr << "Uso: ./AnalisadorSintatico <arquivo_tokens.txt>" << endl;
        return 1;
    }
    
    string nomeArquivo = argv[1];
    
    try {
        cout << "Construindo gramatica..." << endl;
        Gramatica gramatica = construirGramatica();//chama a construcao da gramatica, a base de tudo
        
        cout << "\nLendo tokens de: " << nomeArquivo << endl;
        vector<vector<string>> linhasDeTokens = lerTokens(nomeArquivo);//lendo todos os tokens
        cout << "Total de linhas: " << linhasDeTokens.size() << endl;
        
        int sucessos = 0;
        int falhas = 0;
        vector<pair<NoArvore*, int>> todasArvores; // Armazena todas as arvores validas
        vector<Derivacao*> todasDerivacoes;
        
        for (size_t i = 0; i < linhasDeTokens.size(); ++i) {
            int numeroLinha = i + 1;
            const vector<string>& tokens = linhasDeTokens[i];
            //mostra linha sendo processada por pura organizacao
            cout << "\n========================================" << endl;
            cout << "LINHA " << numeroLinha << endl;
            cout << "========================================" << endl;
            
            cout << "Tokens: ";
            for (const auto& token : tokens) {
                cout << token << " ";
            }
            cout << endl;
            
            cout << "\nAnalisando..." << endl;
            Derivacao* derivacao = parsear(tokens, gramatica);
            
            if (!derivacao->sucesso) {//levanta erro de derivacao e pula
                cerr << "ERRO: " << derivacao->mensagemErro << endl;
                falhas++;
                delete derivacao;
                continue;//<-- pula, n faz arvore
            }
            
            cout << "SUCESSO!" << endl;//passa o sucesso
            sucessos++;
            todasDerivacoes.push_back(derivacao);//faz a arvore
            
            cout << "\nPrimeiros passos da derivacao:" << endl;
            for (size_t j = 0; j < derivacao->passos.size() && j < 5; ++j) {
                cout << "  " << derivacao->passos[j] << endl;
            }
            if (derivacao->passos.size() > 5) {
                cout << "  ... (total de " << derivacao->passos.size() << " passos)" << endl;
            }
            
            NoArvore* arvore = gerarArvore(derivacao);//gera a arvore so se der certo
            
            if (arvore) {
                cout << "\nArvore Sintatica:" << endl;
                imprimirArvore(arvore);//mostra no console
                gerarHTML(arvore, numeroLinha);//faz o html dela pra ficar mais facil de ler
                
                // Guarda a arvore para salvar no markdown depois
                todasArvores.push_back(make_pair(arvore, numeroLinha));
            }
        }
        
        // Salva TODAS as arvores validas no arquivo markdown
        for (const auto& arvoreInfo : todasArvores) {
            NoArvore* arvore = arvoreInfo.first;
            int numeroLinha = arvoreInfo.second;
            salvarArvoreMarkdown(arvore, numeroLinha);
        }
        
        // Limpa memoria de todas as derivacoes (que contem as arvores)
        for (auto deriv : todasDerivacoes) {
            delete deriv;
        }
        
        cout << "\n========================================" << endl;
        cout << "RESUMO" << endl;
        cout << "========================================" << endl;
        cout << "Total de linhas: " << linhasDeTokens.size() << endl;
        cout << "Sucessos: " << sucessos << endl;
        cout << "Falhas: " << falhas << endl;
        
        cout << "\n=== ANALISE CONCLUIDA ===" << endl;
        cout << "\nArquivos gerados:" << endl;
        cout << "- analise_gramatica.md (gramatica, FIRST, FOLLOW, tabela LL(1) e todas as arvores)" << endl;
        cout << "- tabela_ll1.html (tabela LL(1) - visualizacao extra)" << endl;
        cout << "- arvore_linha_N.html (todas as arvores - visualizacao extra)" << endl;
        cout << "\nAbra os arquivos HTML no navegador para visualizacao grafica!" << endl;
        
    } catch (const exception& e) {
        cerr << "ERRO: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}