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

int n,m;
int i,j,k;
char S[maxn],T[maxn];
int TA[maxn],TB[maxn],SA[maxn],SB[maxn];
char ans[maxn];
int check(int CA,int CB,int DA,int DB){
    if (CA<DA) return 0;
    if (CA==DA&&!CB&&DB) return 0;
    if ((CA-DA)%3) CB+=2;
    if (DB<CB) return 0;
    if ((DB-CB)&1) return 0;
    return 1;
}
int solve(int CA,int CB,int DA,int DB){
    int ret=check(CA,CB,DA,DB);
    printf("  %d %d %d %d; %d\n",CA,CB,DA,DB,ret);
    return ret;
}
int main(){
//    solve(2,1,0,3);
    scanf("%s%s",S+1,T+1);
    n=strlen(S+1);
    FOR(i,1,n){
        if (S[i]=='A') SA[i]=SA[i-1]+1,SB[i]=SB[i-1];
        else SB[i]=SB[i-1]+1;
    }n=strlen(T+1);
    FOR(i,1,n){
        if (T[i]=='A') TA[i]=TA[i-1]+1,TB[i]=TB[i-1];
        else TB[i]=TB[i-1]+1;
    }
    int C;
    scanf("%d",&C);
    REP(i,C){
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        int CA=min(SA[b],b-a+1),CB=SB[b]-SB[a-1];
        int DA=min(TA[d],d-c+1),DB=TB[d]-TB[c-1];
        ans[i]=check(CA,CB,DA,DB)+'0';
    }ans[C]=0;
    puts(ans);
}
/*
*/
