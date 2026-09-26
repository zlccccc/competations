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
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL N=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,m;
struct ring{
	LL a,b,h;
};
bool cmp(ring i,ring j){
	return i.b==j.b?i.a<j.a||(i.a==j.a&&i.h<j.h):i.b<j.b;
}
ring a[N];
stack<ring> q;
LL i,j,k;
LL hmax,h;
int main(){
	cin>>n;
	REP(i,n) cin>>a[i].a>>a[i].b>>a[i].h;
	sort(a,a+n,cmp);
//	REP(i,n) printf("%d %d %d\n",a[i].a,a[i].b,a[i].h);
	hmax=0;h=0;
	rREP(i,n){
		while (!q.empty()&&!(q.top().a<a[i].b&&q.top().b>=a[i].b)){
			h-=q.top().h;
			q.pop();
		}
		q.push(a[i]);
		h+=a[i].h;
		if (h>hmax) hmax=h;
	}
	cout<<hmax;
}
/*
4
21 25 26
14 30 22
6 29 30
13 23 21
*/
