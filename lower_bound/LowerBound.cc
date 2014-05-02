#ifndef SiStripDelay_h
#define SiStripDelay_h

#include <vector>
#include <algorithm>
#include <stdint.h>
#include <sstream>


class SiStripDelay
{
 public:

  SiStripDelay() {}

  // Defined as public for genreflex
  struct Delay
  {
    Delay(const uint32_t inputDetId, const uint16_t inputCoarseDelay, const uint16_t inputFineDelay) :
      detId(inputDetId),
      coarseDelay(inputCoarseDelay),
      fineDelay(inputFineDelay)
    {}
    /// Default constructor needed by genreflex
    Delay() :
      detId(0),
      coarseDelay(255),
      fineDelay(0)
    {}
    uint32_t detId;
    unsigned char coarseDelay;
    unsigned char fineDelay;
  };
  typedef std::vector<Delay>::iterator delayIt;
  typedef std::vector<Delay>::const_iterator delayConstIt;

  bool put( const uint32_t detId, const uint16_t coarseDelay, const uint16_t fineDelay );

  /** Reduce ranges of consecutive detIdsAndApvs with the same latency and mode to
   * one value (the latest) so that lower_bound will return the correct value for
   * latency and mode.
   */
  void compress();

  /// Prints the number of ranges as well as the value of singleDelay and singleMode
  void printSummary(std::stringstream & ss) const;
  /// Prints the full list of all ranges and corresponding values of latency and mode
  void printDebug(std::stringstream & ss) const;

 private:

  struct OrderByDetId
  {
    bool operator()(const Delay & delay1, const uint32_t detId) const {
      return delay1.detId < detId;
    }
  };

  /// Used to compute the position with the lower_bound binary search
  // If put in the cc file it will not know about the typedefs and the Delay class
  const delayConstIt position(const uint32_t detId) const
  {
    if( delays_.empty() ) {
      // std::cout << "SiStripDelay: Error, range is empty" << std::endl;
      return delays_.end();
    }
    delayConstIt pos = lower_bound(delays_.begin(), delays_.end(), detId, OrderByDetId());
    return pos;
  }
  std::vector<Delay> delays_;
};

#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>

bool SiStripDelay::put( const uint32_t detId, const uint16_t coarseDelay, const uint16_t fineDelay )
{
  delayIt pos = lower_bound(delays_.begin(), delays_.end(), detId, OrderByDetId());

  if( pos != delays_.end() && pos->detId == detId ) {
    std::cout << "Value already inserted, skipping insertion" << std::endl;
    return false;
  }
  // std::cout << "Filling with: latency = " << latency << ", mode = " << mode << std::endl;
  delays_.insert(pos, Delay(detId, coarseDelay, fineDelay));

  return true;
}

void SiStripDelay::compress()
{
  std::cout << "Starting compression" << std::endl;
  std::cout << "Total number of elements before compression = " << delays_.size() << std::endl;

  // Go through the elements one by one and remove the current one if it has the same latency as the next one
  delayIt delay = delays_.begin();
  while( delay != delays_.end() ) {
    // If it is not the last and it has the same coarseDelay and fineDelay as the next one remove it
    if( ((delay+1) != delays_.end()) && ((delay+1)->fineDelay == delay->fineDelay) && ((delay+1)->coarseDelay == delay->coarseDelay) ) {
      delay = delays_.erase(delay);
    }
    else {
      ++delay;
    }
  }
  std::cout << "Total number of elements after compression = " << delays_.size() << std::endl;
}

void SiStripDelay::printSummary(std::stringstream & ss) const
{
  // uint16_t lat = singleDelay();
  // uint16_t mode = singleMode();
  // if( lat != 255 ) {
  //   ss << "All the Tracker has the same latency = " << lat << std::endl;
  // }
  // else {
  //   std::vector<uint16_t> allLatenciesVector;
  //   allLatencies(allLatenciesVector);
  //   if( allLatenciesVector.size() > 1 ) {
  //     ss << "There is more than one latency value in the Tracker" << std::endl;
  //   }
  //   else {
  //     ss << "Delay value is " << lat << " that means invalid" << std::endl;
  //   }
  // }

  // if( mode != 0 ) {
  //   ss << "All the Tracker has the same mode = " << mode << std::endl;
  // }
  // else {
  //   std::vector<uint16_t> allModesVector;
  //   allModes(allModesVector);
  //   if( allModesVector.size() > 1 ) {
  //     ss << "There is more than one mode in the Tracker" << std::endl;
  //   }
  //   else {
  //     ss << "Mode value is " << mode << " that means invalid" << std::endl;
  //   }
  // }

  // ss << "Total number of ranges = " << latencies_.size() << std::endl;
}

void SiStripDelay::printDebug(std::stringstream & ss) const
{
  // ss << "List of all the latencies and modes for the " << latencies_.size() << " ranges in the object:" << std::endl;
  // for( latConstIt it = latencies_.begin(); it != latencies_.end(); ++it ) {
  //   int detId = it->detIdAndApv >> 3;
  //   int apv = it->detIdAndApv & 7; // 7 is 0...0111
  //   ss << "for detId = " << detId << " and apv pair = " << apv << " latency = " << int(it->latency) << " and mode = " << int(it->mode) << std::endl;
  // }
}




#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main()
{

  SiStripDelay delays;

  std::ifstream inputFile;
  inputFile.open("pll_detid.txt");

  std::string line;
  unsigned int totalLines = 0;
  while(std::getline(inputFile, line)) {
    //Do here whatever you need to do
    if( line != "" ) {
      std::istringstream iss(line);
      std::vector<std::string> tokens;
      std::copy(std::istream_iterator<std::string>(iss),
		std::istream_iterator<std::string>(),
		std::back_inserter<std::vector<std::string> >(tokens));
      // std::cout << "tokens size = " << tokens.size() << std::endl;
      if( tokens.size() == 4 ) {
	// std::cout << "coarse delay = " << tokens[0] << ", fine delay = " << tokens[1] << ", detId = " << tokens[3] << std::endl;
	++totalLines;
	std::stringstream ss;
	ss << tokens[3];
	unsigned int detId;
	ss >> detId;
	std::stringstream ss1;
	ss1 << tokens[1];
	unsigned int fineDelay;
	ss1 >> fineDelay;
	std::stringstream ss2;
	ss2 << tokens[0];
	unsigned int coarseDelay;
	ss2 >> coarseDelay;
	std::cout << "detId = " << detId << ", coarseDelay = " << coarseDelay << ", fineDelay = " << fineDelay << std::endl;
	delays.put( detId, coarseDelay, fineDelay );
      }
    }
  }

  delays.compress();

  std::cout << "total lines = " << totalLines << std::endl;
  inputFile.close();
  return 0;
}

#endif
