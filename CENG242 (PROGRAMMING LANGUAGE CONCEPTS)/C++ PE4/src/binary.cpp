#include "binary.h"
#include "nullary.h"
#include <math.h>

namespace sym 
{
	bool AddOp::is_add() const {return true;}

	__expr_t* AddOp::eval(const var_map_t& vars) const
	{
		__expr_t *lhs = this->lhs_->eval(vars);
		__expr_t *rhs = this->rhs_->eval(vars);

		if(lhs->is_nullary() && rhs->is_nullary())
		{
			Const lhs_const = dynamic_cast<Const&>(*lhs);
			Const rhs_const = dynamic_cast<Const&>(*rhs);

			if(lhs_const.is_con() && rhs_const.is_con())
			{
				return new Const(lhs_const.get_value() + rhs_const.get_value());
			}
		}


		if (lhs->is_nullary() && dynamic_cast<__nullary_op_t*>(lhs)->is_con() && dynamic_cast<Const&>(*lhs).get_value() == 0)
		{
			return rhs;
		}
		if(rhs->is_nullary() && dynamic_cast<__nullary_op_t*>(rhs)->is_con() && dynamic_cast<Const&>(*rhs).get_value() == 0)
		{
			return lhs;
		}


		return new AddOp(lhs, rhs);

	}

	__expr_t* AddOp::diff(const std::string& v) const
	{
		return new AddOp(this->lhs_->diff(v), this->rhs_->diff(v));
	}

	std::ostream& AddOp::operator<< (std::ostream &out) const 
	{
		
		if(lhs_->is_nullary() && rhs_->is_nullary())
		{
		    if(dynamic_cast<const __nullary_op_t&>(*lhs_).is_con() && dynamic_cast<const __nullary_op_t&>(*rhs_).is_con())
		    {
		        if((dynamic_cast<const Const&>(*lhs_).get_value() + (dynamic_cast<const Const&>(*rhs_).get_value())) == 0)
		        {
		            return out;
		        }
		    }
		}
		
		if(lhs_->is_nullary() && dynamic_cast<const __nullary_op_t&>(*lhs_).is_con() && dynamic_cast<const Const&>(*lhs_).get_value() == 0)
		{
			this->rhs_->operator<<(out);
			return out;
		}
		else if(rhs_->is_nullary() && dynamic_cast<const __nullary_op_t&>(*rhs_).is_con() && dynamic_cast<const Const&>(*rhs_).get_value() == 0)
		{
			this->lhs_->operator<<(out);
			return out;
		}
		if(!lhs_ -> is_nullary()) out << "(";
		this->lhs_->operator<<(out);
		if(!lhs_ -> is_nullary()) out << ")";
		out << " + ";
		if(!rhs_ -> is_nullary()) out << "(";
		this->rhs_->operator<<(out);
        if(!rhs_ -> is_nullary()) out << ")";
		return out;
	}

	bool AddOp::operator==(const __expr_t& other_) const 
	{
		if(other_.is_binary())
		{
			if(dynamic_cast<const __binary_op_t&>(other_).is_add())
			{
				return (
					((dynamic_cast<const AddOp&>(other_).lhs_ == this-> lhs_) && (dynamic_cast<const AddOp&>(other_).rhs_ == this -> rhs_))
					|| ((dynamic_cast<const AddOp&>(other_).lhs_ == this-> rhs_) && (dynamic_cast<const AddOp&>(other_).rhs_ == this -> lhs_))
				);
			}
		}

		return false;
	}
}

namespace sym 
{
	bool MulOp::is_mul() const {return true;}

	__expr_t* MulOp::eval(const var_map_t& vars) const
	{
		__expr_t *lhs = this->lhs_->eval(vars);
		__expr_t *rhs = this->rhs_->eval(vars);

		if(lhs->is_nullary() && rhs->is_nullary())
		{
			Const lhs_const = dynamic_cast<Const&>(*lhs);
			Const rhs_const = dynamic_cast<Const&>(*rhs);

			if(lhs_const.is_con() && rhs_const.is_con())
			{
				return new Const(lhs_const.get_value() * rhs_const.get_value());
			}
		}


		if(lhs->is_nullary() && dynamic_cast<__nullary_op_t*>(lhs)->is_con() && dynamic_cast<Const&>(*lhs).get_value() == 1)
		{
			return rhs;
		}
		if(rhs->is_nullary() && dynamic_cast<__nullary_op_t*>(rhs)->is_con() && dynamic_cast<Const&>(*rhs).get_value() == 1)
		{
			return lhs;
		}

		return new MulOp(lhs, rhs);

	}

	__expr_t* MulOp::diff(const std::string& v) const
	{
		return (new AddOp(new MulOp(this->lhs_->diff(v), this->rhs_),new MulOp(this->lhs_, this->rhs_->diff(v))))->eval();
	}

	std::ostream& MulOp::operator<< (std::ostream &out) const
	{

		if(lhs_->is_nullary() && dynamic_cast<const __nullary_op_t&>(*lhs_).is_con())
		{
			if(dynamic_cast<const Const&>(*lhs_).get_value() == 1)
			{
        		this->rhs_->operator<<(out);
				return out;
			}
			if(dynamic_cast<const Const&>(*lhs_).get_value() == 0)
			{
        		
				return out;
			}

		}
		else if(rhs_->is_nullary() && dynamic_cast<const __nullary_op_t&>(*rhs_).is_con())
		{
			if(dynamic_cast<const Const&>(*rhs_).get_value() == 1)
			{	
        		this->lhs_->operator<<(out);
				return out;
			}	
			if(dynamic_cast<const Const&>(*rhs_).get_value() == 0)
			{	
				return out;
			}
		}
		if(!lhs_ -> is_nullary()) out << "(";
		this->lhs_->operator<<(out);
		if(!lhs_ -> is_nullary()) out << ")";
		out << " * ";
		if(!rhs_ -> is_nullary()) out << "(";
		this->rhs_->operator<<(out);
        if(!rhs_ -> is_nullary()) out << ")";
		return out;
	}

	bool MulOp::operator==(const __expr_t& other_) const
	{
		if(other_.is_binary())
		{
			if(dynamic_cast<const __binary_op_t&>(other_).is_add())
			{
				return (
					((dynamic_cast<const MulOp&>(other_).lhs_ == this-> lhs_) && (dynamic_cast<const MulOp&>(other_).rhs_ == this -> rhs_))
					|| ((dynamic_cast<const MulOp&>(other_).lhs_ == this-> rhs_) && (dynamic_cast<const MulOp&>(other_).rhs_ == this -> lhs_))
				);
			}
		}

		return false;
	}

}
