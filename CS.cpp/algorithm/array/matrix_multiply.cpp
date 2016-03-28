#include "inc.h"

NS_BEGIN(elloop);

#define DIM 3

void multiply_matrix(int ma[][DIM], int mb[][DIM], int*** mc)
{
	int i, j, k;
	for (i = 0; i < DIM; ++i)
	{
		for (j = 0; j < DIM; ++j)
		{
			(*mc)[i][j] = 0;
			for (k = 0; k < DIM; ++k)
			{
				(*mc)[i][j] += ma[i][k] * mb[k][j];
			}
		}
	}
}

void print_matrix(int m[][DIM])
{
	for (int i = 0; i < DIM; ++i)
	{
		for (int j = 0; j < DIM; ++j)
		{
			p(m[i][j]); p(" ");
		}
		cr;
	}
}

BEGIN_TEST(ArrayAlgo, MatrixMultiply, @@);

int ma[DIM][DIM] = 
{
	{2, 3, 5},
	{3, 4, 8},
	{9, 7, 5}
};

int mb[DIM][DIM] =
{
	{5, 3, 1},
	{8, 2, 9},
	{7, 1, 3}
};

int mc[DIM][DIM] = { 0 };

print_matrix(ma);
cr;
print_matrix(mb);
cr;
print_matrix(mc);
cr;

int i, j, k;
for (i = 0; i < DIM; ++i)
{
	for (j = 0; j < DIM; ++j)
	{
		mc[i][j] = 0;
		for (k = 0; k < DIM; ++k)
		{
			mc[i][j] += ma[i][k] * mb[k][j];
		}
	}
}

print_matrix(mc);
cr;
//multiply_matrix(ma, mb, mc);


END_TEST;

NS_END(elloop);