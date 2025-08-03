#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x7f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=1e-7;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

LL n,m,mm;
int T,len,i;
char a[maxn];
inline LL lowbit(LL x){return x&(-x);}
int main(){
	cin>>n>>T;
	while (T--){
		scanf("%d",&m);
		scanf("%s",&a);
		len=strlen(a);
		REP(i,len){
			if (a[i]=='U'){
				mm=(m^lowbit(m))|(lowbit(m)<<1);
				if (mm<=n) m=mm;
			}
			if (a[i]=='L') m=m-(lowbit(m)>>1);
			if (a[i]=='R') m=m+(lowbit(m)>>1);
		}
		printf("%I64d\n",m);
	}
}
/*
*/
