#ifndef LAB1_TRITSET_H
#define LAB1_TRITSET_H

#include "trit.h"
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;
typedef unsigned int uint;
typedef unsigned long long ull;
#define unknownInteger 1431655765 //mask for init. 16 trits  with unknown

class tritSet {
private:
    vector<uint>  array;
    set <ull> settedTrits;
    ull counterOfTrits = 0;
    ull logicalLength = 0;

    void initializerOfMemory(ull position);
    void updateOfSettedTrits();
public:
    tritSet(ull numberOfTrits); //constructor

    ~tritSet(){ shrink();}

    tritSet operator!();
    tritSet operator|(tritSet &tritSetB);
    tritSet operator&(tritSet &tritSetB);

    void setTrit(trit value, ull position);
    trit getValueOfTrit(ull position);

    ull capacity();
    ull length();
    ull lengthLogical();

    ull cardinality(trit value);
    unordered_map<trit, int> cardinality();

    void shrink();
    void trim(ull lastIndex);

    void printAllTrits();

    typedef struct proxy{
    private:
        tritSet& set;
        ull pointer;
    public:
        proxy(ull r, tritSet& s) : pointer(r), set(s) {}

        proxy& operator=(const trit &trit) {
           if(trit != trit::Unknown && pointer >= set.counterOfTrits){
                set.array.resize(ceil((2.0 * (1.0 + pointer)) / (8.0 * sizeof(uint))), unknownInteger);
                set.counterOfTrits = pointer + 1;
                set.setTrit(trit, pointer);
            }
           else if(pointer < set.counterOfTrits) set.setTrit(trit, pointer);
           return *this;
        }
        trit operator|(const trit &trit){
            return this->set.getValueOfTrit(this->pointer) | trit;
        }
        trit operator|(const proxy &trit){
            return this->set.getValueOfTrit(this->pointer) | trit.set.getValueOfTrit(trit.pointer);
        }
        trit operator&(const trit &trit){
            return this->set.getValueOfTrit(this->pointer) & trit;
        }
        trit operator&(const proxy &trit){
            return this->set.getValueOfTrit(this->pointer) & trit.set.getValueOfTrit(trit.pointer);
        }
        trit operator!(){
            return !this->set.getValueOfTrit(this->pointer);
        }

        bool operator==(const trit &trit){
            return this->set.getValueOfTrit(this->pointer) == trit;
        }
        bool operator==(const proxy &trit){
            return this->set.getValueOfTrit(this->pointer) == trit.set.getValueOfTrit(trit.pointer);
        }
        bool operator!=(const trit &trit){
            return this->set.getValueOfTrit(this->pointer) != trit;
        }
        bool operator!=(const proxy &trit){
            return this->set.getValueOfTrit(this->pointer) != trit.set.getValueOfTrit(trit.pointer);
        }

    } proxy;

    proxy operator[](ull b);

};


#endif //LAB1_TRITSET_H
