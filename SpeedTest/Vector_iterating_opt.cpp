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

  // Iterating
  // for( std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it ) {
  std::vector<int>::const_iterator it = v.begin();
  std::vector<int>::const_iterator end = v.end();
  for( ; it != end; ++it ) {
    int j = *it;
  }
}
