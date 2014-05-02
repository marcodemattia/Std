#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> v;
  for( int i=0; i<10000; ++i ) {
    v.push_back(i);
  }

  // Looping
  for( int i=0; i<10000; ++i ) {
    int j = v[i];
  }

  // Looping, safer
  for( int i=0; i<10000; ++i ) {
    int j = v.at(i);
  }

  // Iterating
  for( std::vector<int> it = v.begin(); it != v.end(); ++it ) {
    int j = *it;
  }

  // Finding
  for( int i=0; i<20000; ++i ) {
    std::find(v.begin(), v.end(), i);
  }
}
