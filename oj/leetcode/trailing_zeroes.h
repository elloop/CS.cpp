_Pragma("once")

#include <string>
#include <cmath>

namespace trailing_zeroes {
  /*
  template <int n>
    int factorial() {
      return n * factorial<n-1>;
    }

  template <>
    int factorial<1>() {
      return 1;
    }
    */
  template <int n>
      class Factorial {
        public:
        enum { value = n * Factorial<n-1>::value};
      };

      template <>
      class Factorial<1> {
        public:
        enum { value = 1 };
      };

      template <unsigned long long N>
      unsigned long long f() {
        return N * f<N-1>();
      }

      template <>
      unsigned long long f<1>() {
        return 1;
      }

  class Solution {
    public:

      // template <int n>
      //   int factorial() {
      //     return n * factorial<n-1>;
      //   }

      // template <>
      //   int factorial<1>() {
      //     return 1;
      //   }

      int factorial(int n) {
        if (n <= 1) {
          return 1;
        }
        return n * factorial(n - 1);
      }

      int trailingZeroes(int n) {

        int result(0);
        result = n / 10 * 2;

        if ((n - n / 10 * 10) >= 5) {
          ++result;
        }

        return result;

        // unsigned long long ff = f<20>();
        // psln(ff);
        // return 0;

        // int result1 = Factorial<12>::value;
        // psln(result1);
        // return result1;

        // int fac = factorial(n);
        // psln(fac);
        // int result(0);
        // while (fac > 10) {
          // if (0 == fac - fac / 10 * 10 ) {
            // ++result;
          // }
          // else {
            // break;
          // }
          // fac /= 10;
        // }

        return result;
      }
  };

}
