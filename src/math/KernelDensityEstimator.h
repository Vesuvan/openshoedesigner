///////////////////////////////////////////////////////////////////////////////
// Name               : KernelDensityEstimator.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 05.06.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SRC_MATH_KERNELDENSITYESTIMATOR_H_
#define SRC_MATH_KERNELDENSITYESTIMATOR_H_

/*!\class KernelDensityEstimator
 * \brief Kernel density estimation
 *
 * This Class does a (cyclic) kernel density estimation.
 *
 * Common properties for Kernels are:
 *
 *  * %Symmetry: \f$ K(x) = K(-x)  \f$
 *
 *  * %Unit area: \f$ \int K(x)\cdot dx = 1 \f$
 *
 *  * %Kernel order k: \f$ \int x^n \cdot K(x)\cdot x = 0 \f$ for \f$ 0 < n < k \f$ and \f$ \int x^k \cdot K(x)\cdot x \neq 0\f$
 *
 * Common kernels of order k = 2:
 *  * Uniform
 *  * Triangle
 *  * Epanechnikov
 *  * Quartic
 *  * Triweight
 *  * Gaussian
 *
 * https://en.wikipedia.org/wiki/Kernel_density_estimation
 *
 * https://en.wikipedia.org/wiki/Kernel_(statistics)
 *
 * Kernel:      | Efficiency:
 * -------------|------------
 * Epanechnikov | 100   %
 * Cosine       |  99.9 %
 * Tricube      |  99.8 %
 * Quartic      |  99.4 %
 * Triweight    |  98.7 %
 * Triangular   |  98.6 %
 * Gaussian     |  95.1 %
 * Uniform      |  92.9 %
 * Logistic     |  88.7 %
 * Sigmoid      |  84.3 %
 *
 * * Epanechnikov (sharp, compact support)
 *
 * 		ke = @(x) 3/4*max((1-x.^2),0);
 *
 * * Gauss Kernel (standard normal distributed kernel)
 *
 * 		kg = @(x) exp(-(x.^2)/2)/sqrt(2*pi);
 *
 * * Picard Kernel (pointy kernel, drops to zero in reasonable distance)
 *
 * 		kp = @(x) exp(-abs(x))/2;
 *
 * * Cauchy Kernel (wide support)
 *
 * 		kc = @(x) 1./(pi*(1+x.^2));
 *
 *
 */

#include <cstddef>

#include "DependentVector.h"

class KernelDensityEstimator:public DependentVector {
public:
	KernelDensityEstimator();

	enum kerneltype {
		EpanechnikovKernel, //!< Parabolic window
		CosineKernel,
		TricubeKernel,
		QuarticKernel, //!< Biweight
		TriweightKernel,
		TriangularKernel,
		GaussianKernel,
		UniformKernel, //!< Rectangular window, "Boxcar"
		LogisticKernel,
		SigmoidKernel,
		SilvermanKernel,
		PicardKernel,
		CauchyKernel
	};

	void YInit(double value = 0.0);

	void Insert(double pos, double weight = 1.0, double sigma = 1.0,
			kerneltype kernel = EpanechnikovKernel);

	void Attenuate(double pos, double weight = 1.0, double sigma = 1.0,
			kerneltype kernel = EpanechnikovKernel);

	void Normalize(void);
	void NormalizeByWeightSum(void);

	static double EpanechnikovFunction(double x);
	static double CosineFunction(double x);
	static double TricubeFunction(double x);
	static double QuarticFunction(double x);
	static double TriweightFunction(double x);
	static double TriangularFunction(double x);
	static double GaussianFunction(double x);
	static double UniformFunction(double x);
	static double LogisticFunction(double x);
	static double SigmoidFunction(double x);
	static double SilvermanFunction(double x);
	static double PicardFunction(double x);
	static double CauchyFunction(double x);

private:
	size_t count;
	double weightsum;
};

#endif /* SRC_MATH_KERNELDENSITYESTIMATOR_H_ */
