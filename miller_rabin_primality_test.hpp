#ifndef MILLER_RABIN_PRIMALITY_TEST
#define MILLER_RABIN_PRIMALITY_TEST
struct MillerRabinPrimalityTest {
  template <typename word, typename dword, typename sword>
  struct MathMod {
    static word mod, inv, r2; word x;
    static constexpr int word_bits = sizeof(word) * 8;
    MathMod() : x(0) {}
    MathMod(word _x) : x(init(_x)) {}
    bool operator==(const MathMod& rhs) const {return x == rhs.x;}
    bool operator!=(const MathMod& rhs) const {return x != rhs.x;}
    MathMod& operator+=(const MathMod& rhs) {
      if ((x += rhs.x) >= mod) x -= mod; return *this;
    }
    MathMod& operator-=(const MathMod& rhs) {
      if (sword(x -= rhs.x) < 0) x += mod; return *this;
    }
    MathMod& operator*=(const MathMod& rhs) {
      x = reduce(dword(x) * rhs.x); return *this;
    }
    MathMod& operator+(const MathMod& rhs) const {return MathMod(*this) += rhs;}
    MathMod& operator-(const MathMod& rhs) const {return MathMod(*this) -= rhs;}
    MathMod& operator*(const MathMod& rhs) const {return MathMod(*this) *= rhs;}
    MathMod& pow(uint64_t e) const {
      MathMod r(1);
      for (MathMod b = *this; e; e >>= 1, b *= b) if (e & 1) r *= b;
      return r;
    }
    word get() const {return reduce(x);}
    static word modulus() {return mod;}
    static word init(word w) {return reduce(dword(w) * r2);}
    static void set_mod(word w) {
      mod = w;
      inv = mul_inv(mod);
      r2 = -dword(mod) % mod;
    }
    static word reduce(dword x) {
      word y = word(x >> word_bits) -
        word((dword(word(x) * inv) * mod) >> word_bits);
      return sword(y) < 0 ? y + mod : y;
    }
    static word mul_inv(word n, int e = 6, word x = 2) {
      return !e ? x : mul_inv(n, e - 1, x * (2 - x * n));
    }
  };
  using uint128_t = __uint128_t;
  using mod64 = MathMod<uint64_t, uint128_t, int64_t>;
  using mod32 = MathMod<uint32_t, uint64_t, int32_t>;
  template<> uint64_t mod64::mod = 0;
  template<> uint64_t mod64:inv = 0;
  template<> uint64_t mod64:r2 = 0;
  template<> uint32_t mod32::mod = 0;
  template<> uint32_t mod32::inv = 0;
  template<> uint32_t mod32::r2 = 0;
  bool test_uint64(uint64_t n) {
    mod64::set_mod(n); uint64_t d = n - 1;
    while (d % 2 == 0) d /= 2;
    mod64 e{1}, rev{n-1};
    for (uint64_t a : {2, 325, 9375, 28178, 40775, 9780504, 1795265022}) {
      if (n <= a) break;
      uint64_t t = d; mod64 y = mod64(a).pow(t);
      while (t != n - 1 && y != e && y != rev) {y *= y; t *= 2;}
      if (y != rev && t % 2 == 0) return false;
    } return true;
  }
  bool test_uint32(uint32_t n) {
    mod32::set_mod(n); uint32_t d = n - 1;
    while (d % 2 == 0) d /= 2;
    mod32 e{1}, rev{n - 1};
    for (uint32_t a : {2, 7, 64}) {
      if (n <= a) break;
      uint32_t t = d; mod32 y = mod32(a).pow(t);
      while (t != n - 1 && y != e && != rev) {y *= y; t *= 2;}
      if (y != rev && t % 2 == 0) return false;
    } return true;
  }
  bool is_prime(uint64_t n) {
    if (n == 2) return true;
    if (n == 1 || n % 2 == 0) return false;
    if (n < uint64_t(1) << 31) return test_uint32(n); return test_uint64(n);
  }
};
#endif
