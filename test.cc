// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Practica 1: Representación de números grandes en notación posicional
// Autor: Pedro Hernandez ALonso
// Correo: alu0101423944@ull.edu.es
// Fecha: 11/02/2023

#include "bigint_new.h"
#include "board.h"
#include <iostream>

size_t string_to_size_t(const std::string &str) {
  size_t result = 0;
  for (char c : str) {
    result = result * 10 + (c - '0');
  }
  return result;
}

int main(int argc, char *argv[]) {

  std::string filein(argv[1]);
  std::string fileout(argv[2]);
  std::string line;
  std::ifstream file{filein};
  std::ofstream file2{fileout};
  getline(file, line);  
  int pos_space = line.rfind(" ");
  const std::string last = line.substr(pos_space+1);
  size_t Base = string_to_size_t(last); 

  if (Base == 2) {
    Board<2> board(file);
    file2 << board;
    std::cout << board;
  } else if (Base == 8) {
    Board<8> board(file);
    file2 << board;
    std::cout << board;
  } else if (Base == 10) {
    Board<10> board(file);
    file2 << board;
    std::cout << board;
  } else if (Base == 16) {
    Board<16> board(file);
    file2 << board;
    std::cout << board;
  }
  return 0;
}