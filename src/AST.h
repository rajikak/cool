#ifndef AST_H
#define AST_H

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

class AST;
class Expr;
class BinaryOp;

class ASTVisitor {
	public:
		virtual void visit(AST &) {};
		virtual void visit(Expr &) {};
		virtual void visit(BinaryOp &) = 0;
};

class AST {
	public:
		virtual ~AST() {}
		virtual void accept(ASTVisitor &V) = 0;
};

class Expr: public AST {
	public:
		Expr() {}
};

class BinaryOp : public Expr {
	public:
		enum Operator {Plus, Minus, Mul, Div};

	private:
		Expr *Left;
		Expr *Right;
		Operator Op;

	public:
		BinaryOp(Operator Op, Expr *L, Expr *R)
			: Op(Op), Left(L), Right(R) {}

		Expr *getLeft() {
			return Left;
		}

		Expr *getRight() {
			return Right;
		}

		Operator getOperator() {
			return Op;
		}

		virtual void accept(ASTVisitor &V) override {
			V.visit(*this);
		}
};
	
#endif
