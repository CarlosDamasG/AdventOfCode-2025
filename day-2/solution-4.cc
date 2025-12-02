#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

bool TodosIguales(const std::vector<std::string>& vector) {
  if (vector.empty()) return true;
  const std::string& primero = vector[0];
  for (const auto& numero : vector) {
    if (numero != primero) {
      return false;
    }
  }
  return true;
}


std::vector<int> CalcularDivisoresUtiles(long long numero) {
  std::vector<int> divisores{};
  int num_digitos = std::to_string(numero).length();
  for (int i = 1; i <= (num_digitos / 2); i++) {
    if ((num_digitos % i) == 0) {
      divisores.push_back(i);
    }
  }
  return divisores;
}

long long SumaIDInvalidos(const std::string& input) {
  std::stringstream rangos_digitos(input);
  std::string rango{};
  long long sumatorio = 0;
  std::unordered_set<long long> ids_invalidos;
  // Cada rango de números
  while (std::getline(rangos_digitos, rango, ',')) {
    int posicion_guion = rango.find('-');
    std::string str_num1 = rango.substr(0, posicion_guion);
    std::string str_num2 = rango.substr(posicion_guion + 1);
    long long num1 = stoll(str_num1);
    long long num2 = stoll(str_num2);
    // Cada número del rango
    for (long long i = num1; i <= num2; i++) {
      bool invalido = false;
      std::vector<int> divisores = CalcularDivisoresUtiles(i);
      std::string num = std::to_string(i);
      int num_digitos = num.length();
      // Dividir dígitos por sus divisores
      for (int j = 0; j < divisores.size(); j++) {
        int num_string = num_digitos / divisores[j];
        std::vector<std::string> numeros(num_string);
        int posicion = 0;
        // Rellenar vector con los números de tamaño j
        for (int k = 0; k < num_string; k++) {
          numeros[k] = num.substr(posicion, divisores[j]);
          posicion += divisores[j];
        }
        if (TodosIguales(numeros)) {
          invalido = true;
          if (ids_invalidos.find(i) == ids_invalidos.end()) {
            sumatorio += i;
            ids_invalidos.insert(i);
          }
        }
        if (invalido) break;
      }
    }
  }
  return sumatorio;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Uso: " << argv[0] << " <nombre_archivo>" << std::endl;
    return 1;
  }
  std::ifstream archivo(argv[1]);
  if (!archivo.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo '" << argv[1] << "'" << std::endl;
    return -1;
  }
  std::string input;
  std::getline(archivo, input);
  long long password = SumaIDInvalidos(input);
  if (password >= 0) {
    std::cout << "La contraseña es " << password << std::endl;
  } else {
    std::cout << "No se pudo abrir el archivo" << std::endl;
  }  
  return 0;
}