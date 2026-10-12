class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long long> prefix(nums.size() + 1, 0);

        for (int i = 0; i < nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        return mergeSort(prefix, 0, prefix.size(), lower, upper);
    }

private:
    int mergeSort(vector<long long>& sums, int left, int right,
                  int lower, int upper) {
        if (right - left <= 1) return 0;

        int mid = left + (right - left) / 2;

        int count = mergeSort(sums, left, mid, lower, upper);
        count += mergeSort(sums, mid, right, lower, upper);

        int low = mid, high = mid;

        for (int i = left; i < mid; i++) {
            while (low < right && sums[low] - sums[i] < lower)
                low++;

            while (high < right && sums[high] - sums[i] <= upper)
                high++;

            count += high - low;
        }

        vector<long long> temp;
        int i = left, j = mid;

        while (i < mid && j < right) {
            if (sums[i] <= sums[j])
                temp.push_back(sums[i++]);
            else
                temp.push_back(sums[j++]);
        }

        while (i < mid) temp.push_back(sums[i++]);
        while (j < right) temp.push_back(sums[j++]);

        for (int k = 0; k < temp.size(); k++) {
            sums[left + k] = temp[k];
        }

        return count;
    }
};


