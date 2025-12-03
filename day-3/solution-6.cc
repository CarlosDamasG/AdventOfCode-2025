#include <iostream>
#include <fstream>
#include <string>

long long VoltajeTotal(const std::string& nombre_archivo) {
  std::ifstream archivo(nombre_archivo);
  if (!archivo.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo '" << nombre_archivo << "'" << std::endl;
    return -1;
  }
  int const VOLTAJE_SIZE = 12;
  std::string banco_bateria;
  long long voltaje_total = 0;
  while (std::getline(archivo, banco_bateria)) {
    if (banco_bateria.empty()) continue;
    std::string str_voltaje_banco{};
    int size_actual_banco_bateria = banco_bateria.size();
    std::string copia_banco_bateria = banco_bateria;
    int size_buscado = VOLTAJE_SIZE;
    int posicion_digito_limite = copia_banco_bateria.size() - size_buscado;
    std::string digitos_donde_buscar = copia_banco_bateria.substr(0, posicion_digito_limite + 1);
    int h = 0;
    while ((posicion_digito_limite > 0) && (!copia_banco_bateria.empty()) && (str_voltaje_banco.size() < VOLTAJE_SIZE)) {
      if (h > 20) {
        std::exit(1);
      }
      char digito_maximo = digitos_donde_buscar[0];
      int posicion_digito_maximo = 0;
      for (int j = 1; j < digitos_donde_buscar.size(); j++) {
        if (digitos_donde_buscar[j] > digito_maximo) {
          digito_maximo = digitos_donde_buscar[j];
          posicion_digito_maximo = j;
        }
      }
      size_buscado--;
      str_voltaje_banco += {digito_maximo};
      copia_banco_bateria = copia_banco_bateria.substr(posicion_digito_maximo + 1);
      posicion_digito_limite = copia_banco_bateria.size() - size_buscado;
      digitos_donde_buscar = copia_banco_bateria.substr(0, posicion_digito_limite + 1);
      h++;
    }
    if (str_voltaje_banco.size() != VOLTAJE_SIZE) {
      str_voltaje_banco += copia_banco_bateria;
    }
    voltaje_total += std::stoll(str_voltaje_banco);
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