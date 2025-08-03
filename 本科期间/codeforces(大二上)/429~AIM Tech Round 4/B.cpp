#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int val[maxn];
int nxt[maxn];
void query(int i){
	fflush(stdout);
	cout<<"? "<<i<<"\n";
	cin>>val[i]>>nxt[i];
}
int main(){
	int n,m,k,x,s,ans=INF,now;
	int i,j,pos;
	scanf("%d%d%d",&n,&pos,&x);
	srand(time(0));
	query(pos);
	if (val[pos]<ans&&val[pos]>=x) ans=val[pos];
	REP(i,min(n,1000)){
		now=((rand()<<16)|rand())%n+1;
		if (!nxt[now]) query(now);
		if (val[now]<ans&&val[now]>=x) ans=val[now];
		if (val[now]<x&&val[now]>val[pos]) pos=now;
	}
	while (nxt[pos]!=-1&&val[pos]<x){
		now=nxt[pos];
		if (!nxt[now]) query(now);
		if (val[now]<ans&&val[now]>=x) ans=val[now];
		pos=now;
	}
	if (ans==INF) ans=-1;
	cout<<"! "<<ans<<"\n";
}
/*
*/
