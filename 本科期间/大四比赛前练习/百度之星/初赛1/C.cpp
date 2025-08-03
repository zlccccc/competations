#include <sstream>
#include <fstream>
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
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1.7e5+107;
const double pi=acos(-1.0);
const double eps=0.000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

vector<int> Vx,Vy;
struct node {
	int x1,x2,y1,y2;
} A[207];
int S[407][407];
inline int getidx(int x) {
	return lower_bound(Vx.begin(),Vx.end(),x)-Vx.begin();
}
inline int getidy(int x) {
	return lower_bound(Vy.begin(),Vy.end(),x)-Vy.begin();
}
inline int getactualid(int x,int y) {
	return x*Vy.size()+y;
}

struct ENode {
	double len; int v,next;
} edge[maxn*8];
int head[maxn],tot;
void addedge(int x,int y,double length) {
	edge[++tot]=ENode{length,y,head[x]}; head[x]=tot;
	edge[++tot]=ENode{length,x,head[y]}; head[y]=tot;
}
priority_queue<pair<double,int> > Q;
double dis[maxn];
bool marked[maxn];
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int i,j,n;
		Vx.clear(); Vy.clear(); tot=0;
		FOR(i,0,402) FOR(j,0,402) S[i][j]=0;
		FOR(i,0,402*402) head[i]=-1,dis[i]=INFF,marked[i]=0;
		scanf("%d",&n);
		FOR(i,1,n) {
			scanf("%d%d%d%d",&A[i].x1,&A[i].y1,&A[i].x2,&A[i].y2);
			// A[i].x2++; A[i].y2++;//坐标轴不用++
			Vx.push_back(A[i].x1); Vy.push_back(A[i].y1);
			Vx.push_back(A[i].x2); Vy.push_back(A[i].y2);
		}
		int xa,ya,xb,yb;
		scanf("%d%d%d%d",&xa,&ya,&xb,&yb);
		Vx.push_back(xa); Vy.push_back(ya);
		Vx.push_back(xb); Vy.push_back(yb);
		sort(Vx.begin(), Vx.end());
		Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
		sort(Vy.begin(), Vy.end());
		Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
		FOR(i,1,n) {
			A[i].x1=getidx(A[i].x1); A[i].y1=getidy(A[i].y1);
			A[i].x2=getidx(A[i].x2); A[i].y2=getidy(A[i].y2);
			S[A[i].x1][A[i].y1]++;
			S[A[i].x2][A[i].y1]--;
			S[A[i].x1][A[i].y2]--;
			S[A[i].x2][A[i].y2]++;
		}
		REP(i,(int)Vx.size()) {
			REP(j,(int)Vy.size()) {
				if (i) S[i][j]+=S[i-1][j];
				if (j) S[i][j]+=S[i][j-1];
				if (i&&j) S[i][j]-=S[i-1][j-1];
				if (i) {
					int MAX=(S[i-1][j]+1);
					if (j) MAX=max(MAX,(S[i-1][j-1])+1);
					addedge(getactualid(i-1,j),getactualid(i,j),1.0*(Vx[i]-Vx[i-1])/MAX);
				} if (j) {
					int MAX=(S[i][j-1]+1);
					if (j) MAX=max(MAX,(S[i-1][j-1])+1);
					addedge(getactualid(i,j-1),getactualid(i,j),1.0*(Vy[j]-Vy[j-1])/MAX);
				}
			}
		}
		xa=getidx(xa); ya=getidy(ya);
		xb=getidx(xb); yb=getidy(yb);
		Q.push(make_pair(0,getactualid(xa,ya)));
		dis[getactualid(xa,ya)]=0;
		// REP(i,Vx.size()) {
		// 	REP(j,Vy.size()) printf("%d ",getactualid(i,j)); puts("");
		// }
		while (Q.size()) {
			auto p=Q.top(); Q.pop();
			// printf("(%f,%d)\n",p.first,p.second);
			if (marked[p.second]) continue; marked[p.second]=1;
			for (int i=head[p.second]; i!=-1; i=edge[i].next) {
				ENode &now=edge[i];
				if (dis[now.v]>dis[p.second]+now.len) {
					dis[now.v]=dis[p.second]+now.len;
					Q.push(make_pair(-dis[now.v],now.v));
				// printf("%d->%d: %f\n",p.second,now.v,dis[p.second]+now.len);
				}
			}
		}
		printf("%.5f\n",dis[getactualid(xb,yb)]);
	}
}
/*
1
1
5 5 6 6
1 1 8 8
*/