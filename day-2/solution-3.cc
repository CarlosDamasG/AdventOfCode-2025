#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

long long SumaIDInvalidos(const std::string& input) {
  std::stringstream rangos_digitos(input);
  std::string rango{};
  long long sumatorio = 0;
  while (std::getline(rangos_digitos, rango, ',')) {
    int posicion_guion = rango.find('-');
    //std::cout << "-llegue0-\n";
    std::string str_num1 = rango.substr(0, posicion_guion);
    std::string str_num2 = rango.substr(posicion_guion + 1);
    //std::cout << "str1: " << str_num1 << " - " << str_num2 << ":str2\n";
    //std::cout << "-llegue1-\n";
    long long num1 = stoll(str_num1);
    long long num2 = stoll(str_num2);
    for (long long i = num1; i <= num2; i++) {
      std::string str_i = std::to_string(i);
      int tamaño_num = str_i.length();
      if (tamaño_num % 2 == 0) {
        //std::cout << "-llegue2-\n";
        std::string primera_mitad_num = str_i.substr(0, tamaño_num / 2);
        std::string segunda_mitad_num = str_i.substr((tamaño_num / 2));
        //std::cout << "num1: " << primera_mitad_num << " - " << segunda_mitad_num << ":num2\n";
        if (primera_mitad_num == segunda_mitad_num) {
          //std::cout << "añadimos el numero: " << i << std::endl;
          sumatorio += i;
        }
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