#include <iostream>
#include <cmath>
#include <sstream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int atoi_(const string& s) {
    stringstream ss(s);
    int result;
    ss >> result;
    return result;
}

vector<string> split_str(const string& s, char delim = ' ') {
    vector<string> res;
    size_t b(0);
    size_t e = s.find(delim, b);
    while (e != string::npos) {
        res.push_back(s.substr(b, e-b));
        b = e + 1;
        e = s.find(delim, b);
    }
    res.push_back(s.substr(b, string::npos));
    return res;
}

void convert_ip_to_number(const vector<string>& strs, vector<size_t>& ipns) {
    for (auto ip : strs) {
        auto ipitems = split_str(ip, '.');
        size_t ipn(0);
        for (int i=0; i<ipitems.size(); ++i) {
            ipn += atoi_(ipitems[i]) * pow(2, (4-i-1)*8);
        }
        ipns.push_back(ipn);
    }
}

int main() 
{
    size_t t, m, n;

    cin >> t;

    for (size_t i=0; i<t; ++i) {
        vector<string> ips;
        cin >> n >> m;
        ips.reserve(n);
        while (n--) {
            string str;
            cin >> str;
            ips.push_back(str);
        }
        vector<string> codes;
        codes.reserve(m);
        for (size_t j=0; j<m; ++j) {
            string str;
            cin >> str;
            codes.push_back(str);
        }
        
        vector<size_t> ip_number;
        ip_number.reserve(ips.size());
        convert_ip_to_number(ips, ip_number);

        vector<size_t> code_number;
        code_number.reserve(codes.size());
        convert_ip_to_number(codes, code_number);

        cout << "Case #" << (i+1) << ":" << endl;
        for (size_t j=0; j<m; ++j) {
            set<size_t> res;
            for (auto ip : ip_number ) {
                res.insert(ip & code_number[j]);
            }
            cout << res.size() << endl;
        } 
    }

    return 0;
}
