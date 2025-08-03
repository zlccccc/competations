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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

string A[3]={"00001111",
             "00110011",
             "01010101"};
string NOT(string a){
    string ret;int i;
    REP(i,a.size())
        ret+=char('0'+!(a[i]-'0'));
    return ret;
}
string OR(string a,string b){
    string ret;int i;
    REP(i,a.size())
        ret+=char('0'+((a[i]-'0')|(b[i]-'0')));
    return ret;
}
string AND(string a,string b){
    string ret;int i;
    REP(i,a.size())
        ret+=char('0'+((a[i]-'0')&(b[i]-'0')));
    return ret;
}
bool changed;
void update(string &a,string b){
    if (a==""||a.size()>b.size()||(a.size()==b.size()&&b<a)){
        a=b;
        changed=1;
    }
}
//E:could !
//F:could &
//T:must () |
map<string,string> E,F,T;
int main(){
    E["00001111"]="x";
    E["00110011"]="y";
    E["01010101"]="z";
    while (1){
        changed=0;
        for (auto A:E) update(F[A.first],A.second);
        for (auto A:F) update(T[A.first],A.second);
        for (auto A:E)
            update(E[NOT(A.first)],"!"+A.second);
        for (auto A:F) for (auto B:F)
            update(F[AND(A.first,B.first)],A.second+"&"+B.second);
        for (auto A:T) for (auto B:T)
            update(T[OR(A.first,B.first)],A.second+"|"+B.second);
        for (auto A:T)
            update(E[A.first],"("+A.second+")");
        if (!changed) break;
    }
//    for (auto now:T)
//        cout<<"E[\""+now.first+"\"]=\""+now.second+"\";\n";puts("   OK  !!!   ");
    int n;string a;
    scanf("%d",&n);
    while (n--){
        cin>>a;
        cout<<T[a]<<"\n";
    }
}
/*
*/
