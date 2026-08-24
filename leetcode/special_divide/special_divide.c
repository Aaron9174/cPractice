#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Divide Two Integers
 *
 * Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator. 
 * The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would be truncated to 8, and -2.7335 
 * would be truncated to -2.
 *
 * Return the quotient after dividing dividend by divisor.
 *
 * Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. For this 
 * problem, if the quotient is strictly greater than 231 - 1, then return 231 - 1, and if the quotient is strictly less than -231, then return -231.
 * 
 *
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

int divide(int dividend, int divisor) {
  int sum = 0;
  int divisorCount = 0;
  if (dividend == 0) {
    return 0;
  }

  if (dividend < 0 && divisor < 0)
  {
    if (divisor == -1) {
      return -dividend;
    }

    divisorCount = -1;

    while (sum > dividend) {
      if (sum == -INT_MAX) {
        return sum;
      }
      sum += divisor;
      // NOTE: positive divisor count
      divisorCount++;
    }
  }
  else if (dividend > 0 && divisor > 0)
  {
    if (divisor == 1) {
      return dividend;
    }
    else if (divisor == dividend) {
      return 1;
    }

    divisorCount = -1;

    while (sum < dividend) {
      if (sum == INT_MAX) {
        return sum;
      }
      sum += divisor;
      // NOTE: positive divisor count
      divisorCount++;
    }

    // divisor count remains positive since both same sign
    return divisorCount;
  }
  else if (dividend < 0 && divisor > 0) {
    if (divisor == 1) {
      return dividend;
    }
    divisorCount = 1;

    while (sum > dividend) {
      if (sum == -INT_MAX) {
        return sum;
      }
      sum -= divisor;
      // NOTE: negative divisor count
      divisorCount--;
    }
  }
  else
  {
    if (divisor == -1) {
      return -dividend;
    }
    divisorCount = 1;

    while (sum < dividend) {
      if (sum == INT_MAX) {
        return sum;
      }
      sum -= divisor;
      // NOTE: negative divisor count
      divisorCount--;
    }
  }

  return divisorCount;
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
