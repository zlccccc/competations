#include <sstream>
#include <fstream>
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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=100+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

map<string,int> id;
map<int,string> name;
string A[maxn]; int Bid[maxn];
int pre[maxn][maxn];
int TaskA(){
    int n,m,i,j,k;
    scanf("%d",&n);int tot=0;
    id.clear();
    string nowname;
    FOR(i,1,n){
        cin>>nowname;tot++;
        id[nowname]=tot;name[tot]=nowname;
    }scanf("%d",&m); getline(cin,nowname);
    FOR(i,1,m) FOR(j,1,n) pre[i][j]=0;
    FOR(i,1,m){
        string now;
        int pos=0; A[i]="";
        getline(cin,now); nowname="";
        while (pos<now.size()&&now[pos]!=':') {nowname+=now[pos++];}
        A[i]+=now[pos++];//:
        int P=0;
        if (i==1) FOR(j,1,n) pre[1][j]=1;
        else{
            FOR(j,1,n) if (pre[i-1][j]){
                if (P){
                    pre[i][P]=j;
                    break;
                }else{
                    P=j;
                    FOR(k,1,n) if (k!=P) pre[i][k]=P;
                }
            };
        }
        if (id.count(nowname)){
            FOR(k,1,n) if (k!=id[nowname]) pre[i][k]=0;
            while (pos<now.size()) A[i]+=now[pos++];
        }else{
            while (pos<now.size()){
                string text="";
                while (pos<now.size()&&now[pos]!='.'&&now[pos]!=','&&now[pos]!='!'&&now[pos]!='?'&&now[pos]!=' '){
                    text+=now[pos];
                    A[i]+=now[pos++];
                }if (id.count(text)) pre[i][id[text]]=0;
                if (pos<now.size()) A[i]+=now[pos++];
            }
        }
    }FOR(j,1,n) if (pre[m][j]){
        for (i=m;i;j=pre[i][j],i--) Bid[i]=j;
        FOR(i,1,m) cout<<name[Bid[i]]+A[i]+'\n';
        return 0;
    }puts("Impossible");
    return 0;
}
void initialize(){}
int main() {
    int startTime=clock();
    //initialize
    initialize();
    debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
    int T=1;
    scanf("%d",&T);
    while (T--) TaskA();
}
/*
1
1
b
1
b:lala!

*/
