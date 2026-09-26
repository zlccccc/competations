#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int i,j,k,t;
LL b1,q,l,m;
int ans;
set<LL> S;
int main()
{
	cin>>b1>>q>>l>>m;
	REP(i,m) {scanf("%d",&j); S.insert(j);}
	j=0;ans=0;
	while (abs(b1)<=l){
		if (!S.count(b1)) {
			ans++;
	//		printf("%d ",b1);
		}
		t++;
		if (ans>10000){
			puts("inf");
			return 0;
		}
		if (t>80000){
			printf("%d",ans);
			return 0;
		}
		b1=b1*q;
	}
	printf("%d",ans);
}
