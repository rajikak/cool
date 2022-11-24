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

void Lexer::printToken(Token Tok) {
	cout << "{Type: " << Tok.getType() << ", Literal: " << Tok.getLiteral().data() << "}" << endl;
}
