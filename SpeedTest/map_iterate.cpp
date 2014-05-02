#include <iostream>
#include <map>

int main()
{
  std::map<int, int> m;

  for( int i=0; i<1000000; ++i ) {
    m.insert(std::make_pair(i, i));
  }

  for( std::map<int, int>::const_iterator it=m.begin(); it!=m.end(); ++it ) {
    int k = it->second;
  }
}
