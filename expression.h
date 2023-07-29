#pragma once
#include <iostream>

struct Number;
struct BinaryOperation;

struct Visitor
{
    virtual void visitNumber(Number const *number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const *operation) = 0;
    virtual ~Visitor() {}
};

struct Expression
{
    virtual double evaluate() const = 0;
    virtual void visit(Visitor *vistitor) const = 0;
    virtual ~Expression() {}
};

struct Number : Expression
{
    Number(double value)
        : value(value)
    {
    }

    double evaluate() const
    {
        return value;
    }

    void visit(Visitor *visitor) const
    {
        visitor->visitNumber(this);
    }

private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const *left, char op, Expression const *right)
        : left(left), op(op), right(right)
    {
    }
    ~BinaryOperation()
    {
        delete left;
        delete right;
    }

    char get_op() const
    {
        return op;
    }

    Expression const *get_left() const
    {
        return left;
    }

    Expression const *get_right() const
    {
        return right;
    }

    double evaluate() const
    {
        double result = 0;
        switch (op)
        {
        case '+':
            result = (left->evaluate()) + (right->evaluate());
            break;

        case '-':
            result = (left->evaluate()) - (right->evaluate());
            break;

        case '*':
            result = (left->evaluate()) * (right->evaluate());
            break;

        case '/':
            result = (left->evaluate()) / (right->evaluate());
            break;
        }
        return result;
    }

    void visit(Visitor *visitor) const
    {
        visitor->visitBinaryOperation(this);
    }

private:
    Expression const *left;
    Expression const *right;
    char op;
};


struct PrintVisitor : Visitor
{
    void visitNumber(Number const *number)
    {
        std::cout << number->evaluate();
    }

    void visitBinaryOperation(BinaryOperation const *bop)
    { 
        if (bop -> get_op() == '+' || bop -> get_op() == '-')
        {    
            std::cout << '(';
        }
        bop -> get_left() -> visit(this);
        std::cout << " " << bop -> get_op() << " ";
        bop -> get_right() -> visit(this);
        if (bop -> get_op() == '+' || bop -> get_op() == '-')
        {
            std::cout << ")";
        }
    }
};