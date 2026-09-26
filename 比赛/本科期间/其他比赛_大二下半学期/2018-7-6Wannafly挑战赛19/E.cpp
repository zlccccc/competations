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
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

//mdzz读错题意了
struct node {
    int to,cap,cost,rev;
    node(int t=0,int c=0,int n=0,int r=0):
        to(t),cap(c),cost(n),rev(r) {}
};
vector<node> edge[maxn];
void addedge(int from,int to,int cap,int cost) {
    edge[from].push_back(node(to,cap,cost,edge[to].size()));
    edge[to].push_back(node(from,0,-cost,edge[from].size()-1));
}
int dis[maxn];
bool mark[maxn];
int pre_v[maxn],pre_e[maxn];
deque<int> Q;
pair<int,int> mincostflow(int s,int t,int f) {
    int ret=0,d;
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
            REP(i,(int)edge[v].size()) {
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
        if (dis[t]==INF) break;
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
    return make_pair(INF-f,ret);
}
int len[1<<17|7];
inline int get(string A){
    int ret=0;
    for (auto now:A) ret=ret*2+now-'0';
    return ret;
}
int rev[18][1<<17|7];//reverse
void bfs(string A){
    int i,j,k;
    REP(i,(1<<(A.size()+1))) len[i]=2000;
    queue<int> Q;
    Q.push(get(A)); len[get(A)]=0;
    while (Q.size()){
        int x=Q.front(); Q.pop();
        REP(i,(int)A.size()) rep(j,i+1,(int)A.size()){
            int nxt=x,all=((1<<(j-i+1))-1)<<i;
            nxt&=~all;
            nxt|=rev[j-i+1][(x&all)>>i]<<i;
            if (len[nxt]!=2000) continue;
            else len[nxt]=len[x]+1,Q.push(nxt);
//            REP(k,(int)A.size()) printf("%d",(x>>k)&1); putchar(' ');
//            REP(k,(int)A.size()) printf("%d",(all>>k)&1);
//            printf(" -(%d to %d)->  ",i,j);
//            REP(k,(int)A.size()) printf("%d",(nxt>>k)&1);
//            printf("  (%d); cnt=%d \n",j-i+1,len[x]);
        }
    }
}
string A[107],B[107];
int delA[107],changeA[107];
int delB[107],changeB[107];
int TaskA(){
    int n,m;
    int i,j;
    cin>>n; FOR(i,1,n) cin>>A[i];
    cin>>m; FOR(i,1,m) cin>>B[i];
    FOR(i,1,n) cin>>delA[i];
    FOR(i,1,m) cin>>delB[i];
    FOR(i,1,n) cin>>changeA[i];
    FOR(i,1,m) cin>>changeB[i];
    int s=n+m+1,t=n+m+2,ans=0;
    FOR(i,1,n) ans+=delA[i];
    FOR(i,1,m) ans+=delB[i];
    ans-=2000*min(n,m);
    FOR(i,1,n) {
        bfs(A[i]);
        FOR(j,1,m){
            int val=delA[i]+delB[j];
            if (A[i].length()==B[j].length())
                val=min(val,min(changeA[i],changeB[j])*len[get(B[j])]);
            addedge(i,n+j,1,2000-(delA[i]+delB[j])+val);
        }
    }FOR(i,1,n) addedge(s,i,1,0);
    FOR(i,1,m) addedge(i+n,t,1,0);
    printf("%d\n",ans+mincostflow(s,t,INF).second);
    return 0;
}
void initialize(){
    int i,j,k,t;
    FOR(t,2,16){
        int len=1<<t;
        rev[t][len-1]=len-1;
        for (i=1,j=len/2;i<len-1;i++){
            rev[t][i]=j; rev[t][j]=i;
//            if (i<j) swap(A[i],A[j]);
            k=len/2;
            while(j>=k){
                j-=k;
                k/=2;
            }if (j<k) j+=k;
        }
    }
}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
