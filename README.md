# Analisador Sintático LL(1) - Fase 2

## Informações Institucionais

**Instituição:** Pontificia Universidade do Paraná (PUC-PR)  
**Ano:** 2025  
**Disciplina:** Linguagem Formal de Compiladores
**Professor:** Franl de Alcantara

**Desenvolvedor:** Guilherme Knapik - kingnapik

---

## Descrição do Projeto

Este projeto implementa um **analisador sintático descendente recursivo LL(1)** para uma linguagem de programação simplificada baseada em **notação polonesa reversa (RPN)**. O analisador utiliza uma gramática LL(1), calcula conjuntos FIRST e FOLLOW, constrói uma tabela de análise, e gera árvores sintáticas para validar a estrutura de expressões.

### Características Principais

- Parser LL(1) com pilha
- Suporte a expressões aritméticas em RPN
- Operadores: `+`, `-`, `*`, `/` (divisão inteira), `|` (divisão real), `%`, `^`
- Operadores de comparação: `>`, `<`, `>=`, `<=`, `==`, `!=`
- Estruturas de controle e repetição: `IF` e `FOR`
- Comandos especiais: `RES` (resultados anteriores) e variáveis de memória
- Geração de árvores sintáticas em HTML
- Análise linha por linha com tratamento de erros
- Código modularizado em múltiplos arquivos

---

## Estrutura do Projeto

```
├── main.cpp           # Programa principal
├── gramatica.h/cpp    # Definição da gramática e cálculo de FIRST/FOLLOW
├── parser.h/cpp       # Implementação do parser LL(1)
├── arvore.h/cpp       # Estruturas de árvore e geração HTML
├── leitor.h/cpp       # Leitura de arquivos de tokens
├── compile.bat        # Compilação automática
├── teste1.txt         # Arquivo de teste 1
├── teste2.txt         # Arquivo de teste 2
├── teste3.txt         # Arquivo de teste 3
└── README.md          # Este arquivo
```

---

## Estrutura da Linguagem

### Sintaxe Básica

A linguagem utiliza **notação polonesa reversa (RPN)**, onde operadores aparecem após seus operandos. Todas as expressões devem estar entre parênteses:

```
( operando1 operando2 operador )
```

### Operadores Suportados

#### Operadores Aritméticos
- `+` : Adição
- `-` : Subtração
- `*` : Multiplicação
- `/` : Divisão inteira (trunca para inteiro)
- `|` : Divisão real (mantém casas decimais)
- `%` : Resto da divisão inteira (apenas para inteiros)
- `^` : Potenciação (expoente deve ser inteiro)

#### Operadores de Comparação
- `>` : Maior que
- `<` : Menor que
- `>=` : Maior ou igual
- `<=` : Menor ou igual
- `==` : Igual
- `!=` : Diferente

#### Comandos Especiais
- `(N RES)` : Retorna o resultado da expressão N linhas anteriores
- `(V MEM)` : Armazena o valor V na variável MEM
- `(MEM)` : Retorna o valor armazenado em MEM (retorna 0 se não inicializada)

### Estruturas de Controle

#### IF - Tomada de Decisão

**Sintaxe:**
```
( condição valor_verdadeiro valor_falso IF )
```

**Descrição:**
- `condição`: Expressão que retorna 0 (falso) ou diferente de 0 (verdadeiro)
- `valor_verdadeiro`: Valor retornado se condição for verdadeira
- `valor_falso`: Valor retornado se condição for falsa

#### FOR - Laço de Repetição

**Sintaxe:**
```
( condição corpo FOR )
```

**Descrição:**
- `condição`: Condição que define o numero de execuções.
- `corpo`: Expressão a ser executada

### Expressões Aninhadas

Expressões podem ser aninhadas sem limite:

```
( ( 10 5 + ) ( 3 2 * ) - )              // (10+5) - (3*2) = 9
( ( ( A B + ) ( C D * ) / ) X )         // Armazena (A+B)/(C*D) em X
```

---

## Compilação e Execução

### Requisitos

- Compilador C++ com suporte a C++17 (g++ recomendado)
- Navegador web (para visualizar árvores e tabelas)

### Método 1: Usando batch file (Recomendado)

```bash
# Compilar
.\compile.bat

# Executar com arquivo de teste
.\AnalisadorSintatico teste1.txt
```

### Método 2: Compilação Manual

```bash
# Compilar todos os arquivos objeto
g++ -std=c++17 -Wall -O2 -c gramatica.cpp
g++ -std=c++17 -Wall -O2 -c parser.cpp
g++ -std=c++17 -Wall -O2 -c arvore.cpp
g++ -std=c++17 -Wall -O2 -c leitor.cpp
g++ -std=c++17 -Wall -O2 -c main.cpp

# Linkar
g++ -std=c++17 -Wall -O2 -o AnalisadorSintatico main.o gramatica.o parser.o arvore.o leitor.o

# Executar
./AnalisadorSintatico teste1.txt
```

### Arquivos de Entrada

O programa espera um arquivo de texto contendo tokens separados por espaços, com uma expressão por linha. Exemplo de `tokens.txt`:

```
( 5 3 + )
( 10 X )
( X 5 > )
( ( X 5 > ) ( X 2 * ) ( X ) IF )
```

### Arquivos de Saída

O programa gera os seguintes arquivos:

1. **`gramatica_analise.txt`** - Contém:
   - Regras de produção da gramática
   - Conjunto NULLABLE
   - Conjuntos FIRST
   - Conjuntos FOLLOW

2. **`tabela_ll1.html`** - Tabela de análise LL(1) em formato HTML (abra no navegador)

3. **`arvore_linha_N.html`** - Árvore sintática para cada linha N (abra no navegador)

### Visualização dos Resultados

Para visualizar as árvores sintáticas e a tabela LL(1):

```bash
# Abrir tabela LL(1)
open tabela_ll1.html        # macOS
xdg-open tabela_ll1.html    # Linux
start tabela_ll1.html       # Windows

# Abrir árvore da linha 1
open arvore_linha_1.html    # macOS
xdg-open arvore_linha_1.html  # Linux
start arvore_linha_1.html   # Windows
```

Ou simplesmente arraste os arquivos HTML para o navegador.

---

## Depuração

### Mensagens de Erro

O analisador fornece mensagens de erro detalhadas indicando:
- O tipo de erro sintático
- A posição (índice do token) onde o erro ocorreu
- O token esperado vs. o token encontrado

**Exemplo de erro:**
```
LINHA 3
========================================
Tokens: ( 5 3 +
Analisando...
ERRO: Erro sintatico: esperado ')' mas encontrado '$' na posicao 3
```

### Modo de Depuração

O programa exibe no console:
- Tokens lidos de cada linha
- Status de parsing (SUCESSO/ERRO)
- Primeiros passos da derivação
- Árvore sintática em formato texto
- Resumo final (sucessos e falhas)

### Testando com Erros Intencionais

Use o arquivo `teste3.txt` que contém exemplos de erros sintáticos:
- Linha 13: Parênteses faltando
- Linha 14: Parêntese de fechamento faltando
- Linha 15: Expressão incompleta

---

## Módulos do Código

### gramatica.h/cpp
Responsável por:
- Definir as regras de produção da gramática
- Calcular conjuntos NULLABLE
- Calcular conjuntos FIRST
- Calcular conjuntos FOLLOW
- Construir a tabela de análise LL(1)
- Salvar análise em arquivos TXT e HTML

**Funções principais:**
```cpp
Gramatica construirGramatica();
void salvarAnaliseGramatica(const Gramatica& g);
```

### parser.h/cpp
Responsável por:
- Implementar o algoritmo de parsing LL(1)
- Gerenciar pilha de análise
- Mapear tokens para terminais da gramática
- Construir árvore sintática durante o parsing
- Detectar e reportar erros sintáticos

**Funções principais:**
```cpp
Derivacao* parsear(const vector<string>& tokens, const Gramatica& gramatica);
string mapearTokenParaTerminal(const string& token);
```

### arvore.h/cpp
Responsável por:
- Estruturas de dados para árvore sintática
- Geração de visualização HTML com SVG
- Impressão da árvore no console
- Gerenciamento de memória dos nós

**Funções principais:**
```cpp
NoArvore* gerarArvore(Derivacao* derivacao);
void imprimirArvore(NoArvore* no, int nivel);
void gerarHTML(NoArvore* raiz, int numeroLinha);
```

### leitor.h/cpp
Responsável por:
- Leitura de arquivos de tokens
- Processamento linha por linha
- Validação de abertura de arquivos

**Funções principais:**
```cpp
vector<vector<string>> lerTokensPorLinha(string arquivo);
```

### main.cpp
Responsável por:
- Coordenação de todos os módulos
- Processamento de argumentos de linha de comando
- Loop principal de análise
- Exibição de resultados e estatísticas

---

## Gramática LL(1)

### Regras de Produção

```
P -> ( CORPO )

CORPO -> E CORPO'

CORPO' -> E CORPO'
       | epsilon

E -> E_ARITIMETICO
  | E_ESPECIAL
  | OP

E_ARITIMETICO -> num
              | P

E_ESPECIAL -> var
           | res
           | if
           | for

OP -> + | - | * | % | / | | | ^ | > | < | >= | <= | == | !=
```

### Terminais e Não-Terminais

**Não-Terminais:** P, CORPO, CORPO', E, E_ARITIMETICO, E_ESPECIAL, OP

**Terminais:** `(`, `)`, num, var, res, if, for, +, -, *, %, /, |, ^, >, <, >=, <=, ==, !=

---

## Exemplos de Uso

### Exemplo:

**Entrada (`teste1.txt`):**
```
( 10 5 + )
( 20 4 - )
( 7 3 * )
( 15 3 / )
```

**Saída:**
```
LINHA 1
Tokens: ( 10 5 + )
SUCESSO!
Arquivo HTML gerado: arvore_linha_1.html
```

## Testes

### Arquivos de Teste Incluídos

1. **`teste1.txt`** (15 linhas)
   - Todas as operações aritméticas
   - Comparações básicas
   - IF e RES
   - Variáveis

2. **`teste2.txt`** (16 linhas)
   - Operações com números reais
   - Todos os operadores de comparação
   - IF aninhado
   - Múltiplas variáveis

3. **`teste3.txt`** (19 linhas)
   - Mistura de inteiros e reais
   - Casos de erro sintático (linhas 13-15)
   - Expressões complexas

### Executando os Testes

```bash
# Método 1: Usando Makefile
make test1
make test2
make test3

# Método 2: Diretamente
./AnalisadorSintatico teste1.txt
./AnalisadorSintatico teste2.txt
./AnalisadorSintatico teste3.txt
```

---

## Tratamento de Erros

O analisador detecta e reporta os seguintes tipos de erros:

1. **Erro de token não reconhecido**
   - Quando não há produção na tabela LL(1)
   
2. **Erro de símbolo esperado**
   - Quando o terminal lido não corresponde ao esperado

3. **Erro de tokens extras**
   - Quando há tokens após o parsing completo

4. **Erro de entrada vazia**
   - Quando a linha não contém tokens

5. **Erro de arquivo não encontrado**
   - Quando o arquivo de entrada não existe

**Exemplo de saída de erro:**
```
LINHA 5
========================================
Tokens: ( 10 5 + + )
Analisando...
ERRO: Erro sintatico: esperado ')' mas encontrado '+' na posicao 4
```

---

## Estrutura de Compilação

### Dependências entre Módulos

```
main.cpp
  ├── gramatica.h
  ├── parser.h
  │   ├── gramatica.h
  │   └── arvore.h
  ├── arvore.h
  └── leitor.h
```

### Ordem de Compilação

1. gramatica.cpp (sem dependências externas)
2. arvore.cpp (sem dependências externas)
3. leitor.cpp (sem dependências externas)
4. parser.cpp (depende de gramatica.h e arvore.h)
5. main.cpp (depende de todos)

---
