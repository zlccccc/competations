// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I, N) for (int I = 0, END = (N); I < END; I++)
#define rREP_(I, N) for (int I = (N)-1; I >= 0; I--)
#define rep_(I, S, N) for (int I = (S), END = (N); I < END; I++)
#define rrep_(I, S, N) for (int I = (N)-1, START = (S); I >= START; I--)
#define FOR_(I, S, N) for (int I = (S), END = (N); I <= END; I++)
#define rFOR_(I, S, N) for (int I = (N), START = (S); I >= START; I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n", str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int INF = 0x3f3f3f3f;
const LL INFF = 0x3f3f3f3f3f3f3f3fll;
const LL maxn = 1e6 + 7;
const double pi = acos(-1.0);
const double eps = 1e-10;
template <typename T> inline void pr2(T x, int k = 64) { REP_(i, k) debug("%d", (x >> i) & 1); putchar(' '); }
template <typename T> inline void max_(T &A, T B) { (A < B) && (A = B); }
template <typename T> inline void min_(T &A, T B) { (A > B) && (A = B); }
inline ll fastgcd(ll a, ll b) { // __gcd()
    if (!a)
        return b;
    ll az = __builtin_ctzll(a), bz = __builtin_ctzll(b), z = min(az, bz), diff;
    b >>= bz;
    while (a) {
        a >>= az, diff = b - a, az = __builtin_ctzll(diff);
        (b > a) && (b = a), a = abs(diff);
    }
    return b << z;
}
int startTime;
void startTimer() { startTime = clock(); }
void printTimer() { debug("/--- Time: %ld milliseconds ---/\n", clock() - startTime); }
typedef array<int, 4> ar4;
typedef array<int, 3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
vector<pii> direction8 = {{-1, -1}, {-1, 0}, {1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

// const int mod = 1e9+7;
const int mod=998244353;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this; }
    mint operator-() const { return mint(0) - *this; }
    mint operator~() const { return mint(1) / *this; }
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this; }
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this; }
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this; }
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this; }
    mint operator+(const mint &a)const { return mint(*this) += a; }
    mint operator-(const mint &a)const { return mint(*this) -= a; }
    mint operator*(const mint &a)const { return mint(*this) *= a; }
    mint operator/(const mint &a)const { return mint(*this) /= a; }
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x; }
    bool operator==(const mint &a)const { return x == a.x; }
};
istream & operator>>(istream &o,mint &a) { o>>a.x; a=a.fix(); return o; }
ostream & operator<<(ostream &o,const mint &a) { o<<a.x; return o; }

struct comb {
    vector<mint> f, g; // f:fac; g:inv
    comb() {}
    comb(int mx):f(mx+1),g(mx+1) {
        f[0] = 1;
        FOR_(i,1,mx) f[i] = f[i-1]*i;
        g[mx] = f[mx].pow(mod-2);
        rFOR_(i,1,mx) g[i-1] = g[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return f[a]*g[b]*g[a-b];
    }
} C(maxn);

int solve() {
    map<string,int> MP;
    map<int,string> name;
    int n;
    cin>>n;
    vector<int> id(n+1),prob(n+1),tim(n+1),op(n+1);
    vector<int> useful(n+1);  // 是否会对结果产生影响
    int tot=0,team_num=0;  // team number
    FOR_(i,1,n) {
        string c,p,s;
        cin>>c>>p>>tim[i]>>s;
        if (!MP.count(c)) MP[c]=++tot,name[tot]=c;
        id[i]=MP[c];
        prob[i]=p[0]-'A';
        op[i]=s=="accepted"?1:0;
    }
    FOR_(i,1,n) useful[i]=1;
    map<pair<int,int>,vector<int>> items;
    map<int,pair<int,int>> probs;
    {
        map<int,map<int,int>> cnt;  // 忘记罚时这个事情了...
        map<int,set<int>> solved;
        FOR_(i,1,n) {
            tim[i]+=cnt[id[i]][prob[i]]*20;
            if (solved[id[i]].count(prob[i])) useful[i]=0; // already solved
            else if (op[i]) {
                probs[id[i]].first++;  // problem number
                probs[id[i]].second+=tim[i];  // solved times
                solved[id[i]].insert(prob[i]);
            }
            cnt[id[i]][prob[i]]++;
        }
        for (auto &cur:probs) {
            if (cur.second.first) team_num++;
            items[{-cur.second.first,cur.second.second}].push_back(cur.first);
        }
    }
    set<int> okay;
    pii limit={-INF,-INF};  // (更改后)需要通过的最少题数
    auto judge_k_items=[&](int p1,int t1,int p2,int t2,int team) {  // p1,t1的队伍变成p2 t2
        int cur_team_num=team_num;
        if (p1) cur_team_num--;
        if (p2) cur_team_num++;
        int numb=min((cur_team_num+9)/10,35);  // 金牌总数量
        auto it=items.begin();
        int cnt=0,c1=-1,c2=1;  // c1&c2: 是否被算到了
        // cout<<"change team "<<name[team]<<" "<<p1<<" "<<t1<<" "<<p2<<" "<<t2<<"  num="<<numb<<" team="<<cur_team_num<<"\n";
        while (cnt<numb) {
            if (c2&&team!=-1) {
                if (it==items.end()||it->first>pii(-p2,t2)) {  // 没有对应的item
                    cnt+=c2; okay.insert(team); c2=0;
                    if (limit<pii{-p2,t2}) limit={-p2,t2};
                    // cout<<cnt<<" <- cnt; "<<-p2<<" "<<t2<<" <- current limit\n";
                    continue;
                }
            }
            cnt+=it->second.size();
            if (team!=-1) {
                if (it->first==pii(-p1,t1)) cnt+=c1,c1=0;
                if (it->first==pii(-p2,t2)) {cnt+=c2,c2=0; okay.insert(team);}
            }
            if (limit<it->first) limit=it->first;
            // for (int v:it->second) okay.insert(v);
            // cout<<cnt<<" <- cnt; "<<it->first.first<<" "<<it->first.second<<" <- current limit\n";
            it++;
        }
    };
    // for (auto &cur:probs) {
    //     cout<<name[cur.first]<<" "<<cur.second.first<<" "<<cur.second.second<<"  <- origin\n";
    // }
    judge_k_items(-INF,-INF,-INF,-INF,-1);
    // FOR_(i,1,n) printf("%d ",useful[i]); puts(" <- useful");
    {
        map<int,map<int,int>> solved;
        rFOR_(i,1,n) {
            if (useful[i]) {  // 第一次solve
                int p=probs[id[i]].first,t=probs[id[i]].second; // 题数&罚时
                if (op[i]) {
                    if (solved[id[i]].count(prob[i])) {
                        judge_k_items(p,t,p,t+solved[id[i]][prob[i]]-tim[i],id[i]);
                    } else {
                        judge_k_items(p,t,p-1,t-tim[i],id[i]);
                    }
                } else {
                    if (solved[id[i]].count(prob[i])) {
                        judge_k_items(p,t,p,t-solved[id[i]][prob[i]]+tim[i],id[i]);
                    } else {
                        judge_k_items(p,t,p+1,t+tim[i],id[i]);
                    }
                }
            }
            if (op[i]) solved[id[i]][prob[i]]=tim[i];  // 下一个solve的时间
        }
    }
    // // printf("limit: %d %d\n",limit.first,limit.second);
    for (auto &p:items) if (p.first<=limit) {
        for (int v:p.second) okay.insert(v);
    }
    cout<<okay.size()<<"\n";
    for (int v:okay) cout<<name[v]<<" "; puts("");
    return 0;
}
int main() {
    int T;
    T = 1;
    cin>>T;
    // scanf("%d", &T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
2
13
A A 1 accepted
A X 1 accepted
K K 1 rejected
B B 2 accepted
C C 2 accepted
D D 2 accepted
E E 2 accepted
F F 2 accepted
G G 2 accepted
H H 2 accepted
I I 2 accepted
J J 2 accepted
K K 2 rejected
12
A A 1 accepted
A X 1 accepted
B B 2 accepted
C C 2 accepted
D D 2 accepted
E E 2 accepted
F F 2 accepted
G G 2 accepted
H H 2 accepted
I I 2 accepted
J J 2 rejected
K K 2 rejected

12
A A 1 accepted
A X 1 accepted
B B 2 accepted
C C 2 accepted
D D 2 accepted
E E 2 accepted
F F 2 accepted
G G 2 accepted
H H 2 accepted
I I 2 accepted
J J 2 rejected
K K 2 rejected
 */