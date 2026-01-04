# Gerenciador de Tarefas em C (CLI) 🚀

Projeto de conclusão de estrutura de dados e programação em C. Um sistema CRUD completo rodando no terminal com persistência de dados.

## 🛠️ Funcionalidades Técnicas

- **Persistência Binária:** Salva e carrega tarefas automaticamente usando serialização binária (`fread`/`fwrite`).
- **Gerenciamento de Memória:** Uso de alocação dinâmica (`malloc`) com estratégia de *Deep Free* para evitar Memory Leaks.
- **Tratamento de Buffer:** Input seguro usando `fgets` e limpeza de buffer, imune a falhas de `scanf`.
- **Modularização:** Código separado em Interface (`.h`), Implementação (`.c`) e Cliente (`main.c`).
- **Automação:** Compilação automatizada via `Makefile`.

## 📋 Como Rodar

### Pré-requisitos
- Compilador GCC (MinGW no Windows ou nativo no Linux)
- Make (Opcional)

### Compilando e Rodando

1. Clone o repositório:
   ```bash
   git clone [https://github.com/SEU_USUARIO/task-manager-c.git](https://github.com/SEU_USUARIO/task-manager-c.git)
2. Compile usando o Makefile
    ```bash
    make run
3. Ou compile manualmente:
    ```bash
    gcc gerenciadorDeTarefas.c gerenciador.c -o gerenciador
    ./gerenciador