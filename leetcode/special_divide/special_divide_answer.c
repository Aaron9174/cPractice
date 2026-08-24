#include <limits.h>

int divide (int dividend, int divisor) {
  // Special case overflow
  if (dividend == INT_MIN && divisor == -1) {
    return INT_MAX;
  }

  int negatives = 2;
  if (dividend > 0) {
    negatives--;
    // Convert to negative here to prevent integer overflow (-2^31 is a larger solution space than 2^31-1)
    dividend = -dividend;
  }
  if (divisor > 0) {
    negatives--;
    // Convert to negative here to prevent integer overflow (-2^31 is a larger solution space than 2^31-1)
    divisor = -divisor;
  }

  int quotient = 0;
  while (dividend - divisor <= 0) {
    dividend -= divisor;
    quotient--;
  }

  // The divident and divisor have the same sign
  if (negatives != 1) {
    return -quotient;
  }

  return quotient;
}

void main() {

/*
 * Example 1:
 * Input: dividend = 10, divisor = 3
 * Output: 3
 * Explanation: 10/3 = 3.33333.. which is truncated to 3.
 *
 * Example 2:
 * Input: dividend = 7, divisor = -3
 * Output: -2
 * Explanation: 7/-3 = -2.33333.. which is truncated to -2.
 *
 * Constraints:
 * -231 <= dividend, divisor <= 231 - 1
 * divisor != 0
 */

  int dividend = 10;
  int divisor = 3;
  int result = divide(dividend, divisor);
  printf("%d / %d = %d\n", dividend, divisor, result);

  dividend = 7;
  divisor = -3;
  result = divide(dividend, divisor);
  printf("%d / %d = %d\n", dividend, divisor, result);
}
