#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> v;
  for( int i=0; i<10000; ++i ) {
    v.push_back(i);
  }

  // Finding
  for( int i=0; i<20000; ++i ) {
    std::find(v.begin(), v.end(), i);
  }
}
