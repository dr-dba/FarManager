﻿#ifndef RECTANGLE_HPP_5553FC58_2069_43EC_AA37_98495C03BAD2
#define RECTANGLE_HPP_5553FC58_2069_43EC_AA37_98495C03BAD2
#pragma once

/*
rectangle.hpp

*/
/*
Copyright © 2018 Far Group
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../algorithm.hpp"
#include "../preprocessor.hpp"
#include "../rel_ops.hpp"
#include "../type_traits.hpp"
#include "point.hpp"

#include <type_traits>

//----------------------------------------------------------------------------

namespace detail
{
	IS_DETECTED(has_Left, T::Left);
	IS_DETECTED(has_Top, T::Top);
	IS_DETECTED(has_Right, T::Right);
	IS_DETECTED(has_Bottom, T::Bottom);
}

template<typename T>
struct rectangle_t: public rel_ops<rectangle_t<T>>
{
	T left;
	T top;
	T right;
	T bottom;

	rectangle_t() noexcept = default;

	rectangle_t(T const Left, T const Top, T const Right, T const Bottom) noexcept:
		left(Left),
		top(Top),
		right(Right),
		bottom(Bottom)
	{
		//assert(left <= right);
		//assert(top <= bottom);
	}

	template<typename Y>
	rectangle_t(rectangle_t<Y> const Rectangle) noexcept:
		rectangle_t(Rectangle.left, Rectangle.top, Rectangle.right, Rectangle.bottom)
	{
	}

	template<typename Y, REQUIRES(detail::has_Left<Y> && detail::has_Top<Y> && detail::has_Right<Y> && detail::has_Bottom<Y>)>
	rectangle_t(Y const& Rectangle) noexcept:
		rectangle_t(Rectangle.Left, Rectangle.Top, Rectangle.Right, Rectangle.Bottom)
	{
	}

	bool operator==(rectangle_t const& rhs) const
	{
		return
			left == rhs.left &&
			top == rhs.top &&
			right == rhs.right &&
			bottom == rhs.bottom;
	}

	[[nodiscard]]
	auto width() const noexcept { assert(left <= right); return right - left + 1; }

	[[nodiscard]]
	auto height() const noexcept { assert(top <= bottom); return bottom - top + 1; }

	[[nodiscard]]
	bool contains(point const& Point) const noexcept
	{
		return in_closed_range(left, Point.x, right) && in_closed_range(top, Point.y, bottom);
	}
};

using small_rectangle = rectangle_t<short>;
using rectangle = rectangle_t<int>;

#endif // RECTANGLE_HPP_5553FC58_2069_43EC_AA37_98495C03BAD2
