#include <cctype>
#include <iostream>
#include <limits>

namespace odaci
{
  int countMax(std::istream & in, int & result)
  {
    int value = 0;
    int maxValue = 0;
    int count = 0;
    bool hasElements = false;
    bool countOverflow = false;
    while (in >> value)
    {
      const int next = in.eof() ? std::char_traits< char >::eof() : in.peek();
      if (next != std::char_traits< char >::eof() && !std::isspace(next))
      {
        return 1;
      }
      if (value == 0)
      {
        break;
      }
      if (!hasElements || value > maxValue)
      {
        hasElements = true;
        maxValue = value;
        count = 1;
        countOverflow = false;
      }
      else if (value == maxValue)
      {
        if (count == std::numeric_limits< int >::max())
        {
          countOverflow = true;
        }
        else
        {
          ++count;
        }
      }
    }
    if (!in)
    {
      return 1;
    }
    if (!hasElements || countOverflow)
    {
      return 2;
    }
    result = count;
    return 0;
  }
}

int main()
{
  int result = 0;
  int status = odaci::countMax(std::cin, result);
  if (status == 1)
  {
    std::cerr << "Error: not a sequence\n";
    return 1;
  }
  if (status == 2)
  {
    std::cerr << "Error: cannot compute maximum count\n";
    return 2;
  }
  std::cout << result << '\n';
  return 0;
}
