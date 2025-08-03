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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j;
char op[20],s[maxn];
bool mark[27],now[27];
int ans;
int main(){
    REP(i,26) mark[i]=1;
    scanf("%d",&n);
    int could=0;
    REP(j,n){
        scanf("%s%s",op,s);
        if (could){
            if (j!=n-1&&(op[0]=='?'||op[0]=='!')) ans++;
            continue;
        }int len=strlen(s);
        if (op[0]!='!'){
            REP(i,len) mark[s[i]-'a']=0;
        }else{
            REP(i,26) now[i]=0;
            REP(i,len) now[s[i]-'a']=1;
            REP(i,26) if (!now[i]) mark[i]=0;
        }
        REP(i,26) could+=mark[i];
        if (could!=1) could=0;
//        REP(i,26) printf("%d",mark[i]);puts("");
    }printf("%d\n",ans);
}
/*
5
! abc
. ad
. b
! cd
? c
*/
