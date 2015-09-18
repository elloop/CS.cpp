#ifdef _MSC_VER
//__pragma ("once")
#pragma once
#else
_Pragma("once")
#endif

namespace elloop {

	class Noncopyable {
	protected:
		Noncopyable() = default;
		~Noncopyable() = default;
		Noncopyable(const Noncopyable& rhs) = delete;
		Noncopyable& operator=(const Noncopyable & rhs) = delete;

		// Movable.
		//Noncopyable(Noncopyable&& rhs) = delete;
	};

}