#include <iostream>
using namespace std;
int main(){
    int a[501];
    int n,i,ans,k;
    cin>>n>>k;
    a[0]=0; ans=0;
    for (i=1;i<=n;i++) cin>>a[i];
    for (i=2;i<=n;i++) if (a[i]+a[i-1]<k)
        {
            ans+=k-a[i]-a[i-1];
            a[i]=k-a[i-1];
        }
    cout<<ans<<"\n";
    for (i=1;i<=n;i++) cout<<a[i]<<" ";
}
