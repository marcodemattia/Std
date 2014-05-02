#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  // Note: using a factor 10 smaller otherwise it cannot allocate the array and it segfaults
  int N = 1000000;

  int a[1000000];
  for( int i=0; i<N; ++i ) {
    a[i] = i;
  }

  // Looping
  for( int i=0; i<10; ++i ) {
    for( int j=0; j<N; ++j ) {
      int k = a[j];
    }
  }
}
