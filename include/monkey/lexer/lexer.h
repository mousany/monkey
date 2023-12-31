#ifndef MONKEY_LEXER_LEXER_H_
#define MONKEY_LEXER_LEXER_H_

#include <monkey/lexer/token.h>

#include <iterator>
#include <memory>
#include <string>

namespace monkey::lexer {

class Lexer {
 public:
  explicit Lexer(std::string input);

  class Iterator;

  [[nodiscard]] Iterator begin() const;
  [[nodiscard]] Iterator end() const;
  [[nodiscard]] Iterator cbegin() const;
  [[nodiscard]] Iterator cend() const;

 private:
  std::string input_;
};

class Lexer::Iterator : public std::iterator<std::forward_iterator_tag, Token> {
 public:
  Iterator() = default;
  Iterator(std::string::const_iterator start_location,
           std::string::const_iterator end_location);
  Iterator(const Iterator& other);
  Iterator(Iterator&& other) noexcept = default;
  Iterator& operator=(const Iterator& other);
  Iterator& operator=(Iterator&& other) noexcept = default;

  ~Iterator() = default;

  Iterator& operator++();
  Iterator operator++(int);

  bool operator==(const Iterator& rhs) const;
  bool operator!=(const Iterator& rhs) const;

  Token operator*() const;
  Token operator->() const;

 private:
  class IteratorImpl;

  std::shared_ptr<IteratorImpl> impl_;
};

class Lexer::Iterator::IteratorImpl {
 public:
  IteratorImpl() = default;
  IteratorImpl(std::string::const_iterator start_location,
               std::string::const_iterator end_location);
  IteratorImpl(const IteratorImpl& other) = default;
  IteratorImpl(IteratorImpl&& other) noexcept = default;
  IteratorImpl& operator=(const IteratorImpl& other) = default;
  IteratorImpl& operator=(IteratorImpl&& other) noexcept = default;
  ~IteratorImpl() = default;

  bool operator==(const IteratorImpl& rhs) const;
  bool operator!=(const IteratorImpl& rhs) const;

  Token next_token();

 private:
  std::string::const_iterator current_location_;
  std::string::const_iterator peek_location_;
  std::string::const_iterator end_location_;

  [[nodiscard]] char current_char() const;
  [[nodiscard]] char peek_char() const;

  void read_char();
  void skip_whitespace();

  std::string read_identifier();
  std::string read_integer();
  std::string read_string();
};

}  // namespace monkey::lexer

#endif  // MONKEY_LEXER_LEXER_H_