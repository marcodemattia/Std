#include <iostream>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include <algorithm>

/**
 * Testing the speed of the lower_bound algorithm. <br>
 * The speed does not seem to depend on the type of container (array or std::vector) and
 * it depends on the total number of elements. <br>
 * For comparison, check the Boost/Unordered/unordered_map where the same test is done with
 * a boost::unordered_map. This is much faster (tested with a total number of elements
 * of 10000 and 15000). <br>
 * For a size of 15000 the std::map::find is also competitive with the lower_bound approach.
 */

struct Delay
{
  Delay() {}
  Delay(const unsigned int inputDetId, const double & inputDelay) :
    detId(inputDetId),
    delay(inputDelay)
  {}
  unsigned int detId;
  double delay;
};

struct OrderByDetId
{
  bool operator()(const Delay & delay1, const uint32_t detId) const {
    return delay1.detId < detId;
  }
};

int main()
{
  std::cout << "Testing the lower_bound" << std::endl;

  // int totalLoops = 10000;
  int totalLoops = 100;

  // Test with the std::vector
  // std::vector<Delay> delays;
  // Test with the array
  Delay delays[12000];

  int entries = 12000;
  // int entries = 100;

  for( int i=0; i<entries; ++i ) {
    // delays.push_back(Delay(i, 2.3+i));
    delays[i] = Delay(i, 2.3+i);
  }

  for( int loop = 0; loop < totalLoops; ++loop ) {

    // for( int i=0; i<entries; ++i ) {
    for( int i=0; i<20000; ++i ) {
      // std::vector<Delay>::const_iterator pos = lower_bound(delays.begin(), delays.end(), i, OrderByDetId());
      Delay* pos = std::lower_bound(delays, delays+entries, 1000, OrderByDetId());
    }
    // std::cout << "find(1000) = " << testMap.find(1000)->second << std::endl;
  }

  return 0;
}
