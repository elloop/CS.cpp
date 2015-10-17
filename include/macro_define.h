#include <iterator>

#define USING_NS_ELLOOP using namespace elloop
#define USING_NS_STD using namespace std
#define NS_ELLOOP_BEGIN namespace elloop {
#define NS_ELLOOP_END }
#define NS_BEGIN(x) namespace x {
#define NS_END(x) }
#define ARRAY_LEN(x)    sizeof x / sizeof x[0]

#define EL_BREAK_IF(cond) if (cond) break;
#define EL_SAFE_DELETE_ARRAY(p) do { if (p) { delete [] (p); (p) = nullptr;} } while(0); 
#define EL_SAFE_DELETE(p) do { if (p) { delete (p); (p) = nullptr;} } while(0); 


#ifdef _MSC_VER
#define __func__ __FUNCTION__
#define noexcept _NOEXCEPT
//#define _Pragma __pragma // seemed no use, because _Pragma should be the first line in file.
#endif

#define RUN_GTEST(__CASE__, __SUB_CASE__, __TAG__) TEST(__CASE__, __SUB_CASE__) { \
    std::fill_n(std::ostream_iterator<std::string>(std::cout, ""), 10, #__TAG__); \
    p(" "); \
    p(#__CASE__); \
    p(" ---> "); \
    p(#__SUB_CASE__); \
    p(" "); \
    std::fill_n(std::ostream_iterator<std::string>(std::cout, ""), 10, #__TAG__); \
    cr;

#define SKIP_ALL_TEST
#ifdef  SKIP_ALL_TEST
#define BEGIN_TEST(__CASE__, __SUB_CASE__, __TAG__) void __CASE__##__SUB_CASE__() { return;
#else
#define BEGIN_TEST(__CASE__, __SUB_CASE__, __TAG__) RUN_GTEST(__CASE__, __SUB_CASE__, __TAG__)
#endif

#define END_TEST }