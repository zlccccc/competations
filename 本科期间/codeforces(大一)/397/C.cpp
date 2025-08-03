#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e6;
const LL N=1e6;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

LL a,b;
LL n,m;
LL i,j,k;


int main()
{
	cin>>k>>a>>b;
	if (b/k==0&&a%k!=0) printf("-1");
	else if (a/k==0&&b%k!=0) printf("-1");
	else cout<<a/k+b/k;
	return 0;
}
/*
*/
