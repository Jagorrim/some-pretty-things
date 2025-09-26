#include <bits/stdc++.h>

using ll = long long;
using namespace std;

double pow2(ll power) {
    if (power == 0) { return 1; }
    return (double) (((ll) 2) << (power - 1));
}

const static ll precision = 32;

double _binpow(double num, ll n) {
    if (n == 0) {
        return 1;
    } else if (n % 2 == 0) {
        double res = _binpow(num, n / 2);
        return res * res;
    } else {
        return _binpow(num, n - 1) * num;
    }
}


double calc_root(double num, ll power) {
    double l = 0, r = num, mid;
    for (ll i = 0; i < precision; ++i) {
        mid = (l + r) / 2;
        double res = _binpow(mid, power);
        if (res < num) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return l;
}


double calc_fract(double num, double fract) {
    double num_ = 0;
    double ans = 1;
    for (ll i = 1; i <= precision; ++i) {
        if (num_ + (1 / pow2(i)) < fract) {
            num_ += (1 / pow2(i));
            ans *= calc_root(num, pow2(i));
        }
    }
    return ans;
}


double binpow(double num, double power) {
    double fract = power - (double) floor(power);
    double res = _binpow(num, floor(power));
    res *= calc_fract(num, fract);

    return res;
}


signed main() {
    while (true) {
        double num, power;
        cin >> num >> power;
        cout << binpow(num, power) << '\n';
    }
}
