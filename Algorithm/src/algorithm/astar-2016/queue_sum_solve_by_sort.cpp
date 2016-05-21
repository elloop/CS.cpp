#include <algorithm>
#include <vector>
#include <climits>
#include <cmath>
#include <string>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <iostream>
#include <cstdio>
#include <sstream>

using namespace std;
#define psln(x) std::cout << #x " = " << (x) << std::endl; 
#define ps(x) do { std::cout << #x " = " << (x); } while (0);
#define p(x) do { std::cout << (x); } while (0);
#define pln(x) do { std::cout << (x) << endl; } while (0);
#define	cr do { std::cout << std::endl; } while (0);

typedef vector<int> i_array;
typedef i_array::iterator i_iter;

typedef vector<string> str_array;
typedef str_array::iterator s_iter;

typedef set<int> i_set;
typedef i_set::iterator i_set_iter;

typedef set<string> s_set;
typedef s_set::iterator s_set_iter;

typedef map<int, string> is_map;
typedef is_map::iterator is_iter;

typedef multimap<int, int> ii_map;
typedef ii_map::iterator ii_iter;

typedef map<string, string> ss_map;
typedef ss_map::iterator ss_iter;

ii_map iim;

bool special_sort(int a, int b) {
    if (a < b) {
        ii_iter it1 = iim.find(a);
        if (it1 != iim.end()) {
            return (it1->second == b);
        }
        return false;
    }
    else {
        ii_iter it2 = iim.find(b);
        if (it2 != iim.end()) {
            return (it2->second != a);
        }
        return true;
    }
}

int main() {

    int t(0);
    
    scanf("%d", &t);

    int m(0), n(0);
    i_array a;

    while (t-->0) {
        scanf("%d %d", &n, &m);
        a.reserve(n);

        for (int j=n; j>0; --j) {
            a.push_back(j);
        }

        iim.clear();
        for (int k=0; k<m; ++k) {
            int p1, p2;
            scanf("%d %d", &p1, &p2);
            iim.insert(make_pair(p1, p2));
        }

        sort(a.begin(), a.end(), special_sort);

        // for (int pp=0; pp<n; ++pp) {
            // p(a[pp]); p(" ");
        // }
        // cr;

        // output sum.
        int sum(0), mini(0);
        mini = a[0];
        for (int qq=0; qq<n; ++qq) {
            if (mini > a[qq]) {
                mini = a[qq];
                // psln(mini);
            }
            sum += mini;
        }
        // psln(sum);
        printf("%d\n", sum);

        i_array().swap(a);
    }
    return 0;
}
