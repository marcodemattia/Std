#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  int N = 10000000;

  std::vector<int> v;
  for( int i=0; i<N; ++i ) {
    v.push_back(i);
  }

  // Looping
  for( int i=0; i<N; ++i ) {
    int j = v[i];
  }
}
