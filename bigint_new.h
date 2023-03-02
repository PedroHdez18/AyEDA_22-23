// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Practica 1: Representación de números grandes en notación posicional
// Autor: Pedro Hernandez ALonso
// Correo: alu0101423944@ull.edu.es
// Fecha: 07/02/2023

#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>

template <size_t Base> class BigInt;
template <size_t Base> std::ostream& operator<<(std::ostream&, const BigInt<Base>&);
template <size_t Base> std::istream& operator>>(std::istream&, BigInt<Base>&);
template<size_t Base> bool operator==(const BigInt<Base>&, const BigInt<Base>&);
template<size_t Base> bool operator>(const BigInt<Base>&, const BigInt<Base>&); 
template<size_t Base> bool operator<(const BigInt<Base>&, const BigInt<Base>&);
template<size_t Base> BigInt<Base> operator+(const BigInt<Base>&, const BigInt<Base>&);
template<size_t Base> BigInt<Base> operator/(const BigInt<Base>&, const BigInt<Base>&);
template<size_t Base> BigInt<Base> pow(const BigInt<Base>&, const BigInt<Base>&);

template<size_t Base> 
class BigInt {
 public: 
// Constructores
  BigInt (long n = 0);
  BigInt (std::string&);
  BigInt (const char*);
  BigInt (const BigInt<Base>&);  // Constructor de copia

// Asignacion 
  BigInt<Base>& operator=(const BigInt<Base>& number);

// Insercion y extraccion en flujo
  friend std::ostream& operator<< <>(std::ostream& os, const BigInt<Base>& big);
  friend std::istream& operator>> <>(std::istream&, BigInt<Base>&);

// Accesor
  int sign() const { return sign_? -1 : 1; }  // Signo 1 o -1 -> 0(pos) 1(neg)
  void SetSign (bool sign) {sign_ = sign;}
  char operator[](const int n) const { return numbers_.at(n); }  // Acceso al i-esimo digito
  void update(const int n, const char v) {numbers_.at(n) = v;}
  void addLast(const char n) {numbers_.push_back(n);}
  void removeFirst(void) {numbers_.erase(numbers_.begin());}
  int size() const { return numbers_.size(); } // Tamano vector
  std::vector<char> GetNumbers(void) const { return numbers_; }  // Acceso al i-esimo digito

// Comparacion
  friend bool operator== <>(const BigInt<Base>&, const BigInt<Base>&);
  bool operator!=(const BigInt<Base>&) const;
  friend bool operator> <>(const BigInt<Base>&, const BigInt<Base>&);
  bool operator>=(const BigInt<Base>&) const;
  friend bool operator< <>(const BigInt<Base>&, const BigInt<Base>&);
  bool operator<=(const BigInt<Base>&) const;

// // Incremento/Decremento
  BigInt<Base>& operator++();  // Pre-incremento
  BigInt<Base> operator++(int);  // Post-incremento
  BigInt<Base>& operator--();  // Pre-decremento
  BigInt<Base> operator--(int);  // Post-decremento

// Operadores aritmeticos
 friend BigInt<Base> operator+ <>(const BigInt<Base>&, const BigInt<Base>&);
  BigInt<Base> operator-(const BigInt<Base>&) const;
  BigInt<Base> operator-() const;
  BigInt<Base> operator*(const BigInt<Base>&) const;
  friend BigInt<Base> operator/ <>(const BigInt<Base>&, const BigInt<Base>&);
  BigInt<Base> operator%(const BigInt<Base>&) const;

// // Potencia a^b
 friend BigInt<Base> pow <>(const BigInt<Base>&, const BigInt<Base>&);

 private:
  std::vector<char> numbers_;
  bool sign_;
};

// --------------- FUNCIONES EXTRAS --------------- 
template<size_t Base>  // COMPROBADO
int ToDecimal(const BigInt<Base>& big) { 
  int total{0};
  for (int i{big.size() - 1}, j{0}; i >= 0; i--, j++) {
    if ((big[i] - '0') < 10) {  // numeros menos de 10
      int number{big[i] - '0'};
      total += number * pow(Base, j);
    } else if ((big[i] - 'A' + 10) >= 10)  {  // numeros mayores de 10
      int number{big[i] - 'A' + 10};
      total += number * pow(Base, j);
    }
  }
  return total;
}

template<size_t Base>  // COMPROBADO
BigInt<Base> ToBase(int number) {
  std::string total;
  std::string big;
  if (number < 0) {
    number = number * -1;
    do {
      int rest = number % Base;
      number = number / Base;
      char c;
      if (rest < 10) {
        c = rest + '0';
      } else {
        c = rest + 'A' - 10;
      }
      total.push_back(c);
    } while (number >= 1); 
    for (int i{(int)total.length() - 1}; i >= 0; --i) {
      big.push_back(total.at(i));
    }
    big = '-' + big;
    BigInt<Base> ret(big);
    return ret;
  } else {
    do {
      int rest = number % Base;
      number = number / Base;
      char c;
      if (rest < 10) {
        c = rest + '0';
      } else {
        c = rest + 'A' - 10;
      }
      total.push_back(c);
    } while (number >= 1);
    for (int i{(int)total.length() - 1}; i >= 0; --i) {
      big.push_back(total.at(i));
    }
    BigInt<Base> ret(big);
    return ret;
  }
}

int ToNumber(const char digit) {
  if (digit >= '0' && digit <= '9') {  // numeros menos de 10
    return (int)(digit - '0');
  } else {  // numeros mayores de 10
    return (int)(digit - 'A' + 10);
  }
}

char ToChar(const int digit) {
  if (digit >= 0 && digit < 10) {  // numeros menos de 10
    return (char)(digit + '0');
  } else {  // numeros mayores de 10
    return (char)(digit + 'A' - 10);
  }
}

// ----------------- CONTRUCTORES -----------------
template <size_t Base>
BigInt<Base>::BigInt (long n) {
  sign_ = false;  // positivo
  numbers_.push_back('0');  // valor del BigInt = 0
}

template <size_t Base>
BigInt<Base>::BigInt (std::string& chain) {
  std::string copy(chain);
  if (copy.at(0) == '-') {
    sign_ = true; // negativo
    copy.erase(copy.begin());  // eliminamos el -
  } else {
    sign_ = false; // positivo
  }
  for (auto number: copy) {
    numbers_.push_back(number);
  }
}

template <size_t Base>  // NO FUNCIONA
BigInt<Base>::BigInt (const char* chain) { 
 std::string number = chain;
 BigInt<Base> big(number);
 *this = big;
}

template <size_t Base>
BigInt<Base>::BigInt (const BigInt<Base>& big) {
  *this = big;
} 

// ----------------- Asignacion ---------------
template <size_t Base>   // N1 = N2 no esta bien
BigInt<Base>& BigInt<Base>::operator=(const BigInt<Base>& number) {
  if (this != &number) {
    numbers_ = std::vector<char>();
    sign_ = number.sign() == 1 ? false : true;
    for (int i = 0; i < number.size(); i++) {
      numbers_.push_back(number[i]);
    }
  }
  return *this;
}

// ---------------- Comparacion ----------------
template <size_t Base>
std::ostream& operator<< (std::ostream& os, const BigInt<Base>& big) {
  if (big.sign() == -1) {
    os << '-';
  }
  for (int i{0}; i < big.size(); ++i) {
    os << big[i];
  }
  return os;
}

template <size_t Base> 
std::istream& operator>>(std::istream& is, BigInt<Base>& big) {
  std::string number;
  is >> number;
  BigInt<Base> big2(number);
  big = big2;
  return is;
}

template<size_t Base>  // comprobado
bool operator==(const BigInt<Base>& big1, const BigInt<Base>& big2) {
  return ((big1.sign() == big2.sign()) && (big1.GetNumbers() == big2.GetNumbers()));
}

template<size_t Base>  // falta por comprobar
bool BigInt<Base>::operator!=(const BigInt<Base>& big) const {
 return !(*this == big);
}

template<size_t Base>  // falta por comprobar
bool operator>(const BigInt<Base>& big1, const BigInt<Base>& big2) {
  if (big1.sign() > big2.sign()) {
    return true;
  } else if (big1.sign() < big2.sign()) {
    return false;
  }
  if (big1 != big2) {
    if (big1.sign() == 1) {  // ambos positivos 
      if (big1.size() > big2.size()) {
        return true;
      } else if (big1.size() < big2.size()) {
        return false;
      }
      for (int i{0}; i < big1.size(); ++i) {
        if (big1[i] != big2[i]) { return big1[i] > big2[i]; }
      } 
    } else {  // ambos negativos
      if (big1.size() < big2.size()) {
        return true;
      } else if (big1.size() > big2.size()) {
        return false;
      }
      for (int i{0}; i < big1.size(); ++i) {
        if (big1[i] != big2[i]) { return big1[i] < big2[i]; }
      } 
    }
  }
  return false;
}

template<size_t Base>  // falta comprobar
bool BigInt<Base>::operator>=(const BigInt<Base>& big) const {
  return ((*this == big) || (*this > big ));
}

template<size_t Base>  // falta comprobar
bool operator<(const BigInt<Base>& big1, const BigInt<Base>& big2) {
  return !(big1 >= big2);
}

template<size_t Base>  // falta comprobar
bool BigInt<Base>::operator<=(const BigInt<Base>& big) const {
  return !(*this > big); 
}

// ---------- Operadores aritmeticos ----------
// CASI LOGRADO
template<size_t Base>  // no del todo bien
BigInt<Base> operator+(const BigInt<Base>& big1, const BigInt<Base>& big2) {
  bool sign{true};
  std::string result;
  int carry = 0;
  // determine the size of the result and set the sign
  if (big1.size() > big2.size()) {
    sign = big1.sign() == 1 ? 0 : 1;
  } else {
    sign = big2.sign() == 1 ? 0 : 1;
  }

  if (big1.sign() != big2.sign()) { // Si alguno de los dos numeros son negativos
    BigInt<Base> cp1 = big1;
    BigInt<Base> cp2 = big2;
    cp1.SetSign(0);
    cp2.SetSign(0);
    // Compruebo cual es el mas grande numericamente
    BigInt<Base> max = cp1 > cp2 ? cp1 : cp2;
    BigInt<Base> min = cp1 < cp2 ? cp1 : cp2;
    // Resto el mas grande numericamente con el mas pequeño
    for (int i = max.size() - 1, j = min.size() - 1; i >= 0 || j >= 0; --i, --j) {
      int n1 = (i >= 0 ? ToNumber(max[i]) : 0);
      int n2 = (j >= 0 ? ToNumber(min[j]) : 0);
      int x = n1 - n2 - carry;
      if (x < 0) {
        x = (n1 + Base) - n2 - carry;
        carry = 1;
      } else {
        carry = 0;
      }
      result.push_back(ToChar(x));
    }   
    std::reverse(result.begin(), result.end());
    while(!result.empty() && result.at(0) == '0') {
      result.erase(result.begin());
    }
    if (result.empty()) return BigInt<Base>("0");
    BigInt<Base> ret(result);
    // Asigno el simbolo en base al que era numericamente mas grande
    if (max == cp1) {
      ret.SetSign(big1.sign() == 1 ? 0 : 1);
    } else {
      ret.SetSign(big2.sign() == 1 ? 0 : 1);      
    }
    return ret;   
  } else {
    for (int i = big1.size() - 1, j = big2.size() - 1; i >= 0 || j >= 0 || carry; --i, --j) {
        int x = (i >= 0 ? ToNumber(big1[i]) : 0) + (j >= 0 ? ToNumber(big2[j]) : 0) + carry;
        result.push_back(ToChar(x % Base));
        carry = x / Base;
    }
  }

  std::reverse(result.begin(), result.end());
  while(!result.empty() && result.at(0) == '0') {
    std::cout << result.size() << std::endl;
    result.erase(result.begin());
  }
  if (result.empty()) return BigInt<Base>("0");
  BigInt<Base> ret(result);
  ret.SetSign(sign);
  return ret;
}

template<size_t Base> 
BigInt<Base> BigInt<Base>::operator-() const {
  BigInt<Base> copy = *this;
  copy.SetSign(this->sign() == 1 ? 1 : 0);
  return copy;
}
// HORRIBLE 
template<size_t Base>  // mal
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base>& big) const {
  BigInt<Base> n = -big;
  return (*this + n);
}

// HORRIBLE2
template<size_t Base>  // falta comprobar
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base>& big2) const {
  BigInt<Base> big1 = *this;
  BigInt<Base> result;
  std::string temp;
  {
    std::stringstream ss;
    ss << Base;
    temp = ss.str();
  }
  // Necesario para optimizar tiempo de codigo, ya que vamos a estar haciendo varias veces
  // multiplicaciones xBase en el algoritmo, asi que es una forma rapida de realizarla
  if (big2 == BigInt<Base>(temp)) {
    temp = "";
    for (int i{0}; i < big1.size(); ++i) {
      temp.push_back(big1[i]);
    }
    temp.push_back('0');
    result = BigInt<Base>(temp);
    result.SetSign(big1.sign() == 1 ? 0 : 1);
    return result;
  } else if (big1 == BigInt<Base>(temp)) {
    temp = "";
    for (int i{0}; i < big2.size(); ++i) {
      temp.push_back(big2[i]);
    }
    temp.push_back('0');
    result = BigInt<Base>(temp);
    result.SetSign(big2.sign() == 1 ? 0 : 1);
    return result;
  }
  for (int i{big2.size() - 1}, j{0}; i >= 0; i--, j++) {
    BigInt<Base> number;
    for (int k{0}; k < ToNumber(big2[i]); ++k) {
      BigInt<Base> cp = number + big1;
      number = cp;
    }
    for (int k{0}; k < j; ++k) {
      number = number * BigInt<Base>(temp);
    }
    result = result + number;
  }
  if (big1.sign() == -1) {
    if (big2.sign() == -1) {
      result.SetSign(false);
    } else {
      result.SetSign(true);
    }
  } else {
    if (big2.sign() == -1) {
      result.SetSign(true);
    }
  }
  return result;
}
template<size_t Base>  // no del todo bien
BigInt<Base> operator/(const BigInt<Base>& big1, const BigInt<Base>& big2) {
  BigInt<Base> copy = big1, copy2 = big2;
  BigInt<Base> result("0");
  copy.SetSign(0);
  copy2.SetSign(0);
  while (copy >= copy2) {
    copy = copy - copy2;
    ++result;
  }
  if (big1.sign() == big2.sign()) {
    result.SetSign(false);
  } else {
    result.SetSign(true);
  }
  return result;
}

template<size_t Base>  // falta comprobar
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base>& big) const {
  BigInt<Base> copy = *this, copy2 = big;
  copy.SetSign(0);
  copy2.SetSign(0);
  while (copy >= copy2) {
    copy = copy - copy2;
  }
  copy.SetSign(this->sign() == 1 ? 0 : 1);
  return copy;
}

template<size_t Base>  // no del todo bien
BigInt<Base> pow(const BigInt<Base>& big1, const BigInt<Base>& big2) {
  BigInt<Base> copy = big2;
  BigInt<Base> result = BigInt<Base>("1");
  while (copy != BigInt<Base>("0")) {
    result = result * big1;
    --copy;
  }
  return result;
}

// Pre-incremento  --> incremento y luego asignacion ++a
// int b = 1
// int a = ++b
// a = 2
// b = 2
template<size_t Base>  // falta comprobar
BigInt<Base>& BigInt<Base>::operator++() {
  *this = *this + BigInt<Base>("1");
  return (*this);
}

//Post-incremento  --> aignacion y luego incremento
// int b = 1
// int a = b++
// a = 1
// b = 2
template<size_t Base>  // falta comprobar
BigInt<Base> BigInt<Base>::operator++(int) {
  BigInt<Base> temp = *this;
  *this = *this + BigInt<Base>("1");
  return (temp);
}

// Pre-decremento
template<size_t Base>  // falta comprobar
BigInt<Base>& BigInt<Base>::operator--() {
  *this = *this - BigInt<Base>("1");
  return (*this);
}

// Post-decremento
template<size_t Base>  // falta comprobar
BigInt<Base> BigInt<Base>::operator--(int) {
  BigInt<Base> temp = *this;
  *this = *this - BigInt<Base>("1");
  return (temp);
} 

#endif