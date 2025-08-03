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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
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

int n;
int A[1607][1607];
int sum[1607];
inline int lowbit(int x){return x&-x;}
int get(int x){
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=sum[x];
    return ret;
}
int get(int l,int r){
//    printf("get: %d-%d:\n",l,r);
    return get(r)-get(l-1);
}
int add(int x,int n,int val){
//    printf("ADD: %d: (n=%d)\n",x,n);
    for (;x<=n;x+=lowbit(x)) sum[x]+=val;
}
char c[2];
int nxt[1607],pre[1607];
vector<int> del[1607];
int Solve(int n){
    int i,ret=0;
    FOR(i,1,n) sum[i]=0,del[i].clear();
    FOR(i,1,n) {
        if (nxt[i]){
            ret+=get(i-pre[i]+1,i);
            add(i,n,1);
            del[i+nxt[i]].push_back(i);
        }for (int v:del[i]) add(v,n,-1);
    }
    return ret;
}
int L[1607][1607],D[1607][1607],U[1607][1607],R[1607][1607];
int solve(int x,int n,int m){
    int i,j,k,ret=0;
    FOR(i,1,n) FOR(j,1,m) if (A[i][j]==x){
        D[i][j]=D[i-1][j]+1;
        R[i][j]=R[i][j-1]+1;
    }else D[i][j]=R[i][j]=0;
    rFOR(i,1,n) rFOR(j,1,m) if (A[i][j]==x){
        U[i][j]=U[i+1][j]+1;
        L[i][j]=L[i][j+1]+1;
    }else U[i][j]=L[i][j]=0;
    FOR(i,1,n) FOR(j,1,m){
        D[i][j]=min(D[i][j],R[i][j]);
        U[i][j]=min(U[i][j],L[i][j]);
    }
//    FOR(i,1,n){
//        FOR(j,1,m) printf("%d ",D[i][j]);puts("");
//    }
    FOR(i,1,n){
        FOR(j,1,m) if (i==1||j==1){
            for (k=1;i+k-1<=n&&j+k-1<=m;k++){
                nxt[k]=U[i+k-1][j+k-1];
                pre[k]=D[i+k-1][j+k-1];
            }k--;
            ret+=Solve(k);
//            printf("%d %d\n",i,j);
//            int t;
//            FOR(t,1,k) printf("%d ",nxt[t]);puts("  <- nxt");
//            FOR(t,1,k) printf("%d ",pre[t]);puts("  <- pre");
//            printf("ret=%d\n",ret);
        }
    }return ret;
}
void solve(){
    int n,m,i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) FOR(j,1,m){
        scanf("%s",c);
        if (c[0]=='G') A[i][j]=1;
    }
    printf("%d\n",solve(1,n,m));
    printf("%d\n",solve(0,n,m));
}
int main() {
    int i,j,k;
    solve();
    return 0;
}
/*
*/
