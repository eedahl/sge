#pragma once
#include <string>

struct GLFWwindow;

namespace sge::util
{
	float aspect_ratio(GLFWwindow*);
	template<typename T>
	const T& clamp(const T& x, const T& upper, const T& lower);
	std::string load_text(const std::string&);
}