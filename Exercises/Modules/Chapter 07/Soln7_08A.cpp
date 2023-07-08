// Exercise 7-8. Testing whether something is a tautogram.
//
// The loop based on find_first_of/find_first_not_of we use here is only one of many possible solutions.
// See Soln7_08B for an alternate solution that first splits the text into a vector of words.
//
// Our solution in this file more or less assumes you enter only characters 
// that are either a letter or whitespace, 
// although it does cope with commas or dots that come directly after a word.
// The alternate solution is more robust against non-letter characters.

import std;

int main()
{
  std::string text;      // The text to be checked
  std::println("Enter some text terminated by *:");
  std::getline(std::cin, text, '*');

  const auto whitespace{ " \t\n\r\f\v" };  // Can be solved using std::isspace() as well...

  const std::size_t first_letter_index{ text.find_first_not_of(whitespace) };
  if (first_letter_index == std::string::npos)
  {
    // Is an empty string a tautogram? Let's not go there.
    return 0;
  }

  const char start_letter{ static_cast<char>(std::toupper(text[first_letter_index])) };
  bool tautogram{ true };

  for (std::size_t start_current_word{ first_letter_index };;)  // Use an indefinite loop (see the break; statements)
  {
    const std::size_t next_space_index{ text.find_first_of(whitespace, start_current_word) };
    if (next_space_index == std::string::npos)
    {
      break;
    }

    const std::size_t next_letter_index{ text.find_first_not_of(whitespace, next_space_index) };
    if (next_letter_index == std::string::npos)
    {
      break;
    }

    if (std::toupper(text[next_letter_index]) != start_letter)
    {
      tautogram = false;
      break;
    }

    start_current_word = next_letter_index;
  }
  
  std::println("The text that you entered {} a tautogram.", tautogram ? "is" : "is not");
  if (tautogram)
  {
    std::println("All words start with the letter {}.", start_letter);
  }
}
