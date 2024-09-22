#ifndef tree_h
#define tree_h

#include <iostream>
#include <string>
#include "../inc/token.h"
#include "visitors.h"


template <typename T>
class Expr {
public: 
	virtual std::string getType() const = 0;
	virtual T accept(Visitor<T> visitor) = 0;
};

template <typename T>
class Binary : public Expr<T> {
public: 
	//Class Constructor
	inline Binary(Expr<T>* left, Token<T>* op, Expr<T>* right) {
		this->left = left;
		this->op = op;
		this->right = right;
	}

	inline std::string getType() const override {
		return "Binary";
	}

	inline T accept(Visitor<T> visitor) override {
		return visitor.visitBinaryExpr(this);
	}

	Expr<T>* left;
	Token* op;
	Expr<T>* right;
};

template <typename T>
class Grouping : public Expr<T> {
public: 
	//Class Constructor
	inline Grouping(Expr<T>* expression) {
		this->expression = expression;
	}

	inline std::string getType() const override {
		return "Grouping";
	}

	inline T accept(Visitor<T> visitor) override {
		return visitor.visitGroupingExpr(this);
	}

	Expr<T>* expression;
};

template <typename T>
class Literal : public Expr<T> {
public: 
	//Class Constructor
	inline Literal(std::string value) {
		this->value = value;
	}

	inline std::string getType() const override {
		return "Literal";
	}

	inline T accept(Visitor<T> visitor) override {
		return visitor.visitLiteralExpr(this);
	}

	std::string value;
};

template <typename T>
class Unary : public Expr<T> {
public: 
	//Class Constructor
	inline Unary(Token* op, Expr<T>* right) {
		this->op = op;
		this->right = right;
	}

	inline std::string getType() const override {
		return "Unary";
	}

	inline T accept(Visitor<T> visitor) override {
		return visitor.visitUnaryExpr(this);
	}

	Token* op;
	Expr<T>* right;
};

#endif