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
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int ans;
bool O1(bool a,bool b){
	return a^b;
}
bool O2(bool a,bool b){
	return a||b; 
}
bool O3(bool a,bool b){
	return a&&b;
}
int a1,a2,a3,a4;
bool b1,b2,b3,b4;
bool c1,c2;
int d1;
string s;
int main(){
	scanf("%d%d%d%d",&a1,&a2,&a3,&a4);
	b1=O1(a1,a2);
	b2=O2(a3,a4);
	b3=O3(a2,a3);
	b4=O1(a1,a4);
	c1=O3(b1,b2);
	c2=O2(b3,b4);
	d1=O1(c1,c2);
	printf("%d %d %d %d\n",b1,b2,b3,b4);
	printf("%d %d\n",c1,c2);
	printf("%d",d1);
}
