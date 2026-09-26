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
#include <bitset>
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
int len;
char a[maxn];
bitset<5007> f[5007],g[5007];
int ans;
int main(){
    scanf("%s",a);
    len=strlen(a);
    REP(i,len){
        int cnt1=0,cnt2=0;
        rep(j,i,len){
            if (a[j]=='?'||a[j]=='(') cnt1++;
            else if (a[j]==')') cnt2++;
            if (cnt1<cnt2) break;
            if (!((cnt2-cnt1)&1)) f[i][j]=1;
        }cnt1=cnt2=0;
        rREP(j,i+1){
            if (a[j]=='?'||a[j]==')') cnt1++;
            else if (a[j]=='(') cnt2++;
            if (cnt1<cnt2) break;
            if (!((cnt2-cnt1)&1)) g[j][i]=1;
        }
    }REP(i,len) rep(j,i,len) ans+=f[i][j]&g[i][j];
//    REP(i,len) rep(j,i,len) if (f[i][j]&g[i][j]) printf("%d %d\n",i,j);
    printf("%d\n",ans);
}
/*
*/
