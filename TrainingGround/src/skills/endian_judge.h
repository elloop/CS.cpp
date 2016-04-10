/*!
 * \file endian_judge.h
 *
 * \author elloop
 * \date ËÄÔÂ 2015
 *
 * 
 */

// method1
union EndianJudge {
	int i;
	char c;
};

inline bool isLittleEndian() {
	EndianJudge endian;
	endian.i = 1;
	return (endian.c == 1);
}
