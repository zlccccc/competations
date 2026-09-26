#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue> 
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
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e3+7;
const LL N=1e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

#define AND 1
#define OR 2
#define XOR 3
LL n,m;
bool num[N][M];
int t[N],o[N],ans1[N],ans2[N],x[N],y[N];
map<string,int> s;
string a,b;
LL i,j;
LL sum1,sum2;
bool xx,c1,c2;
LL F(int ii,bool xx){
	int s=0,i;
	REP(i,n){
		if (o[i]){
			int c1,c2;
			if (x[i]==-1) c1=xx;
			else c1=t[x[i]];
			if (y[i]==-1) c2=xx;
			else c2=t[y[i]];
			if (o[i]==AND) t[i]=c1&c2;
			if (o[i]==OR) t[i]=c1|c2;
			if (o[i]==XOR) t[i]=c1^c2;
		}
		else t[i]=num[i][ii];
		s+=t[i];
	}
	return s;
} 
int main(){
	scanf("%d%d",&n,&m);
	string t;
	REP(i,n){
		cin>>a>>t>>b;
		s.insert(pair<string,int>(a,i));
		if (b[0]=='0'||b[0]=='1'){
			REP(j,m) num[i][j]=b[j]-'0';
		}
		else{
			if (b[0]=='?') x[i]=-1;
			else x[i]=s[b];
			cin>>t;
			if (t[0]=='A') o[i]=AND;
			if (t[0]=='O') o[i]=OR;
			if (t[0]=='X') o[i]=XOR;
			cin>>b;
			if (b[0]=='?') y[i]=-1;
			else y[i]=s[b];
		}
//		cout<<p<<o<<q<<' '<<pp<<' '<<qq;
//		puts("");
	}
	REP(i,m){
		sum1=F(i,0);sum2=F(i,1);
		if (sum1<=sum2) ans1[i]=0;
		else ans1[i]=1;
		if (sum1>=sum2) ans2[i]=0;
		else ans2[i]=1;
	}
	REP(i,m) printf("%d",ans1[i]);
	puts("");
	REP(i,m) printf("%d",ans2[i]);
}
/*
*/
