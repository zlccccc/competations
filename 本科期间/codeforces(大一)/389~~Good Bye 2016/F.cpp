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
const LL maxn=1<<7|7;
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

int ans,cnt;
vector<int> A[maxn];
void get(int x){
    if (A[x].size()) return;
    if (ans) return;
    cnt++; if (cnt==17) ans=x;
    if (ans) return;
    printf("? %d\n",x);
    fflush(stdout);
    int n,i;
    scanf("%d",&n);
    REP(i,n){
        int y; scanf("%d",&y);
        A[x].push_back(y);
    }//random_shuffle(A[x].begin(),A[x].end());
    if (A[x].size()==2) ans=x;
}
int dfs(int x,int f){
    get(x);
    for (int v:A[x]) if (v!=f) return dfs(v,x)+1;
    return 1;
}int getnxt(int x,int f,int dep){
    if (dep==1) return x;
    for (int v:A[x]) if (v!=f) return getnxt(v,x,dep-1);
    return 0;
}
int TaskA(){
    int n,m,i;
    fflush(stdout);
    scanf("%d",&n);//guaranteed n!=1
    m=1<<n; ans=0; cnt=0;
    REP(i,m) A[i].clear();
    int x=1; get(x);
    if (A[x].size()==1) x=A[x][0];
    dfs(x,0);//first
    if (ans) return 0*printf("! %d\n",ans);
    while(1){
        pair<int,int> l_l,L_L; get(x);
        for (int v:A[x]) if (A[v].size()) {l_l=make_pair(dfs(v,x),v);break;}
        for (int v:A[x]) if (!A[v].size()) {L_L=make_pair(dfs(v,x),v);break;}
        if (ans) return 0*printf("! %d\n",ans);
        if (l_l>L_L) swap(l_l,L_L);
        if (L_L.first!=l_l.first) x=getnxt(L_L.second,x,(L_L.first-l_l.first)/2);
//        debug("get %d %d %d (%d)\n",x,l_l.first,L_L.first,(l_l.first+L_L.first)/2);
        for (int v:A[x]) if (!A[v].size()) {x=v; break;}
        if ((l_l.first+L_L.first)/2+1>n/2) break;
    }//deputs("start bfs");
    queue<int> Q; Q.push(x);
    while (1){
        int x=Q.front(); get(x); Q.pop();
        for (int v:A[x]) if (!A[v].size()) Q.push(v);
        if (ans) return 0*printf("! %d\n",ans);
    }
    return 0;
}
void initialize(){}
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
1 2
3 1 3 4
1 2
3 2 5 7
3 4 6 100
1 5

3 4 8 11
3 7 9 100
3 8 10 100
1 9

3 7 12 16
3 11 13 100
3 12 14 100
3 13 15 100
1 14

*/
