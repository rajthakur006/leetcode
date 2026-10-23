class MedianFinder {
private:
    priority_queue<int> small;
    priority_queue<int, vector<int>, greater<int>> large;

public:
    MedianFinder() {
    }

    void addNum(int num) {
        small.push(num);
        large.push(small.top());
        small.pop();

        if (small.size() < large.size()) {
            small.push(large.top());
            large.pop();
        }
    }

    double findMedian() {
        if (small.size() > large.size()) {
            return small.top();
        }

        return (small.top() + (double)large.top()) / 2.0;
    }
};
