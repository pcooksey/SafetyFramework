#include <iostream>
#include "safetywrapper.h"

using namespace std;

class Shared
{
public:
    int hello() {
        int i(0);
        while(i++ < 100)
            cout<<"hello"<<endl;
        return 1;
        }
};

int main()
{
    SafetyWrap<Shared> trying(new Shared);
    trying("hello")->hello();

    return 0;
}
