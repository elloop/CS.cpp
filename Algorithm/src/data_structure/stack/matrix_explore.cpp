#include "inc.h"
#include "stack.h"
#include <array>

NS_BEGIN(elloop);

using std::array;

void matrixExplore() {
    array<array<int, 5>, 5> mat = {
        1, 0, 0, 1, 0,
        1, 1, 1, 1, 0,
        1, 0, 1, 0, 1,
        1, 0, 1, 1, 0,
        1, 1, 0, 1, 1,
    };

    struct Pos { 
        size_t col; 
        size_t row; 
        bool operator == (const Pos& rhs) const {
            return (rhs.row == row && rhs.col == col);
        }
    };

    Pos outlet = {mat.size(), mat[0].size()};

    Stack<Pos> st;
    st.push({0, 0});

    auto pos = st.top();
    if (pos == outlet) {
        pln("solved");
    }
    else {
        pln("not the end");
    }

}

RUN_GTEST(StackTest, explore, @@);

matrixExplore();


END_TEST;


NS_END(elloop);

