extern "C" int getmin(int *a, int n)
{
	int minIdx = 0;
	for(int i = 0 ; i < n ; ++i)
		if (a[i] < a[minIdx])
			minIdx = i;
	return a[minIdx];
}

extern "C" int getmax(int *a, int n)
{
	int maxIdx = 0;
	for(int i = 0 ; i < n; ++i)
		if (a[i] > a[maxIdx])
			maxIdx = i;
	return a[maxIdx];
}

