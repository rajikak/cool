#ifndef PARSER_H
#define PARSER_H

#include "AST.h"
#include "Lexer.h"
#include "llvm/Support/raw_ostream.h"

class Parser {
  Lexer &Lex;
  Token Tok;
  bool HasError;

  void error() {
    llvm::errs() << "unexpected: " << Tok.getLiteral() << "\n";
    HasError = true;
  }

  void advance() { Lex.nextToken(Tok); }

  bool expect(Token::TokenType Type) {
    if (!Tok.is(Type)) {
      error();
      return false;
    }
    return true;
  }

  bool consume(Token::TokenType Type) {
    if (!expect(Type))
      return false;
    advance();
    return true;
  }

  AST *parseProgram();
  Expr *parseExpr();

public:
  Parser(Lexer &Lex) : Lex(Lex), HasError(false) { advance(); }
  bool hasError() const { return HasError; }
  AST *parse();

};

#endif
