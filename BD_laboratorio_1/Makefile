CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

# Objetivos
TARGETS = Parte1.exe Parte2.exe Parte3.exe

# Regla por defecto
all: $(TARGETS)

# Compilación Parte 1
Parte1.exe: Parte1_ArchivosBinarios.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "✓ Compilado: $@"

# Compilación Parte 2
Parte2.exe: Parte2_GestionMemoria.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "✓ Compilado: $@"

# Compilación Parte 3
Parte3.exe: Parte3_TestPage.cpp Page.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✓ Compilado: $@"

# Limpiar archivos generados
clean:
	rm -f $(TARGETS) *.exe *.o data.db page_dump.bin

# Ejecutar todos
run-all: all
	@echo "=========================================="
	@echo "Ejecutando PARTE 1: Archivos Binarios"
	@echo "=========================================="
	./Parte1.exe
	@echo ""
	@echo "=========================================="
	@echo "Ejecutando PARTE 2: Gestión de Memoria"
	@echo "=========================================="
	./Parte2.exe
	@echo ""
	@echo "=========================================="
	@echo "Ejecutando PARTE 3: Clase Page"
	@echo "=========================================="
	./Parte3.exe

.PHONY: all clean run-all
