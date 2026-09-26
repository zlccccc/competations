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
const LL N=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

LL n,m;
LL a[N];//两个开关的异或值
bool r[N];
vector<LL> t[N];
int open[N][3];
LL i,j,k;
bool check(int ii,bool pp){
	LL i,j,k;
	queue<LL> qq;
	open[ii][pp]=pp;
	open[ii][2]=pp; 
	qq.push(ii);
	while (!qq.empty()){
		i=qq.front();
		qq.pop();
		FOR(j,1,t[i][0]){
			k=t[i][j];
			if (open[i^a[k]][pp]==2){
				open[i^a[k]][pp]=open[i][pp]^r[k];
				open[i^a[k]][2]=open[i][pp]^r[k];
				qq.push(i^a[k]);
			}
			else if (open[i^a[k]][pp]!=open[i][pp]^r[k]) return 0;
//		printf("%d  %d\n",k,open[i^a[k]]);
		}
	}
	return 1;
}
int main(){
	cin>>n>>m;
	FOR(i,1,n) scanf("%d",&r[i]),r[i]^=1;
	FOR(i,1,m){
		scanf("%d",&j);
		t[i].push_back(j);
		REP(k,t[i][0]) scanf("%d",&j),t[i].push_back(j),a[j]^=i;
	}
//	FOR(i,1,m) cout<<a[i]<<' ';
//	cout<<"\n";
	j=1;
	FOR(i,1,m) open[i][0]=open[i][1]=open[i][2]=2;
	while (j<=m){
		if (!check(j,1)&&!check(j,0)) {puts("NO"); return 0;}
		while (j<=m&&open[j][2]!=2) j++;
//		cout<<j;
	}
	puts("YES");
}
/*
4 4
1 1 1 0
2 1 2
2 1 2
2 3 4
2 3 4
*/
