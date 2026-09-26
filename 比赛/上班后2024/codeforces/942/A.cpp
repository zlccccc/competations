#include <bits/stdc++.h>
using namespace std;

class LRUCache {
    LRUCache(int size = 0) {
        time_ = 0;
        init(size);
    }
    void init(int size = 0) { size_ = size; }
    int get(int key) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            time_++;
            cache_[key] = {it->second.second, time_};
            queue_.push({key, time_});
            return it->second.first;
        } else {
            cout << "Not Found! " << key << endl;
            return -1;
        }
    }
    void set(int key, int value) {
        time_++;
        if (cache_.size() > size_) {
            auto p = queue_.front();
            queue_.pop();
            int key = p.first, time = p.second;
            auto it = cache_.find(key);
            assert(it != cache_.end());
            if ((*it).second.second == time_) {
                cache_.erase(key);
            }
        }
        cache_[key] = {value, time_};
        queue_.push({value, time_});
    }

  private:
    int time_ = 0;
    int size_ = 0;
    queue<pair<int, int>> queue_;
    unordered_map<int, pair<int, int>> cache_;
};
int main() {
    int a, b;
    while (cin >> a >> b) { // 注意 while 处理多个 case
        // 64 位输出请用 printf("%lld")
        cout << a + b << endl;
    }
}