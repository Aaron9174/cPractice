#include <stdio.h>
#include <string.h>

/**
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D
 * and M.
 *
 * Symbol       Value
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 * For example, 2 is written as II in Roman numeral, just two ones added
 * together. 12 is written as XII, which is simply X + II. The number 27 is
 * written as XXVII, which is XX + V + II.
 *
 * Roman numerals are usually written largest to smallest from left to right.
 * However, the numeral for four is not IIII. Instead, the number four is
 * written as IV. Because the one is before the five we subtract it making four.
 * The same principle applies to the number nine, which is written as IX. There
 * are six instances where subtraction is used:
 *
 * I can be placed before V (5) and X (10) to make 4 and 9.
 * X can be placed before L (50) and C (100) to make 40 and 90.
 * C can be placed before D (500) and M (1000) to make 400 and 900.
 * Given a roman numeral, convert it to an integer.
 *
 *
 *
 * Example 1:
 *
 * Input: s = "III"
 * Output: 3
 * Explanation: III = 3.
 * Example 2:
 *
 * Input: s = "LVIII"
 * Output: 58
 * Explanation: L = 50, V= 5, III = 3.
 * Example 3:
 *
 * Input: s = "MCMXCIV"
 * Output: 1994
 * Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 *
 *
 * Constraints:
 *
 * 1 <= s.length <= 15
 * s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
 * It is guaranteed that s is a valid roman numeral in the range [1, 3999].
 */

#define MAX_REPEAT_ROMAN_CHAR_LEN 3

void printResult(char *s, int convertedNum) {
  printf("Converted %s to %d\n", s, convertedNum);
}

unsigned int convertI(char *s, unsigned int *index) {
  char iRn = s[*index];
  unsigned int accum = 1;

  while (*index < *index + (MAX_REPEAT_ROMAN_CHAR_LEN - 1)) {
    char nextChar = s[*index + 1];

    if (nextChar == 'I') {
      accum += 1;
      *index += 1;
    } else if (nextChar == 'V') {
      accum += 3;
      *index += 1;
      break;
    } else if (nextChar == 'X') {
      accum += 8;
      *index += 1;
      break;
    } else {
      // printf("Failed to parse value: s[%d] = %c\n at line %d\n", i, s[i],
      //        __LINE__);
      break;
    }
  }

  return accum;
}

unsigned int convertX(char *s, unsigned int *index) {
  char iRn = s[*index];
  unsigned int accum = 10;

  while (*index < *index + (MAX_REPEAT_ROMAN_CHAR_LEN - 1)) {
    char nextChar = s[*index + 1];

    if (nextChar == 'X') {
      accum += 10;
      *index += 1;
    } else if (nextChar == 'L') {
      accum += 30;
      *index += 1;
      break;
    } else if (nextChar == 'C') {
      accum += 80;
      *index += 1;
      break;
    } else {
      // printf("Failed to parse value: s[%d] = %c\n at line %d\n", i, s[i],
      //        __LINE__);
      break;
    }
  }

  return accum;
}

unsigned int convertC(char *s, unsigned int *index) {
  char iRn = s[*index];
  unsigned int accum = 100;

  while (*index < *index + (MAX_REPEAT_ROMAN_CHAR_LEN - 1)) {
    char nextChar = s[*index + 1];

    if (nextChar == 'C') {
      accum += 100;
      *index += 1;
    } else if (nextChar == 'D') {
      accum += 300;
      *index += 1;
      break;
    } else if (nextChar == 'M') {
      accum += 800;
      *index += 1;
      break;
    } else {
      // printf("Failed to parse value: s[%d] = %c\n at line %d\n", i, s[i],
      //        __LINE__);
      break;
    }
  }

  return accum;
}

int romanToInt(char *s) {
  unsigned int sum = 0;
  unsigned int temp = 0;
  for (unsigned int i = 0; i < strlen(s); i++) {
    char rn = s[i];
    if (rn == 'I') {
      sum += convertI(s, &i);
    } else if (rn == 'V') {
      sum += 5;
    } else if (rn == 'X') {
      sum += convertX(s, &i);
    } else if (rn == 'L') {
      sum += 50;
    } else if (rn == 'C') {
      sum += convertC(s, &i);
    } else if (rn == 'D') {
      sum += 500;
    } else if (rn == 'M') {
      sum += 1000;
    }
    temp++;
  }

  return sum;
}

int main() {
  char *input = "III";
  int result = romanToInt(input);
  printResult(input, result);

  input = "IV";
  result = romanToInt(input);
  printResult(input, result);

  input = "IX";
  result = romanToInt(input);
  printResult(input, result);

  input = "X";
  result = romanToInt(input);
  printResult(input, result);

  input = "XX";
  result = romanToInt(input);
  printResult(input, result);

  input = "XL";
  result = romanToInt(input);
  printResult(input, result);

  input = "XC";
  result = romanToInt(input);
  printResult(input, result);

  input = "C";
  result = romanToInt(input);
  printResult(input, result);

  input = "CC";
  result = romanToInt(input);
  printResult(input, result);

  input = "CD";
  result = romanToInt(input);
  printResult(input, result);

  input = "CM";
  result = romanToInt(input);
  printResult(input, result);

  input = "LVIII";
  result = romanToInt(input);
  printResult(input, result);

  input = "MCMXCIV";
  result = romanToInt(input);
  printResult(input, result);
}
