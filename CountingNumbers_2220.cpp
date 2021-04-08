/*
 ~ Author    : @tridib_2003
 ~ Title     : Counting Numbers
 ~ Link      : https://cses.fi/problemset/task/2220/
*/

#include<bits/stdc++.h>
using namespace std;

#define ll                  long long
#define FIO                 ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

ll dp[20][10][2][2];

ll countingNumbers(string& num, int n, int prev, bool leading_zeros, bool tight) {

	if (n == 0)
		return 1;

	if (dp[n][prev][leading_zeros][tight] != -1)
		return dp[n][prev][leading_zeros][tight];

	int maxDigit = 9;

	if (tight)
		maxDigit = num[num.length() - n] - '0';

	ll ans = 0;

	for (int dig = 0; dig <= maxDigit; ++dig) {

		if (dig == prev && leading_zeros == 0)
			continue;

		ans += countingNumbers(num, n - 1, dig, (leading_zeros & (dig == 0)), tight & (dig == maxDigit));
	}

	return dp[n][prev][leading_zeros][tight] = ans;
}

void solve() {

	ll L, R;
	cin >> L >> R;

	--L;

	string L_str, R_str;
	L_str = to_string(L);
	R_str = to_string(R);

	memset(dp, -1, sizeof(dp));
	ll R_count = countingNumbers(R_str, R_str.length(), -1, 1, 1);

	memset(dp, -1, sizeof(dp));
	ll L_count = countingNumbers(L_str, L_str.length(), -1, 1, 1);

	cout << R_count - L_count;
}

int main() {

	FIO;

	int t = 1;
	// cin >> t;
	while (t--) {

		solve();
		cout << '\n';
	}

	return 0;
}
