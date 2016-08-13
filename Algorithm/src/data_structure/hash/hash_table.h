
template <typename T>
class HashTable {
public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable & other);
    HashTable(HashTable && moved);

private:
    class HashNode {
        public:
            HashNode(const T &val, const HashNode *next) : _val(val), _next(next) { }
            ~HashNode() {
                if (_next) {
                    delete _next;
                }
            }

            HashNode(const HashNode & other) = delete;
            HashNode(HashNode && moved) = delete;

        private:
            T           _val;
            HashNode    *_next;
    };
    HashNode        **_slots;
    int32_t         _size;
};
