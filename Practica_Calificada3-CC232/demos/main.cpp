#include <iostream>
#include "Solution.h"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Solution sol;
    int q;
    if (std::cin >> q) {
        while (q--) {
            int type;
            std::cin >> type;
            if (type == 1) {
                long long x;
                std::cin >> x;
                sol.processQuery1(x);
            } else if (type == 2) {
                long long x;
                int k;
                std::cin >> x >> k;
                std::cout << sol.processQuery2(x, k) << "\n";
            } else if (type == 3) {
                long long x;
                int k;
                std::cin >> x >> k;
                std::cout << sol.processQuery3(x, k) << "\n";
            }
        }
    }
    return 0;
}