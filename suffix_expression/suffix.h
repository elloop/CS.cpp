_Pragma("once")

#include <string>

namespace elloop {

class SuffixTest {
public:
	void test();
	std::string suffix2midfix ( std::string & suffixStr );
private:
	bool _isFirstOpPriorityHigher(char, char);
	enum OpType {
		NUM,
		OP,
		LEFT_BRACKET,
		RIGHT_BRACKET,
	};
	OpType _fectchAElement(char elem);
};

} // end namespace elloop;
