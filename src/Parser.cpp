#include "Parser.h"

AST *Parser::parse() {
	AST *Res = parseProgram();
	expect(Token::EOI);
	return Res;
}


AST *Parser::parseProgram() {
	Expr *E;
	llvm::SmallVector<llvm::StringRef, 8> Vars;

	return E;

}
