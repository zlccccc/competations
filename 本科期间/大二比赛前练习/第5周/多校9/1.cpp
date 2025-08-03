#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=2e7+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
    LL ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}
LL n,m;
map<LL,LL> MX,val;
set<int> mark;//改以后的 max
inline LL getval(LL x){
	if (val.count(x)) return val[x];
	return x;
}
LL count(LL x){
	if (x>n) return 0;
	if (MX.count(x)) return MX[x];
	LL ret=0,t=getval(x);
	if (mark.count(x)) ret=max(ret,getval(x)+max(count(x<<1),count(x<<1|1)));
	else ret=max(ret,getval(x)+count(x<<1|1));
//	MX[x]=ret;
	return ret;
}
LL query(LL x){
	LL len1,len2,len3,pre=0,prex=getval(x);
	len1=count(x<<1),len2=count(x<<1|1),len3=0;
	while(x!=1){
//		printf("x:%d,%d\n",x,count(x^1)+pre+getval(x>>1));
		len3=max(len3,count(x^1)+pre+getval(x>>1));
		x>>=1;
		pre+=getval(x);
	}
//	printf("%lld %lld %lld-%d\n",len1,len2,len3,pre);
	return prex+len1+len2+len3-min(min(len1,len2),len3);
}
void update(LL x,LL t){
	LL pre=t;
	val[x]=t;
	while(x){
		MX[x]=max(count(x<<1),count(x<<1|1))+getval(x);
//	printf("%d:%d\n",x,MX[x]);
		x>>=1;
	}
}
char a[50];
int main(){
	LL i;
    while (~scanf("%lld%lld",&n,&m)){
    	mark.clear();
		for (int x=n;x;x>>=1) mark.insert(x);
		MX.clear();val.clear();
		REP(i,m){
    		scanf("%s",a);
    		LL k,t;
    		scanf("%lld",&k);
    		if (a[0]=='q'){
    			printf("%lld\n",query(k));
			}else{
    			scanf("%lld",&t);
				update(k,t);
			}
//		FOR(i,1,n) if (MX.count(i)) printf("%d : %d\n",i,MX[i]);
		}
    } 
}
/*
*/

