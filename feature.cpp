#include <iostream>
#include <functional> //invoke
//#include <ext/typelist.h> //typelist apply
#include <tuple>

//auto ident = [] (int n) constexpr { return n; };
constexpr auto ident(int n) { return n; }
static_assert(ident(123) == 123);
/*
constexpr auto add2 = [] (int x, int y) {
  auto L = [=] { return x; };
  auto R = [=] { return y; };
  return [=] { return L() + R(); };
};


static_assert(add2(1, 2)() == 3);
*/
auto identity(auto obj) { return obj; }
auto add(auto a, auto b) { return a+b; }
auto sum(auto... args) { return (... + args); }

	
int main() {
	using namespace std;
	cout << identity(5) << '\n';
	cout << identity(3.14) << '\n';
	cout << identity("Hello World"s) << '\n';
	//cout << apply(add, {1,2,3}) << '\n';
	//cout << invoke(add, 1, 2) << '\n';
	cout << invoke([](auto x, auto y) { return x+y; }, 1, 2) << '\n';
	cout << sum(1,2,3) << '\n';
}
