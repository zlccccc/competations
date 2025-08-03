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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2000+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B) {A+=B; (A>=M) &&(A-=M);}
inline void mul(ll &A,ll B) {(A*=B)%=M;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m;
char S[maxn];
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",S)) TaskA();}

struct node {
    int to; ll cap; int next;
    node(int t=0,ll c=0,int n=0):to(t),cap(c),next(n) {};
} edge[maxn*2000];
int head[maxn],tot;
void addedge(int from,int to,ll cap,ll rcap=0) {
    edge[tot]=node(to,cap,head[from]); head[from]=tot++;
    edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
}
queue<int> Q;
int gap[maxn],dep[maxn],cur[maxn];
void bfs(int s,int t) {
    memset(dep,0xff,sizeof(dep));
    memset(gap,0,sizeof(gap));
    gap[0]=1; dep[t]=0; Q.push(t);
    while (Q.size()) {
        int u=Q.front(); Q.pop();
        for (int i=head[u]; ~i; i=edge[i].next) {
            int v=edge[i].to;
            if (dep[v]!=-1) continue;
            Q.push(v); dep[v]=dep[u]+1;
            gap[dep[v]]++;
        }
    }
}
ll sap(int s,int t,int n) {
	static int S[maxn];
    bfs(s,t);
    memcpy(cur,head,sizeof(head));
    int top=0,u=s; ll ret=0;
    while (dep[s]<n) {
        if (u==t) {
            ll MIN=INFF; int inser=0,i;
            REP(i,top) if (MIN>edge[S[i]].cap)
                MIN=edge[S[i]].cap,inser=i;
            REP(i,top) {
                edge[S[i]].cap-=MIN; edge[S[i]^1].cap+=MIN;
            } ret+=MIN; top=inser; u=edge[S[top]^1].to;
            continue;
        } bool flag=0; int v;
        for (int i=cur[u]; ~i; i=edge[i].next) {
            v=edge[i].to;
            if (edge[i].cap&&dep[v]+1==dep[u]) {
                flag=1; cur[u]=i; break;
            }
        } if (flag) {
            S[top++]=cur[u]; u=v; continue;
        } int MIN=n;
        for (int i=head[u]; ~i; i=edge[i].next) {
            v=edge[i].to;
            if (edge[i].cap&&dep[v]<MIN)
                MIN=min(MIN,dep[v]),cur[u]=i;
        } gap[dep[u]]--;
        if (ret>INFF) return ret;//not okay
        if (!gap[dep[u]]) return ret;
        dep[u]=MIN+1; gap[dep[u]]++;
        if (u!=s) u=edge[S[--top]^1].to;
    } return ret;
}
inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}
struct Point{
	double x,y;
    Point (ll x = 0 , ll y = 0) : x(x) , y(y) {}
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    double operator % (const Point& R) const {
        return x * R.x + y * R.y;
    }
    double len() {
        return sqrt(*this % *this);
    }
    double operator ^ (const Point& R) const {
        return x * R.y - y * R.x;
    }
    bool operator == (const Point& R) const {
        return dcmp(x - R.x) == 0 && dcmp(y - R.y) == 0;
    }
}A[maxn],B[maxn];
double DistancePointToSegment(Point P , Point A , Point B) {
    if (A == B) return (P - A).len();
    Point v1 = B - A , v2 = P - A , v3 = P - B;
    if (dcmp(v1 % v2) < 0) return v2.len();
    if (dcmp(v1 % v3) > 0) return v3.len();
    return fabs(v1 ^ v2) / v1.len();
}
double R[maxn];
bitset<1007> id[maxn],now;
int TaskA(){
	int i;
	int n,m,k;
	memset(head,-1,sizeof(head)); tot=0;
	scanf("%d%d%d",&n,&m,&k);
	FOR(i,1,n) {
		ll val;
		scanf("%lf%lf%lld",&A[i].x,&A[i].y,&val);
		addedge(n+m+1,i,val);
		id[i][i]=1;
	}FOR(i,1,k) scanf("%lf%lf%lf",&B[i].x,&B[i].y,&R[i]);
	FOR(i,1,m){
		Point P; now.reset();
		int s,j; ll lim;
		scanf("%lf%lf",&P.x,&P.y);
		scanf("%d%lld",&s,&lim);
		REP(j,s){
			int _k;
			scanf("%d",&_k);
			bool okay=1; int t;
			FOR(t,1,k) if (DistancePointToSegment(B[t],P,A[_k])<R[t]+eps) okay=0;
			if (!okay) continue;
			now|=id[_k]; id[_k]=now;
		}FOR(j,1,n) if (now[j]) addedge(j,i+n,lim);
		addedge(i+n,n+m+2,lim); 
	}printf("%lld\n",sap(n+m+1,n+m+2,n+m+2));
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
3 3 1
1 1 500000000000
4 5 0
9 2 700000000000
2 2 1
4 4 2 300000000000 1 2
0 9 2 300000000000 1 2
9 1 2 800000000000 3 2
*/
