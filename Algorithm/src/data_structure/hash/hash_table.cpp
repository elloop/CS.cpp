#include "data_structure/hash/hash_table.h"
#include "inc.h"
#include <string>

NS_BEGIN(elloop);

template <typename T>
void dumpHashTable(const HashTable<T> &ht) {
    psln(ht.size());
    psln(ht.capacity());
}

// todo: use HashTable to solve real oj problem.
RUN_GTEST(HashTableTest, StringHash, @@);

    std::cout << std::boolalpha;
    bool isUnique(false);

    HashTable<std::string> ht;

    dumpHashTable(ht);

    psln(ht.search("hello"));

    psln(ht.insert("hello", isUnique));
    psln(isUnique);
    psln(ht.search("hello"));

END_TEST;

NS_END(elloop);

