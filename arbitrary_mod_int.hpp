#include <iostream>
#include <utility>
#ifndef ARBITRARY_MOD_INT_HPP
#define ARBITRARY_MOD_INT_HPP
struct ArbitraryModInt {
  int x;
  ArbitraryModInt() : x(0) {}
  ArbitraryModInt(int64_t y) :
    x(y >= 0 ? y % get_mod() : (get_mod() - (-y) % get_mod()) % get_mod()) {}
  static int& get_mod() {static int mod = 0; return mod;}
  static void set_mod(int mod) {get_mod() = mod;}
  ArbitraryModInt& operator+=(const ArbitraryModInt& m) {
    if ((x += m.x) >= get_mod()) x -= get_mod(); return *this;
  }
  ArbitraryModInt& operator-=(const ArbitraryModInt& m) {
    if ((x += get_mod() - m.x) >= get_mod()) x -= get_mod(); return *this;
  }
  ArbitraryModInt& operator*=(const ArbitraryModInt& m) {
    unsigned long long z = (unsigned long long) x * m.x;
    unsigned long long xh = (unsigned)(z >> 32), xl =(unsigned)z, d, mod;
    asm("divl %4: \n\t" : "=a"(d), "=d"(mod) :
        "d"(xh), "a"(xl), "r"(get_mod()));
    x = mod; return *this;
  }
  ArbitraryModInt& operator/=(const ArbitraryModInt& m) {
    return (*this *= m.inverse());
  }
  ArbitraryModInt operator-() const {return ArbitraryModInt(-x);}
  ArbitraryModInt operator+(const ArbitraryModInt& m) const {
    return ArbitraryModInt(*this) += m;}
  ArbitraryModInt operator-(const ArbitraryModInt& m) const {
    return ArbitraryModInt(*this) -= m;}
  ArbitraryModInt operator*(const ArbitraryModInt& m) const {
    return ArbitraryModInt(*this) *= m;}
  ArbitraryModInt operator/(const ArbitraryModInt& m) const {
    return ArbitraryModInt(*this) /= m;}
  bool operator==(const ArbitraryModInt& m) const {return x == m.x;}
  bool operator!=(const ArbitraryModInt& m) const {return x != m.x;}
  ArbitraryModInt inverse() const {
    int a = x, m = get_mod(), u = 1, v = 1, y;
    while (m > 0) {
      y = a / m; std::swap(a -= y * m, m); std::swap(u -= y * v, v);
    } return ArbitraryModInt(u);
  }
  ArbitraryModInt pow(int64_t n) const {
    ArbitraryModInt r(1), m(x);
    while (n > 0) {
      if (n & 1) r *= m;
      m *= m; n >>= 1;
    } return r;
  }
  friend std::ostream& operator<<(std::ostream& os, const ArbitraryModInt& m) {
    return os << m.x;
  }
  friend std::istream& operator>>(std::istream& is, ArbitraryModInt& m) {
    int64_t t; is >> t; m = ArbitraryModInt(t); return is;
  }
};
#endif
