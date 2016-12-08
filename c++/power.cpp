
/* http://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/ */

/* Iterative Function to calculate (x^n)%p in O(logy) */
uint64_t power_mode(uint64_t x, uint64_t n, uint64_t p)
{
    uint64_t res = 1;
    x = x % p;  
    while (n > 0) {
        if (n & 1) {
            n--;
            res = (res*x) % p;
        } else {
            n >>= 1; // n = n/2
            x = (x*x) % p;
        }
    }
    return res;
}
