//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <numeric>
#include <iomanip>
#include <set>
#include <queue>

#include <iostream>
//#pragma GCC target("avx,avx2,bmi,bmi2,fma,abm,mmx,popcnt,lzcnt,tune=native")

#define int long long
#define ld long double

using namespace std;
random_device lal;
mt19937 rnd(lal());

const static ld inf = 1e18, mod = 1000000007;
const static ld pi = 3.141592653589793, eps = 1e-14;

int pow2(int power) {
	if (power == 0) { return 1; }
	return ((int)2) << (power - 1);
}

struct P {
	ld x, y;
};

struct V {
	ld x, y;
	V(P a, P b) :x(b.x - a.x), y(b.y - a.y) {}
};

ld rad_to_deg = 57.29577951308232;


struct Line {
	ld a, b, c, x, y;
	P start;

	Line(P f, P s) {
		x = s.x - f.x;
		y = s.y - f.y;
		start = f;

		a = (s.y - f.y);
		b = -(s.x - f.x);
		c = -f.x * s.y + f.y * s.x;
	}
};

P interception(Line f, Line s) {
	if (f.x * s.x + f.y * s.y == 0) {
		return { inf, inf };
	}
	ld x, y;
	y = (s.c * f.a - f.c * s.a) / (f.b * s.a - s.b * f.a);
	if (f.a == 0) {
		swap(f, s);
		y = (s.c * f.a - f.c * s.a) / (f.b * s.a - s.b * f.a);
	}
	x = (-f.b * y - f.c) / f.a;
	return { x, y };
}

ld dot(V f, V s) {
	return f.x * s.x + f.y * s.y;
}

ld cross(V f, V s) {
	return f.x * s.y - s.x * f.y;
}


// точка b - центр
ld angle(P a, P b, P c) {
	V f = V(a, b);
	V s = V(c, b);
	return abs(atan2(cross(f, s), dot(f, s)));
}


// a - центр
P get_biss_pos(P b, P a, P c) {
	ld lx = b.x, rx = c.x;
	ld ly = b.y, ry = c.y;

	while (abs(rx - lx) > eps || abs(ry - ly) > eps) {
		ld mid1 = lx + (rx - lx) / 3;
		ld mid1y = ly + (ry - ly) / 3;

		ld mid2 = lx + (rx - lx) / 3 * 2;
		ld mid2y = ly + (ry - ly) / 3 * 2;

		P f{ mid1, mid1y }, s{ mid2, mid2y };

		ld diff1 = abs(angle(f, a, c) - angle(b, a, f));
		ld diff2 = abs(angle(s, a, c) - angle(b, a, s));

		if (diff1 < diff2) {
			rx = mid2;
			ry = mid2y;
		}
		else {
			lx = mid1;
			ly = mid1y;
		}
	}
	return { lx, ly };
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(18);
}
