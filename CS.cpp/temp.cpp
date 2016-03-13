#include <iostream>
#include <cstring>
using namespace std;

struct HashNode
{
    int         data;
    HashNode    *next;
    HashNode(int data, HashNode* next)
    {
        this->data = data;
        this->next = next;
    }
};

class HashTable 
{
public:
    HashTable(size_t capacity) : _capacity(capacity), _size(0)
    {
        _table = new HashNode*[_capacity];
        memset(_table, 0, _capacity * sizeof (HashNode*));
    }

    size_t hash_func(int value)
    {
        return (value ^ 0xdeadbeef) % _capacity;
    }

    void insert(int value)
    {
        int idx = hash_func(value);
        HashNode *p = _table[idx];
        while (p && p->data != value) {
            p = p->next;
        }
        if (!p) {
            HashNode *new_node = new HashNode(value, _table[idx]);
            new_node->next = _table[idx]->next;
            _table[idx] = new_node;
        }
    }

    void find(int value)
    {
        size_t idx = hash_func(value);
        HashNode *p = _table[idx];
        while (p && p->data != value) {
            p = p->next;
        }

    }
private:
    HashNode    **_table;
    size_t      _capacity;
    size_t      _size;
};


int main() 
{
    HashTable ht(10);


}
