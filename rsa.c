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

// Funtion to find the GCD of two numbers
int findGCD(int num1, int num2){
    while(num2 != 0){
        int temp = num2;
        num2 = num1 % num2;
        num1 = temp;
    }
    // once num2 = 0 then GCD has been found
    return num1;
}

// Function to find a suitable public exponent (e)
int findPublicKeyExponent(int r) {
    long int e = 2; // 1 < e < r
    // Increment e until it is coprime with r
    while (1) {
        // Check if e and r are coprime
        if (findGCD(e, r) == 1)
            return e; // Found a suitable value for e

        // Increment e
        e++;
    }
}

// Function to find a suitable private key exponent (e)
int findPrivateKeyExponent(int e, int r) {
    long long int d = 0; //d ≡ e^−1 (mod r)
    // Increment d until it is the modular multiplicative inverse of e modulo r. 
    while (1) {
        // Check if d is modular multiplicative inverse of e mod r
        if (((d * e) % r) == 1)
            return d; // Found a suitable value for d

        // Increment d
        d++;

        // Check if d exceeds r
        if (d >= r)
            break; // Break the loop if d exceeds r
    }
    return -1; // No suitable d found
}

int main() {
    int p;
    int q;
    int iterations = 5; // Number of iterations for prime test

    int data, cipher, decrypt;

    // Seed the random number generator
    srand(time(NULL));

    printf("Enter your first prime number: ");
    scanf("%d", &p);

    if (isPrime(p, iterations)) {
        printf("%d is likely a prime number.\n", p);
    } else {
        printf("Error: %d is not a prime number \n", p);
        return 0;
    }

    printf("Enter your second prime number: ");
    scanf("%d", &q);

    if (isPrime(q, iterations)) {
        printf("%d is likely a prime number.\n", q);
    } else {
        printf("Error: %d is not a prime number \n", q);
        return 0;
    }

    // continue with RSA algo function
    long int n = p * q;

    long int r = (p-1) * (q-1);

    // Find a suitable public exponent (e)
    int e = findPublicKeyExponent(r);
    printf("e value is: %d\n", e);

    // Find private key exponent (d)
    int d = findPrivateKeyExponent(e, r);
    printf("d value is: %d\n", d);

    printf("Enter numerical data: ");
	scanf("%d", &data);

	cipher = power(data, e, n);
	printf("The cipher text is: %d\n", cipher);

	decrypt = power(cipher, d, n);
	printf("The decrypted text is: %d\n", decrypt);

    return 0;
}
