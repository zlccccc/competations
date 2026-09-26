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
const LL M=1e4+7;
const LL N=5e3+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

#define AND 1
#define OR 2
#define XOR 3
int n,m;
bool num[N][M],t[N];
int o[N],ans1[N],ans2[N],x[N],y[N];
map<string,int> s;
string a,b;
int i,j;
int sum1,sum2;
bool xx,c1,c2;
int F(int ii,bool xx){
	int s=0,i;
	FOR(i,1,n){
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
//	printf("ii=%d xx=%d s=%d\n",ii,xx,s);
//	FOR(i,1,n) printf("%d",t[i]);
//	puts("");
	return s;
} 
int main(){
	scanf("%d%d",&n,&m);
	string t;
	FOR(i,1,n){
		cin>>a>>t>>b;
		s.insert(pair<string,int>(a,i));
		if (b[0]=='0'||b[0]=='1'){
			FOR(j,1,m) num[i][j]=b[j-1]-'0';
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
	FOR(i,1,m){
		sum1=F(i,0);sum2=F(i,1);
		if (sum1<=sum2) ans1[i]=0;else ans1[i]=1;
		if (sum1>=sum2) ans2[i]=0;else ans2[i]=1;
	}
	FOR(i,1,m) printf("%d",ans1[i]);
	puts("");
	FOR(i,1,m) printf("%d",ans2[i]);
}
/*
*/
