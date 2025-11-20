#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
const int h = 1000004;
vector<int> f1(h), f2(h);
int64 fun(int64 a, int64 ss) {
    int64 ans = 1;
    while (ss > 0) {
        if (ss & 1) 
            ans = (ans*a)%h;
        a = (a*a) % h;
        ss >>= 1;
    }
    return ans;
}
void factls() {
    f1[0] = 1;
    for (int i = 1;i<h;i++) {
        f1[i] = (int)((int64)f1[i - 1] * i % h);
    }
    f2[h- 1] = (int)fun(f1[h - 1],h-2);
    for (int i = h-2;i>=1;i--) {
        f2[i] = (int)((int64)f2[i + 1] * (i + 1) % h);
    }
    f2[0] = 1;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    factls();
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i=0;i<n;i++) 
            cin >> a[i];
        for (int i=0;i<n;i++) 
            cin >> b[i];
        const int mx = 19; 
        int64 A = (int64)4e18;
        vector<int> SS;
        for (int j = 0;j<=mx;j++) {
            int64 H = 1LL << j;
            bool okk = true;
            int64 anss = 0;

            for (int i=0;i<n;i++) {
                int64 e1 = (int64)a[i] * H;
                if (e1 > b[i]) {
                    okk = false;
                    break;
                }
                int64 d = (int64)b[i] -e1;
                if (j == 0) {
                    anss += d;
                } else {
                    for (int k=j;k>=0;k--) {
                        int64 c = d >> k; 
                        if (c) {
                            anss += c;
                            d -= c << k;
                        }
                    }
                }
            }

            if (!okk) 
                continue;
            int64 he = anss + j;
            if (he < A) {
                A= he;
                SS.clear();
                SS.push_back(j);
            } else if (he == A) {
                SS.push_back(j);
            }
        }
        int64 ress = 0;

        for (int D : SS) {
            int64 hh = 1LL << D;
            vector<int64> S(D + 1, 0);       
            vector<int> s1(D + 1, 1);    
            bool okk = true;
            for (int i=0;i<n;i++) {
                int64 base = (int64)a[i] * hh;
                if (base > b[i]) {
                    okk = false;
                    break;
                }
                int64 d = (int64)b[i] - base;
                for (int k=D;k>=0;k--) {
                    if (!d) break;
                    int64 pw = 1LL << k;
                    int64 c = d >> k; 
                    if (c) {
                        int t = D - k; 
                        S[t] += c;
                        if (c >= h) {
                            okk = false;
                            break;
                        }
                        s1[t] = (int)((int64)s1[t] *f2[(int)c] % h);
                        d -= c * pw;
                    }
                }
                if (!okk) 
                    break;
            }

            if (!okk) 
                continue;

            int64 AB = 1;
            for (int j = 0; j<= D;j++) {
                if (S[j] == 0) 
                    continue;
                if (S[j] >=h) {
                    AB = 0;
                    break;
                }
                int64 st = S[j]; 
                AB = AB * f1[(int)st] % h;
                AB =AB* s1[j] %h;
            }

            ress = (ress+ AB) % h;
        }

        cout << A << " " << ress %h << "\n";
    }

    return 0;
}
