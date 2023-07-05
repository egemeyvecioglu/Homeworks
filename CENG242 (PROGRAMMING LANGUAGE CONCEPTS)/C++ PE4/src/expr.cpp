#include "expr.h"
#include "binary.h"
#include "unary.h"
#include "nullary.h"


namespace sym 
{

	Expr::Expr(const Const& c):	expr_(new Const(c.get_value())){}
	Expr::Expr(const Var& v):	expr_(new Var(v.get_variable())){}
	Expr::Expr(const __expr_t* e): expr_(e) {}
	Expr::Expr(const __expr_t& e)
	{
		if(e.is_nullary())
		{
			// cast to __nullary_op_t
			const __nullary_op_t& n = dynamic_cast<const __nullary_op_t&>(e);

			if(n.is_con())
			{
				// cast to Const
				const Const& c = dynamic_cast<const Const&>(n);
				// copy c into expr_
				expr_ = new Const(c.get_value());
			}
			else if(n.is_var())
			{
				// cast to Var
				const Var& v = dynamic_cast<const Var&>(n);
				expr_ = new Var(v.get_variable());
			}
		}
		if(e.is_binary())
		{
			// cast to __binary_op_t
			const __binary_op_t& b = dynamic_cast<const __binary_op_t&>(e);

			if(b.is_add())
			{
				// cast to AddOp
				const AddOp& a = dynamic_cast<const AddOp&>(b);
				expr_ = new AddOp(a);
			}
			
			if(b.is_mul())
			{
				// cast to MulOp
				const MulOp& m = dynamic_cast<const MulOp&>(b);
				expr_ = new MulOp(m);
			}
		}
		if(e.is_unary())
		{
			const __unary_op_t& u = dynamic_cast<const __unary_op_t&>(e);

			if(u.is_neg())
			{
				const NegOp& n = dynamic_cast<const NegOp&>(u);
				expr_ = new NegOp(n);
			}
			if(u.is_exp())
			{
				const ExpOp& ex = dynamic_cast<const ExpOp&>(u);
				expr_ = new ExpOp(ex);
			}
		}
	}
	Expr::Expr(const Expr& e)
	{
		//deepcopy e.expr_ into expr_

		if(e.expr_->is_nullary())
		{
			// cast to __nullary_op_t
			const __nullary_op_t& n = dynamic_cast<const __nullary_op_t&>(*(e.expr_));

			if(n.is_con())
			{
				// cast to Const
				const Const& c = dynamic_cast<const Const&>(n);
				// copy c into expr_
				expr_ = new Const(c);
			}
			else if(n.is_var())
			{
				// cast to Var
				const Var& v = dynamic_cast<const Var&>(n);
				expr_ = new Var(v);
			}
		}
		if(e.expr_->is_binary())
		{
			// cast to __binary_op_t
			const __binary_op_t& b = dynamic_cast<const __binary_op_t&>(*(e.expr_));

			if(b.is_add())
			{
				// cast to AddOp
				const AddOp& a = dynamic_cast<const AddOp&>(b);
				expr_ = new AddOp(a);
			}
			
			if(b.is_mul())
			{
				// cast to MulOp
				const MulOp& m = dynamic_cast<const MulOp&>(b);
				expr_ = new MulOp(m);
			}
		}
		if(e.expr_->is_unary())
		{
			const __unary_op_t& u = dynamic_cast<const __unary_op_t&>(*(e.expr_));

			if(u.is_neg())
			{
				const NegOp& n = dynamic_cast<const NegOp&>(u);
				expr_ = new NegOp(n);
			}
			if(u.is_exp())
			{
				const ExpOp& ex = dynamic_cast<const ExpOp&>(u);
				expr_ = new ExpOp(ex);
			}
		}
	}
		
	Expr::~Expr()
	{
		/*if(expr_ != nullptr)
	    {
	        delete expr_;
	        expr_ = nullptr;
	    }*/	
	}

	__expr_t* Expr::eval(const var_map_t& var_map) const
	{
		__expr_t* copy = expr_->eval(var_map);

		if(copy->is_nullary())
		{
			// cast to __nullary_op_t
			const __nullary_op_t& n = dynamic_cast<const __nullary_op_t&>(*copy);

			if(n.is_con())
			{
				// cast to Const
				const Const& c = dynamic_cast<const Const&>(n);
				// copy c into expr_
				return new Const(c);
			}
			else if(n.is_var())
			{
				// cast to Var
				const Var& v = dynamic_cast<const Var&>(n);
				return new Var(v);
			}
		}
		if(copy->is_binary())
		{
			// cast to __binary_op_t
			const __binary_op_t& b = dynamic_cast<const __binary_op_t&>(*copy);

			if(b.is_add())
			{
				// cast to AddOp
				const AddOp& a = dynamic_cast<const AddOp&>(b);
				return new AddOp(a);
			}
			
			if(b.is_mul())
			{
				// cast to MulOp
				const MulOp& m = dynamic_cast<const MulOp&>(b);
				return new MulOp(m);
			}
		}
		if(copy->is_unary())
		{
			const __unary_op_t& u = dynamic_cast<const __unary_op_t&>(*copy);

			if(u.is_neg())
			{
				const NegOp& n = dynamic_cast<const NegOp&>(u);
				return new NegOp(n);
			}
			if(u.is_exp())
			{
				const ExpOp& ex = dynamic_cast<const ExpOp&>(u);
				return new ExpOp(ex);
			}
		}
		
		return copy;
	}
	__expr_t* Expr::diff(const std::string& v) const 
	{ 
		__expr_t *copy = expr_->diff(v);

		if(copy->is_nullary())
		{
			const __nullary_op_t& n = dynamic_cast<const __nullary_op_t&>(*copy);

			if(n.is_con())
			{
				const Const& c = dynamic_cast<const Const&>(n);
				return new Const(c);
			}
			else if(n.is_var())
			{
				const Var& v = dynamic_cast<const Var&>(n);
				return new Var(v);
			}
		}
		if(copy->is_binary())
		{
			const __binary_op_t& b = dynamic_cast<const __binary_op_t&>(*copy);

			if(b.is_add())
			{
				const AddOp& a = dynamic_cast<const AddOp&>(b);
				return new AddOp(a);
			}
			
			if(b.is_mul())
			{
				const MulOp& m = dynamic_cast<const MulOp&>(b);
				return new MulOp(m);
			}
		}
		if(copy->is_unary())
		{
			const __unary_op_t& u = dynamic_cast<const __unary_op_t&>(*copy);

			if(u.is_neg())
			{
				const NegOp& n = dynamic_cast<const NegOp&>(u);
				return new NegOp(n);
			}
			if(u.is_exp())
			{
				const ExpOp& ex = dynamic_cast<const ExpOp&>(u);
				return new ExpOp(ex);
			}
		}

		return copy;
	}

	std::ostream& Expr::operator<< (std::ostream &out) const 
	{
		std::streampos	s = out.tellp();

		out << *expr_;

		if(out.tellp() == s) out << "0";
		
		return out;
	}
	
	bool Expr::operator==(const Expr& other) const 
	{
		return (*expr_ == *(other.expr_));
	}
	bool Expr::operator==(const __expr_t& other) const 
	{
		return (*expr_ == other);
	}
}                                                                   	
