#include <iostream>
#include <fstream>
#include <string>

long long VoltajeTotal(const std::string& nombre_archivo) {
  std::ifstream archivo(nombre_archivo);
  if (!archivo.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo '" << nombre_archivo << "'" << std::endl;
    return -1;
  }
  std::string banco_bateria;
  long long voltaje_total = 0;
  while (std::getline(archivo, banco_bateria)) {
    if (banco_bateria.empty()) continue;
    char primer_digito = banco_bateria[0], segundo_digito = '0';
    for (int i = 1; i < (banco_bateria.size() - 1); i++) {
      if (primer_digito < banco_bateria[i]) {
        primer_digito = banco_bateria[i];
        segundo_digito = banco_bateria[i + 1];
      } else if (segundo_digito < banco_bateria[i]) {
        segundo_digito = banco_bateria[i];
      }
    }
    if (banco_bateria[banco_bateria.size() - 1] > segundo_digito) {
      segundo_digito = banco_bateria[banco_bateria.size() - 1];
    }
    std::string str_voltaje_banco = {primer_digito, segundo_digito};
    voltaje_total += std::stoi(str_voltaje_banco);
    std::cout << "Sumo el: " << str_voltaje_banco << std::endl;
  }
  archivo.close();
  return voltaje_total;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Uso: " << argv[0] << " <nombre_archivo>" << std::endl;
    return 1;
  }  
  long long voltaje = VoltajeTotal(argv[1]);
  if (voltaje >= 0) {
    std::cout << "El voltaje total es: " << voltaje << std::endl;
  } else {
    std::cout << "No se pudo abrir el archivo" << std::endl;
  }  
  return 0;
}