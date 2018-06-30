#include <cassert>
#include <iostream>
#include <vector>
#include <sys/time.h>

#include "testwork.h"

const std::size_t vec_size = 1e1;
const std::size_t n_trials = 1e8;

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

  {
    const int rval = gettimeofday(&times[0], NULL);
    assert (!rval);
  }

  do_trials<unsigned int, unsigned int>(times[4*0+1]);
  do_trials<unsigned int, unsigned int>(times[4*0+2]);
  do_trials<unsigned int, int>(times[4*0+3]);
  do_trials<unsigned int, std::size_t>(times[4*0+4]);
  do_trials<unsigned int, std::ptrdiff_t>(times[4*0+5]);

  do_trials<int, unsigned int>(times[4*1+2]);
  do_trials<int, int>(times[4*1+3]);
  do_trials<int, std::size_t>(times[4*1+4]);
  do_trials<int, std::ptrdiff_t>(times[4*1+5]);

  do_trials<std::size_t, unsigned int>(times[4*2+2]);
  do_trials<std::size_t, int>(times[4*2+3]);
  do_trials<std::size_t, std::size_t>(times[4*2+4]);
  do_trials<std::size_t, std::ptrdiff_t>(times[4*2+5]);

  do_trials<std::ptrdiff_t, unsigned int>(times[4*3+2]);
  do_trials<std::ptrdiff_t, int>(times[4*3+3]);
  do_trials<std::ptrdiff_t, std::size_t>(times[4*3+4]);
  do_trials<std::ptrdiff_t, std::ptrdiff_t>(times[4*3+5]);

  std::cout << "Start = " << times[0].tv_sec << ',' << times[0].tv_usec << std::endl;

  std::vector<std::size_t> elapsed_times(times.size()-1);
  for (std::size_t i = 1; i != times.size(); ++i)
    {
      elapsed_times[i-1] =
        ((times[i].tv_sec - times[i-1].tv_sec)*1000000+
         (times[i].tv_usec - times[i-1].tv_usec));

      std::cout << "Next = " << times[i].tv_sec << ',' << times[i].tv_usec << std::endl;

      std::cout << "Total time " << i << " = " << elapsed_times[i-1] << std::endl;

      if (i > 1)
        {
          double reldiff = ((double)(elapsed_times[i-1]) - (double)(elapsed_times[1])) /
                           (double)(elapsed_times[1]);
          std::cout << "Relative difference " << i << " = " << reldiff << std::endl;
        }
    }

  return 0;
}
