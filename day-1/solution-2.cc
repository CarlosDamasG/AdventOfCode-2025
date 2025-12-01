#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int CalcularPassword(const std::string& nombre_archivo) {
  std::ifstream archivo(nombre_archivo);
  if (!archivo.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo" << std::endl;
    return -1;
  }
  std::string linea;
  int total_ceros = 0;
  int posicion = 50;
  while (std::getline(archivo, linea)) {
    if (linea.empty()) continue;
    char dir = linea[0];
    int movimiento = std::stoi(linea.substr(1));
    int dist_to_cero = 0;

    if (dir == 'R') {
      if (posicion == 0) {
        dist_to_cero = 100;
      } else {
        dist_to_cero = 100 - posicion;
      }
    } else if (dir == 'L') {
      if (posicion == 0) {
        dist_to_cero = 100;
      } else {
        dist_to_cero = posicion;
      }
    }

    if (movimiento >= dist_to_cero) {
      total_ceros += 1 + ((movimiento - dist_to_cero) / 100);
    }

    if (dir == 'R') {
        posicion = (posicion + (movimiento % 100)) % 100;
    } else if (dir == 'L') {
      int desplazamiento = movimiento % 100;
      posicion = (posicion - desplazamiento);
      if (posicion < 0) posicion += 100;
    }
  }  
  archivo.close();
  return total_ceros;
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