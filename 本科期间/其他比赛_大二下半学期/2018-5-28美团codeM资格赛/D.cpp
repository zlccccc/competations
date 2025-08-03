#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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

int n,m,k,C;
int A[507][507];
int w[507];
LL now[507],base[507];//__int128
int id[507],mark[507];
int main() {
    int i,j,_i,_j;
    scanf("%d%d%d%d",&n,&m,&k,&C);
    FOR(i,1,m) scanf("%d",&w[i]);
    FOR(i,1,n) id[i]=i;
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&A[i][j]);
    FOR(_i,1,n) FOR(_j,1,m) if (A[_i][_j]==-1){
        FOR(A[_i][_j],0,C){
            FOR(i,1,n) now[i]=0,base[i]=1;
            now[0]=now[n+1]=-1;
            FOR(j,1,m){
                int MAX=1;//base
                FOR(i,1,n) MAX=max(MAX,A[i][j]);
                FOR(i,1,m) if (i!=j) base[i]*=MAX;
            }
            FOR(j,1,m) FOR(i,1,n){
                now[i]+=A[i][j]*w[j]*base[j];
            }
            sort(id+1,id+1+n,[](int i,int j){
                return now[i]>now[j];
            });
            FOR(i,1,n){
                if (i>k&&now[id[i]]!=now[id[i-1]]) break;
                mark[id[i]]|=1;
            }rFOR(i,1,n){
                if (i<=k&&now[id[i]]!=now[id[i+1]]) break;
                mark[id[i]]|=2;
            }
        }
    }FOR(i,1,n) printf("%d\n",mark[i]);
    return 0;
}
/*
*/
