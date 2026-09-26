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
#include <cassert>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,T;
int i,j,k;
pair<int,int> A[maxn],B[maxn],C[maxn];
int cnt1,cnt2;
double all1,all2;
double ans;
int main(){
    scanf("%d%d",&n,&T);
    FOR(i,1,n) scanf("%d",&C[i].second);
    FOR(i,1,n) scanf("%d",&C[i].first);
    FOR(i,1,n){
        if (C[i].first<=T){
            A[++cnt1]=make_pair(T-C[i].first,C[i].second);
            all1+=(LL)(T-C[i].first)*(C[i].second);
        }else{
            B[++cnt2]=make_pair(C[i].first-T,C[i].second);
            all2+=(LL)(C[i].first-T)*(C[i].second);
        }
    }all1=min(all1,all2);all2=min(all1,all2);
    sort(A+1,A+1+cnt1);
    sort(B+1,B+1+cnt2);
    FOR(i,1,cnt1){
        double DIV;
        if (A[i].first!=0) {
            DIV=min(1.0*all1/A[i].first,1.0*A[i].second);
            all1-=DIV*A[i].first;
        }else DIV=A[i].second;
        ans+=DIV;
    }
    FOR(i,1,cnt2){
        double DIV;
        if (B[i].first!=0) {
            DIV=min(1.0*all2/B[i].first,1.0*B[i].second);
            all2-=DIV*B[i].first;
        }else DIV=B[i].second;
        ans+=DIV;
    }
    printf("%.10f\n",ans);
}
/*
*/
