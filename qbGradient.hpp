/* ************************************************************************
		qbGradient class definition.
		
		qbGradient is a simple implementation of the gradient descent method for
		numerical optimization, intended to demonstrate the principles of the
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

#ifndef QBGRADIENT_H
#define QBGRADIENT_H

#include <vector>
#include <functional>

class qbGradient
{
	public:
		// Constructor (default) / destructor.
		qbGradient();
		~qbGradient();
	
		// Function to add a pointer to the object function.
		void SetObjectFcn(std::function<double(std::vector<double>*)> objectFcn);
		
		// Function to set the start point.
		// Note that this also sets the number of degrees of freedom.
		void SetStartPoint(const std::vector<double> startPoint);
	
		// Function to set the step size.
		void SetStepSize(double stepSize);
		
		// Function to set the maximum number of iterations.
		void SetMaxIterations(int maxIterations);
		
		// Function to set the gradient magnitude threshold (stopping condition).
		void SetGradientThresh(double gradientThresh);
	
		// Function to perform the optimization.
		bool Optimize(std::vector<double> *funcLoc, double *funcVal);
	
	// Private functions.
	private:
		// Function to compute the gradient in the specified dimension.
		double ComputeGradient(int dim);
		
		// Function to compute the gradient vector.
		std::vector<double> ComputeGradientVector();
		
		// Function to compute the gradient magnitude.
		double ComputeGradientMagnitude(std::vector<double> gradientVector);
	
	// Private member variables.
	private:
		// The number of degrees of freedom of the system.
		int m_nDims;
		
		// The step size.
		double m_stepSize;
		
		// The maximum number of iterations.
		int m_maxIter;
		
		// The gradient step size (h).
		double m_h;
		
		// The gradient magnitude threshold (stopping condition).
		double m_gradientThresh;
		
		// The start point.
		std::vector<double> m_startPoint;
		
		// The current point.
		std::vector<double> m_currentPoint;

		// Function-pointer to the object function.
		std::function<double(std::vector<double>*)> m_objectFcn;

};

#endif
