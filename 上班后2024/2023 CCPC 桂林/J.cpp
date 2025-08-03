// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)
    
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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!b) return a;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az, diff=b-a, az=__builtin_ctzll(diff);
        (b>a)&&(b=a), a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    
const ll M=1e9+7;
struct Hash{
    vector<ll> px,val; ll P;
    Hash(int n=1,int p=131) {
        // printf("hash %d %d %d\n",n,p,mod);
        px.resize(n+1); val.resize(n+1);
        P=p; px[0]=1;
        FOR_(i,1,n) px[i]=px[i-1]*p;
    }
    void set(const char a[]){ // id start from 0
        val[0]=0; int n=val.size()-1;
        FOR_(i,1,n) val[i]=(val[i-1]*P+a[i-1]-'a'+1);
    }
    ll get(int l,int r){
        if (l>r) return 0;
        // printf("get %d %d\n",l,r);
        ll ret=val[r]-(LL)val[l-1]*px[r-l+1];
        return ret;
    }
};

map<pair<ll,int>,queue<pair<pair<ll,int>,int>>> MP;
map<pair<ll,int>,int> in;
vector<int> res;
void dfs(pair<ll,int> x) {
    // printf("dfs: %d\n",x);
    while (MP[x].size()) {
        auto f=MP[x].front(); MP[x].pop();
        dfs(f.first);
        res.push_back(f.second);
    }
};

char s[maxn];
int solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    vector<Hash> hsh;
    REP_(i,n+n) {
        scanf("%s",s);
        Hash cur(m+1);
        cur.set(s);
        hsh.push_back(move(cur));
    }
    REP_(k,m) {
        MP.clear(); in.clear();
        REP_(i,n+n) {
            pair<ll,int> vx,vy;
            if (i<n) vx={hsh[i].get(1,k),0},vy={hsh[i].get(k+1,m),1};
            else vx={hsh[i].get(1,m-k),1},vy={hsh[i].get(m-k+1,m),0};
            MP[vx].push({vy,i}); in[vy]++;
            // printf("i=%d: %d -> %d\n",i,vx,vy);
        }
        bool okay=true;
        for (auto &[vx,edg]:MP) {
            if (in[vx]!=edg.size()) {okay=false; break;}
        }
        if (okay&&MP.size()) {
            res.clear();
            vector<pair<ll,int>> nod;
            for (auto &[vx,edg]:MP) nod.push_back(vx);
            dfs(nod[0]);
            if (res.size()==n+n) {
                reverse(res.begin(),res.end());
                // for (int v:res) printf("%d ",v); puts("<- v");
                for (int v:res) if (v<n) printf("%d ",v+1); puts("");
                for (int v:res) if (v>=n) printf("%d ",v-n+1); puts("");
                return 0;
            }
        }
    }
    puts("-1");
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
100
2 2
ab
ba
ab
ba
*/