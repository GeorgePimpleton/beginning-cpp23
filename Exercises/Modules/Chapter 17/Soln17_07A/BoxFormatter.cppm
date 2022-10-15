export module box.formatter;

import box;
import std;

// Adding specific specializations to the std namespace is allowed
export template <>
class std::formatter<Box>
{
public:
  constexpr auto parse(auto& context)
  {
    // [context.begin(), context.end()) is a character range that contains a part of
    // the format string starting from the format specifications to be parsed,
    // e.g. in
    //
    //   std::format("My new box, {:.2}, is fabulous!", box)
    //
    // the range will contain ".2}, is fabulous!". The formatter should
    // parse specifiers until '}' or the end of the range.
    //
    // Our goal for this same example is to store "Box({:.2}, {:.2}, {:.2})" in m_box_format.
    // We first find the range where for instance ".2" is present,
    // and then copy that three times into a format string of the correct form.

    if (std::ranges::empty(context))  // May happen for empty {} format specifiers
    {
      m_box_format = "Box({}, {}, {})";
      return context.begin();
    }

    auto closing_brace = std::ranges::find(context, '}');

    if (closing_brace == context.end()) // If no '}' found, fail
    {
      throw std::format_error{ "missing closing braces, }" };
    }
    
    auto format = std::string(context.begin(), closing_brace);
    m_box_format = "Box({" + format + "}, {" + format + "}, {" + format + "})";

    return closing_brace;
  }

  auto format(const Box& box, auto& context)
  {
    return std::vformat_to(
      context.out(), 
      m_box_format,
      std::make_format_args(box.getLength(), box.getWidth(), box.getHeight())
    );
  }

private:
  std::string m_box_format;
};
