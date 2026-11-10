# Sistema de Gestão Kanban

Trabalho prático 1 (TP1) de **Técnicas de Programação 1**.
Sistema em C++ de console para gestão de projetos pelo método Kanban: pessoas, projetos,
quadros e cartões de atividade, com limite WIP e métricas de tempo de ciclo e lead time.

## Autores

| Nome | Matrícula |
|---|---|
| Samuel Mendes Monteiro | 252030399 |
| Rafael Cruxen Da Silva Lima | 252024319 |
| Paulo Augusto Ferreira Rocha | 252003275 |
| Daniel Arruda Silva | _preencher_ |

## Estrutura do projeto

```
include/                 Declarações (.h), documentadas com Doxygen
  Domains/               11 classes de domínio
  Entities/              4 classes de entidade
  Containers/            4 contêineres em memória
  Interfaces/            5 interfaces de serviço (classes abstratas)
  Presentation/          controladoras e Session
  Services/              implementações dos serviços
src/                     Implementações (.cpp) e main.cpp
Doxyfile                 Configuração do Doxygen
teste_fumaca_entrada.txt Entrada pronta para o teste fumaça
doc/html/                Documentação gerada pelo Doxygen (abrir index.html)
```

## Arquitetura

Estilo em camadas, com duas camadas.

- **Apresentação:** interface com o usuário por `cin`/`cout`, validação dos dados de entrada
  e verificação de permissões pelo papel da sessão. Depende apenas das interfaces de serviço.
- **Serviço:** lógica de negócio e armazenamento dos dados em memória. Implementa as
  interfaces de serviço.

A camada de serviço é dividida em quatro módulos: Pessoas, Projetos, Quadros e Cartões de
Atividades. O modelo de arquitetura (diagramas UML e descrição dos módulos) está no PDF
entregue junto com o trabalho.

## Como compilar

Requisitos: compilador C++ com suporte a C++11 (testado com `g++`).

Na pasta do projeto:

```
g++ -std=c++11 -Wall -Wextra -o kanban src/main.cpp src/Domains/*.cpp src/Entities/*.cpp src/Presentation/*.cpp src/Services/*.cpp
```

No Code::Blocks: crie um projeto de console C++, adicione todos os `.cpp` de `src/` e
ative C++11 em *Settings > Compiler*. Não é preciso configurar pastas de include, porque
os `#include` são relativos.

## Como executar

```
./kanban
```

No Windows: `kanban.exe`.

O sistema começa vazio, com os dados apenas em memória. Ao fechar o programa, tudo é perdido.

### Primeiros passos

1. No menu inicial, escolha **1** para criar uma conta e **2** para fazer login.
2. Depois do login, o menu mostra os serviços numerados:

| Opções | Serviço |
|---|---|
| 1 a 5 | Pessoas: criar, ler, atualizar, excluir, listar |
| 6 a 10 | Projetos: criar, ler, atualizar, excluir, listar |
| 11 a 15 | Quadros: criar, ler, atualizar, excluir, listar |
| 16 a 20 | Cartões: criar, ler, atualizar, excluir, listar |
| 21 | Mover cartão (A FAZER para FAZENDO, FAZENDO para FEITO) |
| 22 a 26 | Tempo de ciclo, tempo de ciclo médio, lead time, lead time médio e WIP |
| 27 | Logout |
| 0 | Sair |

Ordem sugerida para um primeiro uso: criar um gestor e um desenvolvedor, entrar como gestor,
criar um projeto, um quadro e cartões, e então mover os cartões.

## Formatos dos dados

| Dado | Regra |
|---|---|
| Identificador | 6 caracteres: 3 letras seguidas de 3 dígitos (ex.: `PRJ001`) |
| E-mail | `parte-local@domínio`; letras minúsculas, dígitos, ponto e hífen; ponto ou hífen deve ser seguido por letra ou dígito |
| Nome | Até 15 caracteres; letras e espaços; não começa nem termina com espaço; espaço é seguido por letra |
| Senha | Exatamente 5 caracteres, letras ou dígitos, com ao menos uma letra e um dígito |
| Texto (descrição) | Até 30 caracteres; começa com letra maiúscula e termina com ponto; sem duas pontuações seguidas |
| Data e hora | `DD-MMM-AAAA-HH:MM` (ex.: `25-FEV-2026-14:30`); meses `JAN` a `DEZ`; ano de 2000 a 2099; considera ano bissexto |
| Limite WIP | Inteiro de 1 a 25 |
| Papel | `GESTOR` ou `DESENVOLVEDOR` |
| Prioridade | `ALTA`, `MEDIA` ou `BAIXA` |
| Tamanho | `GRANDE`, `MEDIO` ou `PEQUENO` |
| Estado | `A FAZER`, `FAZENDO` ou `FEITO` |

Não há acentuação nem `ç` nas validações.

## Permissões

- **Pessoas (1 a 5):** qualquer papel. A criação de conta não exige login.
- **Ler e listar** projetos, quadros e cartões: gestor e desenvolvedor.
- **Criar, atualizar e excluir** projetos, quadros e cartões: apenas gestor.
- **Atualizar e excluir um projeto:** apenas o gestor que o criou.
- **Mover cartão e métricas (21 a 26):** gestor e desenvolvedor.

## Regras de negócio implementadas

- Todo cartão novo nasce em A FAZER. Só são permitidas as transições A FAZER para FAZENDO
  e FAZENDO para FEITO.
- O horário informado na movimentação é gravado como data de início (entrada em FAZENDO) ou
  de término (entrada em FEITO), e não pode ser anterior à data anterior do cartão.
- O WIP de um quadro é o número de cartões em FAZENDO. Um cartão só entra em FAZENDO se o
  WIP estiver abaixo do limite, e o limite do quadro não pode ser reduzido abaixo do WIP atual.
- Tempo de ciclo é o tempo de FAZENDO até FEITO; lead time é o tempo de A FAZER até FEITO.
  Ambos, e suas médias por quadro, são calculados apenas para cartões em FEITO e exibidos em
  dias, horas e minutos.
- O gestor de um projeto é quem o criou e não muda na atualização. O término do projeto não
  pode ser anterior ao início.
- Um quadro pertence a um projeto existente. Um cartão pertence a um quadro existente e é
  atribuído a uma pessoa com papel `DESENVOLVEDOR`.
- A chave primária (e-mail ou identificador) não pode ser editada. O projeto de um quadro não
  muda na atualização.
- Excluir um projeto exclui seus quadros e cartões. Excluir um quadro exclui seus cartões.
- Uma pessoa que é gestora de projetos ou responsável por cartões não pode ser excluída nem
  trocar de papel.

## Teste fumaça

O arquivo `teste_fumaca_entrada.txt` reproduz uma sessão completa, com pelo menos um caso de
sucesso para cada um dos 26 serviços. Para rodar:

```
./kanban < teste_fumaca_entrada.txt
```

O programa deve começar sem dados. Para ver só os resultados:

```
./kanban < teste_fumaca_entrada.txt | grep -E "SUCESSO|ERRO|NEGADO|Tempo|Lead|WIP atual"
```

Resultados esperados incluem: bloqueio do terceiro cartão em FAZENDO com limite 2
("Limite WIP do quadro atingido."), tempo de ciclo `1d 2h 30m` e lead time `2d 3h 30m`,
bloqueio da troca de papel de gestor com projeto, e `ACESSO NEGADO` quando outro gestor tenta
alterar ou excluir o projeto.

## Documentação

A documentação das classes, escrita da perspectiva de quem as usa, é gerada com o Doxygen:

```
doxygen Doxyfile
```

As páginas HTML ficam em `doc/html`. Abra `doc/html/index.html` no navegador.
