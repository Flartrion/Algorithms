class CharListEl {
    char s = 0;
    int weight = 0;
    CharListEl* next = 0;
}

class CharList {
    CharListEl *top=0;
    
    CharList* split(int where);
    
    CharListEl* operator [](int where);
    
    void add(char s);
}
