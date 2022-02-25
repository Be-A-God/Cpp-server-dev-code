/*
 * @lc app=leetcode.cn id=125 lang=cpp
 *
 * [125] 验证回文串
 *
 * https://leetcode-cn.com/problems/valid-palindrome/description/
 *
 * algorithms
 * Easy (47.10%)
 * Likes:    468
 * Dislikes: 0
 * Total Accepted:    316.4K
 * Total Submissions: 671.7K
 * Testcase Example:  '"A man, a plan, a canal: Panama"'
 *
 * 给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。
 *
 * 说明：本题中，我们将空字符串定义为有效的回文串。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: "A man, a plan, a canal: Panama"
 * 输出: true
 * 解释："amanaplanacanalpanama" 是回文串
 *
 *
 * 示例 2:
 *
 *
 * 输入: "race a car"
 * 输出: false
 * 解释："raceacar" 不是回文串
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1
 * 字符串 s 由 ASCII 字符组成
 *
 *
 */

// @lc code=start
class Solution {
 public:
  bool isPalindrome(string s) {
    // string alnum;
    // for (auto ch : s) {
    //   if (isalnum(ch)) {
    //     alnum += tolower(ch);
    //   }
    // }
    // string ralnum(alnum.crbegin(), alnum.crend());
    // return ralnum == alnum;

    // string alnum;
    // for (auto ch : s) {
    //   if (isalnum(ch)) {
    //     alnum += tolower(ch);
    //   }
    // }
    // int head = 0, tail = alnum.size() - 1;
    // while (head < tail) {
    //   if (alnum[head] != alnum[tail]) {
    //     return false;
    //   }
    //   head++;
    //   tail--;
    // }
    // return true;

    int head = 0, tail = s.size() - 1;
    while (head < tail) {
      while (head < tail && !isalnum(s[head])) {
        head++;
      }
      while (head < tail && !isalnum(s[tail])) {
        tail--;
      }
      if (tolower(s[head]) != tolower(s[tail])) {
        return false;
      }
      head++;
      tail--;
    }
    return true;
  }
};
// @lc code=end
