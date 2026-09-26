#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=200009;

int n;
int a[maxn],b[maxn];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d%d",&a[i],&b[i]);
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	long long ans=0;
	for(int i=1;i<=n;++i){
		ans+=abs(a[i]-i)+abs(b[i]-i);
	}
	printf("%lld\n",ans);
	return 0;
}
