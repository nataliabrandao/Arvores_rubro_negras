CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = tests.exe

# Lista de arquivos a serem compilados
SRCS = tests.cpp \
       libTreeRB/tree_rb.cpp

# Objetos a serem gerados a partir dos arquivos fonte
OBJS = $(SRCS:.cpp=.o)

# Regra padrão para compilar o programa
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regra de compilação para cada arquivo fonte
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra de limpeza
clean:
	rm -f $(TARGET) $(OBJS)