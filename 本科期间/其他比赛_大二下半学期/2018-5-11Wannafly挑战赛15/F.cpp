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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
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

int block[maxn];
int cur[maxn],cnt[maxn];
void add(int x){
    if (!cur[x]) cnt[block[x]]++;
    cur[x]++;
}
void del(int x){
    cur[x]--;
    if (!cur[x]) cnt[block[x]]--;
}
int SIZE;
int query(){
    int ret=0;
    while (cnt[ret]==SIZE) ret++;
    ret*=SIZE;
    while (cur[ret]) ret++;
    return ret;
}
struct node{
    int l,r;
}Q[maxn];
int L,R;
bool cmp(node A,node B){
    if (block[A.r]==block[B.r]) return A.l<B.l;
    else return block[A.r]<block[B.r];
}
vector<int> edge[maxn];
int SG[maxn];
int main() {
    int n,m,k,i;
    scanf("%d%d%d",&n,&m,&k);
    REP(i,m){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
    }
    SIZE=sqrt(n);if (!SIZE) SIZE=1;
//    SIZE=100;
    FOR(i,1,n) block[i]=i/SIZE;
//    add(0);
    FOR(i,1,n){
        for (int v:edge[i]) del(SG[v]);
        SG[i]=query(); add(SG[i]);
        for (int v:edge[i]) add(SG[v]);
    }FOR(i,1,n) del(SG[i]);
//    FOR(i,1,n) printf("%d ",SG[i]);puts("");
    REP(i,k){
        scanf("%d%d",&Q[i].l,&Q[i].r);
    }sort(Q,Q+k,cmp);
    L=1;R=0;
    int ans=0;
    REP(i,k){
        while (L<Q[i].l) {del(SG[L]);L++;}
        while (R>Q[i].r) {del(SG[R]);R--;}
        while (L>Q[i].l) {L--;add(SG[L]);}
        while (R<Q[i].r) {R++;add(SG[R]);}
        ans^=query();
//        printf("%d-%d:%d\n",L,R,query());
    }if (ans) puts("Alice");
    else puts("Bob");
}
/*


5 2 3
4 3
5 1
1 3
4 5
1 2
*/
