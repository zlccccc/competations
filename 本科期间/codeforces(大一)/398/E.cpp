#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}


LL n,m;
LL c[N],k[N],w[N];
bool b[N];
LL i,j;
LL ans;

struct node{
	LL n,i;
	node(LL nn,LL ii){
		n=nn;i=ii;
	}
	bool operator <(const node &x) const{
		return n<x.n||(n==x.n&&i<x.i);
	}
};

priority_queue<node> v;
int main()
{
	scanf("%I64d%I64d",&n,&m);
	REP(i,n){
		scanf("%I64d",c+i);
		k[i]=c[i]%100;
		c[i]/=100;
	}
	REP(i,n) scanf("%I64d",w+i);
	REP(i,n){
		if (k[i]) v.push(node(-w[i]*(100-k[i]),i));
		m-=k[i];
		if (m<0){
			m+=100;
			ans-=v.top().n;
			b[v.top().i]=1;
			v.pop();
		}
	}
	printf("%I64d\n",ans);
	REP(i,n)
		if (b[i]) printf("%I64d 0\n",c[i]+1);
		else printf("%I64d %I64d\n",c[i],k[i]);
}
/*
*/
