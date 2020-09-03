///////////////////////////////////////////////////////////////////////////////
// Name               : MathMatrix.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 05.11.2016
// Copyright          : (C) 2016 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "MathMatrix.h"

#include <assert.h>

#include <math.h>
#include <string.h>
#include <float.h>

double MathMatrix::Min(void) const
{
	double m = DBL_MAX;
	for(size_t n = 0; n < size; n++){
		const double v = buffer[n];
		if(v == DBL_MAX || v == -DBL_MAX) continue;
		m = fmin(m, v);
	}
	return m;
}

double MathMatrix::Max(void) const
{
	double m = -DBL_MAX;
	for(size_t n = 0; n < size; n++){
		const double v = buffer[n];
		if(v == DBL_MAX || v == -DBL_MAX) continue;
		m = fmax(m, v);
	}
	return m;
}

double MathMatrix::MaxAbs(void) const
{
	double v = -DBL_MAX;
	for(size_t n = 0; n < size; n++)
		v = fmax(v, fabs(buffer[n]));
	return v;
}

double MathMatrix::Interp1(const double x) const
{
//	assert(::Nummel()==)
	throw("Not implemented.");
}

void MathMatrix::AlignAtZero(void)
{
	const double m = this->Min();
	for(size_t n = 0; n < size; n++)
		buffer[n] -= m;
}

void MathMatrix::Normalize(double max)
{
	double m = this->MaxAbs();
	if(m == 0.0) return;
	m = max / m;
	for(size_t n = 0; n < size; n++)
		buffer[n] *= m;
}

void MathMatrix::Normalize(double min, double max)
{
	if(max == min){
		memset(buffer, 0, sizeof(double) * size);
		return;
	}
	this->AlignAtZero();
	double m = this->Max();
	if(m == 0.0) return;
	m = (max - min) / m;
	for(size_t n = 0; n < size; n++){
		buffer[n] *= m;
		buffer[n] += min;
	}
}

void MathMatrix::Mirror(Axis a)
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);

	switch(a){
	case Axis::X:
		for(size_t i = 0; i < (Nx / 2); i++){
			for(size_t j = 0; j < Ny; j++){
				for(size_t k = 0; k < Nz; k++){
					const size_t n = i + Nx * (j + Ny * k);
					const size_t m = (Nx - i - 1) + Nx * (j + Ny * k);
					std::swap(buffer[n], buffer[m]);
				}
			}
		}
		break;
	case Axis::Y:
		for(size_t i = 0; i < Nx; i++){
			for(size_t j = 0; j < (Ny / 2); j++){
				for(size_t k = 0; k < Nz; k++){
					const size_t n = i + Nx * (j + Ny * k);
					const size_t m = i + Nx * ((Ny - j - 1) + Ny * k);
					std::swap(buffer[n], buffer[m]);
				}
			}
		}
		break;
	case Axis::Z:
		for(size_t i = 0; i < Nx; i++){
			for(size_t j = 0; j < Ny; j++){
				for(size_t k = 0; k < (Nz / 2); k++){
					const size_t n = i + Nx * (j + Ny * k);
					const size_t m = i + Nx * (j + Ny * (Nz - k - 1));
					std::swap(buffer[n], buffer[m]);
				}
			}
		}
		break;
	}
}

void MathMatrix::Rotate(Axis a, int quarters)
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);

	quarters %= 4;
	if(quarters < 0) quarters += 4;
	if(quarters == 0) return;
	if(quarters == 2){
		switch(a){
		case Axis::X:
			for(size_t i = 0; i < Nx; i++){
				for(size_t n = i; n < (size / 2); n += Nx){
					std::swap(buffer[n], buffer[(size - Nx) - n + 2 * i]);
				}
			}
			break;
		case Axis::Y:
			for(size_t j = 0; j < Ny; j++){
				size_t n = j * Nx;
				size_t m = size - 1 - (Ny - 1) * Nx + j * Nx;
				for(size_t k = 0; k < (Nx * Nz / 2); k++){
					std::swap(buffer[n], buffer[m]);
					n = (n + Nx * Ny) % (size - 1);
					m = (m + (size - Nx * Ny - 1)) % (size - 1);
				}
			}
			break;
		case Axis::Z:
			const size_t m = Nx * Ny;
			for(size_t k = 0; k < Nz; k++){
				for(size_t n = 0; n < (m / 2); n++){
					std::swap(buffer[k * Nx * Ny + n],
							buffer[k * Nx * Ny + (m - n - 1)]);
				}
			}
			break;
		}
		return;
	}
	assert(quarters == 1 || quarters == 3);
	double* temp = new double[size];
	if(temp == NULL) throw("Out of memory!");

	switch(a){
	case Axis::X:
		{
			if(quarters == 1){
				const size_t mo = size + Nx;
				const size_t ad = size - (Nx * (Ny - 1));
				for(size_t i = 0; i < Nx; i++){
					size_t m = size - Ny * Nx + i;
					for(size_t n = 0; n < (Ny * Nz); n++){
						temp[n * Nx + i] = buffer[m];
						m = (m + ad) % mo;
					}
				}
			}
			if(quarters == 3){
				const size_t mo = size + Nx;
				const size_t ad = Nx * Ny;
				for(size_t i = 0; i < Nx; i++){
					size_t m = (Ny - 1) * Nx + i;
					for(size_t n = 0; n < (Ny * Nz); n++){
						temp[n * Nx + i] = buffer[m];
						m = (m + ad) % mo;
					}
				}
			}

//		std::swap(Ny, Nz);
			MatlabMatrix::Reshape(Nx, Nz, Ny);
			break;
		}
	case Axis::Y:
		{
			if(quarters == 1){
//			Nx = 4;
//			Ny = 5;
//			Nz = 5;
//			size = Nx * Ny * Nz;
				size_t n = 0;
				size_t m = Nx - 1;
				for(size_t i = 0; i < Nx; i++){
					for(size_t j = 0; j < Ny; j++){
						for(size_t k = 0; k < Nz; k++){
							temp[n] = buffer[m];
							n++;
							m += Nx * Ny;
						}
						m = m + Nx - size;
					}
					m = m - Nx * Ny - 1;
				}
			}
			if(quarters == 3){
				size_t n = 0;
				size_t m = size;
				for(size_t i = 0; i < Nx; i++){
					for(size_t j = 0; j < Ny; j++){
						for(size_t k = 0; k < Nz; k++){
							m -= Nx * Ny;
							temp[n] = buffer[m];
							n++;
						}
						m = m + size + Nx;
					}
					m = m - Nx * Ny + 1;
				}
			}
			MatlabMatrix::Reshape(Nz, Ny, Nx);
//		std::swap(Nz, Nx);
			break;
		}
	case Axis::Z:
		{
			const size_t mo = Nx * Ny + 1;
			size_t ad;
			if(quarters == 1) ad = Nx * (Ny - 1) + 1;
			if(quarters == 3) ad = Nx;
			for(size_t k = 0; k < Nz; k++){
				size_t n = 0;
				for(size_t m = ad - 1; m != mo - 1; m = (m + ad) % mo){
					temp[n + k * Nx * Ny] = buffer[m + k * Nx * Ny];
					n++;
				}
			}
//		std::swap(Nx, Ny);
			MatlabMatrix::Reshape(Ny, Nx, Nz);
			break;
		}
	}

	delete[] buffer;
	buffer = temp;
}

MathMatrix MathMatrix::XRay(Method method) const
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);

	MathMatrix temp;
	temp.SetSize(Nx, 1, Nz);
	temp.SetInsertPosition(0);

	for(size_t z = 0; z < Nz; z++){
		for(size_t x = 0; x < Nx; x++){
			switch(method){
			case Method::MaxValue:
				{
					double vm = -DBL_MAX;
					for(size_t y = 0; y < Ny; y++){
						const double v = MatlabMatrix::operator()(x, y, z);
						if(v > vm) vm = v;
					}
					temp.Insert(vm);
					break;
				}
			case Method::MinValue:
				{
					double vm = DBL_MAX;
					for(size_t y = 0; y < Ny; y++){
						const double v = MatlabMatrix::operator()(x, y, z);
						if(v < vm) vm = v;
					}
					temp.Insert(vm);
					break;
				}
			case Method::MeanValue:
				{
					double vm = 0;
					for(size_t y = 0; y < Ny; y++){
						const double v = MatlabMatrix::operator()(x, y, z);
						vm += v;
					}
					temp.Insert(vm / (double) Ny);
					break;
				}
			case Method::Sum:
				{
					double vm = 0;
					for(size_t y = 0; y < Ny; y++){
						const double v = MatlabMatrix::operator()(x, y, z);
						vm += v;
					}
					temp.Insert(vm);
					break;
				}
			}
		}
	}
	return temp;
}
