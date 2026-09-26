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
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
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

struct node {
    int to,cap,next;
    node(int t=0,int c=0,int n=0):to(t),cap(c),next(n) {};
} edge[maxn*50];
int head[maxn],tot;
void addedge(int from,int to,int cap,int rcap=0) {
    edge[tot]=node(to,cap,head[from]); head[from]=tot++;
    edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
}
queue<int> Q;
int gap[maxn],dep[maxn],cur[maxn];
void bfs(int s,int t,int n) {
    int i;
    FOR(i,1,n) dep[i]=-1;
    FOR(i,1,n) gap[i]=0;
//    memset(dep,0xff,sizeof(dep));
//    memset(gap,0,sizeof(gap));
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
int S[maxn];
int sap(int s,int t,int n) {
    bfs(s,t,n);int i;
    FOR(i,1,n) cur[i]=head[i];
    int top=0,u=s,ret=0;
    while (dep[s]<n) {
        if (u==t) {
            int MIN=INF,inser=0,i;
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
        if (ret>INF) return ret;//not okay
        if (!gap[dep[u]]) return ret;
        dep[u]=MIN+1; gap[dep[u]]++;
        if (u!=s) u=edge[S[--top]^1].to;
    } return ret;
}
const int maxm=1e5+7;
int p[maxm],cntp;
map<int,int> id;int cnt;
map<int,int> cnt_in,cnt_out;
int A[maxm],B[maxm];
int TaskA(){
    int n,i,j,k,s,t;
    id.clear();cnt=0;cnt_in.clear();cnt_out.clear();
    memset(head,-1,sizeof(head));tot=0;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) scanf("%d",&B[i]);
    s=++cnt;t=++cnt;
    FOR(i,1,n) FOR(j,1,n){
        int g=gcd(A[i],B[j]);
        if (g==1) continue;
        if (A[i]<B[j]) cnt_in[g]++;
        if (A[i]>B[j]) cnt_out[g]++;
        for(k=1;p[k]*p[k]<=g&&k<=cntp;k++) if (g%p[k]==0) {
            if (!id[p[k]]) id[p[k]]=++cnt;
            while (g%p[k]==0) g/=p[k];
        }if (g!=1&&!id[g]) id[g]=++cnt;
    }
    for(auto now:cnt_in){
        int g=now.first,i=++cnt;
        addedge(s,i,now.second);
        for(k=1;p[k]*p[k]<=g&&k<=cntp;k++) if (g%p[k]==0) {
            addedge(i,id[p[k]],INF);
            while (g%p[k]==0) g/=p[k];
        }if (g!=1) addedge(i,id[g],INF);
    }
    for(auto now:cnt_out){
        int g=now.first,i=++cnt;
        addedge(i,t,now.second);
        for(k=1;p[k]*p[k]<=g&&k<=cntp;k++) if (g%p[k]==0) {
            addedge(id[p[k]],i,INF);
            while (g%p[k]==0) g/=p[k];
        }if (g!=1) addedge(id[g],i,INF);
    }
    printf("%d\n",sap(s,t,cnt));
    return 0;
}
void initialize(){
    int i,j;
    FOR(i,2,31623){
        if (!p[i]) p[++cntp]=i;
        for (j=i+i;j<=31623;j+=i) p[j]=1;
    }debug("primecnt=%d\n",cntp);
}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
