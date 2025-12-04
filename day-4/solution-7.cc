#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

std::vector<std::vector<char>> LeerMatriz(const std::string& nombre_archivo) {
  std::ifstream archivo(nombre_archivo);
  if (!archivo.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo '" << nombre_archivo << "'" << std::endl;
    std::exit(1);
  }
  std::vector<std::vector<char>> matriz{};
  std::string linea{};
  while (std::getline(archivo, linea)) {
    std::vector<char> fila;
    if (linea.empty()) continue;
    for (char c : linea) {
      fila.push_back(c);
    }
    matriz.push_back(fila);
  }

  /**
  for (int i = 0; i < matriz.size(); i++) {
    for (int j = 0; j < matriz.size(); j++) {
      std::cout << matriz[i][j];
    }
    std::cout << std::endl;
  } */

  return matriz;
}


int RollosPapelValidos(std::vector<std::vector<char>> matriz) {
  const int MAX_FILAS = matriz.size();
  const int MAX_COLS = matriz[0].size();
  int rollos_papel_validos = 0;
  // Para recorrer vecinos
  int df[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  const int NUM_VECINOS = 8;
  for (int i = 0; i < MAX_FILAS; i++) {
    for (int j = 0; j < MAX_COLS; j++) {
      if (matriz[i][j] != '@') continue;
      int contador_rollos_adyecentes = 0;
      // Recorrer los vecinos validos de la posición actual (i, j)
      for (int k = 0; k < NUM_VECINOS; k++) {
        int nueva_fila = i + df[k];
        int nueva_col = j + dc[k];
        bool pos_valida = (nueva_fila >= 0 && nueva_fila < MAX_FILAS) && 
                          (nueva_col >= 0 && nueva_col < MAX_COLS);
        if (pos_valida) {
          if (matriz[nueva_fila][nueva_col] == '@') {
            contador_rollos_adyecentes++;
          }
        }
      }
      if (contador_rollos_adyecentes < 4) {
        rollos_papel_validos++;
      }
    }
  }
  return rollos_papel_validos;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Uso: " << argv[0] << " <nombre_archivo>" << std::endl;
    return 1;
  }  
  std::vector<std::vector<char>> matriz = LeerMatriz(argv[1]);
  int rollos_papel = RollosPapelValidos(matriz);
  std::cout << "El número de rollos de papel válidos es: " << rollos_papel << std::endl;
  return 0;
}