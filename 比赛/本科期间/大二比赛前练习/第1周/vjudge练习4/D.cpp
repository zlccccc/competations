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
const LL maxn=2e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

double a[maxn],b[maxn],len;
int n,m;
int i,j,t;
double l,r,mid1,mid2;
double ans,now;
double L1,L2,L1h,L2h,R1h,R2h;
inline double calc(double T){
	return (((T-L1)*(R2h-R1h)/(L2-L1)+R1h)+R1h)*(T-L1)/2
		  -(((T-L1)*(L2h-L1h)/(L2-L1)+L1h)+L1h)*(T-L1)/2;
}
int main(){
	int T,x=0;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		REP(i,n) scanf("%lf%lf",&a[i],&b[i]);
		scanf("%lf",&len);
		len*=2;
		L1=L2=a[0];
		L1h=b[0];
		i=1;//not chose
		j=1;now=0;
		while (L1+len>a[j]&&j<n){
			now+=(b[j]+b[j-1])*(a[j]-a[j-1])/2;
			j++;
		}
		R1h=(b[j]-b[j-1])/(a[j]-a[j-1])*(len-a[j-1])+b[j-1];
		now+=(R1h+b[j-1])*(len-a[j-1])/2;
		ans=now;
//			printf("          L1h=%lf,L2h=%lf, R1h=%lf,R2h=%lf\n",L1h,L2h,R1h,R2h);
		while (L1+len+eps<m&&i<n&&j<n){
			if (a[i]<a[j]-len){//left+
				L2=a[i];
				L2h=b[i];
				R2h=(b[j]-b[j-1])/(a[j]-a[j-1])*(L2-L1)+R1h;
				i++;
			}else{
				L2=a[j]-len;
				L2h=(b[i]-b[i-1])/(a[i]-a[i-1])*(L2-L1)+L1h;
				R2h=b[j];
				j++;
			}
			l=L1;r=L2;
			while(r-l>0.0001){
				mid1=(l*2+r)/3,mid2=(l+r*2)/3;
				if (now+calc(mid1)>now+calc(mid2)) r=mid2;
				else l=mid1;
			}
//			printf("%lf->%lf ,\n",L1,L2);
//			printf("	L1h=%lf,L2h=%lf, R1h=%lf,R2h=%lf\n",L1h,L2h,R1h,R2h);
//			printf("   mid1=%lf nowans=%lf\n",mid1,now+calc(mid1));
			ans=max(ans,now+calc(mid1));
			now=now+calc(L2);
			L1=L2;
			L1h=L2h;
			R1h=R2h;
			///这里更新now 
		}
		printf("%.3lf\n",ans/len);
	}
}
/*
*/
