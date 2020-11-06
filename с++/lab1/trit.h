#ifndef LAB1_TRIT_H
#define LAB1_TRIT_H

#include <iostream>

enum class trit: int {
    False = 0,
    Unknown = 1,
    True = 3
};

trit operator!(trit a);
trit operator|(trit a, trit b);
trit operator&(trit a, trit b);

#endif //LAB1_TRIT_H
