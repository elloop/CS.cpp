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
    enum class MazePosType {
        kWall    = 0,
        kPass    = 1,
        kTryFail = 2,
        kInStack = 3,
    };

    array<array<MazePosType, 5>, 5> mat = {
        MazePosType::kPass, MazePosType::kWall, MazePosType::kWall, MazePosType::kPass, MazePosType::kWall,
        MazePosType::kPass, MazePosType::kPass, MazePosType::kPass, MazePosType::kPass, MazePosType::kWall,
        MazePosType::kPass, MazePosType::kPass, MazePosType::kPass, MazePosType::kWall, MazePosType::kPass,
        MazePosType::kWall, MazePosType::kPass, MazePosType::kWall, MazePosType::kPass, MazePosType::kWall,
        MazePosType::kPass, MazePosType::kPass, MazePosType::kPass, MazePosType::kPass, MazePosType::kPass,
    };

    struct Pos { 
        int row_; 
        int col_; 
        Pos(int row = -1, int col = -1) : row_(row), col_(col) { }
        bool operator == (const Pos& rhs) const {
            return (rhs.row_ == row_ && rhs.col_ == col_);
        }
        bool operator != (const Pos& rhs) const {
            return !(*this == rhs);
        }
        void makeValid(int size) {
            row_ = std::max(0, row_);
            col_ = std::max(0, col_);
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
            pv("{%d, %d} -> ", iter->row_, iter->col_);
            ++iter;
        }
    };
    

    Pos outlet = {static_cast<int>(mat.size() - 1), static_cast<int>(mat[0].size() - 1)};
    Pos noWay = {-1, -1};

    auto getNextPos = [&mat, &noWay] (const Pos& pos) -> Pos {
        array<Pos, 4> anticlockwisePos = { 
                                        Pos(pos.row_ - 1, pos.col_),
        Pos(pos.row_, pos.col_ - 1),                                    Pos(pos.row_, pos.col_ + 1), 
                                        Pos(pos.row_ + 1, pos.col_),
        };
        for (auto& posi : anticlockwisePos) {
            posi.makeValid(mat.size() - 1);
            if ( (posi != pos) && 
                 (posi != noWay) &&
                 (mat[posi.row_][posi.col_] == MazePosType::kPass) ) {
                return posi;
            }
        }
        return noWay;
    };

    auto markMazePos = [&mat] (const Pos& pos, MazePosType t) {
        mat[pos.row_][pos.col_] = t;
    };

    Stack<Pos> st;
    st.push({0, 0});

    Pos currentPos = st.top();
    markMazePos(currentPos, MazePosType::kInStack);
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
            markMazePos(currentPos, MazePosType::kTryFail);
            pv("{%d, %d} out\n", currentPos.row_, currentPos.col_);
            if (st.empty()) {
                pln("no solution");
                break;
            }
            currentPos = st.top();
        }
        else {
            // currentPos has other way? push it
            st.push(nextPos);
            pv("{%d, %d} in\n", nextPos.row_, nextPos.col_);
            markMazePos(nextPos, MazePosType::kInStack);
            currentPos = nextPos;
        }
    }
}

RUN_GTEST(StackTest, explore, @@);

matrixExplore();

END_TEST;


NS_END(elloop);

