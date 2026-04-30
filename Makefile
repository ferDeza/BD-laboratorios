# Makefile para Laboratorio 1 - Base de Datos II
# Compilador y opciones
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
LDFLAGS = 

# Archivos fuente
SOURCES = main.cpp Page.cpp part1_binary_files.cpp part2_memory_management.cpp part3_page_class.cpp
HEADERS = Page.h

# Archivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Nombre del ejecutable
EXECUTABLE = laboratorio1

# Objetivos
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✓ Compilación completada: $(EXECUTABLE)"

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS) $(EXECUTABLE) data.db
	@echo "✓ Archivos limpios"

rebuild: clean all

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean rebuild run
