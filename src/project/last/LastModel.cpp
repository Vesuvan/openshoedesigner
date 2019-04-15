///////////////////////////////////////////////////////////////////////////////
// Name               : LastModel.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 02.03.2019
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

#include "LastModel.h"
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <ostream>

#include "../../math/NelderMeadOptimizer.h"
LastModel::LastModel()
{
	center.SetCount(101);
	center.InitAngle(0);
	center.Finish(0.3);

	sx = sy = sz = 0.01;

	mirrored = false;
	modified = true;
}

LastModel::~LastModel()
{
}

bool LastModel::LoadModel(std::string filename)
{
	this->filename = filename;
	return data.Load(filename);
}

void LastModel::UpdateForm(const FootMeasurements& measurements)
{
	NelderMeadOptimizer optim;
	optim.param.push_back(sx);
	optim.param.push_back((sy + sz) / 2);
	optim.simplexSpread = 1e-3;
	optim.errorLimit = 1e-8;
	optim.reevalBest = true;
	optim.Start();
	while(optim.IsRunning()){
		if(mirrored){
			data.Scale(optim.param[0], -optim.param[1], optim.param[1]);
		}else{
			data.Scale(optim.param[0], optim.param[1], optim.param[1]);
		}
		double err = pow(
				measurements.footLength.value - data.dx * data.sections.size(),
				2.0)
				+ pow(
						measurements.ballGirth.value
								- data.sections[37].GetLength(), 2);
		if(optim.param[0] <= 0) err += 1e6 - optim.param[0];
		if(optim.param[1] <= 0) err += 1e6 - optim.param[1];
		optim.SetError(err);
	}
	sx = optim.param[0];
	sy = optim.param[1];
	sz = optim.param[1];
	std::cout << "Min. Err: " << optim.ResidualError() << "\n";
	std::cout << data.dx * data.sections.size() << " m\n";
	std::cout << data.sections[37].GetLength() << " m\n";

}

void LastModel::UpdatePosition(const Shoe& shoe, double offset)
{
	NelderMeadOptimizer optim;
	optim.simplexSpread = 1e-3;
	optim.errorLimit = 1e-8;
	optim.reevalBest = true;

	optim.param.push_back(sx);
	optim.param.push_back((sy + sz) / 2);
	optim.Start();
	while(optim.IsRunning()){
		center.InitAngle(0);
		center.SetBend(-1.2, 0.3, 0.3, BendLine::Epanechnikov);
		center.SetBend(1.3, 0.75, 0.03, BendLine::Gauss);
		center.Finish();
	}

}

void LastModel::UpdateGeometry(void)
{
	geometry.Clear();
	size_t N = 34;
	const double dr = 1.0 / (double) N;
	Vector3 a, b, c, d;

	{
		a.Zero();
		double r = 0.0;
		for(size_t m = 0; m < N; ++m){
			a += data.sections[0].Evaluate(r);
			r += dr;
		}
		a /= N;
		a.x = -0.5 * data.dx;
		r = 0.0;
		b = data.sections[0].Evaluate(0);
		for(size_t m = 0; m < N; ++m){
			r += dr;
			c = data.sections[0].Evaluate(r);
			if(mirrored){
				geometry.AddTriangle(a, b, c);
			}else{
				geometry.AddTriangle(a, c, b);
			}
			b = c;
		}
	}

	for(size_t n = 1; n < data.sections.size(); ++n){
		double r = 0.0;
		a = data.sections[n - 1].Evaluate(r);
		b = data.sections[n].Evaluate(r);
		a.x = (n - 1) * data.dx;
		b.x = (n) * data.dx;
		for(size_t m = 0; m < N; ++m){
			r += dr;
			c = data.sections[n - 1].Evaluate(r);
			d = data.sections[n].Evaluate(r);
			c.x = (n - 1) * data.dx;
			d.x = (n) * data.dx;
			if(mirrored){
				geometry.AddQuad(a, b, d, c);
			}else{
				geometry.AddQuad(b, a, c, d);
			}
			a = c;
			b = d;
		}
	}
	{
		a.Zero();
		double r = 0.0;
		for(size_t m = 0; m < N; ++m){
			a += data.sections[data.sections.size() - 1].Evaluate(r);
			r += dr;
		}
		a /= N;
		a.x = ((double) (data.sections.size() - 1) + 0.5) * data.dx;
		r = 0.0;
		b = data.sections[data.sections.size() - 1].Evaluate(0);
		b.x = (data.sections.size() - 1) * data.dx;
		for(size_t m = 0; m < N; ++m){
			r += dr;
			c = data.sections[data.sections.size() - 1].Evaluate(r);
			c.x = (data.sections.size() - 1) * data.dx;
			if(mirrored){
				geometry.AddTriangle(a, c, b);
			}else{
				geometry.AddTriangle(a, b, c);
			}
			b = c;
		}
	}
}

void LastModel::Paint(void) const
{
//	data.Paint();
	geometry.Paint(geometryColorNone);
//	glBegin(GL_LINE_STRIP);
//	for(size_t n = 0; n < center.N; ++n){
//		glVertex3d(center.x[n], 0, center.y[n]);
//	}
//	glEnd();
}

bool LastModel::IsModified(void) const
{
	return modified;
}

void LastModel::Modify(bool modified)
{
	this->modified = modified;
}
