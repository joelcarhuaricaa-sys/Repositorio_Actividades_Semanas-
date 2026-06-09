#include "Solution.h"

void Solution::processQuery1(long long x) {
    tree.add(x);
}

long long Solution::processQuery2(long long x, int k) {
    int total_le = tree.countLessOrEqual(x);
    if (total_le < k) return -1;

    int target_index = total_le - k;
    return tree.findKth(target_index);
}