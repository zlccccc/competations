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
const LL maxn=4e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
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

vector<ll> Vx,Vy;
struct node{
	int x1,x2,y1,y2,c;
}A[maxn];
int fa[maxn];
inline int getid(int x,int y) {
	return x*Vy.size()+y+1;
}
inline int getfa(int x) {
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
bool inside(node &x,node &y){
	return y.x1<=x.x1&&x.x2<=y.x2&&y.y1<=x.y1&&x.y2<=y.y2;
}
struct _edge{
	int x,y,len;
}edge[maxn]; int etot;
void addedge(int x,int y,int len){
	edge[etot].x=x; edge[etot].y=y;
	edge[etot].len=len; etot++;
}
int MAX[307][307],R[307][307],D[307][307];//inside
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,i,j,k;
		scanf("%d",&n);
		Vx.clear(); Vy.clear();
		FOR(i,1,n) {
			scanf("%d%d%d%d%d",&A[i].x1,&A[i].y1,&A[i].x2,&A[i].y2,&A[i].c);
			Vx.push_back(A[i].x1);
			// Vx.push_back(A[i].x2); 
			Vx.push_back(A[i].x2+1);
			Vy.push_back(A[i].y1);
			// Vy.push_back(A[i].y2);
			Vy.push_back(A[i].y2+1);
		} sort(Vx.begin(), Vx.end());
		sort(Vy.begin(), Vy.end());
		Vx.erase(unique(Vx.begin(), Vx.end()),Vx.end());
		Vy.erase(unique(Vy.begin(), Vy.end()),Vy.end());
		int cnt=Vx.size()*Vy.size();
		REP(i,(int)Vx.size()-1) REP(j,(int)Vy.size()-1) MAX[i][j]=R[i][j]=D[i][j]=0;
		FOR(k,1,n) {
			int ans=0; etot=0;
			FOR(i,1,cnt) fa[i]=i;
			REP(i,(int)Vx.size()-1) REP(j,(int)Vy.size()-1) {
				node que;
				que.x1=Vx[i]; que.x2=Vx[i+1]-1;
				que.y1=Vy[j]; que.y2=Vy[j+1]-1;
				if (inside(que,A[k])) max_(MAX[i][j],A[k].c);
				add_(ans,((ll)(Vx[i+1]-Vx[i])*(Vy[j+1]-Vy[j])-1)%M*MAX[i][j]%M);
				//addedge_x
				que.x1=Vx[i+1]-1; que.x2=Vx[i+1];
				que.y1=Vy[j]; que.y2=Vy[j+1]-1;
				if (inside(que,A[k])) max_(R[i][j],A[k].c);
				addedge(getid(i,j),getid(i+1,j),R[i][j]);
				//addedge_y
				que.x1=Vx[i]; que.x2=Vx[i+1]-1;
				que.y1=Vy[j+1]-1; que.y2=Vy[j+1];
				if (inside(que,A[k])) max_(D[i][j],A[k].c);
				addedge(getid(i,j),getid(i,j+1),D[i][j]);
			}
			sort(edge,edge+etot,[](const _edge &x,const _edge &y){
				return x.len>y.len;
			});
			REP(i,etot) {
				int x=getfa(edge[i].x),y=getfa(edge[i].y);
				if (x==y) continue;
				add_(ans,edge[i].len%M);
				fa[x]=y;
			}
			printf("%d\n",ans);
		}
	}
}
/*
2
3
2 2 3 3 1
1 2 2 3 2
1 1 1 3 5
1
1 1 2000000000 2000000000 1000000000
*/