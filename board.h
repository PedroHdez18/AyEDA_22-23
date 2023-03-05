// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Practica 1: Representación de números grandes en notación posicional
// Autor: Pedro Hernandez ALonso
// Correo: alu0101423944@ull.edu.es
// Fecha: 11/02/2023

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

#include "bigint_new.h"
#include "rpn.h"

template <size_t Base> class Board;
template <size_t Base> std::ostream& operator<<(std::ostream&, const Board<Base>&);
template <size_t Base> std::ofstream& operator<<(std::ofstream&, const Board<Base>&);

template<size_t Base> 
class Board {
 public:
  Board() {}
  Board(std::ifstream&);
  std::vector<std::pair<std::string, BigInt<Base>>> GetPares(void) const {return pares_;}
  BigInt<Base> Find(const std::string&);

  // Sobrecarga de operadores
  friend std::ostream& operator<< <>(std::ostream&, const Board<Base>&);
  friend std::ofstream& operator<< <>(std::ofstream&, const Board<Base>&);

private:
  std::vector<std::pair<std::string, BigInt<Base>>> pares_;
};

template<size_t Base> 
Board<Base>::Board(std::ifstream& file) {
  std::string line;
  while (getline(file, line)) {
    int pos_inte = line.find("?");
    if (pos_inte != -1) {
      std::string etiqueta = line.substr(0, pos_inte - 1);
      std::string valor = line.substr(pos_inte + 2);
      rpn<Base> calculadora(*this);
      BigInt<Base> resultado = calculadora.evaluate(valor);
      pares_.push_back(std::make_pair(etiqueta, resultado));
    } else {
      int pos_equal = line.find("=");
      std::string etiqueta = line.substr(0, pos_equal-1);
      std::string valor = line.substr(pos_equal + 2);
      pares_.push_back(std::make_pair(etiqueta, BigInt<Base>(valor)));      
    }
  }
  file.close();
}

// Encontrar un numero en base a su etiqueta
template <size_t Base> 
BigInt<Base> Board<Base>::Find(const std::string& etiqueta) {
  for (const auto &pair : this->GetPares()) {
    if (pair.first == etiqueta) {
      return pair.second;
    }
  }
  std::cerr << "No existe un numero con etiqueta: " << etiqueta << std::endl;
  return BigInt<Base>();
}

template <size_t Base> 
std::ostream& operator<<(std::ostream& os, const Board<Base>& board) {
  os << "Base = " << Base << std::endl;
  for (const auto &pair : board.GetPares()) {
    os << pair.first << " = " << pair.second << std::endl;
  }
  return os;
}

template <size_t Base> 
std::ofstream& operator<<(std::ofstream& os, const Board<Base>& board) {
  os << "Base = " << Base << std::endl;
  for (const auto &pair : board.GetPares()) {
    os << pair.first << " = " << pair.second << std::endl;
  }
  return os;
}


#endif