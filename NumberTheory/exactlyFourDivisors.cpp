#include <cmath>
#include <iostream>

bool hasExactlyFourDivisors(int x) {
    /*
        A number has exactly 4 divisors IFF:
        1) x = p^3   where p is prime
           divisors = {1, p, p^2, p^3}

        2) x = p * q where p and q are distinct primes
           divisors = {1, p, q, p*q}

        No other number can have exactly 4 divisors.
    */

    // ---------- Case 1: x = p^3 ----------
    // Find integer cube root of x
    int p = round(cbrt(x));

    // Check if p^3 == x and p is prime
    if ((long long)p * p * p == x && isPrime(p)) {
        return true;
    }

    // ---------- Case 2: x = p * q ----------
    // Try to find first prime factor p
    for (int p = 2; p * p <= x; p++) {
        if (x % p == 0) {
            int q = x / p;

            // p and q must be distinct primes
            if (q != p && isPrime(p) && isPrime(q)) {
                return true;
            }

            // If one divisor found and condition fails,
            // no need to continue
            return false;
        }
    }

    // No valid form found
    return false;
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}


int main() {
    return 0;
}