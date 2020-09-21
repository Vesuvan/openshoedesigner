///////////////////////////////////////////////////////////////////////////////
// Name               : Kernel.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 31.05.2020
// Copyright          : (C) 2020 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef SRC_MATH_KERNEL_H_
#define SRC_MATH_KERNEL_H_

/*!\struct Kernel
 * \brief Collection of mathematical kernel and their integrals
 *
 * Usage:
 *
 * 		Kernel::Epanechnikov
 *
 * and
 *
 * 		Kernel::Integrated::Epanechnikov
 *
 * Every kernel and integrated kernel is a function with one parameter
 *
 *      double kernelname(double x)
 *
 * All Kernel%s are unit-kernels that have an area of 1.
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
 * https://en.wikipedia.org/wiki/Kernel_(statistics)
 *
 * %Kernel:     | Efficiency: | %Unit support: |
 * -------------|-------------|----------------|
 * Epanechnikov | 100   %     | Yes            |
 * Cosine       |  99.9 %     | Yes            |
 * Tricube      |  99.8 %     | Yes            |
 * Quartic      |  99.4 %     | Yes            |
 * Triweight    |  98.7 %     | Yes            |
 * Triangular   |  98.6 %     | Yes            |
 * Gaussian     |  95.1 %     | No             |
 * Uniform      |  92.9 %     | Yes            |
 * Logistic     |  88.7 %     | No             |
 * Sigmoid      |  84.3 %     | No             |
 * Silverman    |             | No             |
 * Picard       |             | No             |
 * Cauchy       |             | No             |
 *
 * Kernel with unit support evaluate to 0 for x < -1 or x > +1
 *
 *
 * * Epanechnikov (sharp, compact support)
 *
 * 		ke = @(x) 3/4*max((1-x.^2),0);
 *
 * * Gaussian Kernel (standard normal distributed kernel)
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
 */

#include <cmath>
#include <functional>

struct Kernel {
	typedef std::function <double(double)> Function;

	/**\brief Shift the kernel in x and y-direction.
	 *
	 * The shift in x-direction does not change the area under the kernel. A shift in y-direction immediately
	 * sets the area to + or - infinity.
	 *
	 * \htmlonly
	 <svg width="40mm" height="40mm"> <g transform="translate(0,-946.06299)">
	 <path d="m 10,1037.3622 120,0 -10,-5 0,10 10,-5"
	 style="fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;fill-opacity:1" />
	 <path d="m 55.213758,1037.3659 0,-85.1254 -5,10 10,0 -5,-10"
	 style="fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges;fill-opacity:1" />
	 <path d="m 15.118116,1037.3567 20,0 c 10,0 10,-35 20,-35 10,0 10,35 20,35 l 20,0"
	 style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1" />
	 <path d="m 56.550065,1018.0745 35,0 -10,-5 0,10 10,-5"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1" />
	 <path d="m 88.993235,1007.9532 0,-34.99992 -5,10 10,0 -5,-10"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 49.090126,1037.381 20,0 c 10,0 10,-35 20,-35 10,0 10,35 20.000004,35 l 20,0"
	 style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 49.044153,987.00864 20,0 c 10,0 10,-35 20,-35 10.000004,0 10.000004,35 20.000007,35 l 20,0"
	 style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 </g></svg>
	 * \endhtmlonly
	 */
	static Function Shift(Function func, double x, double y = 0.0);

	/**\brief Scales the kernel in x- and y-direction
	 *
	 * The kernel is widened by x and the height is changed by y. The area of the kernel is multiplyd by x*y.
	 *
	 * \htmlonly
	 <svg width="40mm" height="40mm">  <g
	 transform="translate(0,-946.06299)"
	 id="layer1">
	 <path d="m 10,1037.3622 120,0 -10,-5 0,10 10,-5"
	 style="fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;fill-opacity:1" />
	 <path d="m 55.213758,1037.3659 0,-85.1254 -5,10 10,0 -5,-10"
	 style="fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges;fill-opacity:1" />
	 <path d="m 15.118116,1037.3567 20,0 c 10,0 10,-35 20,-35 10,0 10,35 20,35 l 20,0"
	 style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1" />
	 <path d="m 75.713247,1015.932 35.000003,0 -10,-5 0,10 10,-5"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1" />
	 <path d="m 72.44863,993.5511 0,-34.99996 -5,10 10,0 -5,-10"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 15.167727,1037.381 20,0 c 10,0 10,-61.30474 20,-61.30474 10,0 10,61.30474 20.000004,61.30474 l 20,0"
	 style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 0.36253494,1037.4756 20.00000006,0 c 10,0 24.878245,-35 34.878245,-35 10.000004,0 25.116301,35 35.116304,35 l 19.999996,0"
	 style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 37.90766,993.31123 0,-34.99996 -5,10 10,0 -5,-10"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 36.07135,1015.0988 -35.0000058,0 9.9999998,5 0,-10 -9.9999998,5"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 </g></svg>
	 * \endhtmlonly
	 */
	static Function Scale(Function func, double x, double y = 1.0);

	/**\brief Stretches the kernel in x-direction
	 *
	 * At the same time as the kernel is stretched in x-direction, it is shrinked in y-direction.
	 * The area of the kernel stays unchanged.
	 *
	 * \htmlonly
	 <svg width="40mm" height="40mm"><g transform="translate(0,-946.06299)">
	 <path d="m 10,1037.3622 120,0 -10,-5 0,10 10,-5"
	 style="fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;fill-opacity:1" />
	 <path d="m 55.213758,1037.3659 0,-85.1254 -5,10 10,0 -5,-10"
	 style="fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges;fill-opacity:1" />
	 <path d="m 15.118116,1037.3567 20,0 c 10,0 10,-35 20,-35 10,0 10,35 20,35 l 20,0"
	 style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1" />
	 <path d="m 74.999089,1020.6931 35.000001,0 -10.000001,-5 0,10 10.000001,-5"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1" />
	 <path d="m 41.97798,977.96681 0,34.99989 5,-10 -10,0 5,10"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 0.17045593,1037.262 20.00000007,0 c 10,0 19.926946,-24.4067 34.878245,-24.4067 14.951299,0 24.640193,24.5257 34.640197,24.5257 l 20.000002,0"
	 style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 35.522189,1020.2648 -35.00000392,0 9.99999992,5 0,-10 -9.99999992,5"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 67.725371,977.84507 0,35.00003 5,-10 -10,0 5,10"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 </g></svg>
	 * \endhtmlonly
	 */
	static Function Stretch(Function func, double x);

	/**\brief Normalize the kernel to return the value 1 at the center.
	 *
	 * The kernel is scaled in y-direction to return a value of 1 at position 0.
	 * Integrated kernels will be scaled by 2 in y if this function is applied. (Because an integrated Kernel has the value 0.5 at x=0.)
	 *
	 * \htmlonly
	 <svg width="40mm" height="40mm"><g transform="translate(0,-946.06299)">
	 <path d="m 10,1037.3622 120,0 -10,-5 0,10 10,-5"
	 style="fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;fill-opacity:1" />
	 <path d="m 55.213758,1037.3659 0,-85.1254 -5,10 10,0 -5,-10"
	 style="fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges;fill-opacity:1" />
	 <path d="m 15.118116,1037.3567 20,0 c 10,0 10,-35 20,-35 10,0 10,35 20,35 l 20,0"
	 style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1" />
	 <path d="m 37.097916,1014.0235 0,-34.9999 -5,10 10,0 -5,-10"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 72.843487,1014.7351 0,-35.00006 -5,10 10,0 -5,-10"
	 style="fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 14.977468,1037.2864 20,0 c 10,0 10,-64.28039 20,-64.28039 10,0 10,64.28039 20,64.28039 l 20.000004,0"
	 style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;shape-rendering:crispEdges" />
	 <path d="m 30,972.3622 50.118116,0"
	 style="fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:1, 2;stroke-dashoffset:0;stroke-opacity:1" />
	 <text y="978.55151" x="13.976559" style="font-style:normal;font-weight:normal;font-size:20px;line-height:125%;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1"
	 xml:space="preserve"><tspan y="978.55151" x="13.976559">1</tspan></text>
	 </g></svg>
	 * \endhtmlonly
	 */
	static Function NormalizeY(Function func);

	/**\brief Multiplication and addition on x.
	 *
	 * Transforms the x value linearly before it is passed to the function.
	 *
	 * y = F(x) becomes y = F((x - a) * b)
	 */
	static Function SubMul(Function func, double a, double b = 1.0);

	static double Epanechnikov(double x)
	{
		if(x < -1.0 || x > 1.0) return 0.0;
		return (1.0 - x * x) * 0.75;
	}

	static double Cosine(double x)
	{
		if(x < -1.0 || x > 1.0) return 0.0;
		return ((M_PI_4) * cos(M_PI_2 * x));
	}

	static double Tricube(double x)
	{
		if(x < -1.0 || x > 1.0) return 0.0;
		const double b = fabs(x);
		const double a = (1.0 - b * b * b);
		return (70.0 / 81.0 * a * a * a);
	}

	static double Quartic(double x)
	{
		if(x < -1.0 || x > 1.0) return 0.0;
		const double a = (1.0 - x * x);
		return (15.0 / 16.0 * a * a);
	}

	static double Triweight(double x)
	{
		if(x < -1.0 || x > 1.0) return 0.0;
		const double a = (1.0 - x * x);
		return (35.0 / 32.0 * a * a * a);
	}

	static double Triangular(double x)
	{
		if(x < -1.0 || x > 1.0) return 0.0;
		return (1 - fabs(x));
	}

	static double Gaussian(double x)
	{
		return (1 / sqrt(2 * M_PI) * exp(-x * x / 2.0));
	}

	static double Uniform(double x)
	{
		return (x >= -1 && x <= 1)? 0.5 : 0;
	}

	static double Logistic(double x)
	{
		const double b = exp(x);
		const double a = 1 + b;
		return (b / (a * a));
	}

	static double Sigmoid(double x)
	{
		const double b = exp(x);
		return (M_2_PI * 1 / (b + 1 / b));
	}

	static double Silverman(double x)
	{
		const double a = fabs(x) / M_SQRT2;
		return exp(-a) / 2.0 * sin(a + M_PI_4);
	}

	static double Picard(double x)
	{
		return exp(-fabs(x)) / 2.0;
	}

	static double Cauchy(double x)
	{
		return 1.0 / (M_PI * (1.0 + x * x));
	}

	struct Integrated {
		static double Epanechnikov(double x)
		{
			if(x <= -1.0) return 0.0;
			if(x >= 1.0) return 1.0;
			return ((-x * x + 3.0) * x + 2.0) / 4.0;
		}

		static double Cosine(double x)
		{
			if(x <= -1.0) return 0.0;
			if(x >= 1.0) return 1.0;
			return (1.0 + sin(M_PI_2 * x)) / 2.0;
		}

		static double Tricube(double x)
		{
			if(x <= -1.0) return 0.0;
			if(x >= 1.0) return 1.0;
			if(x <= 0.0){
				const double h = (1.0 + x);
				const double a = h * h * h * h;
				const double b = (((((14.0 * x - 56.0) * x + 140.0) * x - 220.0)
						* x + 250.0) * x - 184.0) * x + 81.0;
				return (a * b) / 162.0;
			}
			const double h = x * x * x;
			return 0.5
					- ((((14.0 * h - 60.0) * h + 105.0) * h - 140.0) * x)
							/ 162.0;
		}

		static double Quartic(double x)
		{
			if(x <= -1.0) return 0.0;
			if(x >= 1.0) return 1.0;
			const double h = (1.0 + x);
			const double a = h * h * h;
			const double b = (3.0 * x - 9.0) * x + 8.0;
			return (a * b) / 16.0;
		}

		static double Triweight(double x)
		{
			if(x <= -1.0) return 0.0;
			if(x >= 1.0) return 1.0;
			const double h = (1.0 + x);
			const double a = h * h * h * h;
			const double b = ((-5.0 * x + 20.0) * x - 29.0) * x + 16;
			return (a * b) / 32.0;
		}

		static double Triangular(double x)
		{
			if(x <= -1.0) return 0.0;
			if(x >= 1.0) return 1.0;
			if(x <= 0.0){
				return ((2.0 + x) * x + 1.0) / 2.0;
			}
			return ((2.0 - x) * x + 1.0) / 2.0;
		}

		static double Gaussian(double x)
		{
			return (erf(x * M_SQRT1_2) + 1.0) / 2.0;
		}

		static double Uniform(double x)
		{
			if(x <= -1.0) return 0.0;
			if(x >= 1.0) return 1.0;
			return (x + 1.0) / 2.0;
		}

		static double Logistic(double x)
		{
			const double a = exp(x);
			return a / (1.0 + a);
		}

		static double Sigmoid(double x)
		{
			return 2.0 * atan(exp(x)) / M_PI;
		}

		static double Silverman(double x)
		{
			const double a = x / M_SQRT2;
			if(x < 0.0){
				const double b = exp(a);
				return b * (cos(a - M_PI_4) - sin(a - M_PI_4)) / (2.0 * M_SQRT2);
			}
			const double b = exp(-a);
			return 1.0
					- (b * (cos(a + M_PI_4) + sin(a + M_PI_4)) / (2.0 * M_SQRT2));
		}

		static double Picard(double x)
		{
			if(x < 0.0) return 0.5 * exp(x);
			return 1.0 - 0.5 * exp(-x);
		}

		static double Cauchy(double x)
		{
			return 0.5 + atan(x) / M_PI;
		}
	};

};

inline Kernel::Function Kernel::Shift(Kernel::Function func, double x, double y)
{
	return [func,x,y](double v){return func(v-x)+y;};
}

inline Kernel::Function Kernel::Scale(Kernel::Function func, double x, double y)
{
	return [func,x,y](double v){return func(v/x)*y;};
}

inline Kernel::Function Kernel::Stretch(Kernel::Function func, double x)
{
	return [func,x](double v){return func(v/x)/x;};
}

inline Kernel::Function Kernel::NormalizeY(Kernel::Function func)
{
	return [func](double v){return func(v)/func(0);};
}

inline Kernel::Function Kernel::SubMul(Kernel::Function func, double a,
		double b)
{
	return [func,a,b](double v){return func((v-a)*b);};
}

#endif /* SRC_MATH_KERNEL_H_ */
