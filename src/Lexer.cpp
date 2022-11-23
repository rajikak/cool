#include "Lexer.h"
#include <iostream>

using namespace std;

namespace charinfo {
LLVM_READNONE inline bool isWhilteSpace(char c) {
  return c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\r' ||
         c == '\n' || c == '\b';
}

LLVM_READNONE inline bool isDigit(char c) { return c >= '0' && c <= '9'; }

LLVM_READNONE inline bool isLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A');
}
} // namespace charinfo

void Lexer::nextToken(Token &token) {

  // skip white spaces
  while (*BufferPtr && charinfo::isWhilteSpace(*BufferPtr))
    ++BufferPtr;

  // if this is end of file just return that token
  if (!*BufferPtr) {
    token.Type = Token::END_OF_FILE;
  }

  char ch = *BufferPtr;
  switch (ch) {
 	case '=':

  }

}

void Lexer::newToken(Token &Result, const char *TokEnd, Token::TokenType Type) {


}
