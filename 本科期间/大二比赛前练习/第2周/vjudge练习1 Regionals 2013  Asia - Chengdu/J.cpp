#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e6+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;
inline LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
int TT;
LL ans,all;
LL a,b,c,d,m,p,pos;
int i;
LL L,R;
vector<LL> H;
LL I1[maxn],I2[maxn];
int main()
{
	int x=0;
	scanf("%d",&TT);
	while (TT--){
		ans=0;
		scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&m,&p);
		c-=p;d-=p;
		pos=c;c=-d;d=-pos;//reverse
		pos=(a%m+m)%m;
		b+=pos-a;a=pos;
		pos=(c%m+m)%m;
		d+=pos-c;c=pos;
//		printf("%d %d %d %d %d\n",a,b,c,d,m);
		H.clear();
		H.push_back(a%m);
		H.push_back(b%m);
		H.push_back(c%m);
		H.push_back(d%m);
		H.push_back(a%m+1);
		H.push_back(b%m+1);
		H.push_back(c%m+1);
		H.push_back(d%m+1);
		H.push_back(0);
		H.push_back(m);
		sort(H.begin(),H.end());
		H.erase(unique(H.begin(),H.end()),H.end());
		REP(i,H.size()) I1[i]=I2[i]=0;
		all=(b-a+1)*(d-c+1);
		if (a<=b&&(b+1)%m!=a%m){
			L=a;R=min(b,((a-1)/m+1)*m-1);
//			printf("L,R=%d %d, %% L  R==%d  %d\n",L,R,L%m,R%m);
			REP(i,H.size()-1){
//				printf("ADD::%d %d %d %d\n",L%m,H[i],H[i+1],R%m);
				if (L%m<=H[i]&&H[i+1]<=R%m+1) I1[i]++;
			}
			a=R+1;
			if (a<=b){
				L=max(a,b/m*m);R=b;
//				printf("L,R=%d %d, %% L  R==%d  %d\n",L,R,L%m,R%m);
				REP(i,H.size()-1)
					if (L%m<=H[i]&&H[i+1]<=R%m+1) I1[i]++;
				b=L-1;
			}
		}
		REP(i,H.size()-1) I1[i]+=(b-a+1)/m;
		if (c<=d&&(d+1)%m!=c%m){
//			printf("c,d===%d %d\n",c,d);
			L=c;R=min(d,((c-1)/m+1)*m-1);
//			printf("L,R=%d %d, %% L  R==%d  %d\n",L,R,L%m,R%m);
			REP(i,H.size()-1){
//				printf("ADD::%d %d %d %d\n",L%m,H[i],H[i+1],R%m);
				if (L%m<=H[i]&&H[i+1]<=R%m+1) I2[i]++;
			}
			c=R+1;
//			printf("c,d===%d %d\n",c,d);
			if (c<=d){
				L=max(c,d/m*m);R=d;
	//			printf("L,R=%d %d, %% L  R==%d  %d\n",L,R,L%m,R%m);
				REP(i,H.size()-1)
					if (L%m<=H[i]&&H[i+1]<=R%m+1) I2[i]++;
				d=L-1;
			}
		}
		REP(i,H.size()-1) I2[i]+=(d-c+1)/m;
		REP(i,H.size()-1) ans+=(H[i+1]-H[i])*I2[i]*I1[i];
//		REP(i,H.size()) printf("%d ",H[i]);puts("");
//		REP(i,H.size()) printf("%d ",I1[i]);puts("");
//		REP(i,H.size()) printf("%d ",I2[i]);puts("");
//		puts("");

		printf("Case #%d: ",++x);
		if (ans==0) puts("0/1");
		else printf("%lld/%lld\n",ans/gcd(all,ans),all/gcd(all,ans));
	}
    return 0;
}
/*
*/
