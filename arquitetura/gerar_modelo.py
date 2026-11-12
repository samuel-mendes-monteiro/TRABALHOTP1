"""Gera modelo-arquitetura.html (diagramas UML em SVG).

Uso:  python3 arquitetura/gerar_modelo.py
Depois converta para PDF com o Chrome (ver README da pasta).
"""
import os

OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "modelo-arquitetura.html")

FONT = "font-family='Helvetica, Arial, sans-serif'"
STROKE = "#222"


def component(x, y, w, h, lines, fill="#f1f1f1"):
    """Componente UML: retângulo com o ícone de componente no canto."""
    s = f"<rect x='{x}' y='{y}' width='{w}' height='{h}' rx='3' fill='{fill}' stroke='{STROKE}' stroke-width='1.2'/>"
    ix, iy = x + w - 20, y + 6
    s += (f"<rect x='{ix}' y='{iy}' width='13' height='10' fill='white' stroke='{STROKE}' stroke-width='0.9'/>"
          f"<rect x='{ix-3}' y='{iy+2}' width='6' height='2.4' fill='white' stroke='{STROKE}' stroke-width='0.8'/>"
          f"<rect x='{ix-3}' y='{iy+5.6}' width='6' height='2.4' fill='white' stroke='{STROKE}' stroke-width='0.8'/>")
    cy = y + h / 2 - (len(lines) - 1) * 7 + 4
    for i, t in enumerate(lines):
        s += f"<text x='{x + w/2}' y='{cy + i*14}' text-anchor='middle' font-size='12' {FONT}>{t}</text>"
    return s


def package(x, y, w, h, title, label_top=True):
    """Camada: moldura com o nome em destaque (no topo ou na base)."""
    ty = y + 15 if label_top else y + h - 7
    return (f"<rect x='{x}' y='{y}' width='{w}' height='{h}' rx='4' fill='none' stroke='{STROKE}' "
            f"stroke-width='1.1' stroke-dasharray='7,3'/>"
            f"<text x='{x+8}' y='{ty}' font-size='11' font-weight='bold' {FONT}>{title}</text>")


# ---------------------------------------------------------------- Figura 1
def figura1():
    W, H = 780, 395
    s = [f"<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 {W} {H}' width='100%'>"]
    s.append(package(10, 8, 760, 112, "«camada» Apresentação"))
    s.append(package(10, 248, 760, 112, "«camada» Serviço", label_top=False))

    pres = [("Autenticação", "IAuthenticationService"), ("Pessoas", "IPersonService"),
            ("Projetos", "IProjectService"), ("Quadros", "IBoardService"),
            ("Cartões de Atividades", "ITaskService")]
    bw, gap, x0 = 136, 13, 25
    centers = []
    for i, (nome, _) in enumerate(pres):
        x = x0 + i * (bw + gap)
        centers.append(x + bw / 2)
        linhas = ["Apresentação", nome] if len(nome) < 16 else ["Apresentação", "Cartões de", "Atividades"]
        s.append(component(x, 44, bw, 62, linhas))

    # módulos de serviço
    serv = [(x0, 2 * bw + gap, ["Pessoas"]),
            (x0 + 2 * (bw + gap), bw, ["Projetos"]),
            (x0 + 3 * (bw + gap), bw, ["Quadros"]),
            (x0 + 4 * (bw + gap), bw, ["Cartões de Atividades"])]
    for x, w, l in serv:
        s.append(component(x, 262, w, 56, l))

    # interfaces: bola (fornecida) e soquete (requerida)
    yb = 186
    for cx, (_, iface) in zip(centers, pres):
        s.append(f"<line x1='{cx}' y1='262' x2='{cx}' y2='{yb+8}' stroke='{STROKE}' stroke-width='1.2'/>")
        s.append(f"<circle cx='{cx}' cy='{yb}' r='8' fill='white' stroke='{STROKE}' stroke-width='1.2'/>")
        s.append(f"<line x1='{cx}' y1='106' x2='{cx}' y2='{yb-13}' stroke='{STROKE}' stroke-width='1.2'/>")
        s.append(f"<path d='M {cx-13} {yb} A 13 13 0 0 1 {cx+13} {yb}' fill='none' stroke='{STROKE}' stroke-width='1.2'/>")
        s.append(f"<text x='{cx+17}' y='{yb+22}' font-size='10.5' {FONT}>{iface}</text>")

    # legenda
    ly = 380
    s.append(f"<circle cx='22' cy='{ly-4}' r='5' fill='white' stroke='{STROKE}'/>"
             f"<text x='32' y='{ly}' font-size='10' {FONT}>interface fornecida (realizada pelo módulo de Serviço)</text>"
             f"<path d='M 330 {ly-2} A 8 8 0 0 1 346 {ly-2}' fill='none' stroke='{STROKE}'/>"
             f"<text x='352' y='{ly}' font-size='10' {FONT}>interface requerida (módulo de Apresentação)</text>")
    s.append("</svg>")
    return "".join(s)


# ---------------------------------------------------------------- Figura 2
def figura2():
    W, H = 780, 380
    # as faixas das setas começam em y=102 e a moldura em y=70: o desenho começa em y=60
    s = [f"<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 60 {W} {H}' width='100%'>"]
    s.append("<defs><marker id='ah' viewBox='0 0 10 10' refX='9' refY='5' markerWidth='7' markerHeight='7' orient='auto'>"
             f"<path d='M0,0 L10,5 L0,10' fill='none' stroke='{STROKE}' stroke-width='1.4'/></marker></defs>")
    s.append(package(10, 70, 760, 346, "«camada» Serviço", label_top=False))

    top, h, w = 335, 56, 160
    comps = {"P": (30, ["Pessoas"]), "J": (220, ["Projetos"]),
             "Q": (410, ["Quadros"]), "C": (600, ["Cartões de", "Atividades"])}
    cx = {k: x + w / 2 for k, (x, _) in comps.items()}
    iface = {"P": "IPersonService", "J": "IProjectService", "Q": "IBoardService", "C": "ITaskService"}
    yc = 290  # centro das bolas
    for k, (x, l) in comps.items():
        s.append(component(x, top, w, h, l))
        s.append(f"<line x1='{cx[k]}' y1='{top}' x2='{cx[k]}' y2='{yc+8}' stroke='{STROKE}' stroke-width='1.2'/>")
        s.append(f"<circle cx='{cx[k]}' cy='{yc}' r='8' fill='white' stroke='{STROKE}' stroke-width='1.2'/>")
        s.append(f"<text x='{cx[k]+14}' y='{yc+18}' font-size='10.5' {FONT}>{iface[k]}</text>")

    # (origem, deslocamento da origem, destino, lado de entrada, faixa y, rótulo, posição do rótulo)
    deps = [
        ("J", -62, "P", -5, 262, "valida o gestor", None),
        ("Q", -62, "J", +5, 262, "valida o projeto", None),
        ("C", -62, "Q", +5, 262, "valida o quadro e o WIP", 566),
        ("P", -62, "J", -5, 222, "vínculos do gestor", 180),
        ("Q", -40, "C", -5, 222, "WIP e cascata", 557),
        ("J", -40, "Q", -5, 182, "cascata dos quadros", 340),
        ("C", -40, "P", +5, 142, "valida o desenvolvedor", 420),
        ("P", -40, "C", +5, 102, "vínculos do desenvolvedor", 420),
    ]
    for src, off, dst, side, ly, label, lx in deps:
        sx = cx[src] + off
        tx = cx[dst] + side
        ty = yc - 7
        s.append(f"<path d='M {sx} {top} L {sx} {ly} L {tx} {ly} L {tx} {ty}' fill='none' stroke='{STROKE}' "
                 f"stroke-width='1.1' stroke-dasharray='5,3' marker-end='url(#ah)'/>")
        mx = lx if lx is not None else (sx + tx) / 2
        s.append(f"<text x='{mx}' y='{ly-5}' text-anchor='middle' font-size='10' {FONT}>"
                 f"«usa» {label}</text>")
    s.append(f"<text x='20' y='432' font-size='10' {FONT}>Seta tracejada: dependência «usa» do módulo de origem sobre a interface "
             "fornecida pelo módulo de destino.</text>")
    s.append("</svg>")
    return "".join(s)


CSS = """
@page { size: A4; margin: 18mm 17mm 18mm 17mm; }
body { font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; font-size: 10.5pt; line-height: 1.45; color: #111; }
h1 { text-align: center; font-size: 20pt; margin: 0 0 4px; }
.sub { text-align: center; color: #444; font-size: 10pt; margin: 0; }
.team { text-align: center; color: #555; font-size: 9pt; margin: 4px 0 18px; }
h2 { font-size: 13pt; margin: 20px 0 6px; }
p { text-align: justify; margin: 6px 0; }
code { font-family: Menlo, Consolas, monospace; font-size: 8.8pt; }
figure { margin: 10px 0 4px; page-break-inside: avoid; }
figcaption { text-align: center; font-style: italic; color: #555; font-size: 9pt; margin-top: 4px; }
table { border-collapse: collapse; width: 100%; font-size: 9pt; margin: 8px 0; page-break-inside: auto; }
tr { page-break-inside: avoid; }
th { background: #2b2b2b; color: white; text-align: left; padding: 5px 6px; }
table.ids td:first-child { white-space: nowrap; }
td { border: 1px solid #999; padding: 4px 6px; vertical-align: top; }
tr:nth-child(even) td { background: #f4f4f4; }
.brk { page-break-before: always; }
ul { margin: 4px 0 4px 18px; padding: 0; }
"""


def tabela(cab, linhas, cls=""):
    h = f"<table class='{cls}'><tr>" + "".join(f"<th>{c}</th>" for c in cab) + "</tr>"
    for l in linhas:
        h += "<tr>" + "".join(f"<td>{c}</td>" for c in l) + "</tr>"
    return h + "</table>"


MODULOS = [
    ("Apresentação Autenticação", "Apresentação",
     "Ler e-mail e senha, validá-los com as classes de domínio, acionar a autenticação e abrir/encerrar a sessão do usuário.",
     "<code>AuthController</code>, <code>Session</code>", "Requer <code>IAuthenticationService</code>"),
    ("Apresentação Pessoas", "Apresentação",
     "Interface com o usuário para criar, ler, atualizar, excluir e listar pessoas; atualizar e excluir apenas a própria conta.",
     "<code>PersonController</code>", "Requer <code>IPersonService</code>"),
    ("Apresentação Projetos", "Apresentação",
     "Interface para os serviços de projeto; restringe criar, atualizar e excluir ao papel GESTOR (e ao gestor que criou o projeto).",
     "<code>ProjectController</code>", "Requer <code>IProjectService</code>"),
    ("Apresentação Quadros", "Apresentação",
     "Interface para os serviços de quadro; restringe criar, atualizar e excluir ao papel GESTOR.",
     "<code>BoardController</code>", "Requer <code>IBoardService</code>"),
    ("Apresentação Cartões de Atividades", "Apresentação",
     "Interface para os serviços de cartão, para a movimentação e para as métricas (tempo de ciclo, lead time e WIP).",
     "<code>TaskController</code>", "Requer <code>ITaskService</code>"),
    ("Pessoas", "Serviço",
     "Cadastro de pessoas e autenticação; impede excluir ou trocar o papel de quem é gestor de projeto ou responsável por cartão.",
     "<code>PersonService</code>, <code>AuthenticationService</code>, <code>PersonContainer</code>",
     "Provê <code>IPersonService</code> e <code>IAuthenticationService</code>; requer <code>IProjectService</code> e <code>ITaskService</code>"),
    ("Projetos", "Serviço",
     "Cadastro de projetos; exige gestor válido e término não anterior ao início; a exclusão remove os quadros do projeto.",
     "<code>ProjectService</code>, <code>ProjectContainer</code>",
     "Provê <code>IProjectService</code>; requer <code>IPersonService</code> e <code>IBoardService</code>"),
    ("Quadros", "Serviço",
     "Cadastro de quadros; exige projeto existente; impede limite de WIP abaixo do WIP atual; a exclusão remove os cartões do quadro.",
     "<code>BoardService</code>, <code>BoardContainer</code>",
     "Provê <code>IBoardService</code>; requer <code>IProjectService</code> e <code>ITaskService</code>"),
    ("Cartões de Atividades", "Serviço",
     "Cadastro e movimentação de cartões (A FAZER → FAZENDO → FEITO) com limite de WIP; cálculo de tempo de ciclo, lead time, médias e WIP.",
     "<code>TaskService</code>, <code>TaskContainer</code>",
     "Provê <code>ITaskService</code>; requer <code>IBoardService</code> e <code>IPersonService</code>"),
]

SERVICOS = [
    ("1 a 5", "Criar, ler, atualizar, excluir e listar pessoa", "<code>IPersonService</code>",
     "<code>createPerson</code>, <code>readPerson</code>, <code>updatePerson</code>, <code>deletePerson</code>, <code>listPersons</code>"),
    ("—", "Autenticar usuário", "<code>IAuthenticationService</code>", "<code>authenticate</code>"),
    ("6 a 10", "Criar, ler, atualizar, excluir e listar projeto", "<code>IProjectService</code>",
     "<code>createProject</code>, <code>readProject</code>, <code>updateProject</code>, <code>deleteProject</code>, <code>listProjects</code>"),
    ("11 a 15", "Criar, ler, atualizar, excluir e listar quadro", "<code>IBoardService</code>",
     "<code>createBoard</code>, <code>readBoard</code>, <code>updateBoard</code>, <code>deleteBoard</code>, <code>listBoards</code>"),
    ("16 a 20", "Criar, ler, atualizar, excluir e listar cartão", "<code>ITaskService</code>",
     "<code>createTask</code>, <code>readTask</code>, <code>updateTask</code>, <code>deleteTask</code>, <code>listTasks</code>"),
    ("21", "Mover cartão", "<code>ITaskService</code>", "<code>moveTask</code>"),
    ("22 e 23", "Ler tempo de ciclo e tempo de ciclo médio", "<code>ITaskService</code>",
     "<code>readCycleTime</code>, <code>readAverageCycleTime</code>"),
    ("24 e 25", "Ler lead time e lead time médio", "<code>ITaskService</code>",
     "<code>readLeadTime</code>, <code>readAverageLeadTime</code>"),
    ("26", "Ler WIP", "<code>ITaskService</code>", "<code>readWip</code>"),
]


def html():
    return f"""<!doctype html>
<html lang="pt-BR"><head><meta charset="utf-8"><title>Modelo de Arquitetura de Software</title>
<style>{CSS}</style></head><body>

<h1>Modelo de Arquitetura de Software</h1>
<p class="sub">Trabalho Prático — Técnicas de Programação 1 (CIC0197)</p>
<p class="sub">Sistema de Gestão de Projetos com Quadro Kanban — Universidade de Brasília (UnB)</p>
<p class="team">Equipe: Samuel Mendes · Rafael Cruxen · Daniel Arruda · Paulo Augusto</p>

<h2>1. Introdução</h2>
<p>O sistema adota o estilo de arquitetura em camadas (<i>layers</i>) com duas camadas. A camada de
<b>Apresentação</b> é responsável pela interface com o usuário (<code>cin</code>/<code>cout</code>) e pela
validação dos dados de entrada. A camada de <b>Serviço</b> é responsável pela lógica de negócio e pelo
armazenamento dos dados em memória. Cada camada é decomposta em módulos: cinco na Apresentação e quatro no
Serviço, num total de nove módulos.</p>
<p>Os módulos interagem <b>exclusivamente por meio de serviços especificados em interfaces</b>, declaradas no
código como classes abstratas compostas por métodos virtuais puros (pasta <code>include/Interfaces</code>).
Isso vale tanto entre as camadas (Apresentação → Serviço) quanto entre os próprios módulos da camada de Serviço.
Cada módulo de Serviço guarda seus objetos num contêiner próprio, que nenhum outro módulo acessa.</p>

<h2>2. Módulos e interfaces entre as camadas</h2>
<p>A figura 1 apresenta os módulos em notação de diagrama de componentes da UML. Cada interface é fornecida
(bola) por um módulo da camada de Serviço e requerida (soquete) por um módulo da camada de Apresentação.
O módulo Pessoas fornece duas interfaces: <code>IAuthenticationService</code> e <code>IPersonService</code>.</p>
<figure>{figura1()}<figcaption>Figura 1 — Modelo de arquitetura em camadas: módulos e interfaces.</figcaption></figure>
<p>A função <code>main</code> não é um módulo: ela cria os contêineres, os serviços, a sessão e as
controladoras, liga cada módulo às interfaces de que ele depende (injeção de dependência) e executa o menu
principal, que encaminha a opção escolhida à controladora correspondente.</p>

<h2 class="brk">3. Descrição dos módulos</h2>
{tabela(["Módulo", "Responsabilidade", "Classes", "Interfaces"], [(m[0] + "<br><small>(" + m[1] + ")</small>",) + m[2:] for m in MODULOS])}


<h2 class="brk">4. Interações entre os módulos da camada de Serviço</h2>
<p>Algumas regras de negócio envolvem mais de uma entidade. Nesses casos, um módulo de Serviço requer a
interface fornecida por outro módulo, como mostra a figura 2. Nenhum módulo acessa o contêiner de outro.</p>
<figure>{figura2()}<figcaption>Figura 2 — Dependências entre os módulos da camada de Serviço, por meio de interfaces.</figcaption></figure>
<ul>
<li><b>Projetos → <code>IPersonService</code></b>: valida se o gestor do projeto existe e tem o papel GESTOR.</li>
<li><b>Pessoas → <code>IProjectService</code></b>: impede excluir ou trocar o papel de quem é gestor de algum projeto.</li>
<li><b>Cartões de Atividades → <code>IPersonService</code></b>: valida se o responsável existe e tem o papel DESENVOLVEDOR.</li>
<li><b>Pessoas → <code>ITaskService</code></b>: impede excluir ou trocar o papel de quem é responsável por algum cartão.</li>
<li><b>Quadros → <code>IProjectService</code></b>: valida a existência do projeto ao qual o quadro pertence.</li>
<li><b>Cartões de Atividades → <code>IBoardService</code></b>: valida a existência do quadro e lê o seu limite de WIP.</li>
<li><b>Quadros → <code>ITaskService</code></b> (WIP e cascata): obtém o WIP atual (o limite não pode ficar abaixo dele) e exclui os cartões de um quadro excluído.</li>
<li><b>Projetos → <code>IBoardService</code></b>: exclui os quadros de um projeto excluído (e, por consequência, os seus cartões).</li>
</ul>
<p>Essas dependências garantem as multiplicidades do diagrama de classes e que a exclusão de uma entidade
não resulte em inconsistência, conforme exigido pelo enunciado.</p>

<h2 class="brk">5. Serviços especificados nas interfaces</h2>
<p>A tabela relaciona os serviços dos requisitos funcionais aos métodos virtuais puros das interfaces.</p>
{tabela(["ID", "Serviço", "Interface", "Métodos"], SERVICOS, "ids")}

<h2>6. Classes compartilhadas, controladoras e contêineres</h2>
<p><b>Domínios.</b> As 11 classes de domínio (<code>Email</code>, <code>Identifier</code>, <code>Limit</code>,
<code>Name</code>, <code>Password</code>, <code>Priority</code>, <code>Role</code>, <code>Size</code>,
<code>State</code>, <code>Text</code>, <code>Timestamp</code>) validam o formato dos dados e são usadas por todos
os módulos. A camada de Apresentação usa os domínios para validar a entrada antes de acionar os serviços.</p>
<p><b>Entidades.</b> As 4 classes de entidade (<code>Person</code>, <code>Project</code>, <code>Board</code>,
<code>Task</code>) têm atributos que são instâncias de domínios e são os dados trocados pelas interfaces.</p>
<p><b>Controladoras.</b> Na camada de Apresentação, as classes <code>*Controller</code> são as controladoras
de interação com o usuário. Na camada de Serviço, as classes <code>*Service</code> são as controladoras da
lógica de negócio e realizam as interfaces.</p>
<p><b>Contêineres.</b> As classes <code>PersonContainer</code>, <code>ProjectContainer</code>,
<code>BoardContainer</code> e <code>TaskContainer</code> mantêm os objetos em memória. Cada uma pertence a
um único módulo da camada de Serviço e só é acessada pelo serviço desse módulo.</p>

</body></html>
"""


if __name__ == "__main__":
    with open(OUT, "w", encoding="utf-8") as f:
        f.write(html())
    print("gerado:", OUT)
