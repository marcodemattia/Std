#include <iostream>
#include <unordered_map>

int main()
{
  std::unordered_map<int, int> map;

  for( int i=0; i<10000; ++i ) {
    map.insert(std::make_pair(i, i*3));
  }

  std::cout << map[100] << std::endl;
  std::cout << map.find(100)->second << std::endl;
}
