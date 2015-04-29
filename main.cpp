#include <iostream>
#include "safetywrapper.h"

using namespace std;

class Shared
{
public:
    void hello() { cout<<"hello"<<endl; }
};

int main()
{
    SafetyWrap<Shared> trying(new Shared);
    trying->hello();
    return 0;
}
