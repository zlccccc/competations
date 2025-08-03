#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
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
const LL N=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

LL n,k;
LL a[N];
LL i,j;
LL sum;
LL num;
map<LL,LL> s;
int main(){
	cin>>n>>k;
	REP(i,n) cin>>a[i];
	sum=0;
	REP(i,n){
		sum+=a[i];
		if (s.count(sum)) s[sum]++;
		else s.insert(pair<LL,LL>(sum,1ll));
	}
	sum=0;
	REP(i,n){
		if (k==1) num+=s[1+sum];
		else if (k==-1) num+=s[1+sum]+s[sum-1];
		else for (j=1;abs(j*10)<=INFF;j*=k) num+=s[j+sum];
		sum+=a[i];
		s[sum]--;
	}
	cout<<num;
}
/*
*/
