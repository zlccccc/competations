#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
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
const LL N=3e6+7;
const double eps=1e-7;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

int n,m,mn,i;
int a[N];
int main(){
	scanf("%d",&n);
    REP(i,n) scanf("%d",a+i);
    sort(a,a+n);
    m=INF;mn=0;
	REP(i,n-1) if (m>a[i+1]-a[i]) m=a[i+1]-a[i];
	REP(i,n-1) if (m==a[i+1]-a[i]) mn++;
    printf("%d %d",m,mn);
}
/*
*/
