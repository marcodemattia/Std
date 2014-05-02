#include <iostream>
#include <unordered_map>

int main()
{
  std::unordered_map<int, int> m;
  for( int i=0; i<1000000; ++i ) {
    m.insert(std::make_pair(i, i));
  }
}
