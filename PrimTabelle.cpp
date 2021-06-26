//
// Created by Xuantong Pan on 2021/6/2.
//
#include "PrimTabelle.h"
size_t PrimTabelle::primzahl(size_t i) const
{
    size_t n = primZahlen.size();
    if (i >= n - 1)
    {
        size_t last_prim = primZahlen[n-1];
        size_t check_number = last_prim;
        do
        {
            check_number += 2;
            size_t wurzel = size_t(sqrt(check_number));
            for (size_t p : primZahlen)
            {
                if (p > wurzel)
                {
                    primZahlen.push_back(check_number);
                    ++n;
                    break;
                }
                if (check_number % p == 0)
                    break;
            }
        } while (n - 1 <= i);
    }
    return primZahlen[i];
}

size_t PrimTabelle::index(size_t n) const
{
    size_t next_prim = n;
    while(!(istPrim(next_prim)))
        ++next_prim;             // find next prim number
    size_t l = 0;
    size_t r = next_prim;
    while (l < r)
    {
        size_t m = size_t(l + (r - l) / 2); // (l + r)/2
        if (primzahl(m) == next_prim)
            return m;
        else if (primzahl(m) > next_prim)
            r = m - 1;
        else
            l = m + 1;
    }
    return r;
}

bool PrimTabelle::istPrim(size_t n) const
{
    size_t l = 0;
    size_t r = n;
    while (l < r)
    {
        size_t m = size_t(l + (r - l) / 2); // besser als (l + r)/2, weil (l + r) könnte ganz groß sein.
        if (primzahl(m) == n)
            return true;
        else if (primzahl(m) > n)
            r = m;
        else
            l = m + 1;
    }
    return false;
}
vector<size_t> PrimTabelle::primZahlen = {2, 3};

