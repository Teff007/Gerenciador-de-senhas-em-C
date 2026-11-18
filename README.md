# Sistema de Senhas de Atendimento

Projeto em linguagem C desenvolvido para a **Tia Karla Soluções**. É um gerenciador de senhas de atendimento para pacientes: o atendente informa os dados do paciente, o sistema classifica a categoria automaticamente, emite uma senha sequencial e controla a fila de chamadas.

## Objetivo

Organizar o atendimento de pacientes por ordem de prioridade (urgente, preferencial e normal), emitindo senhas sequenciais e permitindo chamar, acompanhar e finalizar atendimentos por meio de um menu no terminal.

## Funcionalidades

- Registro de senha com validação dos dados (gênero, idade, gestante, lactante, necessidade especial, obesidade)
- Classificação automática em três categorias
- Senha sequencial por categoria: `N001`, `P001`, `U001`...
- Consultar a próxima senha a ser chamada
- Chamar paciente (registra a chamada)
- Identificar a senha de um paciente (situação e posição na fila)
- Ver a senha em atendimento
- Finalizar atendimento e atualizar a fila
- Painel de chamada com resumo
- Listagem da fila

### Regras de classificação

| Categoria | Código | Quem entra |
|---|---|---|
| Urgente | `U001` | Idade **superior a 80 anos** |
| Preferencial | `P001` | Gestante, lactante, necessidade especial, obesidade, mulheres com 60+ anos e homens com 65+ anos |
| Normal | `N001` | Pacientes sem nenhuma condição de prioridade |

Ordem de chamada: **Urgente → Preferencial → Normal**. Dentro da mesma categoria, vale a ordem de chegada.

## Estrutura do projeto

Cada módulo tem um `.c` (implementação) e um `.h` (declarações). A `main()` apenas chama o painel.

```
├── main.c                      # ponto de entrada (só chama iniciarPainel)
├── tipos.h                     # structs, enums e constantes compartilhados
├── utils.c / utils.h           # leitura de dados com validação
├── registro_senha.c / .h       # MÓDULO 1 - registro de senha
├── classificacao_senha.c / .h  # MÓDULO 2 - classificação e geração do código
├── registro_atendimento.c / .h # MÓDULO 3 - fila, chamada e finalização
├── painel_chamada.c / .h       # MÓDULO 4 - menu e painel
├── test_sistema.c              # testes automáticos
├── Makefile
└── README.md
```

### Bibliotecas usadas

| Biblioteca | Para quê |
|---|---|
| `<stdio.h>` | `printf`, `fgets`, `snprintf` |
| `<stdlib.h>` | `strtol`, `exit` |
| `<string.h>` | `strlen`, `strcmp` |
| `<ctype.h>` | `toupper` |
| `<stdbool.h>` | tipo `bool` |
| `<assert.h>` | testes automáticos |

### Estruturas de dados

- `struct Paciente`: dados informados pelo atendente
- `struct Senha`: código, categoria e status
- `enum Categoria`: `NORMAL`, `PREFERENCIAL`, `URGENTE`
- `enum StatusSenha`: `AGUARDANDO`, `EM_ATENDIMENTO`, `FINALIZADA`
- A fila é um **vetor (array)** de `Senha` com até 100 posições

## Compilação e execução

Requer `gcc`.

```bash
gcc -Wall -Wextra -std=c99 -o senhas main.c painel_chamada.c registro_senha.c registro_atendimento.c classificacao_senha.c utils.c
./senhas
```

No Windows (PowerShell ou CMD), execute com `senhas.exe`.

### Testes

```bash
gcc -Wall -Wextra -std=c99 -o test_sistema test_sistema.c classificacao_senha.c registro_atendimento.c
./test_sistema
```

Os testes verificam a classificação (incluindo os limites 59/60, 64/65 e 80/81 anos), a geração dos códigos e o fluxo da fila (ordem de chamada, finalização e atualização).

## Funções implementadas

### utils
| Função | O que faz |
|---|---|
| `void lerLinha(char*, int)` | lê uma linha com `fgets` e remove o Enter |
| `int lerInteiro(msg, min, max)` | repete até o usuário digitar um número válido na faixa |
| `bool lerSimNao(msg)` | repete até receber S ou N |
| `char lerGenero(void)` | repete até receber F ou M |

### registro_senha (módulo 1)
| Função | O que faz |
|---|---|
| `Paciente coletarDadosPaciente(void)` | pergunta os dados ao atendente |
| `Senha emitirSenha(Paciente)` | classifica e gera o código da senha |
| `void registrarSenha(void)` | fluxo completo: coleta, emite e coloca na fila |

### classificacao_senha (módulo 2)
| Função | O que faz |
|---|---|
| `bool temCondicaoPrioritaria(Paciente)` | verifica as condições de preferencial |
| `Categoria classificarPaciente(Paciente)` | decide urgente, preferencial ou normal |
| `char prefixoCategoria(Categoria)` | devolve `N`, `P` ou `U` |
| `const char* nomeCategoria(Categoria)` | nome para exibir |
| `void gerarCodigoSenha(Categoria, char*)` | gera `N001`, `P001`, `U001`... |
| `void reiniciarContadores(void)` | zera os contadores (testes) |

### registro_atendimento (módulo 3)
| Função | O que faz |
|---|---|
| `bool adicionarNaFila(Senha)` | coloca a senha no fim da fila |
| `int consultarProximaSenha(void)` | índice da próxima senha a chamar |
| `bool chamarPaciente(void)` | marca a próxima senha como em atendimento |
| `int buscarSenha(const char*)` | identifica uma senha pelo código |
| `int indiceEmAtendimento(void)` | identifica a senha em atendimento |
| `bool finalizarAtendimento(void)` | conclui o atendimento atual |
| `void atualizarFila(void)` | remove da fila as senhas finalizadas |
| `int totalAguardando / totalNaFila / totalAtendidos` | contadores |
| `int posicaoNaFila(int)` | posição na ordem de chamada |
| `const Senha* obterSenha(int)` | acesso somente leitura a uma senha |

### painel_chamada (módulo 4)
| Função | O que faz |
|---|---|
| `void exibirMenu(void)` | mostra as opções |
| `void exibirPainel(void)` | senha atual, próxima e resumo |
| `void listarFila(void)` | lista a fila |
| `void identificarSenhaPaciente(void)` | pede o código e mostra a situação |
| `void executarOpcao(int)` | trata a opção escolhida (`switch case`) |
| `void iniciarPainel(void)` | laço do menu (`do...while`) |

## Exemplo de utilização

```
Escolha uma opcao: 1

--- REGISTRO DE SENHA ---
Genero do paciente (F/M): F
Idade do paciente (0 a 120): 25
Paciente esta gestante? (S/N): S
Paciente e lactante? (S/N): N
Possui necessidade especial? (S/N): N
Possui condicao de obesidade? (S/N): N

>>> Senha emitida: P001 (PREFERENCIAL)
>>> Pacientes aguardando: 1
```

Após registrar `P001`, `N001`, `U001` e outra `P002`, a opção 8 (painel) mostra:

```
############# PAINEL DE CHAMADA #############
 EM ATENDIMENTO : U001 (URGENTE)
 PROXIMA SENHA  : P001 (PREFERENCIAL)
 Aguardando     : 3
 Atendidos      : 0 (0.0% do total do dia)
#############################################
```

## Boas práticas adotadas

- Nenhuma lógica de negócio na `main()`
- Um `.c` e um `.h` por módulo, com *include guards*
- Funções com responsabilidade única e comentadas
- Validação de todas as entradas (sem travar com letras ou valores fora da faixa)
- Constantes nomeadas (`MAX_FILA`, `TAM_CODIGO`) em vez de números soltos
- Compilação sem avisos com `-Wall -Wextra`

## Autor

Projeto desenvolvido por _[seu nome]_, trainee na Tia Karla Soluções.
