# Autoria — TP1 de Técnicas de Programação 1

Sistema de Gestão de Projetos com Quadro Kanban.

## Equipe

| Nome | Matrícula |
|---|---|
| Samuel Mendes Monteiro | 252030399 |
| Rafael Cruxen Da Silva Lima | 252024319 |
| Paulo Augusto Ferreira Rocha | 252003275 |
| Daniel Arruda Silva | 252022898 |

## Artefatos construídos por membro

| Artefato | Arquivos | Responsável |
|---|---|---|
| Classes de domínio (11) | `include/Domains/`, `src/Domains/` | Samuel Mendes Monteiro |
| Classes de entidade (4) | `include/Entities/`, `src/Entities/` | Rafael Cruxen Da Silva Lima |
| Interfaces entre módulos (5) | `include/Interfaces/` | Rafael Cruxen Da Silva Lima |
| Modelo de arquitetura | `arquitetura/Modelo-de-Arquitetura-TP1.pdf` | Rafael Cruxen Da Silva Lima |
| Camada de apresentação (controladoras e sessão) | `include/Presentation/`, `src/Presentation/` | Daniel Arruda Silva |
| Camada de serviço (controladoras de serviço) | `include/Services/`, `src/Services/` | Paulo Augusto Ferreira Rocha |
| Contêineres | `include/Containers/` | Paulo Augusto Ferreira Rocha |
| Integração e menu principal | `src/main.cpp` | Samuel Mendes Monteiro |
| Documentação Doxygen | `Doxyfile`, `doc/html/` | Samuel Mendes Monteiro |
| Projeto Code::Blocks | projeto Code::Blocks | Samuel Mendes Monteiro |
| Vídeo do teste fumaça | vídeo | Rafael Cruxen Da Silva Lima |
| Organização e empacotamento do ZIP | arquivo ZIP | Daniel Arruda Silva |

## Atividades de cada membro

**Samuel Mendes Monteiro** — classes de domínio, documentação e integração geral.
- Projetou, codificou e documentou as 11 classes de domínio (Email, Estado, Identificador,
  Limite, Nome, Papel, Prioridade, Senha, Tamanho, Texto e Timestamp), com validação de
  formato e lançamento de exceção.
- Configurou o Doxygen e gerou as páginas HTML.
- Integrou os módulos de apresentação e de serviço no Code::Blocks, resolvendo dependências
  e garantindo o funcionamento correto da arquitetura.

**Rafael Cruxen Da Silva Lima** — classes de entidade, arquitetura e vídeo.
- Projetou, codificou e documentou as classes de entidade (Pessoa, Projeto, Quadro e Cartão
  de atividade) e declarou as interfaces entre módulos como classes abstratas.
- Construiu o modelo de arquitetura em UML (módulos, interfaces e relacionamentos) e redigiu
  o documento PDF com a descrição dos módulos.
- Conduziu e gravou o vídeo do teste fumaça, com um cenário de sucesso para cada
  funcionalidade.

**Paulo Augusto Ferreira Rocha** — camada de serviço.
- Projetou e codificou a camada de serviço, que implementa os 26 serviços funcionais: CRUD
  das entidades, movimentação de cartões e cálculo de tempo de ciclo, lead time e WIP.
- Desenvolveu as classes controladoras de serviço e as classes contêiner que armazenam os
  dados em memória.

**Daniel Arruda Silva** — camada de apresentação e empacotamento.
- Projetou e codificou a camada de apresentação: a interface com o usuário via `cin`/`cout`
  e a validação dos dados de entrada.
- Organizou os artefatos finais e preparou o arquivo ZIP no padrão exigido, testando a
  descompactação e a ausência de vírus.
