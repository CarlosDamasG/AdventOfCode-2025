#include <iostream>
#include <fstream>
#include <string>

int CalcularPassword(const std::string& nombre_archivo) {
  std::ifstream archivo(nombre_archivo);
  if (!archivo.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo '" << nombre_archivo << "'" << std::endl;
    return -1;
  }
  std::string linea;
  int contador = 0;
  int posicion = 50;
  while (std::getline(archivo, linea)) {
    if (linea.empty()) continue;    
    char direccion = linea[0];
    int movimiento = std::stoi(linea.substr(1));  
    if (direccion == 'R') {
      posicion += movimiento;
    } else if (direccion == 'L') {
      posicion -= movimiento;
    }
    posicion %= 100;
    if (posicion < 0) {
      posicion += 100;
    }
    if (posicion == 0) {
      contador++;
    }
  }
  archivo.close();
  return contador;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Uso: " << argv[0] << " <nombre_archivo>" << std::endl;
    return 1;
  }  
  int password = CalcularPassword(argv[1]);
  if (password >= 0) {
    std::cout << "La contraseña es " << password << std::endl;
  } else {
    std::cout << "No se pudo abrir el archivo" << std::endl;
  }  
  return 0;
}