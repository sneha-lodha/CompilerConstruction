#include <stdio.h>
#include <stdlib.h>

#include "expr.h"

typedef struct Expr {
  nodetype tp;
  struct Expr *expr0; /* only used if tp != VALUE                   */
  struct Expr *expr1; /* only used if tp != VALUE and tp != NEGNODE */
  int value;       /* only used if tp == VALUE                   */
} *Expr;

static Expr makeExpr() {
  Expr e = malloc(sizeof(struct Expr));
  if (e == NULL) {
    fprintf(stderr, "Error: malloc() failed.\n");
    exit(EXIT_FAILURE);
  }
  return e;
}

static void checkNULL(char *funcname, Expr e) {
  if (e == NULL) {
    printf("\nFATAL ERROR: %s() applied to NULL pointer.\n", funcname);
    exit(EXIT_FAILURE);
  }
}
  
nodetype getNodeType(Expr e) {
  checkNULL("getNodeType", e);
  return e->tp;
}

int getValue(Expr e) {
  checkNULL("getValue", e);
  if (e->tp != VALUE) {
    printf("\nFATAL ERROR in getValue(): type of node != VALUE.\n");
    exit(EXIT_FAILURE);
  }
  return e->value;
}

Expr getLeftSubExpr(Expr e) {
  checkNULL("getLeftSubExpr", e);
  return e->expr0;
}

Expr getRightSubExpr(Expr e) {
  checkNULL("getRightSubExpr", e);
  return e->expr1;
}

Expr getUnarySubExpr(Expr e) {
  checkNULL("getUnarySubExpr", e);
  return e->expr0;
}

Expr makeValueExpr(int value) {
  Expr e = makeExpr();
  e->tp = VALUE;
  e->value = value;
  return e;
}

Expr makeNegExpr(Expr expr) {
  Expr e = makeExpr();
  e->tp = NEGNODE;
  e->expr0 = expr;
  return e;
}

Expr makeBinaryExpr(int oper, Expr lhs, Expr rhs) {
  Expr e = makeExpr();
  switch  (oper) {
  case ADD:
    e->tp = ADDNODE;
    break;
  case SUB:
    e->tp = SUBNODE;
    break;
  case MUL:
    e->tp = MULNODE;
    break;
  case DIV:
    e->tp = DIVNODE;
    break;
  case EXP:
    e->tp = EXPNODE;
    break;
  }
  e->expr0 = lhs;
  e->expr1 = rhs;
  return e;
}

void evalExpr(Expr e) {
  switch (e->tp) {
  case VALUE:
    printf("%d", e->value);
    break;
  case NEGNODE:
    printf("(-"); 
    evalExpr(e->expr0); 
    printf(")");
    break;
  case ADDNODE:
    printf("(");
    evalExpr(e->expr0);
    printf("+");
    evalExpr(e->expr1);
    printf(")");
    break;
  case SUBNODE:
    printf("(");
    evalExpr(e->expr0);
    printf("-");
    evalExpr(e->expr1);
    printf(")");
    break;
  case MULNODE:
    printf("(");
    evalExpr(e->expr0);
    printf("*");
    evalExpr(e->expr1);
    printf(")");
    break;
  case DIVNODE:
    printf("(");
    evalExpr(e->expr0);
    printf("/");
    evalExpr(e->expr1);
    printf(")");
    break;
  case EXPNODE:
    printf("(");
    evalExpr(e->expr0);
    printf("^");
    evalExpr(e->expr1);
    printf(")");
    break;
  }
}

void freeExpr(Expr e) {
  if (e->tp != VALUE) {
    freeExpr(e->expr0);
    if (e->tp != NEGNODE) {
      freeExpr(e->expr1);
    }
  }
  free(e);
}
