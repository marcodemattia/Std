#include <iostream>
#include <map>

int main()
{
  std::map<int, int> m;

  for( int i=0; i<1000000; ++i ) {
    m.insert(std::make_pair(i, i));
  }
}
