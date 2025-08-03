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
LL n,m,k,t;
LL i,j;
LL a[maxn];
LL num1,ans1,num2,ans2,num3,ans3;
LL ans;
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%lld%lld",&n,&k);
        if (k==1){
            if (n%4==0) printf("%lld\n",n);
            else if (n%4==1) printf("%lld\n",1);
            else if (n%4==2) printf("%lld\n",n+1);
            else if (n%4==3) printf("%lld\n",0);
        }else{
        	LL marknum=0;
            m=0;t=1;
            while(n){
                a[m++]=min(n,t);
                n-=min(n,t);
                if (n) t*=k;
            }
//            REP(i,m) printf("%lld ",a[i]);puts("");
            num1=a[m-1];num2=0;
            ans1=1;ans2=ans3=0;
            if (num1&1) ans=1;
            else ans=0;
            m--;
            rREP(i,m){
                t=a[i];
                LL now1,now2,now3;
                LL a1,a2,a3;
                now2=now2||(num1%k!=0);
                now1=num1/k;
                now3=t-now1-now2;
                a1=ans1*k+1;
                a3=ans3*k+1;
                a2=(ans1*num1+ans2*num2+ans3*num3+t)-(now1*a1+now3*a3);
                if (now1&1) ans^=a1;
                if (now2&1) ans^=a2;
                if (now3&1) ans^=a3;
//                printf("NUM %lld %lld %lld\n",num1,num2,num3);
//                printf("ANS:%lld %lld %lld\n",ans1,ans2,ans3);
//                printf("- > %lld %lld %lld\n",now1,now2,now3);
//                printf("->>>%lld %lld %lld\n",a1,a2,a3);
//                printf("NOW ANS=%lld\n",ans);
                num1=now1;num2=now2;num3=now3;
                ans1=a1;ans2=a2;ans3=a3;
            }
            printf("%lld\n",ans);
        }
    }
}
/*
8
5 2
5 3
1000 3
1000000000000000000 2
100000000
99999998
100000000000000
99999999999998
*/

