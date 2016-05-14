/*
 *
 *
度熊所居住的 D 国，是一个完全尊重人权的国度。以至于这个国家的所有人命名自己的名字都非常奇怪。一个人的名字由若干个字符组成，同样的，这些字符的全排列的结果中的每一个字符串，也都是这个人的名字。例如，如果一个人名字是 ACM，那么 AMC， CAM， MAC， MCA， 等也都是这个人的名字。在这个国家中，没有两个名字相同的人。

度熊想统计这个国家的人口数量，请帮助度熊设计一个程序，用来统计每一个人在之前被统计过多少次。

Input
这里包括一组测试数据，第一行包含一个正整数NN，接下来的NN 行代表了 NN 个名字。NN 不会超过100,000100,000，他们的名字不会超过40位.

Output
对于每输入的一个人名，输出一个整数，代表这个人之前被统计了多少次。

Sample Input
5
ACM
MAC
BBA
ACM
BAB
Sample Output
0
1
0
2
1
 *
 *
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int main() {

    // read input
    size_t n(0);
    cin >> n;

    map<string, size_t> names;

    // read n line
    string s;
    for (size_t i=0; i<n; ++i) {
        // read 1 line
        cin >> s;
        sort(s.begin(), s.end());
        map<string, size_t>::iterator iter = names.find(s);
        if (iter != names.end()) {
            cout << iter->second << endl;
            ++(iter->second);
        }
        else {
            cout << "0" << endl;
            names.insert(make_pair(s, 1));
        }
    }
    
    return 0;
}
