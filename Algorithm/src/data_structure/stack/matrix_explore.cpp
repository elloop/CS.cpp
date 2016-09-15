#include "inc.h"
#include "stack.h"
#include <array>
#include <vector>
#include <list>

NS_BEGIN(elloop);

using std::array;
using std::vector;
using std::list;

void matrixExplore() {
    array<array<int, 5>, 5> mat = {
        1, 0, 0, 1, 0,
        1, 1, 1, 1, 0,
        1, 0, 1, 0, 1,
        1, 0, 1, 1, 0,
        1, 1, 0, 1, 1,
    };

    struct Pos { 
        long long row_; 
        long long col_; 
        Pos(long long row = -1, long long col = -1) : row_(row), col_(col) { }
        bool operator == (const Pos& rhs) const {
            return (rhs.row_ == row_ && rhs.col_ == col_);
        }
        bool operator != (const Pos& rhs) const {
            return !(*this == rhs);
        }
        void makeValid(long long size) {
            row_ = std::max(0LL, row_);
            col_ = std::max(0LL, col_);
            row_ = std::min(row_, size);
            col_ = std::min(col_, size);
        }
        // static const long N; // static data member not allowed in local class.
    };


    auto printSolution = [] (Stack<Pos>& st) {
        list<Pos> resPos;
        while (!st.empty()) {
            Pos p = st.top();
            resPos.push_front(p);
            st.pop();
        }
        auto iter = resPos.begin();
        while (iter != resPos.end()) {
            pv("{%lld, %lld} -> ", iter->row_, iter->col_);
            ++iter;
        }
    };
    

    Pos outlet = {static_cast<long long>(mat.size() - 1), static_cast<long long>(mat[0].size() - 1)};
    Pos noWay = {-1, -1};

    vector<Pos> failPos;
    vector<Pos> posInStack;
    auto getNextPos = [&mat, &failPos, &posInStack, &noWay] (const Pos& pos) -> Pos {
        array<Pos, 4> anticlockwisePos = { 
                                        Pos(pos.row_ - 1, pos.col_),
        Pos(pos.row_, pos.col_ - 1),                                    Pos(pos.row_, pos.col_ + 1), 
                                        Pos(pos.row_ + 1, pos.col_),
        };
        for (auto& posi : anticlockwisePos) {
            posi.makeValid(mat.size() - 1);
            if ( (posi != pos) && 
                 (posi != noWay) &&
                 (mat[pos.row_][pos.col_] == 1) &&
                 (find(posInStack.begin(), posInStack.end(), posi) == posInStack.end()) && 
                 (find(failPos.begin(), failPos.end(), posi) == failPos.end())) {
                return posi;
            }
        }
        return noWay;
    };

    Stack<Pos> st;
    st.push({0, 0});
    posInStack.push_back({0, 0});

    Pos currentPos = st.top();
    while (true) {
        // fail to reach outlet.
        
        // find outlet.
        if (currentPos == outlet) {
            printSolution(st);
            break;
        }

        Pos nextPos = getNextPos(currentPos);

        // currentPos is end of way?
        if (nextPos == noWay) {
            st.pop();
            failPos.push_back(currentPos);
            posInStack.pop_back();
            pv("{%lld, %lld} out\n", currentPos.row_, currentPos.col_);
            if (st.empty()) {
                pln("no solution");
                break;
            }
            currentPos = st.top();
        }
        else {
            // currentPos has other way? push it
            st.push(nextPos);
            pv("{%lld, %lld} in\n", nextPos.row_, nextPos.col_);
            posInStack.push_back(nextPos);
            currentPos = nextPos;
        }
    }
}

RUN_GTEST(StackTest, explore, @@);

matrixExplore();

END_TEST;


NS_END(elloop);

