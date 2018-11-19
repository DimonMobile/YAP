#include <cstdio>

extern "C" int getmin(int *a, int n);
extern "C" int getmax(int *a, int n);

int main()
{
	int a[] = {5,423,432,32,42,23,432,13,42,12,325};
	int min = getmin(a, 10);
	int max = getmax(a, 10);
        printf("getmax-getmin = %d\n", max-min);
	return 0;
}
