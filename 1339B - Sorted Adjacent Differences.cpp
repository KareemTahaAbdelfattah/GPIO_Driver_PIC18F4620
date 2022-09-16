/** ========================================**
 ** @Author: Kareem Taha Abdelfatah
 ** @Category: Codeforces problems solutions
 ** @brief: Problem Solving solutions
/** ========================================**/

#include<bits/stdc++.h>
#include<iterator>
using namespace std;
#define IO                  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define endll               "\n"
#define ll                  long long
#define LightOn(n, k)       ((n) | (1<<k))
#define Lightoff(n, k)      ((n) & (~(1<<k)))
#define IsOn(n, k)          ((n>>k)&1)
const long long N = 2e5 + 5;
const double PI = 3.14;
const double Prox = 1e-7;
map<ll, ll>mp;
ll a[N];
set<ll>s;

/*ll GCD(ll a, ll b){
    return (__gcd(a, b));
}

ll LCM(ll a, ll b){
    return ((a * b) / (GCD(a, b)));
}*/
// right shift (n) = num / pow(2, n);
// left shift (n) = num * pow(2, n);
// sleep(micro second); for slow execution
/*bool isPrime(ll n){
    for(ll i = 2; i*i <= n; i++) if(n % i == 0) return 0;
    return 1;
}

bool sortbyCond(const pair<int, int>& a,
                const pair<int, int>& b)
{
    if (a.first != b.first)
        return (a.first < b.first);
    else
       return (a.second > b.second);
}


bool sortbyCond1(const pair<int, int>& a,
                const pair<int, int>& b)
{
    if (a.first != b.first)
        return (a.first > b.first);
    else
       return (a.second > b.second);
}*/


int main()
{
    IO
    ll Tc; cin >> Tc;
    while(Tc--){
        vector<ll>(v);
        ll n, neg = 0, pos = 0; cin >> n;
        for(ll i = 0; i < n; i++) cin >> a[i];
        sort(a, a + n);
        ll l = 0, r = n - 1;
        while(r > l){
            v.push_back(a[r]);
            v.push_back(a[l]);
            r--;
            l++;
        }
        if(n % 2 != 0) v.push_back(a[n / 2]);
        reverse(v.begin(), v.end());
        for(ll i = 0; i < n; i++) cout << v[i] << " ";
        cout << endll;
    }
    return 0;
}
