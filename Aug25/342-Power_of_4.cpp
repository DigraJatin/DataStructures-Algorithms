#include <bits/stdc++.h>

bool solve(int n){
	return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555) != 0;
}

int main(){
	int n;
	std::cin >> n;
	std::cout << solve(n);
	return 0;
}