#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/bind/bind.hpp>

/**
 * Test the find algorithm on a vector of objects.
 */

struct Delay
{
  Delay(const unsigned int inputDetId, const unsigned short inputCoarseDelay, const unsigned short inputFineDelay) :
    detId(inputDetId),
    coarseDelay(inputCoarseDelay),
    fineDelay(inputFineDelay)
  {}
  /// Default constructor needed by genreflex
  Delay() :
    detId(0),
    coarseDelay(255),
    fineDelay(255)
  {}
  unsigned int detId;
  unsigned char coarseDelay;
  unsigned char fineDelay;
};

struct FindDetId
{
  FindDetId(const unsigned int inputDetId) :
    detId(inputDetId)
  {}
  bool operator()(const Delay & delay) const
  {
    return( delay.detId == detId );
  }
  unsigned int detId;
};

int main()
{
  std::vector<Delay> delays;
  delays.push_back(Delay(0,0,0));
  delays.push_back(Delay(1,0,0));

  std::cout << "testing std::find with FindDetId" << std::endl;
  // std::find(delays.begin(), delays.end(), FindDetId(0));
  std::vector<Delay>::iterator it = std::find_if(delays.begin(), delays.end(), 
						 boost::bind(&Delay::detId, _1) == 0);

  std::find_if(delays.begin(), delays.end(), FindDetId(0));

  return 0;
}
