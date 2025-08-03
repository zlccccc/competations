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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void multi(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod(T &A,ll B=M) {A%=M;}
template<typename T>inline void maxi(T &A,T B) {(A<B)&&(A=B);}
template<typename T>inline void mini(T &A,T B) {(A>B)&&(A=B);}
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
 
struct node{
    int x,y,cnt;
    node(int _x,int _y,int _cnt):x(_x),y(_y),cnt(_cnt){};
};
vector<node> P[maxn];
int pool[maxn*8],*st;
int* A[maxn];
int cnt[maxn];
inline int lowbit(int x){return x&-x;}
void update(int x,int val){
    // printf("update: %d  %d\n",x,val);
    for (;x<=m+1;x+=lowbit(x)) cnt[x]+=val;
}
int query(int x){
    // printf("query: %d\n",x);
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=cnt[x];
    return ret;
}
int TaskA() {
    int i,j,T; st=pool;
    scanf("%d",&T);
    FOR(i,0,n*m) P[i].clear();
    FOR(i,0,n+1){A[i]=st; st+=m+2;}
    FOR(i,1,n) FOR(j,1,m) A[i][j]=0;
    FOR(i,1,n){
        int k;
        FOR(j,1,m) {
            scanf("%d",&k);
            P[k].push_back(node(i,j,250));
            P[0].push_back(node(i,j,250));
        }
    }
    FOR(i,1,T){
        int x1,x2,y1,y2,k;
        scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&k);
        x2++; y2++;
        P[k].push_back(node(x1,y1,1));
        P[k].push_back(node(x1,y2,-1));
        P[k].push_back(node(x2,y1,-1));
        P[k].push_back(node(x2,y2,1));
 
        P[0].push_back(node(x1,y1,-1));
        P[0].push_back(node(x1,y2,1));
        P[0].push_back(node(x2,y1,1));
        P[0].push_back(node(x2,y2,-1));
    }int ans=0;
    FOR(i,0,n*m){
        // printf("i=%d\n",i);
        if (!P[i].size()) continue;
        sort(P[i].begin(),P[i].end(),[](node &A,node &B){
            if (A.x!=B.x) return A.x<B.x;
            if (A.y!=B.y) return A.y<B.y;
            return A.cnt<B.cnt;
        });
        for (auto now:P[i]){
            // printf("%d: %d %d; val=%d\n",i,now.x,now.y,now.cnt);
            if (now.cnt!=250) update(now.y,now.cnt);
            else A[now.x][now.y]+=query(now.y);
        }
        for (auto now:P[i])
            if (now.cnt!=250) update(now.y,-now.cnt);
        vector<node>().swap(P[i]);
        // int i,j;FOR(i,1,n) {FOR(j,1,m) printf("%d ",A[i][j]);puts("");}
    }
    FOR(i,1,n) FOR(j,1,m) if (A[i][j]) ans++;
    printf("%d\n",ans);
    return 0;
}
void initialize() {}
int main() {
    int startTime=clock();
    //initialize
    initialize();
    debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
    Task_more_n_m();
}
/*
2 2 2
1 2
2 3
1 1 2 2 2
2 1 2 1 1
*/