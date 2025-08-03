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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

struct node {
    LL to,cap,cost,rev;
    node(int t=0,int c=0,int n=0,int r=0):
        to(t),cap(c),cost(n),rev(r) {}
};
vector<node> edge[maxn];
void addedge(int from,int to,LL cap,LL cost) {
    edge[from].push_back(node(to,cap,cost,edge[to].size()));
    edge[to].push_back(node(from,0,-cost,edge[from].size()-1));
}
int V;
LL dis[maxn];
bool mark[maxn];
int pre_v[maxn],pre_e[maxn];
deque<int> Q;
pair<LL,LL> mincostflow(int s,int t,LL f) {
    LL ret=0,d;
    int i,v;
    while (f) {
        memset(dis,0x3f,sizeof(dis));
        memset(mark,0,sizeof(mark));
        while (Q.size()) Q.pop_front();
        dis[s]=0;
        Q.push_back(s);
        while (Q.size()) {
            v=Q.front();
            mark[v]=0;
            Q.pop_front();
            REP(i,edge[v].size()) {
                node &e=edge[v][i];
                if (e.cap>0&&dis[e.to]>dis[v]+e.cost) {
                    dis[e.to]=dis[v]+e.cost;
                    pre_v[e.to]=v;
                    pre_e[e.to]=i;
                    if (!mark[e.to]) {
                        if (Q.empty()||dis[Q.front()]<dis[e.to])
                            Q.push_back(e.to);
                        else Q.push_front(e.to);
                        mark[e.to]=1;
                    }
                }
            }
        }
        if (dis[t]==INFF) break;
        d=f;
        for (v=t; v!=s; v=pre_v[v])
            d=min(d,edge[pre_v[v]][pre_e[v]].cap);
        f-=d;
        ret+=d*dis[t];
        for (v=t; v!=s; v=pre_v[v]) {
            node &e=edge[pre_v[v]][pre_e[v]];
            e.cap-=d;
            edge[v][e.rev].cap+=d;
        }
        if (d==0) break;
    }
    return make_pair(INFF-f,ret);
}
int _x[107][4],_y[4];
int TaskA() {
	int i,j,k,_j;
	scanf("%d",&n);
	FOR(i,1,n) REP(j,4) scanf("%d",&_x[i][j]);
	FOR(i,1,n) {
		REP(j,4) scanf("%d",&_y[j]);
		FOR(k,1,n){
			int cnt=0;
			REP(j,4) {
				int now=1;
				REP(_j,4) if (_x[k][_j]==_y[j]) now=0;
				cnt+=now;
			} addedge(k,i+n,1,cnt);
		}
	}int s,t; s=n+n+1; t=n+n+2; V=n+n+2;
	FOR(i,1,n) addedge(s,i,1,0);
	FOR(i,1,n) addedge(i+n,t,1,0);
	auto ans=mincostflow(s,t,INFF);
	// printf("%lld %lld\n",ans.first,ans.second);
	printf("%lld\n",ans.second);
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
2
1 2 5 6
3 4 7 8
1 2 7 8
3 4 5 6
*/
