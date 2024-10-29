#include <iostream>
#include <chrono>
#include <regex>
#include <cctype>

int conduct_performance_test(
  const std::string& text,
  const bool is_invalid_expected,
  std::function<bool(std::string)> func
)
{
  const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
  bool is_invalid = func(text);
  const std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();

  if(is_invalid != is_invalid_expected) {
    throw new std::exception();
  }

  const std::chrono::nanoseconds elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  return elapsed.count();
}

int is_invalid_regex_implementation(const std::string& text) {

  const std::string invalid_one = R"((!|@|&)(\w)+(!|@|&))";
  const std::string invalid_two = R"((!|@|&)(!|@|&)+)";

  std::regex invalid_pattern(invalid_one + "|" + invalid_two);

  return std::regex_search(text, invalid_pattern);
}

int is_invalid_loop_implementation(const std::string& text) {

  const auto is_starting_token = [](const char c) -> bool {
    return c == '!' || c == '@' || c == '&';
  };

  bool in_pattern = false;
  for(int i = 0; i < text.length(); ++i) {
    const char c = text[i];

    if(!in_pattern && is_starting_token(c)) {
      in_pattern = true;
      continue;
    }

    // Part of the sequence
    if(in_pattern && std::isalnum(c)) {
      continue;
    }

    // Did not hit space for end of sequence but found
    // another starting token. Invalid
    if(in_pattern && is_starting_token(c)) {
      return true;
    }

    // Space indicates end of sequence
    if(in_pattern && c == ' ') {
      in_pattern = false;
    }
  }

  return false;
}

void run_test(const std::string& text, const bool expected) {
  int milliseconds_regex = 0;
  int milliseconds_loop = 0;

  // Perform x times and take average
  const int times = 10;
  for(int i = 0; i < times; ++i) {
    milliseconds_loop += 
      conduct_performance_test(text, expected, is_invalid_loop_implementation);

    milliseconds_regex += 
      conduct_performance_test(text, expected, is_invalid_regex_implementation);
  }

  std::cout << "Performance Test For: " << text << std::endl;
  std::cout << "\tRegex: " << std::to_string((float)milliseconds_regex / times) << " nanoseconds" << std::endl;
  std::cout << "\tLoop : " << std::to_string((float)milliseconds_loop / times) << " nanoseconds" << std::endl << std::endl;
}

int main() {

  // A sequence starts with any of the 
  // tokens !, @, or &.
  // The sequence can then contain any 
  // number alphanumeric
  // characters. The sequence ends with a
  // space
  // An invalid sequence is when a start 
  // token appears before with the space end 
  // token
  
  // Ex. !asef! aefaedfdfdf == invalid
  // Ex. !akejf efeaf @asef == valid

  run_test("This is invalid: asef @sefaf !sef! asefaef @@!", true);

  run_test("This is very valid: !sef aefef @asef", false);

  run_test(R"(
    This is going to be a very long string that 
    doesn't even have the sequence and it won't be
    invalid because there is nothing to check)", false);
}