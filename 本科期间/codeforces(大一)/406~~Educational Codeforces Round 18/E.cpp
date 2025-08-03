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
const LL maxn=600+7;
const double eps=1e-7;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

int n,m,mm;
int i,k,t;
LL ans;
int a[maxn];
inline LL lowbit(LL x){return x&(-x);}
bool solve(int t){
	int i;
	if (t==0) return 0;
	if (t==1) return 1;
	REP(i,n) if (a[i]!=t+1&&a[i]%t>a[i]/t) return 0;
	return 1;
}
int main(){
	scanf("%d",&n);
	REP(i,n) scanf("%d",&a[i]);
	sort(a,a+n);
	t=a[0];k=1;
	while (!solve(t+1)&&!solve(t)&&!solve(t-1)){
		k++;
		t=a[0]/k;
	}
	t++;
	while (!solve(t)) t--;
	while (solve(t+1)) t++;
	REP(i,n) ans+=a[i]/(t+1)+(a[i]%(t+1)!=0);
	printf("%I64d",ans);
}
/*
*/
