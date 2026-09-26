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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int nxt[maxn*30][2],tot,cnt[maxn*30];
void ins(LL x){
    int now=0,i;
    rREP(i,30){
        int c=(x>>i)&1;
        if (!nxt[now][c]) nxt[now][c]=++tot;
        now=nxt[now][c];
        cnt[now]++;
    }
}LL get(LL x){
    int now=0,i;LL ret=0;
    rREP(i,30){
        int c=(x>>i)&1;
        if (nxt[now][c]&&cnt[nxt[now][c]]){
            now=nxt[now][c];
            cnt[now]--;
        }else{
            ret|=(1<<i);
            now=nxt[now][c^1];
            cnt[now]--;
        }
    }return ret;
}
int n,m;
int i,j,k;
LL A[maxn],B[maxn];
int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%I64d",&A[i]);
    FOR(i,1,n) scanf("%I64d",&B[i]),ins(B[i]);
    FOR(i,1,n) printf("%I64d ",get(A[i]));
}
/*
*/
