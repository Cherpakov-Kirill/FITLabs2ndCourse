#include "tritSet.h"

bool comparator (const ull a, const ull b) {
    return a < b;
}

void tritSet::updateOfSettedTrits(){
    this->settedTrits.clear();
    ull position = -1;
    for(uint &a : this->array){
        for(size_t i = 0; i < ((8 * sizeof(uint)) / 2); ++i){
            position++;
            if((a >> (i * 2) & 1) & 1 && (a >> (i * 2 + 1) & 1)){
                this->settedTrits.insert(position);
            }
            if(!(a >> (i * 2) & 1) && !(a >> (i * 2 + 1) & 1)){
                this->settedTrits.insert(position);
            }
        }
    }
    vector <ull> vectorFromSet(this->settedTrits.begin(), this->settedTrits.end() );
    if(vectorFromSet.size()==0) this->logicalLength = 0;
    else{
        sort(vectorFromSet.begin(), vectorFromSet.end(), comparator);
        this->logicalLength = *(vectorFromSet.end()-1)+1;
    }
    vectorFromSet.clear();
}

tritSet::tritSet(ull numberOfTrits) {
    uint numberOfUints = ceil((2.00*numberOfTrits)/(8.00 * sizeof(uint)));
    vector<uint> newVector(numberOfUints,unknownInteger);
    counterOfTrits = numberOfUints * sizeof(uint) * 4;
    array = newVector;
}

tritSet::proxy tritSet::operator[](ull b) {
    proxy newStruct(b, *this);
    return newStruct;
}

tritSet tritSet::operator!() {
    tritSet tritSetC = tritSet(this->capacity());
    tritSetC.array = this->array;
    tritSetC.settedTrits = this->settedTrits;
    tritSetC.logicalLength = this->logicalLength;
    tritSetC.counterOfTrits = this->counterOfTrits;

    for(uint &a : tritSetC.array){
        a = ~a;
        for(size_t i = 0; i < ((8 * sizeof(uint)) / 2); ++i){
            if(!(a >> (i * 2) & 1) && (a >> (i * 2 + 1) & 1)){
                a |= 1 << i * 2;
                a &= ~(1 << i * 2 + 1);

            }
        }
    }
    return move(tritSetC);
}

tritSet tritSet::operator&(tritSet &tritSetB) {
    tritSet tritSetC = tritSet(this->capacity() > tritSetB.capacity() ? this->capacity() : tritSetB.capacity());
    if(this->capacity()>tritSetB.capacity()){
        tritSetC.array = this->array;
        tritSetC.counterOfTrits = this->counterOfTrits;
        for(ull i = 0; i < tritSetC.capacity();i++) tritSetC.array[i] &= tritSetB.array[i];
    }
    else{
        tritSetC.array = tritSetB.array;
        tritSetC.counterOfTrits = tritSetB.counterOfTrits;
        for(ull i = 0; i < tritSetC.capacity();i++) tritSetC.array[i] &= this->array[i];
    }
    tritSetC.updateOfSettedTrits();
    return move(tritSetC);
}

tritSet tritSet::operator|(tritSet &tritSetB){
    tritSet tritSetC = tritSet(this->capacity() > tritSetB.capacity() ? this->capacity() : tritSetB.capacity());
    if(this->capacity()>tritSetB.capacity()){
        tritSetC.array = this->array;
        tritSetC.counterOfTrits = this->counterOfTrits;
        for(ull i = 0; i < tritSetC.capacity();i++) tritSetC.array[i] &= tritSetB.array[i];
    }
    else{
        tritSetC.array = tritSetB.array;
        tritSetC.counterOfTrits = tritSetB.counterOfTrits;
        for(ull i = 0; i < tritSetC.capacity();i++) tritSetC.array[i] |= this->array[i];
    }
    tritSetC.updateOfSettedTrits();
    return move(tritSetC);
}

ull tritSet::capacity() {
    return ceil((2.00*counterOfTrits)/(8.00 * sizeof(uint))); //count of initialized uint
}

ull tritSet::length() {
    return counterOfTrits;
}

ull tritSet::lengthLogical(){
    return logicalLength;
}

void tritSet::initializerOfMemory(ull position) {
    ull countOfNewUint = ceil((2.00*position+1)/(8.00 * sizeof(uint))) - capacity();
    /*for(ull i = 0;i<countOfNewUint;i++){
        array.push_back(unknownInteger);
    }*/
    array.resize(countOfNewUint, unknownInteger);
    counterOfTrits+=countOfNewUint*sizeof(uint)*4;
}

void tritSet::setTrit(trit value, ull position) {
    if(position > counterOfTrits && value == trit::Unknown) return;

    if(value == trit::True || value == trit::False) settedTrits.insert(position);
    else settedTrits.erase(position);
    vector <ull> vectorFromSet(settedTrits.begin(), settedTrits.end() );
    if(vectorFromSet.size()==0) logicalLength = 0;
    else{
        sort(vectorFromSet.begin(), vectorFromSet.end(), comparator);
        logicalLength = *(vectorFromSet.end()-1)+1;
    }
    vectorFromSet.clear();

    ull numberOfUints = floor((2.00 * position)/(8.00 * sizeof(uint)));
    if(position > counterOfTrits && value != trit::Unknown) initializerOfMemory(position);
    auto it = array.begin() + numberOfUints;
    position -= numberOfUints * sizeof(uint) * 4;
    uint cleanValueMask = 0; //this mask clean current position for new trit
    for(int i=0;i<8.00 * sizeof(uint);i++) cleanValueMask |= (((position) * 2) == i || i == ((position) * 2) + 1 ? 0 : 1) << i;
    *it &= cleanValueMask;
    *it |= (int)value << ((position) * 2);
}

trit tritSet::getValueOfTrit(ull position) {
    if(position > counterOfTrits) return trit::Unknown;
    ull numberOfUints = floor((2.00 * position)/(8.00 * sizeof(uint)));
    position -= numberOfUints * sizeof(uint) * 4;
    auto it = array.begin() + numberOfUints;
    uint currentInteger = *it;
    uint getValueMask =  3 << ((position) * 2);
    currentInteger &= getValueMask;
    currentInteger = currentInteger >> ((position) * 2);
    return (trit)currentInteger;
}

void tritSet::printAllTrits() {
    for(int i=15; i>=0;i--) cout<<((i<=9) ? "  " : " ")<<i;
    cout<<endl;
    for(auto it = array.begin(); it<array.end();it++){
        uint curr = *it;
        for(int i=0; i<32;i++){
            if(i%2 == 0) cout<<" ";
            cout<<(curr & (2147483648>>i)?'1':'0');
        }
        cout<<endl;
    }
}

void tritSet::shrink() {
    counterOfTrits = 0;
    logicalLength = 0;
    settedTrits.clear();
    array.clear();
}

void tritSet::trim(ull lastIndex) {
    ull countOfDeleteUint = capacity() - ceil((2.00*lastIndex)/(8.00 * sizeof(uint)));
    for(ull i=0;i<countOfDeleteUint;i++) array.pop_back();
    counterOfTrits -= countOfDeleteUint*16;
    ull currPosition = lastIndex - ((lastIndex-1)/16)*16;
    uint cleanValueMask = 0;
    for(int i=0;i<8.00 * sizeof(uint);i++) cleanValueMask |= (((currPosition) * 2) - 1 < i ? 0 : 1) << i;
    auto it = array.end() - 1 ;
    *it &= cleanValueMask;
    cleanValueMask = ~cleanValueMask;
    cleanValueMask &= unknownInteger;
    *it |= cleanValueMask;
    updateOfSettedTrits();
}

ull tritSet::cardinality(trit value) {
    vector <ull> vectorFromSet(this->settedTrits.begin(), this->settedTrits.end() );
    if(value == trit::Unknown){
        return logicalLength-vectorFromSet.size();
    }
    if(vectorFromSet.size()==0) return 0;
    else{
        sort(vectorFromSet.begin(), vectorFromSet.end(), comparator);
        ull counterOfTritCurrValue = 0;
        for(ull &a : vectorFromSet){
            if(this->getValueOfTrit(a) == value) counterOfTritCurrValue++;
        }
        return counterOfTritCurrValue;
    }
}

unordered_map<trit, int> tritSet::cardinality() {
    unordered_map<trit, int> mapTrits;
    mapTrits.insert(pair<trit,int>(trit::True, cardinality(trit::True)));
    mapTrits.insert(pair<trit,int>(trit::False, cardinality(trit::False)));
    mapTrits.insert(pair<trit,int>(trit::Unknown, cardinality(trit::Unknown)));
    return mapTrits;
}