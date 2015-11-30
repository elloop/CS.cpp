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

BEGIN_TEST(TempTest, Birth, @@@);

int boy, girl;
int n;
boy = girl = 0;
scanf("%d", &n);
srand(time(0));
const int N = 1000000;
for (int i=0; i<N; ++i) {
    int p0 = rand() % 2;
    if (p0 == 1) {
        // sheng 
        int p1 = rand() % 2;
        if (p1 == 1) {
            boy = boy + 1;
        }
        else {
            girl = girl + 1;
        }
    }
    else {
        // bu sheng hai zi.
    }
}


for (int i=0; i<girl; ++i) {
    int p2 = rand() % 2;
    if (p2 == 1) {
        // sheng
        int p3 = rand() % 100 + 1;
        if (p3 > (50 + n)) {
            girl = girl + 1;
        }
        else {
            boy = boy + 1;
        }
    }
    else {
        // bu zai sheng.
    }
    
}


printf("%.2lf\n", (double)boy / girl);

END_TEST;


template <typename T>
class BinaryTree {
public:
    class Node {
    public:
        Node(const T &data, Node *left, Node *right) :
            data_(data),
            left_(left),
            right_(right) {
        }

        T       data_;
        Node    *left_;
        Node    *right_;
    };
    BinaryTree() : root_(nullptr) {}
    ~BinaryTree() {
        clear();
    }
    void insert(const T & val) {
        insert(root_, val);
    }
    void print() {
        print(root_, 1);
    }
    void clear() {
        clear(root_);
    }
    void invert() {
        invert(root_);
    }
    bool empty() const { return (!root_); }
private:
    void insert(Node *&root, const T &val) {
        if (!root) {
            root = new Node(val, nullptr, nullptr);
        }
        else if (val < root->data_) {
            insert(root->left_, val);
        }
        else if (val > root->data_) {
            insert(root->right_, val);
        }
        else {
            LOGD("val already exists!\n");
        }
    }
    void print(const Node *root, int indent) {
        if (root) {
            print(root->right_, indent + 3);
            for (int i=0; i<indent; ++i) {
                p(" ");
            }
            pln(root->data_);
            print(root->left_, indent + 3);
        }
    }
    void clear(Node *&root) {
        if (root) {
            clear(root->left_);
            clear(root->right_);
            EL_SAFE_DELETE(root);
        }
    }
    void invert(Node *& root) {
        if (root) {
            invert(root->left_);
            invert(root->right_);
            Node *temp = root->left_;
            root->left_ = root->right_;
            root->right_ = temp;
        }
    }
    Node        *root_;
};

BEGIN_TEST(TempTest, BinaryTreeReview, @@@);

BinaryTree<int> btree;
btree.insert(100);
btree.insert(1330);
btree.insert(10);
btree.insert(20);
btree.insert(40);
btree.print();
btree.invert();
btree.print();
btree.clear();


END_TEST;



NS_END(temp);
NS_END(elloop);