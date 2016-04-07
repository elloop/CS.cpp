#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif

#include <string>
#include <cmath>

NS_BEGIN(elloop)
NS_BEGIN(trailing_zeroes)

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
	enum { value = n * Factorial<n - 1>::value };
};

template <>
class Factorial<1> {
public:
	enum { value = 1 };
};

template <unsigned long long N>
unsigned long long f() {
	return N * f<N - 1>();
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

	int numOf5(int n) {
		if (1 == n) {
			return 1;
		}
		return 5 * numOf5(n - 1) + 1;
	}

	int trailingZeroes(int n) {

		int pow5(0);
		unsigned long val(1);
		while (val <= static_cast<unsigned long>(n)) {
			++pow5;
			val *= 5;
		}

		--pow5;
		val /= 5;

		int result(0);
		int inc(0);
		int i(0);
		while (pow5 > 0) {
			for (i = 1; i < 5; ++i) {
				if (inc + i * val <= static_cast<unsigned long>(n)) {
					result += numOf5(pow5);
				}
				else {
					break;
				}
			}
			inc += (i - 1) * val;
			--pow5;
			val /= 5;
		}
		return result;

		// int current_pow(0);
		// int t(1);

		// // log5(n)
		// while (t <= n) {
		// ++current_pow;
		// t *= 5;
		// }

		// t /= 5;
		// --current_pow;

		// int num_of_5(0);
		// int inc(0);
		// int i(0);
		// while (inc < n && current_pow > 0) {
		// for (i=1; i<5; ++i) {

		// if (inc + i*t <= n) {
		// if (current_pow > 1) {
		// num_of_5 += 4 * (1 + current_pow - 1) * (current_pow - 1) / 2 + current_pow;
		// }
		// else {
		// ++num_of_5;
		// }
		// }
		// else {
		// break;
		// }
		// }
		// inc += (i - 1) * t;
		// t /= 5;
		// --current_pow;
		// }

		// return num_of_5;


		// int result(0);
		// result = n / 10 * 2;

		// if ((n - n / 10 * 10) >= 5) {
		// ++result;
		// }
		// return result;


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
		// return result;
	}
};

NS_END(trailing_zeroes)
NS_END(elloop)