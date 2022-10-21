// Exceptions may result in resource leaks!
import std;
import troubles;
import raii;

double computeValue(size_t x);         // A function to compute a single value
double* computeValues(size_t howMany); // A function to compute an array of values

int main()
{
  try
  {
    double* values{ computeValues(10'000) };
    // Unfortunately we won't be making it this far...
    delete[] values;
  }
  catch (const Trouble&)
  {
    std::println("No worries: I've caught it!");
  }
}

double* computeValues(size_t howMany)
{
  DoubleArrayRAII values{ howMany };
  for (size_t i{}; i < howMany; ++i)
    values[i] = computeValue(i);
  return values.release();
}

double computeValue(size_t x)
{
  if (x < 100)
    return std::sqrt(x);   // Return the square root of the input argument
  else
    throw Trouble{ "The trouble with trouble is, it starts out as fun!" };
}

