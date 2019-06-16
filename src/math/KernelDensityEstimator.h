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
 */

#include <cstddef>
#include <vector>

class KernelDensityEstimator {
public:
	KernelDensityEstimator();

	void XLinspace(double t0, double t1, size_t N);
	void XSetCyclic(double cyclelength);
	void XSetLinear(void);

	void YInit(double value = 0.0);

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
	void Insert(double pos, kerneltype kernel = EpanechnikovKernel,
			double sigma = 1.0, double weight = 1.0);

	void Normalize(void);
	void NormalizeByWeightSum(void);

	void Attenuate(double pos, kerneltype kernel = EpanechnikovKernel,
			double sigma = 1.0, double weight = 1.0);

	size_t FindPeaks(const double minvalue = 0.001);
	size_t FindValleys(const double maxvalue = 0.001);
	size_t Count(void) const;
	double Pos(size_t index) const;
	double Value(size_t index) const;

	double Area(void) const;

	size_t Size(void) const; //!< Size of the array with the estimated distribution
	double& operator[](size_t index); //!< Access operator to the array with the estimated distribution
	const double& operator[](size_t index) const; //!< Read-only access operator to the array with the estimated distribution

	KernelDensityEstimator& operator *=(const double v);
	KernelDensityEstimator& operator /=(const double v);

	void Paint(void) const;

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
	bool cyclic;
	double cyclelength;
	size_t count;
	double weightsum;
	std::vector <double> x;
	std::vector <double> y;
	std::vector <double> resultpos;
	std::vector <double> resultvalue;
};

#endif /* SRC_MATH_KERNELDENSITYESTIMATOR_H_ */
