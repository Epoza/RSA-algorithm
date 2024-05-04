#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform modular exponentiation
// (a^b) % c
int power(int base, unsigned int exponent, int modulus) {
    int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent / 2;
        base = (base * base) % modulus;
    }
    return result;
}

// Check if p and q are prime using Fermat's Primality Test
int isPrime(int p, int iterations) {
    // Formula a^p-1 ≅ 1 (mod p)

    // Base cases
    if (p <= 1)
        return 0; // Not prime
    if (p <= 3)
        return 1; // Prime (2 and 3 are prime)

    // Check with multiple iterations to determine if p is prime
    for (int i = 0; i < iterations; i++) {
        // Generate a random number between 2 and num - 1
        int a = 2 + rand() % (p - 3);
        
        // Check if a^(num-1) is congruent to 1 modulo num
        if (power(a, p - 1, p) != 1)
            return 0; // Not prime
    }

    return 1; // Likely prime
}

int main() {
    int num1;
    int num2;
    int iterations = 5; // Number of iterations for prime test

    // Seed the random number generator
    srand(time(NULL));

    printf("Enter your first prime number: ");
    scanf("%d", &num1);

    if (isPrime(num1, iterations)) {
        printf("%d is likely a prime number.\n", num1);
    } else {
        printf("Error: %d is not a prime number \n", num1);
        return 0;
    }

    printf("Enter your second prime number: ");
    scanf("%d", &num2);

    if (isPrime(num2, iterations)) {
        printf("%d is likely a prime number.\n", num1);
    } else {
        printf("Error: %d is not a prime number \n", num2);
        return 0;
    }

    // continue with RSA algo function

    return 0;
}
