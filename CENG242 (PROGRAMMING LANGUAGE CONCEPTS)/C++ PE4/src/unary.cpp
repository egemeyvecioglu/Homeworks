#include "nullary.h"
#include "unary.h"
#include "binary.h"
#include <math.h>

namespace sym 
{
	//Constructor:  takes a expression sub-treepointed to by a root 
	//class pointer (i.e. sym:: expr t) as an argument and sets it to its 
	//attribute (let’s say) operand.


	bool NegOp::is_neg() const {return true;}

	__expr_t* NegOp::eval(const var_map_t& vars) const
	{
		if(operand -> is_nullary())
		{
			if(dynamic_cast<const __nullary_op_t&>(*operand).is_con())
			{
				return new Const(-(dynamic_cast<const Const&>(*operand).get_value()));
			}
		}

		return new NegOp(operand -> eval(vars));
	}

	__expr_t* NegOp::diff(const std::string& v) const 
	{
		return new NegOp(operand -> diff(v));
	}

	std::ostream& NegOp::operator<< (std::ostream &out) const 
	{
		out << "-";
		if(	!operand -> is_nullary())	out << "(";
		operand -> operator<<(out);
		if(	!operand -> is_nullary())	out << ")";

		return out;
	}

	bool NegOp::operator==(const __expr_t& other_) const 
	{
		if(other_.is_unary())
		{
			if(dynamic_cast<const __unary_op_t&>(other_).is_neg())
			{
				return (*operand == *(dynamic_cast<const NegOp&>(other_).operand));
			}
		}

		return false;
	}

}

namespace sym 
{
	bool ExpOp::is_exp() const {return true;}

	__expr_t* ExpOp::eval(const var_map_t& vars) const 
	{
		//returns a pointer to a new sym::Const with an exponent “variable” if its’ operand 
		//is a constant with “variable”. Otherwise, it returns a pointer to a new
		//exponentiation instance whose operand points to a sub- tree that is equal to one 
		//pointed to by operand.

		if(operand -> is_nullary())
		{
			if(dynamic_cast<const __nullary_op_t&>(*operand).is_con())
			{
				return new Const(std::exp((dynamic_cast<const Const&>(*operand)).get_value()));
			}
		}

		return new ExpOp(operand -> eval(vars));
	}

	__expr_t* ExpOp::diff(const std::string& v) const 
	{
		//returns a pointer to a new expression tree that is equal to the differentiation of the tree pointed to by operand.

		//∇(ExpOp(op)) = MulOp(∇(op), ExpOp(op))

		return new MulOp(operand -> diff(v), this);
	}

	std::ostream& ExpOp::operator<< (std::ostream &out) const 
	{
		out << "e^";
		if(	!operand -> is_nullary())	out << "(";
		out << *operand;
		if(	!operand -> is_nullary())	out << ")";

		return out;
	}

	bool ExpOp::operator==(const __expr_t& other_) const 
	{
		// compares if its input argument (say other) is a sym::ExpOp instance with 
		// a sub-tree that is (recursively) equal to the one pointed to by operand.

		if(other_.is_unary())
		{
			if(dynamic_cast<const __unary_op_t&>(other_).is_exp())
			{
				return (*operand == *(dynamic_cast<const ExpOp&>(other_).operand));
			}
		}

		return false;
	}

}
