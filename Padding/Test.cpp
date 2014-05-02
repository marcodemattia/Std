#include <iostream>

struct Delay
{
  Delay(const unsigned int inputDetId, const unsigned short inputCoarseDelay, const unsigned short inputFineDelay) :
    detId(inputDetId),
    // coarseDelay(inputCoarseDelay),
    fineDelay(inputFineDelay)
  {}
  /// Default constructor needed by genreflex
  Delay() :
    detId(0),
    // coarseDelay(255),
    fineDelay(255)
  {}
  unsigned int detId;
  // unsigned char coarseDelay;
  unsigned char fineDelay;
};

int main()
{
  Delay delay1;
  std::cout << "sizeof(delay1) = " << sizeof(delay1) << std::endl;
  return 0;
}
