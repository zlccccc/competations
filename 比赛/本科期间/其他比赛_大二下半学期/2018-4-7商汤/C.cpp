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
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

void fwt(int *A,int len,int inv){
	int i,j,k;
	for(i=2;i<=len;i<<=1){
		for(j=0;j<len;j+=i){
			for(k=j;k<j+i/2;k++){
				if (inv==1){
					LL a=A[k],b=A[k+i/2];
					A[k]=a+b;
					A[k+i/2]=a-b;
				//xor:a[k]=x+y,a[k+i/2]=(x-y+mod)%mod;
				//and:a[k]=x+y;
				//or:a[k+i/2]=x+y;
				}else{
					LL a=A[k],b=A[k+i/2];
					A[k]=(a+b)/2;
					A[k+i/2]=(a-b)/2;
				//xor:a[k]=(x+y)/2,a[k+i/2]=(x-y)/2;
				//and:a[k]=x-y;
				//or:a[k+i/2]=y-x;
				}
			}
		}
	}
}
vector<int> ans;
int cnt[64],C[64];
int solve(){
    int n,i,j;
    scanf("%d",&n);
    REP(i,64) scanf("%d",&cnt[i]),C[i]=cnt[i];
    static int x=0;
    printf("Case #%d: ",++x);
    REP(i,64) if (cnt[i]<0) return 0*puts("-1");
    fwt(cnt,64,1);
//    REP(i,64) printf("%d ",cnt[i]);puts("");
    REP(i,64){
        rep(j,-64,64)
            if (j*j*j==cnt[i]) break;
        if (j*j*j==cnt[i]) cnt[i]=j;
        else return 0*puts("-1");
    }fwt(cnt,64,-1);
    ans.clear();
    REP(i,64) {
        if (cnt[i]<0) return 0*puts("-1");
        REP(j,cnt[i]) ans.push_back(i);
    }
    if (ans.size()!=n) return 0*puts("-1");
    for (int i:ans) for (int j:ans) for (int k:ans) C[i^j^k]--;
    REP(i,64) if (C[i]) return 0*puts("-1");
    REP(i,ans.size()) printf("%d%c",ans[i]," \n"[i==ans.size()-1]);
    return 0;
}
const int g=50;
int f[g],t[1<<10];
int main() {
    int i,j,k;
//    REP(i,g) f[i]=rand()&63;sort(f,f+g);
//    REP(i,g) printf("%d ",f[i]);puts("");
//    REP(i,g) REP(j,g) REP(k,g) t[f[i]^f[j]^f[k]]++;
////    REP(i,(1<<10)) if (t[i]) printf("%d : %d\n",i,t[i]);
//    printf("%d\n",g);REP(i,64) printf("%d ",t[i]);
	int T;
	scanf("%d",&T);
	while (T--) solve();
	return 0;
}
/*
*/
