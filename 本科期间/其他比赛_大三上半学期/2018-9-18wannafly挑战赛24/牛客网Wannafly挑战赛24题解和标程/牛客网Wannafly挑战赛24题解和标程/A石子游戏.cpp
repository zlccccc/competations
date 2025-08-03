#include<iostream>
using namespace std;
int a[10101];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int cnt0=0,cnt1=0;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]%2==0)
			cnt0++;
		if(a[i]%2==1&&a[i]!=1)
			cnt1++;
	}
	if(cnt0==0&&cnt1==0)
		puts("Bob");
	else if(cnt0%2==0)
		puts("Alice");
	else
		puts("Bob");
	return 0;
}
