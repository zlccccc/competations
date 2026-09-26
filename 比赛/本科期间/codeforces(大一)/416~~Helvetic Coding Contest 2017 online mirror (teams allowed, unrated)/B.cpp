#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
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
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


priority_queue<pair<int,int> > Q;
set<int> S;
int a[maxn],pos[maxn],nxt[maxn];
int ans;
int i,n,m,k;
int main(){
	scanf("%d%d",&n,&k);
	REP(i,n) scanf("%d",&a[i]);
	FOR(i,1,n) nxt[i]=-1;
	rREP(i,n){
		if (nxt[a[i]]==-1) pos[i]=INF;
		else pos[i]=nxt[a[i]];
		nxt[a[i]]=i;
	}
//	REP(i,n) printf("%3d",i);puts("");
//	REP(i,n) printf("%3d",pos[i]);puts("");
	REP(i,n){
		if (!S.count(a[i])){
			if (S.size()>=k){
				while (S.size()&&!(S.count(Q.top().second))) Q.pop();
//				printf("%d %d\n",Q.top().second,i);
				S.erase(Q.top().second);
				Q.pop();
			}
			ans++;
			S.insert(a[i]);
		}
		Q.push(make_pair(pos[i],a[i]));
	}
	printf("%d",ans);
}
/*
20 5
2 8 5 1 10 5 9 9 3 5 6 6 2 8 2 2 6 3 8 7 
*/
