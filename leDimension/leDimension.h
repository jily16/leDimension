#pragma once
#include <array>
namespace le
{
#define ALL_TEMPLATE_DECL_PARAMS int _A1, int _A2, int _A3, int _A4, int _A5, int _A6, int _A7
#define ALL_TEMPLATE_INSTANCE_PARAMS _A1,_A2,_A3,_A4,_A5,_A6,_A7

	template<ALL_TEMPLATE_DECL_PARAMS>
	struct dimension;
}
namespace utility
{
	template<typename _D1,typename _D2,typename _Func>
	struct dimension_transform
	{
		using type = le::dimension<
			_Func::template apply<_D1::arg1, _D2::arg1>::value,
			_Func::template apply<_D1::arg2, _D2::arg2>::value,
			_Func::template apply<_D1::arg3, _D2::arg3>::value,
			_Func::template apply<_D1::arg4, _D2::arg4>::value,
			_Func::template apply<_D1::arg5, _D2::arg5>::value,
			_Func::template apply<_D1::arg6, _D2::arg6>::value,
			_Func::template apply<_D1::arg7, _D2::arg7>::value>;
	};
	
	struct plus
	{
		template<int _L,int _R>
		struct apply
		{
			enum { value = _L + _R };
		};
	};

	struct minus
	{
		template<int _L,int _R>
		struct apply
		{
			enum { value = _L - _R };
		};
	};
}

namespace le
{
	template<ALL_TEMPLATE_DECL_PARAMS>
	struct dimension
	{
		enum
		{ arg1 = _A1, arg2 = _A2, arg3 = _A3, arg4 = _A4, arg5 = _A5, arg6 = _A6, arg7 = _A7 };
	};

	template<typename _Dimension>
	struct quality;

	typedef quality<dimension<0, 0, 0, 0, 0, 0, 0>> scalar;
	typedef quality<dimension<1, 0, 0, 0, 0, 0, 0>> mass;			//Kg
	typedef quality<dimension<0, 1, 0, 0, 0, 0, 0>> length;			//m
	typedef quality<dimension<0, 0, 1, 0, 0, 0, 0>> time;			//s
	typedef quality<dimension<0, 0, 0, 1, 0, 0, 0>> current;		//A
	typedef quality<dimension<0, 0, 0, 0, 1, 0, 0>> temperature;	//K
	typedef quality<dimension<0, 0, 0, 0, 0, 1, 0>> illumination;	//cd
	typedef quality<dimension<0, 0, 0, 0, 0, 0, 1>> AOS;			//mol

	template<typename _Dimension>
	struct quality
	{
		typedef _Dimension type;
		double value;
		explicit quality(double const &_V) :value(_V)
		{}
		quality &operator=(quality const &_Other);
		quality &operator+=(quality const &_Other);
		quality &operator+=(double const &_V);
		quality &operator-=(quality const &_Other);
		quality &operator-=(double const &_V);
		quality &operator*=(scalar const &_S);
		quality &operator*=(double const &_V);
		quality &operator/=(scalar const &_S);
		quality &operator/=(double const &_V);
	};

	template<typename _Dimension>
	quality<_Dimension> operator+(
		quality<_Dimension> const &_Q1,
		quality<_Dimension> const &_Q2)
	{
		return quality<_Dimension>(_Q1.value + _Q2.value);
	}


	template<typename _Dimension>
	inline quality<_Dimension> & quality<_Dimension>::operator=(quality<_Dimension> const & _Other)
	{
		if (this == &_Other) return *this;
		this->value = _Other.value;
		return *this;
	}

	template<typename _Dimension>
	inline quality<_Dimension> & quality<_Dimension>::operator+=(
		quality<_Dimension> const &_Other)
	{
		this->value += _Other.value;
		return *this;
	}

	template<typename _Dimension>
	quality<_Dimension> operator+(
		quality<_Dimension> const &_Q,
		double const &_V)
	{
		return quality<_Dimension>(_Q.value + _V);
	}

	template<typename _Dimension>
	quality<_Dimension> operator+(
		double const &_V,
		quality<_Dimension> const &_Q)
	{
		return quality<_Dimension>(_V + _Q.value);
	}

	template<typename _Dimension>
	inline quality<_Dimension> & quality<_Dimension>::operator+=(
		double const &_V)
	{
		this->value += _V;
		return *this;
	}

	template<typename _Dimension>
	quality<_Dimension> operator-(
		quality<_Dimension> const &_Q1,
		quality<_Dimension> const &_Q2)
	{
		return quality<_Dimension>(_Q1.value - _Q2.value);
	}


	template<typename _Dimension>
	inline quality<_Dimension> & quality<_Dimension>::operator-=(
		quality<_Dimension> const &_Other)
	{
		this->value -= _Other.value;
		return *this;
	}

	template<typename _Dimension>
	quality<_Dimension> operator-(
		quality<_Dimension> const &_Q,
		double const &_V)
	{
		return quality<_Dimension>(_Q.value - _V);
	}

	template<typename _Dimension>
	quality<_Dimension> operator-(
		double const &_V,
		quality<_Dimension> const &_Q)
	{
		return quality<_Dimension>(_V - _Q.value);
	}

	template<typename _Dimension>
	inline quality<_Dimension> & quality<_Dimension>::operator-=(
		double const &_V)
	{
		this->value -= _V;
		return *this;
	}

	template<typename _Dimension>
	inline quality<_Dimension> & quality<_Dimension>::operator*=(scalar const & _S)
	{
		this->value *= _S.value;
		return *this;
	}

	template<typename _Dimension>
	inline quality<_Dimension> & quality<_Dimension>::operator*=(double const & _V)
	{
		this->value *= _V;
		return *this;
	}

	template<typename _Dimension>
	inline quality<_Dimension> & quality<_Dimension>::operator/=(scalar const & _S)
	{
		this->value /= _S.value;
		return *this;
	}

	template<typename _Dimension>
	inline quality<_Dimension> & quality<_Dimension>::operator/=(double const & _V)
	{
		this->value /= _V;
		return *this;
	}

	template<typename _D1,typename _D2>
	quality<typename utility::dimension_transform<_D1,_D2,utility::plus>::type>
		operator*(quality<_D1> const &_Q1, quality<_D2> const &_Q2)
	{
		quality<typename utility::dimension_transform<_D1, _D2, utility::plus>::type>
			ret(_Q1.value * _Q2.value);
		return ret;
	}

	template<typename _D1, typename _D2>
	quality<typename utility::dimension_transform<_D1, _D2, utility::minus>::type>
		operator/(quality<_D1> const &_Q1, quality<_D2> const &_Q2)
	{
		quality<typename utility::dimension_transform<_D1, _D2, utility::minus>::type>
			ret(_Q1.value / _Q2.value);
		return ret;
	}

	template<typename _Dimension>
	bool operator==(quality<_Dimension> const &_L, quality<_Dimension> const &_R)
	{
		return _L.value == _R.value;
	}

	template<typename _Dimension>
	bool operator>(quality<_Dimension> const &_L, quality<_Dimension> const &_R)
	{
		return _L.value > _R.value;
	}

	template<typename _Dimension>
	bool operator<(quality<_Dimension> const &_L, quality<_Dimension> const &_R)
	{
		return _L.value < _R.value;
	}

	template<typename _Dimension>
	bool operator==(quality<_Dimension> const &_Q, double const &_V)
	{
		return _Q.value == _V;
	}

	template<typename _Dimension>
	bool operator<(quality<_Dimension> const &_Q, double const &_V)
	{
		return _Q.value < _V;
	}

	template<typename _Dimension>
	bool operator>(quality<_Dimension> const &_Q, double const &_V)
	{
		return _Q.value > _V;
	}

	template<typename _Dimension>
	bool operator==(double const &_V, quality<_Dimension> const &_Q)
	{
		return _Q.value == _V;
	}

	template<typename _Dimension>
	bool operator<(double const &_V, quality<_Dimension> const &_Q)
	{
		return _Q.value < _V;
	}

	template<typename _Dimension>
	bool operator>(double const &_V, quality<_Dimension> const &_Q)
	{
		return _Q.value > _V;
	}
}