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

using namespace std;
#define psln(x) std::cout << #x " = " << (x) << std::endl; 
#define ps(x) do { std::cout << #x " = " << (x); } while (0);
#define p(x) do { std::cout << (x); } while (0);
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

int main() {
    int t(0);
    scanf("%d", &t);
    int m(0), n(0);
    while (t-->0) {
        scanf("%d %d", &n, &m);
        i_array a;
        a.reserve(n);
        for (int j=n; j>0; --j) { a.push_back(j); }
        ii_map ma;
        for (int k=0; k<m; ++k) {
            int p1, p2;
            scanf("%d %d", &p1, &p2);
            ma.insert(make_pair(p1, p2));
        }
        ii_iter it = ma.begin();
        while (it != ma.end()) {
            int tar = it->first;
            int moved = it->second;
            if (tar > moved) { ++it; continue; }
            // find moved
            int imoved(0), itar(0);
            while (imoved < n && a[imoved] != moved) { ++imoved; }
            itar = imoved + 1;
            while (itar<n && a[itar] != tar) { ++itar; }
            if (itar == n ) {
                continue;
            }
            for (int q=imoved; q<itar; ++q) { swap(a[q], a[q+1]); }
            ++it;
        }
        int sum(0);
        int mini = a[0];
        for (int k=0; k<n; ++k) {
            if (mini > a[k]) {
                mini = a[k];
            }
            sum += mini;
        }
        printf("%d\n", sum);
    }
    return 0;
}
