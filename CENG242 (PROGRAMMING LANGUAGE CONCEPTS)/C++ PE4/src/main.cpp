#include <iostream>
#include "expr.h"
#include "binary.h"
#include "nullary.h"
#include "unary.h"
int main() {
	//sym::Const c = 2;
    sym::Const c1 = 2.0;
    sym::Var x = "x", y = "y";

    sym::ExpOp op(x.eval());
    sym::Expr de = op.diff( y );

   std::cout << "expression: " << op << std::endl;
   std::cout << "differention: " << de << std::endl;
    

   //std::cout << "eval: " << de << std::endl;
   //std::cout << "equality with " << c << ": " << (de == c ? "true" : "false") << std::endl;
	//std::cout << "expression: " << f << std::endl;
	//std::cout << "derivation: " << df << std::endl;
    
    //std::cout << "ended\n";
	return 0;
}
