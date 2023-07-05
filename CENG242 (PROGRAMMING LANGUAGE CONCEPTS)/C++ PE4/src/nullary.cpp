#include "type.h"
#include "nullary.h"

namespace sym 
{

	double Const::get_value() const { return value_;}
	Const::operator double() const {return value_;}

	bool Const::is_con() const {return true;}

	__expr_t* Const::eval(const var_map_t& var_map) const
	{
		return new Const(value_);
	}

	__expr_t* Const::diff(const std::string& v) const 
	{
		return new Const(0);
	}

	std::ostream& Const::operator<< (std::ostream &out) const 
	{
		out << value_;
		return out;
	}

	bool Const::operator==(const __expr_t& other) const 
	{
		//compares if its input (say other) is a sym::Const instance with the same variable as it’s variable.
		if(other.is_nullary())
		{
			if(dynamic_cast<const __nullary_op_t&>(other).is_con())
			{
				if(dynamic_cast<const Const&>(other).get_value() == value_)
				{
					return true;
				}
			}
		}
		return false;
	}
}

namespace sym 
{
	std::string Var::get_variable() const { return var_;}
	Var::operator std::string () const {return var_;}
	
	bool Var::is_var() const {return true;}

	__expr_t* Var::eval(const var_map_t& vars) const 
	{
		auto it =  vars.find(var_);
		if(it != vars.end())
		{
			return new Const(it->second);
		}
		else
		{
			return new Var(var_);
		}
	}

	__expr_t* Var::diff(const std::string& v) const 
	{
		if(var_.compare(v) == 0)
		{
			return new Const(1);
		}
		else
		{
			return new Const(0);
		} 
	}
	
	std::ostream& Var::operator<< (std::ostream &out) const 
	{
		out << var_;
		return out;
	}

	bool Var::operator==(const __expr_t& other) const
	{
		if(other.is_nullary())
		{
			if(dynamic_cast<const __nullary_op_t&>(other).is_var())
			{
				if((dynamic_cast<const Var&>(other).get_variable()).compare(var_) == 0)
				{
					return true;
				}
			}
		}
		return false;
	}
}
