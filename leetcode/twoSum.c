#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Two Sum Leetcode Problem (Easy)
 *
 * You are given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * You can return the answer in any order.
 *
 * Example 1:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 *
 * Example 2:
 * Input: nums = [3,2,4], target = 6
 * Output: [1,2]
 *
 * Example 3:
 * Input: nums = [3,3], target = 6
 * Output: [0,1]
 *
 * Constraints:
 * 2 <= nums.length <= 104
 * -109 <= nums[i] <= 109
 * -109 <= target <= 109
 * Only one valid answer exists.
 *
 * Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
 */

void printIndexes(int* foundIndexes, int* returnSize) {
  printf("Found Indexes: [");
  for (int i = 0; i < *returnSize; i++) {
    if (i == *returnSize - 1) {
      printf("%d", foundIndexes[i]);
    } else {
      printf("%d, ", foundIndexes[i]);
    }
  }
  printf("]\n");
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  int* foundIndexes = (int *) calloc(2, sizeof(int));
  unsigned int indexCnt = 0;
  *returnSize = 2;

  for (int i = 0; i < numsSize; i++) {
    foundIndexes[0] = i;
    for (int j = i+1; j < numsSize; j++) {
      foundIndexes[1] = j;

      if (nums[i] + nums[j] == target) {
        return foundIndexes;
      }
    }
  }

  // Nothing found
  foundIndexes[0] = -1;
  foundIndexes[1] = -1;
  return foundIndexes;
}

void main() {
  int* nums = malloc(4 * sizeof(int));

  printf("START TEST CASE 1\n");
  // Test case 1
  nums[0] = 2;
  nums[1] = 7;
  nums[2] = 11;
  nums[3] = 5;
  int target = 9;
  int returnSize = 2;
  int* indexes = twoSum(nums, 4, target, &returnSize);
  printIndexes(indexes, &returnSize);
  printf("END TEST CASE 1\n");

  printf("START TEST CASE 2\n");
  // Test case 2
  nums[0] = 3;
  nums[1] = 2;
  nums[2] = 4;
  target = 6;
  returnSize = 2;
  indexes = twoSum(nums, 3, target, &returnSize);
  printIndexes(indexes, &returnSize);
  printf("END TEST CASE 2\n");

  printf("START TEST CASE 3\n");
  // Test case 3
  nums[0] = 3;
  nums[1] = 3;
  target = 6;
  returnSize = 2;
  indexes = twoSum(nums, 2, target, &returnSize);
  printIndexes(indexes, &returnSize);
  printf("END TEST CASE 3\n");
}
