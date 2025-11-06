/*
  Author     : Lincoln Craddock
  Description: A class for generating random boolean values. 
*/   

/************************************************************/
// Macro guard to prevent multiple inclusions

#ifndef RANDOMBOOL_H
#define RANDOMBOOL_H

/************************************************************/
// System includes

#include <random>

/************************************************************/

class RandomBool
{
public:

  RandomBool ()
      : RandomBool (std::random_device{}())
  { }

  RandomBool (int seed)
      : m_rng (seed),
        m_distr (0, std::numeric_limits<unsigned long long>::max()),
        m_currBools (0),
        m_currBit (0)
  { }

  bool
  nextBool ()
  {
    if (!m_currBit)
    {
        m_currBools = m_distr(m_rng);
        m_currBit = sizeof(unsigned long long) * 8;
    }
    return (m_currBools >> --m_currBit) & 1;
  }

  void
  seed (unsigned seed)
  {
    m_rng.seed(seed);
  }

private:

  std::mt19937 m_rng;
  std::uniform_int_distribution<unsigned long long> m_distr;
  unsigned long long m_currBools;
  std::size_t m_currBit;
};

/************************************************************/

#endif

/************************************************************/