#include <bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
using namespace std;
typedef pair<long long,long long> pii;
const int MAX=1e5+5;
#define pb push_back
#define mp make_pair
typedef long long ll;
int t,n,m,p;
int lo[MAX];
vector<pii>v;
map<int,int>cnt;
map<int,int>::iterator it;
long long cl,cr,sum,ans,tot;
int main(){
    scanf("%d",&t);
    while(t--){
        cnt.clear();v.clear();
        cl=cr=ans=sum=tot=0;
        scanf("%d%d%d",&n,&m,&p);
        for(int i=1;i<=n;i++)scanf("%d",&lo[i]);
        for(int a,b,i=1;i<=p;i++){
            scanf("%d%d",&a,&b);
            int tm=((b-lo[a])%m+m)%m;
            ++cnt[tm];
//            v.pb(tm);u.pb(tm);
        }
        for(it= cnt.begin();it!=cnt.end();it++){
            v.pb(mp((*it).first,(*it).second));
        }
        int ge=v.size()-1;
        ll val=v[ge].first;
        for(int i=ge;i>=0;i--){
            sum+=(val-v[i].first)*1LL*v[i].second;
            tot+=v[i].second;
        }
//        cout<<"tot"<<tot<<endl;
        ans=sum;
        for(int i=ge-1;i>=0;i--){
            ll pre=v[i+1].second;
            ll dis=v[i+1].first-v[i].first;
            sum-=tot*dis;
            sum+=pre*m;
//            cout<<sum<<endl;
            ans=min(ans,sum);
        }
        printf("%lld\n",ans);
//        sort(v.begin(),v.end());
//        for()
    }
}
/*
2
3 10 5
3 4
3 5
3 6
3 10 4
-7 -6
4 5
5 4
*/
