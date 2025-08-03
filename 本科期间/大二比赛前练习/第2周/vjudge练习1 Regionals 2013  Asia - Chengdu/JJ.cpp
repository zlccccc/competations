#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e6+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;
inline LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
int TT;
LL ans,all;
LL a,b,c,d,m,p,pos;
int i;
LL L,R;
vector<LL> H;
LL I1[maxn],I2[maxn];
int main()
{
	int x=0;
	scanf("%d",&TT);
	while (TT--){
		ans=0;
		scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&m,&p);
		c-=p;d-=p;
		pos=c;c=-d;d=-pos;//reverse
		pos=(a%m+m)%m;
		b+=pos-a;a=pos;
		pos=(c%m+m)%m;
		d+=pos-c;c=pos;
//brute force
		all=(b-a+1)*(d-c+1);
		REP(i,m) I1[i]=I2[i]=0;
		FOR(i,a,b) I1[i%m]++;
		FOR(i,c,d) I2[i%m]++;
		REP(i,m) ans+=I2[i]*I1[i];
//
		printf("Case #%d: ",++x);
		if (ans==0) puts("0/1");
		else printf("%lld/%lld\n",ans/gcd(all,ans),all/gcd(all,ans));
	}
    return 0;
}
/*
5
1 1 98 98 99 0
*/
