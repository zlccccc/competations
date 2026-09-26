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
const LL M=1e9+7;
const LL maxn=4e5+7;
const double eps=0.00000001;
const double pi=acos(-1);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
int A[maxn];
LL A1,A2;
vector<int> ans;
int main(){
    int i,j,k;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    j=1;
    FOR(i,1,n) if (A[j]<A[i]) j=i;
    if (A[j]<0){
        printf("%d\n",A[j]);
        printf("%d\n",n-1);
        rFOR(i,j+1,n) printf("%d\n",i);
        FOR(i,1,j-1) printf("1\n");
        return 0;
    }
    FOR(i,1,n){
        if (i&1) A1+=max(0,A[i]);
        else A2+=max(0,A[i]);
    }printf("%lld\n",max(A1,A2));
    if (A1<A2){
        if (n&1) ans.push_back(n),n--;
        ans.push_back(1);
        for (i=2;i<=n&&A[i]<0;i+=2)
            ans.push_back(1),ans.push_back(1);
        for (i+=2;i<=n;i+=2){
            if (A[i]>0) ans.push_back(2);
            else {
                ans.push_back(3);
                if (i==n) ans.push_back(2);
            }
        }
    }else{
        if (!(n&1)) ans.push_back(n),n--;
        for (i=1;i<=n&&A[i]<0;i+=2)
            ans.push_back(1),ans.push_back(1);
        for (i+=2;i<=n;i+=2){
            if (A[i]>0) ans.push_back(2);
            else {
                ans.push_back(3);
                if (i==n) ans.push_back(2);
            }
        }
    }
    printf("%d\n",ans.size());
    for (int v:ans) printf("%d\n",v);
}
/*
5
-1 -2 -3 -4 -5

6
1 2 3 4 5 6
*/
