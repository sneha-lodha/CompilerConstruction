#ifndef EXPR_H
#define EXPR_H

#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define EXP 4

typedef enum {VALUE, NEGNODE, ADDNODE, SUBNODE, MULNODE, DIVNODE, EXPNODE
} nodetype;

typedef struct Expr *Expr;

nodetype getNodeType(Expr e);
int getValue(Expr e);
Expr getLeftSubExpr(Expr e);
Expr getRightSubExpr(Expr e);
Expr getUnarySubExpr(Expr e);
Expr makeValueExpr(int value);
Expr makeNegExpr(Expr expr);
Expr makeBinaryExpr(int oper, Expr lhs, Expr rhs);
void  evalExpr(Expr e);
void freeExpr(Expr e);
#endif /* EXPR_H */
