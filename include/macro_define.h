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
//#define noexcept _NOEXCEPT
//#define _Pragma __pragma // seemed no use, because _Pragma should be the first line in file.
#endif

#define BEGIN_TEST(__CASE__, __SUB_CASE__, __TAG__) TEST(__CASE__, __SUB_CASE__) { \
                                           std::string msg(23, #__TAG__[0]); \
                                           msg.append(" "); \
                                           msg.append(#__CASE__); \
                                           msg.append(" ---> "); \
                                           msg.append(#__SUB_CASE__); \
                                           msg.append(" "); \
                                           msg.append(23, #__TAG__[0]); \
                                           pln(msg);

#define END_TEST }