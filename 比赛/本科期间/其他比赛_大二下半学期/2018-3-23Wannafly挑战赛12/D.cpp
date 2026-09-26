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
#include <cstdlib>
#include <iomanip>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
    int x,y;
}P[maxn];
bool cmp(node A,node B){
    if (A.x!=B.x) return A.x<B.x;
    return A.y<B.y;
}
int T;
int n,m,C,HC;
int i,j,k;
LL ans;
inline LL get1(int x){
    return (LL)x*(x+1)/2%M;
}
int main(){
    scanf("%d%d%d",&n,&m,&C);
    FOR(i,1,C){
        scanf("%d%d",&P[i].x,&P[i].y);
    }sort(P+1,P+1+C,cmp);
    ans=(LL)n*(n+1)/2%M*((LL)m*(m+1)/2%M)%M;
    FOR(i,1,C){
        int D=1,U=m;
        rFOR(j,0,i-1){
            ans=(ans-(LL)(P[j+1].x-P[j].x)*(n-P[i].x+1)%M
                        *(P[i].y-D+1)%M*(U-P[i].y+1))%M;
            if (P[j].y>=P[i].y) U=min(U,P[j].y-1);
            if (P[j].y<=P[i].y) D=max(D,P[j].y+1);
            if (U<P[i].y||D>P[i].y) break;
        }
    }
    printf("%lld\n",(ans%M+M)%M);
}
/*
*/
