#define USING_NS_ELLOOP using namespace elloop
#define USING_NS_STD using namespace std
#define NS_ELLOOP_BEGIN namespace elloop {
#define NS_ELLOOP_END }
#define NS_BEGIN(x) namespace x {
#define NS_END(x) }

#define BEGIN_TEST(__CASE__, __SUB_CASE__) TEST(__CASE__, __SUB_CASE__) { \
                                               pcln(#__CASE__ + std::string(" ---> ") + #__SUB_CASE__);

#define END_TEST }

