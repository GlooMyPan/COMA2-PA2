//
// Created by Xuantong Pan on 2021/6/2.
//

#ifndef PA2_PRIMTABELLE_H
#define PA2_PRIMTABELLE_H
#include <vector>

using namespace std;
class PrimTabelle
{
private:
    static vector<size_t> primZahlen;

public:
    PrimTabelle(){};
    size_t primzahl(size_t i) const;
    size_t index(size_t n ) const;
    bool istPrim(size_t n) const;
};
#endif //PA2_PRIMTABELLE_H
