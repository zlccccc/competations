#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}


int n,m;
int s[N];
int i,j,k,t;
vector<int> v;

struct node{
	int i,n;
}a[N];
bool cmp(node i,node j){
	return i.n>j.n;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	t=(n+m)/k+1;
	REP(i,n){
		scanf("%d",&j);
		if (j<t) s[j]++;
		else s[t]++;
	}
	FOR(i,1,m) scanf("%d",&a[i].n),a[i].i=i;
	sort(a+1,a+m+1,cmp);
//	FOR(i,1,m) printf("%d ",a[i].i);
	rrep(i,1,t) if (s[i]>k) s[i-1]+=s[i]-k;
	if (s[0]>k){
		printf("-1");
		return 0;
	}
	j=1;
	rREP(i,t){
		while (s[i]<k&&j<=m&&a[j].n>=i){
			v.push_back(a[j].i);
			s[i]++;
			j++;
		}
	}
	k=v.size();
	printf("%d\n",k);
	REP(i,k) printf("%d ",v[i]);
}
/*
*/
