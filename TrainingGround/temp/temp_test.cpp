#include "inc.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

NS_BEGIN(elloop);
NS_BEGIN(temp);

USING_NS_STD;
typedef vector<string> StringArray;

bool containString(const StringArray& container, const string& str) {
    return (find(container.begin(), container.end(), str) != container.end());
}

void readStringFromFile(StringArray & container, const string& fileName) {
    ifstream in(fileName.c_str(), ifstream::in);
    if (in.is_open()) {
        string line;
        while (getline(in, line)) {
            if (find(line.begin(), line.end(), '\t') != line.end()) {
                stringstream s(line);
                int id(0);
                string unit;
                s >> id >> unit;
                container.push_back(unit);
            }
            else {
                container.push_back(line);
            }
        }
        in.close();
    }
    else {
        LOGD("fail to open file %s for reading\n", fileName.c_str());
    }
}

void writeStringToFile(const StringArray& container, const string& fileName) {
    ofstream out(fileName.c_str(), ofstream::out);
    if (out.is_open()) {
        for_each(container.begin(), container.end(), [&out](string s){
            out << s << endl;
        });
        out.close();
    }
    else {
        LOGD("fail to open file %s for writing\n", fileName.c_str());
    }
}

void addIdColumn(StringArray& container) {
    int id(1);
    for_each(container.begin(), container.end(), [&container, &id](string& s) {
        char buff[10];
        string temp(itoa(id++, buff, 10));
        temp.append("\t").append(s);
        s.swap(temp);

    });
}

void mergeContainer(const StringArray& src1, const StringArray& src2, StringArray& dest ) {
    dest.clear();
    dest.reserve(src1.size() + src2.size());
    psln(dest.capacity());
    // TODO: summary.
    //copy(src1.begin(), src1.end(), dest.begin());
    copy(src1.begin(), src1.end(), back_inserter(dest));

    for_each(src2.begin(), src2.end(), [&dest](string s){
        if (!containString(dest, s)) {
            dest.push_back(s);
        }
        else {
            LOGD("dupicate string: %s\n", s);
        }
    });

    sort(dest.begin(), dest.end());

    addIdColumn(dest);
    writeStringToFile(dest, "dest.txt");
    psln(dest.size());

}

//---------------------- begin of new test ----------------------
BEGIN_TEST(TempTest, CompareFile, $);

return;

StringArray dic1, dic2, dest;
dic1.reserve(2800);
dic2.reserve(350);
readStringFromFile(dic1, "restrict.dlt");
readStringFromFile(dic2, "re.txt");

sort(dic1.begin(), dic1.end());

StringArray newDic1;
newDic1.reserve(dic1.size());

for_each(dic1.begin(), dic1.end(), [&newDic1](string s) {
    if (find(newDic1.begin(), newDic1.end(), s) == newDic1.end()) {
        newDic1.push_back(s);
    }
    else {
        LOGD("duplicate in dic1 : %s\n", s);
    }
});

writeStringToFile(newDic1, "dic1.txt");
mergeContainer(newDic1, dic2, dest);

END_TEST;

//---------------------- begin of new test ----------------------
void passStringByRef(string & str) {
    string temp;
    temp.swap(str);
    psln(temp);
}

void copyVecFast(vector<int>& original) {

    vector<int> newVec;
    newVec.swap(original);
    printContainer(newVec, "newVec: ");
    
}

BEGIN_TEST(TempTest, PassByRef, $);

return;

string str("he");
passStringByRef(str);

vector<int> origin{1, 2, 3, 4, 5};
printContainer(origin, "before origin: ");
copyVecFast(origin);
printContainer(origin, "after origin: ");

END_TEST;

NS_END(temp);
NS_END(elloop);