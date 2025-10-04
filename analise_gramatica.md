# Analise da Gramatica

## Regras de Producao (EBNF)

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


## Conjunto NULLABLE

```
NULLABLE = { CORPO' }
```

## Conjuntos FIRST

```
FIRST(P) = { ( }
FIRST(CORPO) = { != % ( * + - / < <= == > >= ^ for if num res var | }
FIRST(CORPO') = { != % ( * + - / < <= == > >= ^ for if num res var vazio | }
FIRST(E) = { != % ( * + - / < <= == > >= ^ for if num res var | }
FIRST(E_ARITIMETICO) = { ( num }
FIRST(E_ESPECIAL) = { for if res var }
FIRST(OP) = { != % * + - / < <= == > >= ^ | }
```

## Conjuntos FOLLOW

```
FOLLOW(P) = { != $ % ( ) * + - / < <= == > >= ^ for if num res var | }
FOLLOW(CORPO) = { ) }
FOLLOW(CORPO') = { ) }
FOLLOW(E) = { != % ( ) * + - / < <= == > >= ^ for if num res var | }
FOLLOW(E_ARITIMETICO) = { != % ( ) * + - / < <= == > >= ^ for if num res var | }
FOLLOW(E_ESPECIAL) = { != % ( ) * + - / < <= == > >= ^ for if num res var | }
FOLLOW(OP) = { != % ( ) * + - / < <= == > >= ^ for if num res var | }
```

## Tabela de Analise LL(1)

| Nao-Terminal | != | % | ( | ) | * | + | - | / | < | <= | == | > | >= | ^ | for | if | num | res | var | | | $ |
|--------------|------|------|------|------|------|------|------|------|------|------|------|------|------|------|------|------|------|------|------|------|------|
| P |  |  | P -> ( CORPO ) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| CORPO | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' |  | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' | CORPO -> E CORPO' |  |
| CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> epsilon | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' | CORPO' -> E CORPO' |  |
| E | E -> OP | E -> OP | E -> E_ARITIMETICO |  | E -> OP | E -> OP | E -> OP | E -> OP | E -> OP | E -> OP | E -> OP | E -> OP | E -> OP | E -> OP | E -> E_ESPECIAL | E -> E_ESPECIAL | E -> E_ARITIMETICO | E -> E_ESPECIAL | E -> E_ESPECIAL | E -> OP |  |
| E_ARITIMETICO |  |  | E_ARITIMETICO -> P |  |  |  |  |  |  |  |  |  |  |  |  |  | E_ARITIMETICO -> num |  |  |  |  |
| E_ESPECIAL |  |  |  |  |  |  |  |  |  |  |  |  |  |  | E_ESPECIAL -> for | E_ESPECIAL -> if |  | E_ESPECIAL -> res | E_ESPECIAL -> var |  |  |
| OP | OP -> != | OP -> % |  |  | OP -> * | OP -> + | OP -> - | OP -> / | OP -> < | OP -> <= | OP -> == | OP -> > | OP -> >= | OP -> ^ |  |  |  |  |  | OP -> | |  |

---
*Nota: A arvore sintatica da ultima execucao sera adicionada ao final deste arquivo.*

## Arvore Sintatica - Linha 19

```
P
  ( (terminal)
  CORPO
    E
      E_ESPECIAL
        VAR1 (terminal)
    CORPO'
      E
        E_ESPECIAL
          VAR2 (terminal)
      CORPO'
        E
          OP
            == (terminal)
        CORPO'
  ) (terminal)
```


