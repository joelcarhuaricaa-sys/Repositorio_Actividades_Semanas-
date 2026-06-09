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

long long Solution::processQuery3(long long x, int k) {
    int total_less = tree.countLess(x);
    int target_index = total_less + k - 1;

    int current_total = tree.root() ? tree.root()->subtree_size : 0;
    if (target_index >= current_total) return -1;

    return tree.findKth(target_index);
}