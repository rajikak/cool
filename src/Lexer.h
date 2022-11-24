#ifndef LEXER_H
#define LEXER_H

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/MemoryBuffer.h"

using namespace std;

class Lexer;

class Token {
  friend class Lexer;

public:
  enum TokenType : unsigned short {
    UNKNOWN,     // unknown token
    END_OF_FILE, // end of file

    IDENT,  // identifiers
    NUMBER, // number

    // operators
    ASSIGN,    // "="
    PLUS,      //  "+"
    MINUS,     // "-"
    BANG,      // "!
    ASTERRISK, // "*"
    SLASH,     // "/"

    LT, // "<"
    GT, // ">"

    EQ,     // "=="
    NOT_EQ, // "!="

    // delimiters
    COMMA,     // ","
    SEMICOLON, // ";"

    LPARAN, // "("
    RPARAN, // ")"
    LBRACE, // "{"
    RBRACE, // "}"

    // keywords
    CLASS,
    ELSE,
    FALSE,
    FI,
    IF,
    INHERITS,
    ISVOID,
    LET,
    LOOP,
    POOL,
    THEN,
    WHILE,
    CASE,
    ESAC,
    NEW,
    OF,
    NOT,
    TRUE
  };

private:
  TokenType Type;
  llvm::StringRef Literal;

public:
  TokenType getType() const { return Type; }
  llvm::StringRef getLiteral() const { return Literal; }
  bool is(TokenType T) const { return Type == T; }
  bool isOneOf(TokenType T1, TokenType T2) const { return is(T1) || is(T2); }
  template <typename... Ts>
  bool isOneOf(TokenType T1, TokenType T2, Ts... Ks) const {
    return is(T1) || isOneOf(T2, Ks...);
  }
};

class Lexer {
private:
  const char *BufferStart; // input buffer is a C string ('\0')
  const char *BufferPtr;

  void newToken(Token &Tok, const char *TokEnd, Token::TokenType TokenType);
  void printToken(Token Tok);

public:
  Lexer(const llvm::StringRef &Buffer) {
    BufferStart = Buffer.begin();
    BufferPtr = BufferStart;
  }

  void nextToken(Token &Tok);
};

#endif
