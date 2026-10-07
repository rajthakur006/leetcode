class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;
        
        while (left < right) {
            // Swap characters in place
            swap(s[left], s[right]);
            
            // Move pointers toward the center
            left++;
            right--;
        }
    }
};