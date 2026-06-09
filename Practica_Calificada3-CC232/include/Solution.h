#pragma once

#include "Treap.h"

class Solution {
private:
    ods::Treap<long long> tree;

public:
    Solution() = default;
    ~Solution() = default;

    void processQuery1(long long x);
    long long processQuery2(long long x, int k);
    long long processQuery3(long long x, int k);
};