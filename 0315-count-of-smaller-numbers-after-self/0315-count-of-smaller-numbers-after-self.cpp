
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> counts(n, 0);
        vector<pair<int, int>> arr;

        for (int i = 0; i < n; i++)
            arr.push_back({nums[i], i});

        mergeSort(arr, counts, 0, n - 1);
        return counts;
    }

private:
    void mergeSort(vector<pair<int, int>>& arr,
                   vector<int>& counts, int left, int right) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;

        mergeSort(arr, counts, left, mid);
        mergeSort(arr, counts, mid + 1, right);

        vector<pair<int, int>> temp;
        int i = left, j = mid + 1;
        int rightSmaller = 0;

        while (i <= mid && j <= right) {
            if (arr[j].first < arr[i].first) {
                temp.push_back(arr[j++]);
                rightSmaller++;
            } else {
                counts[arr[i].second] += rightSmaller;
                temp.push_back(arr[i++]);
            }
        }

        while (i <= mid) {
            counts[arr[i].second] += rightSmaller;
            temp.push_back(arr[i++]);
        }

        while (j <= right)
            temp.push_back(arr[j++]);

        for (int k = 0; k < temp.size(); k++)
            arr[left + k] = temp[k];
    }
};
