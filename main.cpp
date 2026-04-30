/**
 * LABORATORIO 1 - BASE DE DATOS II
 * 
 * Programa Principal que integra todas las partes:
 * - Parte 1: Manejo de Archivos Binarios
 * - Parte 2: Gestión de Memoria en C++
 * - Parte 3: Implementación de la clase Page
 */

#include <iostream>
#include <string>

// Declaraciones de funciones principales de cada parte
int main_part1();  // Manejo de archivos binarios
int main_part2();  // Gestión de memoria
int main_part3();  // Clase Page

void displayMenu() {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║   LABORATORIO 1 - BASE DE DATOS II     ║" << std::endl;
    std::cout << "║  Archivos Binarios y Gestión Memoria   ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    
    std::cout << "\nSeleccione un ejercicio:" << std::endl;
    std::cout << "1. Parte 1: Manejo de Archivos Binarios" << std::endl;
    std::cout << "2. Parte 2: Gestión de Memoria en C++" << std::endl;
    std::cout << "3. Parte 3: Concepto de Página (Clase Page)" << std::endl;
    std::cout << "4. Ejecutar todas las partes" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "\nOpción: ";
}

int main() {
    int option = -1;
    
    while (true) {
        displayMenu();
        std::cin >> option;
        
        // Limpiar el búfer de entrada
        std::cin.ignore(10000, '\n');
        
        switch (option) {
            case 1:
                main_part1();
                break;
                
            case 2:
                main_part2();
                break;
                
            case 3:
                main_part3();
                break;
                
            case 4:
                std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
                std::cout << "║     EJECUTANDO TODAS LAS PARTES         ║" << std::endl;
                std::cout << "╚════════════════════════════════════════╝" << std::endl;
                main_part1();
                main_part2();
                main_part3();
                break;
                
            case 0:
                std::cout << "\n¡Hasta luego!" << std::endl;
                return 0;
                
            default:
                std::cout << "\nOpción no válida. Por favor, intente de nuevo." << std::endl;
                break;
        }
        
        std::cout << "\nPresione Enter para continuar...";
        std::cin.get();
    }
    
    return 0;
}
