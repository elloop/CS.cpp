#include <unordered_map>
#include <string>
#include <iostream>
#include "inc.h"


NS_BEGIN(elloop);


RUN_GTEST(UnorderedmapTest, Basic, @);

using namespace std;

unordered_map<int, int> umap;

umap[1] = 100;
if (umap.find(100) != umap.end()) {
    p(umap[100]);
}
else {
    pcln("no 100");
}


// elloop::printMap(umap);



END_TEST;

NS_END(elloop);
