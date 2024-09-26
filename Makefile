# ---------------------------------
# EP01
# Leonardo Carpwiski  - GRR20232331
# ---------------------------------

# Nome do Projeto
PROJECT = pi

# Arquivos .c
C_SOURCE = $(wildcard *.c)

# Arquivos .h
H_SOURCE = $(wildcard *.h)

# Objetos
OBJ = $(C_SOURCE:.c=.o)

# Compilador
CC = gcc

# Flags do Compilador
CC_FLAGS= -c -Wall

# ----------------------------

# all: Compila o projeto
all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CC) -o $@ $^ -lm $(LIBS)

%.o: %.c
	$(CC) $(CC_FLAGS) -o $@ $^ $(LIBS)

# clean: Remove os arquivos objeto e temporários
clean:
	rm -rf *.o $(PROJECT) *~