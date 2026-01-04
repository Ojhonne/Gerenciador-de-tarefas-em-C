# ==========================================
# Makefile para Gerenciador de Tarefas em C
# ==========================================

# 1. Definições do Compilador
CC = gcc
# CFLAGS: Flags de compilação
# -Wall: Ativa todos os avisos (warnings) essenciais
# -Wextra: Ativa avisos extras (boa prática)
# -g: Adiciona informações de debug (para usar o GDB ou Valgrind)
CFLAGS = -Wall -Wextra -g

# 2. Definições de Arquivos
# Nome do executável final
TARGET = gerenciador

# Arquivos fonte (.c)
SRCS = gerenciadorDeTarefas.c gerenciador.c

# Arquivos objeto (.o) gerados automaticamente a partir dos sources
OBJS = $(SRCS:.c=.o)

# 3. Regras de Compilação

# Regra padrão (o que acontece quando você digita apenas 'make')
all: $(TARGET)

# Linkagem: Junta os .o para criar o executável
$(TARGET): $(OBJS)
	@echo "Ligando os objetos..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Compilação concluída com sucesso! Execute com: ./$(TARGET)"
	@echo "----------------------------------------"

# Compilação: Transforma cada .c em .o
# $< significa o arquivo de origem (.c)
# $@ significa o arquivo de destino (.o)
%.o: %.c gerenciador.h
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# 4. Regras Utilitárias

# 'make run': Compila e roda o programa imediatamente
run: all
	./$(TARGET)

# 'make clean': Limpa os arquivos gerados (.o e executável)
# Use 'del' no lugar de 'rm -f' se estiver no CMD do Windows sem ferramentas Unix
clean:
	@echo "Limpando arquivos temporários..."
ifdef OS
	del /Q $(OBJS) $(TARGET).exe
else
	rm -f $(OBJS) $(TARGET)
endif
	@echo "Limpeza concluída."

.PHONY: all clean run