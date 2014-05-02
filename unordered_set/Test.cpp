#include <boost/unordered_set.hpp>
using boost::unordered_set;
using std::string;
using std::cout;
using std::endl;

int main (void)
{
  // Initialize set
  unordered_set<string> s;
  s.insert("red");
  s.insert("green");
  s.insert("blue");

  // Search for membership
  if(s.find("red") != s.end())
    cout << "found red" << endl;
  if(s.find("purple") != s.end())
    cout << "found purple" << endl;
  if(s.find("blue") != s.end())
    cout << "found blue" << endl;

  return 0;
}
