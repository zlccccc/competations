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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=1e6+7;
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

class Resistance{
public:
    vector <double> spyProbability(int P, int S, vector <string> missions){
        int cnt[17],all,i,j;
        REP(j,P) cnt[j]=0;all=0;
        REP(i,(1<<P)){
            int CNT=0;
            for (int t=i;t;t>>=1) if (t&1) CNT++;
            if (CNT!=S) continue;
            int mark=1;
            for (string now:missions){
                int okay=1;
                REP(j,P)
                    if (now[j+1]=='1'&&((i>>j)&1)) okay=false;
                if (okay&&now[0]=='F') mark=0;
            }if (!mark) continue;
            {REP(j,P) printf("%d",((i>>j))&1);puts("");}
            REP(j,P)
                if ((i>>j)&1) cnt[j]++;
            all++;
        }vector<double> ret;
        if (all==0) return ret;
        REP(i,P) ret.push_back(1.0*cnt[i]/all);
        return ret;
    }
}test;
int main() {
    int i,j,k;
    int T;
    vector<double> ans=test.spyProbability(4,1,{"S0110", "F1100", "S0011"});
    for (auto now:ans) printf("%f ",now);
    ans=test.spyProbability(4,2,{"F0100", "S0101", "F1010", "S1011"});
    for (auto now:ans) printf("%f ",now);
    ans=test.spyProbability(3,1,{"F110", "F101", "F011"});
    for (auto now:ans) printf("%f ",now);
    ans=test.spyProbability(5,2,{"F11000", "S00011", "F10100", "S01111"});
    for (auto now:ans) printf("%f ",now);
    ans=test.spyProbability(9,3,{"S100001100", "F011110000", "F001000010", "F100010101", "S010010001", "F100001010", "F000100100"});
    for (auto now:ans) printf("%f ",now);
    return 0;
}
/*
*/
