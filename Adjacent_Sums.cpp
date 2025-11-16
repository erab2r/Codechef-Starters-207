#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        vector<ll>a(n);
        for(int i=0; i<n; i++){
            cin >> a[i];
        }
        vector<ll>dp(n);

        dp[0]=a[0];
        for(int i=1; i<n; i++){
            ll cost1 = a[i]+dp[i-1];
            if(i-1>=0){
                ll cost2 = abs(a[i]-a[i-1]);
                if(i-2>=0) cost2+=a[i-2];
                if(i-3>=0) cost2+=dp[i-3];
                dp[i] = min(cost1, cost2);
            }
        }
        cout << dp[n-1] << "\n";
    }
}