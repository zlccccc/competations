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
#define rep(I,pos,N) for (I=pos;I<N;I++)
#define rrep(I,pos,N) for (I=N-1;I>=pos;I--)
#define FOR(I,pos,N) for (I=pos;I<=N;I++)
#define rFOR(I,pos,N) for (I=N;I>=pos;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=4e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

#define x x_x
#define y y_y
LL n,m,q;
map<LL,LL> S;
map<LL,LL> ans;
LL i,j,k,t;
LL cnt,num;
LL a[maxn],b[maxn],c[maxn];
int main(){
	scanf("%I64d",&n);
	REP(j,n){
		scanf("%I64d",&t);
		S.clear();num=0;
		a[cnt]=t;b[cnt]=1;cnt++;
		REP(i,cnt){
			k=gcd(t,a[i]);
			if (!S.count(k)) a[num++]=k;
			S[k]+=b[i];
		}
		cnt=num;
		REP(i,cnt){
			b[i]=S[a[i]];
			ans[a[i]]+=b[i];
		}
//		REP(i,cnt) printf("%d ",a[i]);puts("////a");
//		REP(i,cnt) printf("%d ",b[i]);puts("////b");
	}
	scanf("%I64d",&m);
	REP(i,m){
		scanf("%I64d",&t);
		printf("%I64d\n",ans[t]);
	}
}
/*
*/
