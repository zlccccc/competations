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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,i,N;
stack<int> S;
int MAX[maxn],a[maxn];
int main(){
	scanf("%d",&n);N=n;
	FOR(i,1,n) scanf("%d",&a[i]),MAX[i]=a[i];
	rFOR(i,1,n-1) MAX[i]=max(MAX[i],MAX[i+1]);
	FOR(i,1,n){
		while (S.size()&&S.top()>MAX[i]){
			printf("%d",S.top());S.pop();
			if (--N) putchar(' ');
		}S.push(a[i]);
	}while (S.size()){
		printf("%d",S.top());S.pop();
		if (--N) putchar(' ');
	}
}
/*
*/
