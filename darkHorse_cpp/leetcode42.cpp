#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:

    int maxSubArray(vector<int>& nums) {//引用传递
        int pre = 0, maxAns = nums[0];
        for (const auto &x: nums) {
            pre = max(pre + x, x);
            maxAns = max(maxAns, pre);
        }
        return maxAns;
    }
};

int main(){
    vector<int> nums = {31, -41, 59, 11, 37, -53, 58, 33, -93, -23, 85};
    class Solution s;
    int max = s.maxSubArray(nums);
    std::cout<<max<<std::endl;
    return 0;
}