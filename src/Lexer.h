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
    ILLEGAL,     // illegal token
    END_OF_FILE, // end of file

    IDENT,  // identifiers
    NUMBER, // number

    // operators
    PLUS,      //  "+"
    MINUS,     // "-"
    ASTERRISK, // "*"
    SLASH,     // "/"
    TIDLE,     // "~"

    ASSIGN, // "<-"
    LT,     // "<"
    LT_EQ,  // "<="
    EQ,     // "="

    // delimiters
    COMMA,     // ","
    SEMICOLON, // ";"
    COLON,     // ":"

    LPARAN, // "("
    RPARAN, // ")"
    LBRACE, // "{"
    RBRACE, // "}"

    // keywords
    CLASS,
    ELSE,
    FALSE,
    TRUE,
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

  Token::TokenType lookupIdent(llvm::StringRef ident);
  void newToken(Token &Tok, const char *TokEnd, Token::TokenType TokenType);

public:
  Lexer(const llvm::StringRef &Buffer) {
    BufferStart = Buffer.begin();
    BufferPtr = BufferStart;
  }

  void nextToken(Token &Tok);
  void printToken(Token Tok);
};

#endif
