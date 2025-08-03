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
const LL maxn=1000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
int n,m,k,i,j;
char a[maxn][maxn];
struct node{
	int x,y,d;
	node (int _x,int _y,int _d):x(_x),y(_y),d(_d){};
	bool operator < (const node &a) const{
		if (d!=a.d) return d>a.d;
		if (x!=a.x) return x<a.x;
		if (y!=a.y) return y<a.y;
	}
};
priority_queue<node> Q;
set<int> X[maxn],Y[maxn];
int x1,x2,y1,y2;
inline void del(int x,int y){
	X[x].erase(y);Y[y].erase(x);
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	FOR(i,1,n) scanf("%s",a[i]+1);
	FOR(i,1,n){
		FOR(j,1,m){
			X[i].insert(j);
			Y[j].insert(i);
		}
	}
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	Q.push({x1,y1,0});
	del(x1,y1);
	while (Q.size()){
		auto now=Q.top();Q.pop();
		if (now.x==x2&&now.y==y2) return 0*printf("%d",now.d);
		while(1){
			auto it=X[now.x].upper_bound(now.y);
			if (it==X[now.x].end()||*it>now.y+k||a[now.x][*it]!='.') break;
			Q.push(node(now.x,*it,now.d+1));del(now.x,*it);
		}
		while(1){
			auto it=X[now.x].lower_bound(now.y);
			if (it==X[now.x].begin()||*(--it)<now.y-k||a[now.x][*it]!='.') break;
			Q.push(node(now.x,*it,now.d+1));del(now.x,*it);
		}
		while(1){
			auto it=Y[now.y].upper_bound(now.x);
			if (it==Y[now.y].end()||*it>now.x+k||a[*it][now.y]!='.') break;
			Q.push(node(*it,now.y,now.d+1));del(*it,now.y);
		}
		while(1){
			auto it=Y[now.y].lower_bound(now.x);
			if (it==Y[now.y].begin()||*(--it)<now.x-k||a[*it][now.y]!='.') break;
			Q.push(node(*it,now.y,now.d+1));del(*it,now.y);
		}
	}
	puts("-1");
}
/*
*/
