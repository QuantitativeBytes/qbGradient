/* ************************************************************************
		qbGradient class implementation.
		
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
#include <fstream>
#include <math.h>

// Constructor.
qbGradient::qbGradient()
{
	// Set defaults.
	m_nDims = 0;
	m_stepSize = 0.0;
	m_maxIter = 1;
	m_h = 0.001;
	m_gradientThresh = 1e-09;
}

// Destructor.
qbGradient::~qbGradient()
{
	// Tidy up anything that needs tidying up...
}

// Function to set the object function.
void qbGradient::SetObjectFcn(std::function<double(std::vector<double>*)> objectFcn)
{
	m_objectFcn = objectFcn;
}

// Function to set the start point.
// Note that this also sets the number of degrees of freedom.
void qbGradient::SetStartPoint(const std::vector<double> startPoint)
{
	// Copy the start point.
	m_startPoint = startPoint;
	
	// Determine the number of degrees of freedom.
	m_nDims = m_startPoint.size();
}

// Function to set the step size.
void qbGradient::SetStepSize(double stepSize)
{
	m_stepSize = stepSize;
}

// Function to set the maximum number of iterations.
void qbGradient::SetMaxIterations(int maxIterations)
{
	m_maxIter = maxIterations;
}

// Function to set the gradient magnitude threshold (stopping condition).
// The optimization stops when the gradient magnitude falls below this value.
void qbGradient::SetGradientThresh(double gradientThresh)
{
	m_gradientThresh = gradientThresh;
}

// Function to perform the actual optimization.
bool qbGradient::Optimize(std::vector<double> *funcLoc, double *funcVal)
{
	// Set the currentPoint to the startPoint.
	m_currentPoint = m_startPoint;
	
	// Loop up to max iterations or until threshold reached.
	int iterCount = 0;
	double gradientMagnitude = 1.0;
	while ((iterCount < m_maxIter) && (gradientMagnitude > m_gradientThresh))
	{
		// Compute the gradient vector.
		std::vector<double> gradientVector = ComputeGradientVector();
		gradientMagnitude = ComputeGradientMagnitude(gradientVector);
	
		// Compute the new point.
		std::vector<double> newPoint = m_currentPoint;
		for (int i=0; i<m_nDims; ++i)
		{
			newPoint[i] += -(gradientVector[i] * m_stepSize);
		}
		
		// Update the current point.
		m_currentPoint = newPoint;
		
		// Increment the iteration counter.
		iterCount++;
	}
	
	// Return the results.
	*funcLoc = m_currentPoint;
	*funcVal = m_objectFcn(&m_currentPoint);
	
	return 0;
}

/* Function to compute the gradient of the object function in the
	specified dimension. */
double qbGradient::ComputeGradient(int dim)
{
	// Make a copy of the current location.
	std::vector<double> newPoint = m_currentPoint;
	
	// Modify the copy, according to h and dim.
	newPoint[dim] += m_h;
	
	// Compute the two function values for these points.
	double funcVal1 = m_objectFcn(&m_currentPoint);
	double funcVal2 = m_objectFcn(&newPoint);
	
	// Compute the approximate numerical gradient.
	return (funcVal2 - funcVal1) / m_h;
}

// Function to compute the gradient vector.
std::vector<double> qbGradient::ComputeGradientVector()
{
	std::vector<double> gradientVector = m_currentPoint;
	for (int i=0; i<m_nDims; ++i)
		gradientVector[i] = ComputeGradient(i);
		
	return gradientVector;
}

// Function to compute the gradient magnitude.
double qbGradient::ComputeGradientMagnitude(std::vector<double> gradientVector)
{
	double vectorMagnitude = 0.0;
	for (int i=0; i<m_nDims; ++i)
		vectorMagnitude += gradientVector[i] * gradientVector[i];
		
	return sqrt(vectorMagnitude);
}

