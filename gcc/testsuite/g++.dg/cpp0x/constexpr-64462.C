// PR c++/64462
// { dg-do compile { target c++11 } }

int x = 0;
int z;

int main() {
  constexpr int& y = x;
  [] { z = y; }();
}
