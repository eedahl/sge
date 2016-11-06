#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <GLFW/glfw3.h>

extern void glfwGetFramebufferSize(GLFWwindow*, int*, int*);

namespace sge::util
{
	float aspect_ratio(GLFWwindow* window)
	{
		int w{}, h{};
		glfwGetFramebufferSize(window, &w, &h);
		return static_cast<float>(w) / static_cast<float>(h);
	}

//For use with AABBvsCircle
template<class T>
	const T& clamp(const T& x, const T& upper, const T& lower) {
		return min(upper, max(x, lower));
	}

	std::string load_text(const std::string& fileName)
	{
		std::ifstream textFile;
		textFile.open(fileName);

		std::string text;
		if (textFile.is_open())
		{
			for (std::string line; std::getline(textFile, line);)
			{
				text += line + "\n";
			}
			std::cout << "Text file" << fileName << "successfully read." << std::endl;
		}
		else
		{
			std::cerr << "Cannot open text file:" << fileName << std::endl;
		}

		return text;

	}
}