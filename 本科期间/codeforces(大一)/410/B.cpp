#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
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
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
int ans,i,t;
string a[maxn];
string b[maxn],k;
int calc(string s){
	int i;
	int ret=0;
	REP(i,n) b[i]=a[i];
	REP(i,n){
		int num=0;
		while (s!=b[i]&&num<1000){
			b[i]=b[i].substr(1,b[i].size()-1)+b[i][0];
			num++;
//			cout<<b[i]<<' ';
		}
//	printf(" %d\n",num);
		if (num>500) return -1;
		ret+=num;
	}
//	printf("%d\n",ret);
	return ret;
}
int main()
{
	scanf("%d",&n);
	REP(i,n) cin>>a[i];
	k=a[0]+a[0];
	ans=INF;
//	cout<<k<<a[0].size()<<endl;
	REP(i,a[0].size()){
//		cout<<k.substr(i,a[0].size())<<endl;
		t=calc(k.substr(i,a[0].size()));
		if (t==-1) return 0*puts("-1");
		ans=min(ans,t);
	}
	printf("%d",ans);
}
