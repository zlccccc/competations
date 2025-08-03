#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL f[27][2][107][2][2];
int value[27];
LL pw10[17],preval[27];
LL A44[27],A77[27];
//mark:already_bigger//pre=0:previous_0|4
LL calc(int x,int bigger,int pre,int has4,int not_0,int flag){
    if (x==0) return 0;
    if (!flag&&f[x][bigger][pre][has4][not_0]!=-1) return f[x][bigger][pre][has4][not_0];
    LL ret=0;int i,maxi=9;
    if (flag) maxi=min(maxi,value[x]);
    FOR(i,0,maxi){
        int nxtpre=pre,nxtbigger=bigger,nxthas4=has4;
        if (not_0||i){
            int subcnt;
            if (flag&&i==maxi) subcnt=preval[x-1];
            else subcnt=pw10[x-1];
            if (i<4||bigger){//choose_4
                ret+=pw10[x-1]*4*subcnt;
                nxtpre=0;nxtbigger=1;
            }else if (i==4){
                ret+=pw10[x-1]*4*subcnt;
                nxtpre=x-1;nxthas4=1;
            }else if (i<7){
                ret+=pw10[x-1]*7*subcnt;
                nxtpre=0;nxtbigger=1;
            }else if (i==7){
                ret+=pw10[x-1]*7*subcnt;
				if (!has4&&!pre) nxtpre=x;
            }else if (has4){
//                printf("has4_pre=%d ",pre);
                ret+=pw10[pre]*3*subcnt;//4->7
                ret+=(A44[pre-x]-A77[pre-x])*pw10[x]*subcnt;
                ret+=pw10[x-1]*4*subcnt;
                nxtpre=0;nxtbigger=1;
            }else if (pre){
//                printf("0_pre=%d %d ",pre,x);
                ret+=(A44[pre-x+1]-A77[pre-x])*pw10[x]*subcnt;//77->444
                ret+=pw10[x-1]*4*subcnt;
                nxtpre=0;nxtbigger=1;
            }else{
//                printf("no_pre=%d   ",pre);
                ret+=pw10[x]*4*subcnt;//7->44
                ret+=pw10[x-1]*4*subcnt;
                nxtpre=0;nxtbigger=1;
            }
        }ret+=calc(x-1,nxtbigger,nxtpre,nxthas4,not_0||i,flag&&(i==maxi));
    }if (!flag) f[x][bigger][pre][has4][not_0]=ret;
    return ret;
}LL calc(LL x){
    int length=0;int i;
//    printf("calc:%lld  ",x);
    while (x) value[++length]=x%10,x/=10;
    LL t=1;preval[0]=1;
    FOR(i,1,length) preval[i]=preval[i-1]+t*value[i],t*=10;
//    FOR(i,0,length) preval[i]++;//cnt
//    FOR(i,1,length) printf("preval=%d ",preval[i]);puts("");
    return calc(length,0,0,0,0,1);
}LL calc(LL l,LL r){
    return calc(r)-calc(l-1);
}
int n,m,i,j,k;
int T;int cnt1,cnt2;
char a[maxn];
int main(){
    memset(f,0xff,sizeof(f));
    pw10[0]=1;
    FOR(i,1,17) pw10[i]=10*pw10[i-1];
    FOR(i,1,17) A44[i]=A44[i-1]*10+4;
    FOR(i,1,17) A77[i]=A77[i-1]*10+7;
//    FOR(i,1,100) printf("%d:%lld all=%lld\n",i,calc(i,i),calc(i));
    LL l,r;
    scanf("%lld%lld",&l,&r);
    printf("%lld\n",calc(l,r));
}
/*
*/
