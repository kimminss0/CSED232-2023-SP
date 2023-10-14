#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <string>

class parser {
 public:
  std::vector<int> load_image(const char *);

  std::vector<std::string> load_config(const char *);

  void write_result(const char *, const std::string &);
};

#endif