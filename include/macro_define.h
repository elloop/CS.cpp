#define USING_NS_ELLOOP using namespace elloop
#define USING_NS_STD using namespace std
#define NS_ELLOOP_BEGIN namespace elloop {
#define NS_ELLOOP_END }
#define NS_BEGIN(x) namespace x {
#define NS_END(x) }
#define ARRAY_LEN(x)    sizeof x / sizeof x[0]

#ifdef _MSC_VER
#define __func__ __FUNCTION__
//#define noexcept _NOEXCEPT
//#define _Pragma __pragma // seemed no use, because _Pragma should be the first line in file.
#endif
