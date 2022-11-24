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
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

LLVM_READNONE inline bool isAlphaNumeric(char c) {
  return isDigit(c) || isLetter(c);
}
} // namespace charinfo

void Lexer::printToken(Token Tok) {
  map<Token::TokenType, string> m{{Token::ILLEGAL, "illegal token"},
                                  {Token::END_OF_FILE, "eof"},
                                  {Token::IDENT, "identtifier"},
                                  {Token::NUMBER, "number"},
                                  {Token::ASSIGN, "operator"},
                                  {Token::PLUS, "operator"},
                                  {Token::MINUS, "operator"},
                                  {Token::ASTERRISK, "operator"},
                                  {Token::SLASH, "operator"},
                                  {Token::LT, "operator"},
                                  {Token::EQ, "operator"},
                                  {Token::COMMA, "comma"},
                                  {Token::SEMICOLON, "semicolon"},
                                  {Token::LPARAN, "leftparan"},
                                  {Token::RPARAN, "rightparan"},
                                  {Token::LBRACE, "leftbrace"},
                                  {Token::RBRACE, "rightbrace"},
                                  {Token::CLASS, "keyword"},
                                  {Token::ELSE, "keyword"},
                                  {Token::FALSE, "keyword"},
                                  {Token::TRUE, "keyword"},
                                  {Token::FI, "keyword"},
                                  {Token::INHERITS, "keyword"},
                                  {Token::ISVOID, "keyword"},
                                  {Token::LET, "keyword"},
                                  {Token::LOOP, "keyword"},
                                  {Token::POOL, "keyword"},
                                  {Token::THEN, "keyword"},
                                  {Token::WHILE, "keyword"},
                                  {Token::CASE, "keyword"}};

  cout << "Type: " << m[Tok.getType()]
       << ", Literal: " << Tok.getLiteral().str() << endl;
}

Token::TokenType Lexer::lookupIdent(llvm::StringRef ident) {
  map<string, Token::TokenType> keywords{
      {"class", Token::CLASS},
      {"else", Token::ELSE},
      {"false", Token::FALSE},
      {"true", Token::TRUE},
      {"fi", Token::FI},
      {"if", Token::IF},
      {"inherits", Token::INHERITS},
      {"isvoid", Token::ISVOID},
      {"let", Token::LET},
      {"loop", Token::LOOP},
      {"pool", Token::POOL},
      {"then", Token::THEN},
      {"while", Token::WHILE},
      {"case", Token::CASE},
      {"esac", Token::ESAC},
      {"new", Token::NEW},
      {"of", Token::OF},
      {"not", Token::NOT},
  };

  if (keywords.find(ident.str()) == keywords.end()) {
    // this is an identifier
    return Token::IDENT;
  }
  return keywords[ident.str()];
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
    newToken(token, BufferPtr + 1, Token::EQ);
    return;
  case '-':
    newToken(token, BufferPtr + 1, Token::MINUS);
    return;
  case '+':
    newToken(token, BufferPtr + 1, Token::PLUS);
    return;
  case '/':
    newToken(token, BufferPtr + 1, Token::SLASH);
    return;
  case '*':
    newToken(token, BufferPtr + 1, Token::ASTERRISK);
    return;
  case '~':
    newToken(token, BufferPtr + 1, Token::TIDLE);
    return;
  case '<':
    if (*(BufferPtr + 2) == '=') {
      // peek to see if the next character is `=`, so this token is `<=`
      newToken(token, BufferPtr + 2, Token::LT_EQ);
    } else if (*(BufferPtr + 2) == '-') {
		newToken(token, BufferPtr + 2, Token::ASSIGN);
    } else {
      newToken(token, BufferPtr + 1, Token::LT);
    }
    return;
  case '(':
    newToken(token, BufferPtr + 1, Token::LPARAN);
    return;
  case ')':
    newToken(token, BufferPtr + 1, Token::RPARAN);
    return;
  case '{':
    newToken(token, BufferPtr + 1, Token::LBRACE);
    return;
  case '}':
    newToken(token, BufferPtr + 1, Token::RBRACE);
    return;
  case ':':
	newToken(token, BufferPtr + 1, Token::SEMICOLON);
	return;
  case ',':
	newToken(token, BufferPtr + 1, Token::COMMA);
	return;
  default:
    if (charinfo::isLetter(*BufferPtr)) {
      // identifier or a key word
      const char *end = BufferPtr + 1;
      while (charinfo::isAlphaNumeric(*end))
        ++end;
      llvm::StringRef Literal(BufferPtr, end - BufferPtr);
      newToken(token, end, lookupIdent(Literal));
      printToken(token);
    } else if (charinfo::isDigit(*BufferPtr)) {
      const char *end = BufferPtr + 1;
      while (charinfo::isDigit(*end))
        ++end;
      newToken(token, end, Token::NUMBER);
    } else {
      newToken(token, BufferPtr + 1, Token::ILLEGAL);
    }
    return;
  }
}

void Lexer::newToken(Token &Tok, const char *TokEnd, Token::TokenType Type) {
  Tok.Type = Type;
  Tok.Literal = llvm::StringRef(BufferPtr, TokEnd - BufferPtr);
  BufferPtr = TokEnd; // point to next possible token
}
