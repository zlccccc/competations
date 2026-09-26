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
int i,j,k;
char s[maxn];
vector<int> have[maxn];
LL inv[1000002];
LL fac[1000002];
LL C(int n,int m){
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
LL ans;
int f[maxn],t[maxn];
int now=0;
int g[maxn];
int main(){
	fac[0]=1;
	FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;
    scanf("%s%d",s,&k);
    if (k==0) return 0*puts("1");
    n=strlen(s);
    FOR(i,1,1000) f[i]=f[i>>1]+(i&1);
    FOR(i,2,1000) t[i]=t[f[i]]+1;
    FOR(i,1,1000) have[t[i]].push_back(i);
    rREP(i,n) g[i]=g[i+1]+s[i]-'0';
    REP(i,n){
        if (s[i]=='1'){
            for (int v:have[k-1]){
                if (0<=v-now&&v-now<=n-i-1){
//                    if (v-now==g[i+1]&&v!=now) ans--;
//                    {ans--;printf("%d",i);};
                    (ans+=C(n-i-1,v-now))%=M;
//                    printf("pos=%d ,ans+= %d %d; ans=%d\n",i,v-now,n-i-1,ans);
                }
            }now++;
        }
    }if (k==1) ans--;
    for (int v:have[k-1]) if (v==now) (ans+=1)%=M;
    printf("%I64d\n",ans);
}
/*
*/
