///////////////////////////////////////////////////////////////////////////////
// Name               : CMAESOptimizer.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 05.10.2019
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

#ifndef SRC_MATH_CMAESOPTIMIZER_H_
#define SRC_MATH_CMAESOPTIMIZER_H_

/*!\class CMAESOptimizer
 * \brief Covariance Matrix Adaption Evolution Strategy Optimizer
 *
 * This class provides a CMA-ES Optimizer.
 * It is an adaption of the example code provided on the Wikipedia page:
 *
 * [Wikipedia page on CMA-ES](https://en.wikipedia.org/wiki/CMA-ES)
 *
 * The optimizer is written to be easiely exchanged with the NelderMeadOptimizer.
 *
 * ~~~~~~~~~~~~~~~{.cpp}
 * CMAESOptimizer optim;
 *
 * // Insert the startup parameter-set
 * optim.param.push_back(0.123);
 *
 * optim.Start();
 * while(optim.IsRunning()){
 *
 *    double x = optim.param[0];
 *    double f = x * x;
 *
 *    optim.SetError(f);
 * }
 *
 * printf("Optimum: x = %g\n", optim.param[0]);
 * ~~~~~~~~~~~~~~~
 *
 *
 * See also NelderMeadOptimizer.
 */

#include <cstddef>
#include <vector>

class CMAESOptimizer {
public:
	CMAESOptimizer();
	virtual ~CMAESOptimizer();

	std::vector <double> param; //!< Parameter of the system

	size_t lambda; //!< Samples per iteration (lambda >= 2), default: 6
	double sigmaInit; //!< Initial step size, default: 0.3

	double errorLimit; //!< Stop optimization if error is less than errorLimit. Default: 1e-3
	size_t evalLimit; //!< Stop optimization if the loop has run more than evalLimit times. Default: 1000

	bool keepCovarianceMatrix; //!< Speed up continued optimisations, if the system changes only a little. Default: false
	bool reevalBest; //!< After the optimization has finished, do an evaluation on the best result. Default: false

	void Start(void); //!< Setup the internal variables and start an optimisation
	bool IsRunning(void); //!< Loop control function for the main loop
	void SetError(double error); //!< Insert the error back into the solver
	void Stop(void); //!< Optional: Stops the optimization prematurely and copies the best result so far into 'param'.

	size_t EvaluationsDone(void) const; //!< Number of evaluations of the loop
	double ResidualError(void) const; //!< Error of the returned result

private:
	static double RandN(void);
	double sigma;

	bool initialized;
	size_t state;
	size_t index;
	size_t evaluationCount;

	size_t mu;
	std::vector <double> weights;
	double mueff;

	double cc;
	double cs;
	double c1;
	double cmu;
	double damps;

	std::vector <double> pc;
	std::vector <double> ps;
	std::vector <double> B;
	std::vector <double> D;
	std::vector <double> C;
	std::vector <double> invsqrtC;
	size_t eigeneval;
	double chiN;

	std::vector <double> arx;
	std::vector <double> arfitness;
	std::vector <size_t> arindex;
	std::vector <double> artmp;
	std::vector <double> xold;
	std::vector <double> temp;
};

#endif /* SRC_MATH_CMAESOPTIMIZER_H_ */
