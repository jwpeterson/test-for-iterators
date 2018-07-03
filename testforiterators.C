#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstddef>
#include <sys/time.h>

#include "testwork.h"

const std::size_t vec_size = 1e1;
const std::size_t n_trials = 1e3;

// Version of stringize macro that takes multiple arguments...
#define _STRINGIZE(...) #__VA_ARGS__
#define STRINGIZE(...) _STRINGIZE(__VA_ARGS__)

#define TEST1 unsigned int, unsigned int
#define TEST2 unsigned int, unsigned int
#define TEST3 unsigned int, int
#define TEST4 unsigned int, std::size_t
#define TEST5 unsigned int, std::ptrdiff_t
#define TEST6 int, unsigned int
#define TEST7 int, int
#define TEST8 int, std::size_t
#define TEST9 int, std::ptrdiff_t
#define TEST10 std::size_t, unsigned int
#define TEST11 std::size_t, int
#define TEST12 std::size_t, std::size_t
#define TEST13 std::size_t, std::ptrdiff_t
#define TEST14 std::ptrdiff_t, unsigned int
#define TEST15 std::ptrdiff_t, int
#define TEST16 std::ptrdiff_t, std::size_t
#define TEST17 std::ptrdiff_t, std::ptrdiff_t

template <typename Iter, typename Value>
void do_trials(struct timeval & endtime)
{
  std::vector<Value> myvec(vec_size);
  for (Iter t=0, t_end=n_trials; t != t_end; ++t)
    {
      for (Iter i=0, i_end=vec_size; i != i_end; ++i)
        {
          myvec[i] = t + vec_size - i;
        }

      examinevector(myvec);
    }

  const int rval = gettimeofday(&endtime, NULL);
  assert (!rval);
}

int main(void)
{
  std::vector<struct timeval> times(4*4+1+1);
  std::vector<std::string> titles(times.size());
  {
    const int rval = gettimeofday(&times[0], NULL);
    assert (!rval);
  }

  do_trials<TEST1>(times[4*0+1]);   titles[4*0+1] = STRINGIZE(TEST1);
  do_trials<TEST2>(times[4*0+2]);   titles[4*0+2] = STRINGIZE(TEST2);
  do_trials<TEST3>(times[4*0+3]);   titles[4*0+3] = STRINGIZE(TEST3);
  do_trials<TEST4>(times[4*0+4]);   titles[4*0+4] = STRINGIZE(TEST4);
  do_trials<TEST5>(times[4*0+5]);   titles[4*0+5] = STRINGIZE(TEST5);

  do_trials<TEST6>(times[4*1+2]);   titles[4*1+2] = STRINGIZE(TEST6);
  do_trials<TEST7>(times[4*1+3]);   titles[4*1+3] = STRINGIZE(TEST7);
  do_trials<TEST8>(times[4*1+4]);   titles[4*1+4] = STRINGIZE(TEST8);
  do_trials<TEST9>(times[4*1+5]);   titles[4*1+5] = STRINGIZE(TEST9);

  do_trials<TEST10>(times[4*2+2]);   titles[4*2+2] = STRINGIZE(TEST10);
  do_trials<TEST11>(times[4*2+3]);   titles[4*2+3] = STRINGIZE(TEST11);
  do_trials<TEST12>(times[4*2+4]);   titles[4*2+4] = STRINGIZE(TEST12);
  do_trials<TEST13>(times[4*2+5]);   titles[4*2+5] = STRINGIZE(TEST13);

  do_trials<TEST14>(times[4*3+2]);   titles[4*3+2] = STRINGIZE(TEST14);
  do_trials<TEST15>(times[4*3+3]);   titles[4*3+3] = STRINGIZE(TEST15);
  do_trials<TEST16>(times[4*3+4]);   titles[4*3+4] = STRINGIZE(TEST16);
  do_trials<TEST17>(times[4*3+5]);   titles[4*3+5] = STRINGIZE(TEST17);

  std::cout << "Start = " << times[0].tv_sec << ',' << times[0].tv_usec << std::endl;

  std::vector<std::size_t> elapsed_times(times.size()-1);
  for (std::size_t i = 1; i != times.size(); ++i)
    {
      elapsed_times[i-1] =
        ((times[i].tv_sec - times[i-1].tv_sec)*1000000+
         (times[i].tv_usec - times[i-1].tv_usec));

      std::cout << "\nNext = " << times[i].tv_sec << ',' << times[i].tv_usec << std::endl;

      std::string title = "";
      if (i < titles.size())
        title = "(" + titles[i] + ")";

      std::cout << "Total time " << i << ", " << title << " = " << elapsed_times[i-1] << std::endl;

      if (i > 1)
        {
          double reldiff = ((double)(elapsed_times[i-1]) - (double)(elapsed_times[1])) /
                           (double)(elapsed_times[1]);
          std::cout << "Relative difference " << i << " = " << reldiff << std::endl;
        }
    }

  return 0;
}
