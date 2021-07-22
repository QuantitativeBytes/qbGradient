/* ************************************************************************
		Code to test the qbGradient class.
		
		qbGradient is a simple implementation of the gradient descent method for
		numerical optimization, indended to demonstrate the principles of the
		method for educational purposes.
		
		The code utilizes function pointers so that the user can specify an
		external object function to be minimized that can take any form over
		any number of variables.
		
		The code is intended to be studied along side the corresponding videos
		on the QuantitativeBytes YouTube channel. The specific videos relating
		to this code may be found here:
		
		Episode 1 - The theory of the gradient descent technique:
		https://youtu.be/BjkmFVv4ccw
		
		Episode 2 - Basic implementation in C++:
		https://youtu.be/eyCq3cNFpMU
		
		The QuantitativeBytes YouTube channel may be found here:
		www.youtube.com/c/QuantitativeBytes
		
		As this code is paired with the corresponding videos, pull requests will
		not be accepted.
		
		MIT LICENSE
		
		Copyright (c) 2021 Michael Bennett
		
		Permission is hereby granted, free of charge, to any person obtaining a copy
		of this software and associated documentation files (the "Software"), to deal
		in the Software without restriction, including without limitation the rights
		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
		copies of the Software, and to permit persons to whom the Software is
		furnished to do so, subject to the following conditions:

		The above copyright notice and this permission notice shall be included in all
		copies or substantial portions of the Software.

		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
		SOFTWARE.		
		
	 ************************************************************************/

#include "qbGradient.hpp"
#include <iostream>
#include <functional>

// Define the object function.
/* The object function can take any form and have any number of
	variables. Multiple variables are contained in the elements
	of the std::vector pointer funcLoc and access with:
	
	funcLoc->at(0);
	funcLoc->at(1);
	funcLoc->at(...);
	And so on.
	
	The function returns a single, double-precision floating
	point representing the value of the function at the location
	specified by the input variables. */
double ObjectFcn(std::vector<double> *funcLoc)
{
	// y = x^2
	double x = funcLoc->at(0);
	return (x * x);
}

int main(int argc, char* argv[])
{
	// Create a function pointer for our object function.
	std::function<double(std::vector<double>*)> p_ObjectFcn{ ObjectFcn };
	
	// Create a test instance of the qbGradient class.
	qbGradient solver;
	
	// Assign the object function.
	solver.SetObjectFcn(p_ObjectFcn);
	
	// Set a start point.
	std::vector<double> startPoint = {1.0};
	solver.SetStartPoint(startPoint);
	
	// Set the maximum number of iterations.
	solver.SetMaxIterations(50);
	
	// Set the step size.
	solver.SetStepSize(0.1);
	
	// Call optimize.
	std::vector<double> funcLoc;
	double funcVal;
	solver.Optimize(&funcLoc, &funcVal);
	
	// Output the result.
	std::cout << "Function location: " << funcLoc[0] << std::endl;
	std::cout << "Function value: " << funcVal << std::endl;
	
	return 0;
}
