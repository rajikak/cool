#include "Lexer.h"
#include <iostream>
#include <map>

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

void Lexer::printToken(Token Tok) {
  map<Token::TokenType, string> m{{Token::UNKNOWN, "unknown"},
                                  {Token::END_OF_FILE, "eof"},
                                  {Token::IDENT, "ident"},
                                  {Token::NUMBER, "number"},
                                  {Token::ASSIGN, "="},
                                  {Token::PLUS, "+"},
                                  {Token::MINUS, "-"},
                                  {Token::BANG, "!"},
                                  {Token::ASTERRISK, "*"},
                                  {Token::SLASH, "/"},
                                  {Token::LT, "<"},
                                  {Token::GT, ">"},
                                  {Token::EQ, "=="},
                                  {Token::NOT_EQ, "!="},
                                  {Token::COMMA, ","},
                                  {Token::SEMICOLON, ";"},
                                  {Token::LPARAN, "("},
                                  {Token::RPARAN, ")"},
                                  {Token::LBRACE, "{"},
                                  {Token::RBRACE, "}"},
                                  {Token::CLASS, "class"},
                                  {Token::ELSE, "else"},
                                  {Token::FALSE, "false"},
                                  {Token::FI, "fi"},
                                  {Token::INHERITS, "inherits"},
                                  {Token::ISVOID, "isvoid"},
                                  {Token::LET, "let"},
                                  {Token::LOOP, "loop"},
                                  {Token::POOL, "pool"},
                                  {Token::THEN, "then"},
                                  {Token::WHILE, "while"},
                                  {Token::CASE, "case"}};

  cout << "{Type: " << m[Tok.getType()]
       << ", Literal: " << Tok.getLiteral().str() << "}" << endl;
}

void Lexer::nextToken(Token &token) {

  // skip white spaces
  while (*BufferPtr && charinfo::isWhilteSpace(*BufferPtr))
    ++BufferPtr;

  // if this is end of file just return that token
  if (!*BufferPtr) {
    token.Type = Token::END_OF_FILE;
  }

  switch (*BufferPtr) {
  case '=':
  default:
    if (charinfo::isLetter(*BufferPtr)) {
      // identifier or a key word
      const char *end = BufferPtr + 1;
      while (charinfo::isLetter(*end))
        ++end;
      llvm::StringRef Literal(BufferPtr, end - BufferPtr);
      newToken(token, end, Token::IDENT);
      printToken(token);
      return;
    } else if (charinfo::isDigit(*BufferPtr)) {

    } else {
      cout << "illegal token\n";
    }

    break;
  }
}

void Lexer::newToken(Token &Tok, const char *TokEnd, Token::TokenType Type) {
  Tok.Type = Type;
  Tok.Literal = llvm::StringRef(BufferPtr, TokEnd - BufferPtr);
  BufferPtr = TokEnd;
}
