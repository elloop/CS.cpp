#include <iostream>
#include <vector>
#define psln(x) std::cout << #x << " = " << (x) << std::endl

using namespace std;

int main() 
{
    vector<int> vi;
    psln(vi.capacity());

    vector<int> v2(10);
    psln(v2.capacity());

    vector<int> v3 = {};
    psln(v3.capacity());

    vector<int> v4 = {1};
    psln(v4.capacity());

    return 0;
}




