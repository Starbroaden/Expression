#include "expression.h"
int main()
{
// first we create objects for subexpression 7 * 2,5
Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
// then we use it in the expression for +
Expression * expr = new BinaryOperation(new Number(6), '+', sube);

// calculate and output the result: 28.5
std::cout << expr->evaluate() << std::endl;

// selected objects are deleted
delete expr;
}