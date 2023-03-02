// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Practica 1: Representación de números grandes en notación posicional
// Autor: Pedro Hernandez ALonso
// Correo: alu0101423944@ull.edu.es
// Fecha: 11/02/2023

#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <stack>

#include "board.h"
#include "bigint_new.h"

template <size_t Base> class Board;

template <size_t Base> 
class rpn {
 public:
  // constructor
 rpn(Board<Base> board) : board_{board}, stack_() {}

  // operaciones
  BigInt<Base> evaluate(std::string&);

 private: 
  Board<Base> board_;
  std::stack<BigInt<Base>> stack_;
  void operate_(const char operador);
};

template<size_t Base> 
BigInt<Base> rpn<Base>::evaluate(std::string& line) {  //  line{E1 N1 N2 - +}
  while (!line.empty()) {
    char c = line.at(0);  // E
    line.erase(line.begin());  // line{1 N1 N2 - +}
    if (c != ' ') {
      if (c == 'N' || c == 'E') {
        char n = line.at(0);  // 1
        line.erase(line.begin());  // line{ N1 N2 - +}
        std::string number;
        number.push_back(c);  // E
        number.push_back(n);  // 1
        stack_.push(BigInt<Base>(board_.Find(number)));  
      } else if (!line.empty() && (c == '-' || c == '+') && line.at(0) != ' ') {
        BigInt<Base> next = stack_.top();
        stack_.pop();
        line.erase(line.begin());
        if (c == '-') {
          --next;
          stack_.push(next);  
        } else {
          ++next;
          stack_.push(next);            
        }
      } else {
        operate_(c);
      }
    }
  }
  return stack_.top();
}

template<size_t Base> 
void rpn<Base>::operate_(const char c) {

  BigInt<Base> result;
  // Sacar de una pila el primer operando
  BigInt<Base> a = stack_.top();
  stack_.pop();
  if (stack_.empty()) {
    switch (c) {
      case '-':
        result = -a;
        break;
      default:
        std::cerr << "'" << c << "' No es un operador valido." << std::endl;
        exit(EXIT_FAILURE);      
    }
    stack_.push(result); 
  } else {
    // Sacar de la pila el segundo operando
    BigInt<Base> b = stack_.top();
    stack_.pop();

    // Falta contemplar los casos unarios, ejemplo: -b, b++, ++b, ...
    switch (c) {
      case '+':
        result = b + a;
        break;
      case '-':
        result = b - a;
        break;
      case '*':
        result = b * a;
        break;
      case '/':
        result = b / a;
        break;
      case '%':
        result = b % a;
        break;
      case '^':
        result = pow(b,a);
        break;
      default:
        std::cerr << "'" << c << "' No es un operador valido." << std::endl;
        exit(EXIT_FAILURE);
    }
    stack_.push(result);
    
  }
}

#endif