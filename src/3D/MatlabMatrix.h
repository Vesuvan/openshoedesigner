///////////////////////////////////////////////////////////////////////////////
// Name               : MatlabMatrix.h
// Purpose            : Matrix for data transfer to Matlab
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 04.11.2014
// Copyright          : (C) 2014 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef MATLABMATRIX_H_
#define MATLABMATRIX_H_
/*!\class MatlabMatrix
 * \brief Matrix for data transfer to Matlab
 *
 * The dimension S1 has the stride 1.
 *
 * (Contrary to Torch.Tensor. Here the last dimension has stride 1.)
 *
 * \image html MatlabMatrix_Configuration.svg
 */

#include <string>
#include <vector>
#include <stdlib.h>

class MatlabMatrix {
public:
	MatlabMatrix();
	MatlabMatrix(const size_t S1, const size_t S2 = 1, const size_t S3 = 1,
			const size_t S4 = 1);
	MatlabMatrix(const std::string &name, const size_t S1 = 0, const size_t S2 =
			1, const size_t S3 = 1, const size_t S4 = 1);
	MatlabMatrix(const MatlabMatrix &other); ///< Copy constructor
	virtual ~MatlabMatrix();

	void Reset(void);
	void Clear(void);

	void SetVariableName(const std::string &name);
	const std::string& GetVariableName(void) const;
	void SetSize(const size_t S1, const size_t S2 = 1, const size_t S3 = 1,
			const size_t S4 = 1);
	void SetSize(const MatlabMatrix &other);
	size_t GetRows(void) const;
	size_t GetCols(void) const;
	size_t Size(const size_t dim = 1) const;
	size_t Numel(void) const;
	/*! Move the insert position around
	 *
	 * Every parameter defaults to 0.
	 */
	void SetInsertPosition(const size_t p1 = 0, const size_t p2 = 0,
			const size_t p3 = 0, const size_t p4 = 0);
	void Insert(const double value);
	void Insert(const double* value, const size_t count);
	void Insert(const float* value, const size_t count);
	void Insert(const bool* value, const size_t count);
	void Insert(const size_t p1, const size_t p2, double value);
	void Insert(const size_t p2, const double* value, const size_t count);

	double& operator[](size_t const& index);
	const double& operator[](size_t const& index) const;

	double GetValue(const size_t p1, const size_t p2, const size_t p3 = 0,
			const size_t p4 = 0) const;
	double GetValue(const size_t pos) const;
	double* Pointer(void);
	const double* Pointer(void) const;

	bool IsEmpty(void) const;
	void Transpose(void);
	void Reshape(const size_t S1 = 0, const size_t S2 = 1, const size_t S3 = 1,
			const size_t S4 = 1);

protected:
	std::string variablename;
	std::vector <size_t> dimension;
	double* buffer;
	size_t size;
	size_t bufferpos;
};

#endif /* MATLABMATRIX_H_ */
