#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
int i,j,k,t;
char a[100007],now;
int num[300];
stack<char> S;
int main()
{
	scanf("%s",&a);
	n=strlen(a);
	REP(i,n) num[a[i]]++;
	now='a';
	REP(i,n){
		num[a[i]]--;
		if (a[i]==now) printf("%c",a[i]);
		else S.push(a[i]);
		while (num[now]==0) now++;
		while (S.size()&&S.top()<=now) printf("%c",S.top()),S.pop();
	}
	while (S.size()) printf("%c",S.top()),S.pop();
}
