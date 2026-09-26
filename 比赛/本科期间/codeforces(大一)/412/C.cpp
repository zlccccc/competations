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
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


int n,m;
int i,j,k;
int t;
LL l,r,mid;
bool judge(LL x,LL y,LL p,LL q,LL num){
	if (q*num<y||p*num<x) return 0;
//	printf("%lld  %lld %lld\n",num,q*num-y,p*num-x);
	return q*num-y>=p*num-x;
}
int main(){
	scanf("%d",&t);
	LL x,y,p,q;
	while (t--){
		scanf("%I64d%I64d%I64d%I64d",&x,&y,&p,&q);
		if (p==q&&x!=y){
			puts("-1");
			continue;
		}
		if (p==0&&x!=0){
			puts("-1");
			continue;
		}
		l=-1;r=INF;
		while (l+1<r){
			mid=(l+r)/2;
			if (!judge(x,y,p,q,mid)) l=mid;
			else r=mid;
		}
		l++;
		printf("%I64d\n",q*l-y);
	}
}
