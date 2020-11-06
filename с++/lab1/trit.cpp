#include "trit.h"

trit operator!(trit a){
    if(a == trit::False) return trit::True;
    if(a == trit::Unknown) return trit::Unknown;
    if(a == trit::True) return trit::False;
    return trit::Unknown;
}

trit operator|(trit a, trit b){
    if(a == trit::False){
        if(b == trit::False) return trit::False;
        if(b == trit::Unknown) return trit::Unknown;
        if(b == trit::True) return trit::True;
    }
    if(a == trit::Unknown){
        if(b == trit::False) return trit::Unknown;
        if(b == trit::Unknown) return trit::Unknown;
        if(b == trit::True) return trit::True;
    }
    if(a == trit::True){
        if(b == trit::False) return trit::True;
        if(b == trit::Unknown) return trit::True;
        if(b == trit::True) return trit::True;
    }
    return trit::Unknown;
}

trit operator&(trit a, trit b){
    if(a == trit::False){
        if(b == trit::False) return trit::False;
        if(b == trit::Unknown) return trit::False;
        if(b == trit::True) return trit::False;
    }
    if(a == trit::Unknown){
        if(b == trit::False) return trit::False;
        if(b == trit::Unknown) return trit::Unknown;
        if(b == trit::True) return trit::Unknown;
    }
    if(a == trit::True){
        if(b == trit::False) return trit::False;
        if(b == trit::Unknown) return trit::Unknown;
        if(b == trit::True) return trit::True;
    }
    return trit::Unknown;
}