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
#include <cctype>
#include <cmath>
#include <iostream>
#include <ostream>
#include <algorithm>

#include "../../3D/PolyCylinder.h"
#include "../../3D/BoundingBox.h"
#include "../../3D/FileSTL.h"
#include "../../3D/OpenGLMaterial.h"
#include "../../math/CoreDensityEstimator.h"
#include "../../math/NelderMeadOptimizer.h"
#include "../../math/PCA.h"
#include "../../math/FourierTransform.h"
#include "../../math/MatlabFile.h"
#include "../../math/MatlabMatrix.h"

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

	std::string::size_type n = filename.find_last_of(".");
	std::string extension = filename.substr(n + 1);
	for(size_t n = 1; n < extension.size(); ++n)
		extension[n] = std::tolower(extension[n]);

	if(extension.compare("dat") == 0){
		PolyCylinder pc;
		if(!pc.Load(filename)) return false;
		Geometry geometry;
		pc.GenerateGeometry(geometry, false);
		hull.CopyFrom(geometry);
		if(hull.IsClosed()){
			std::cout << "Fully closed hull loaded." << "\n";
		}else{
			std::cout << "Hull has open edges." << "\n";
		}
		AnalyseForm();
		return true;
	}
	if(extension.compare("stl") == 0){
		FileSTL stl;
		if(!stl.ReadFile(filename)) return false;
		if(stl.geometry.Count() == 0) return false;
		hull.CopyFrom(stl.geometry[0]);
		if(hull.IsClosed()){
			std::cout << "Fully closed hull loaded." << "\n";
		}else{
			std::cout << "Hull has open edges." << "\n";
		}
		hull.CalcNormals();
		AnalyseForm();
		return true;
	}
	if(extension.compare("obj") == 0){
		if(hull.LoadObj(filename)){
			AnalyseForm();
			return true;
		}
	}
	return false;
}

bool LastModel::Vector3MinX(const Vector3 a, const Vector3 b)
{
	return a.x < b.x;
}

void LastModel::AnalyseForm(void)
{

	// Find orientation of mesh
	PCA pca;
	pca.SetCenter(hull.GetCenter());
	for(size_t i = 0; i < hull.GetVertexCount(); ++i)
		pca.Add(hull.GetVertex(i));
	pca.Calculate();

	// Remove orientation
	if((pca.X * pca.Y).Dot(pca.Z) > 0) pca.Y = -pca.Y;

	AffineTransformMatrix temp;
	temp.a[0] = pca.X.x;
	temp.a[1] = pca.X.y;
	temp.a[2] = pca.X.z;
	temp.a[4] = pca.Z.x;
	temp.a[5] = pca.Z.y;
	temp.a[6] = pca.Z.z;
	temp.a[8] = pca.Y.x;
	temp.a[9] = pca.Y.y;
	temp.a[10] = pca.Y.z;
	temp.a[12] = pca.center.x;
	temp.a[13] = pca.center.y;
	temp.a[14] = pca.center.z;
	temp = temp.Inverse();

	hull.ApplyTransformation(temp);

	// Scan Shape at 20% and 80%
	BoundingBox bb;
	for(size_t i = 0; i < hull.GetVertexCount(); ++i)
		bb.Insert(hull.GetVertex(i));

	Polygon3 shape1 = hull.IntersectPlane(Vector3(1, 0, 0),
			bb.xmin + bb.GetSizeX() * 0.2);
	Polygon3 shape2 = hull.IntersectPlane(Vector3(1, 0, 0),
			bb.xmin + bb.GetSizeX() * 0.8);

	Vector3 center = shape1.GetCenter();
	Vector3 rot = shape1.GetRotationalAxis();
	if(rot.x < 0) rot = -rot;

	Vector3 localx(0, 1, 0);
	Vector3 localy = rot * localx;
	localy.Normalize();

	symmetry.center = center;
	symmetry.localx = localx;
	symmetry.localy = localy;

	FourierTransform ft1, ft2;
	ft1.TSetSize(shape1.GetCount());
	for(size_t n = 0; n < shape1.GetCount(); ++n){
		Vector3 v0 = shape1[n] - center;
		ft1.t[n] = atan2(v0.Dot(localy), v0.Dot(localx));
		ft1.InRe[n] = v0.Abs();
		ft1.InIm[n] = 0.0;
	}
	ft1.TUnwrap();
	ft1.TSetLoopLength(2 * M_PI);
	ft1.TScale(1.0 / (2 * M_PI));
	ft1.FLinspace(0, 20, 21);
	ft1.Transform();
	ft1.SingleSidedResult();

	ft2.TSetSize(shape2.GetCount());
	for(size_t n = 0; n < shape2.GetCount(); ++n){
		Vector3 v0 = shape2[n] - center;
		ft2.t[n] = atan2(v0.Dot(localy), v0.Dot(localx));
		ft2.InRe[n] = v0.Abs();
		ft2.InIm[n] = 0.0;
	}
	ft2.TUnwrap();
	ft2.TSetLoopLength(2 * M_PI);
	ft2.TScale(1.0 / (2 * M_PI));
	ft2.FLinspace(0, 20, 21);
	ft2.Transform();
	ft2.SingleSidedResult();

	symmetry.InitSupport(360);
	symmetry.AddTransform(ft1);
	symmetry.AddTransform(ft2);
	symmetry.FindPeaks();
	AffineTransformMatrix comp;
	comp *= AffineTransformMatrix::RotationAroundVector(rot,
	M_PI_2 - symmetry.angle[0]);
	hull.ApplyTransformation(comp);

	bb.Clear();
	for(size_t i = 0; i < hull.GetVertexCount(); ++i)
		bb.Insert(hull.GetVertex(i));
	shape1 = hull.IntersectPlane(Vector3(1, 0, 0),
			bb.xmin + bb.GetSizeX() * 0.2);
	shape2 = hull.IntersectPlane(Vector3(1, 0, 0),
			bb.xmin + bb.GetSizeX() * 0.8);

	rot = shape1.GetRotationalAxis();
	if(rot.x > 0) shape1.Reverse();
	rot = shape2.GetRotationalAxis();
	if(rot.x > 0) shape2.Reverse();

	cde.SetRange(0, 2 * M_PI, 100, true);

	{
		const double Lmax = shape1.GetLength();
		for(size_t n = 0; n < shape1.Size(); ++n){
			const Vector3 temp = (shape1[(n + 1) % shape1.Size()] - shape1[n]);
			double a = atan2(temp.y, -temp.z);
			cde.Add(CoreDensityEstimator::Epanechnikov, 0.5, a,
					temp.Abs() / Lmax);
		}
	}
	{
		const double Lmax = shape2.GetLength();
		for(size_t n = 0; n < shape2.Size(); ++n){
			const Vector3 temp = (shape2[(n + 1) % shape2.Size()] - shape2[n]);
			double a = atan2(temp.y, -temp.z);
			cde.Add(CoreDensityEstimator::Epanechnikov, 0.5, a,
					temp.Abs() / Lmax);
		}
	}

//	cde.Add(CoreDensityEstimator::Epanechnikov, 1, 1, 1);
//	cde.Add(CoreDensityEstimator::Epanechnikov, 0.5, 2.5, 1);

	loop = shape1;

//	loop = hull.IntersectPlane(Vector3(0, 1, 0), 0.0);
//	loop.Resample(100);
//	rot = loop.GetRotationalAxis();
//	if(rot.y < 0) loop.Reverse();
//
//	formfinder.AddPolygon(loop, loop.GetCount() / 8);

//	std::vector <Vector3>::iterator min = std::min_element(formfinder.b.begin(),
//			formfinder.b.end(), Vector3MinX);
//	size_t dist = std::distance(formfinder.b.begin(), min);
//	std::cout << dist << "\n";
//	std::rotate(formfinder.a.begin(), formfinder.a.begin() + dist,
//			formfinder.a.end());
//	std::rotate(formfinder.b.begin(), formfinder.b.begin() + dist,
//			formfinder.b.end());
//	std::rotate(formfinder.c.begin(), formfinder.c.begin() + dist,
//			formfinder.c.end());
//	std::rotate(formfinder.d.begin(), formfinder.d.begin() + dist,
//			formfinder.d.end());

	MatlabFile mf("data/dist.mat");

	MatlabMatrix F("F", 12, formfinder.a.size());
	for(size_t n = 0; n < formfinder.a.size(); ++n){
		F.Insert(formfinder.a[n].x);
		F.Insert(formfinder.b[n].x);
		F.Insert(formfinder.c[n].x);
		F.Insert(formfinder.d[n].x);
		F.Insert(formfinder.a[n].y);
		F.Insert(formfinder.b[n].y);
		F.Insert(formfinder.c[n].y);
		F.Insert(formfinder.d[n].y);
		F.Insert(formfinder.a[n].z);
		F.Insert(formfinder.b[n].z);
		F.Insert(formfinder.c[n].z);
		F.Insert(formfinder.d[n].z);
	}
	F.Transpose();
	mf.WriteMatrix(F);

//	MatlabMatrix P("P", 2, shape1.GetCount());
//			P.Insert(v0.Dot(localx));
//			P.Insert(v0.Dot(localy));
//	P.Transpose();
//	mf.WriteMatrix(P);
//
//
//	MatlabMatrix X("X", 3, ft.InRe.size());
//	for(size_t n = 0; n < ft.InRe.size(); ++n){
//		X.Insert(ft.t[n]);
//		X.Insert(ft.InRe[n]);
//		X.Insert(ft.InIm[n]);
//	}
//	X.Transpose();
//	mf.WriteMatrix(X);
//
//	MatlabMatrix Y("Y", 3, ft.f.size());
//	for(size_t n = 0; n < ft.f.size(); ++n){
//		Y.Insert(ft.f[n]);
//		Y.Insert(ft.OutRe[n]);
//		Y.Insert(ft.OutIm[n]);
//	}
//	Y.Transpose();
//	mf.WriteMatrix(Y);
//
//	MatlabMatrix S("S", symmetry.support.size());
//	for(size_t n = 0; n < symmetry.support.size(); ++n)
//		S.Insert(symmetry.support[n]);
//	mf.WriteMatrix(S);

	mf.Close();

//	loop = shape1;

//	Vector3 temp;
//	for(size_t i = 0; i < loop.elements.Count(); i++)
//		temp += loop.elements[i];
//	pca.SetCenter(temp / loop.elements.Count());
//	for(size_t i = 0; i < loop.elements.Count(); i++)
//		pca.Add(loop.elements[i]);

}

void LastModel::UpdateForm(const FootMeasurements& measurements)
{

//	NelderMeadOptimizer optim;
//	optim.param.push_back(sx);
//	optim.param.push_back((sy + sz) / 2);
//	optim.simplexSpread = 1e-3;
//	optim.errorLimit = 1e-8;
//	optim.reevalBest = true;
//	optim.Start();
//	while(optim.IsRunning()){
//		if(mirrored){
//			data.Scale(optim.param[0], -optim.param[1], optim.param[1]);
//		}else{
//			data.Scale(optim.param[0], optim.param[1], optim.param[1]);
//		}
//		double err = pow(
//				measurements.footLength.value - data.dx * data.sections.size(),
//				2.0)
//				+ pow(
//						measurements.ballGirth.value
//								- data.sections[37].GetLength(), 2);
//		if(optim.param[0] <= 0) err += 1e6 - optim.param[0];
//		if(optim.param[1] <= 0) err += 1e6 - optim.param[1];
//		optim.SetError(err);
//	}
//	sx = optim.param[0];
//	sy = optim.param[1];
//	sz = optim.param[1];
//	std::cout << "Min. Err: " << optim.ResidualError() << "\n";
//	std::cout << data.dx * data.sections.size() << " m\n";
//	std::cout << data.sections[37].GetLength() << " m\n";

}

void LastModel::UpdatePosition(const Shoe& shoe, double offset)
{
//	NelderMeadOptimizer optim;
//	optim.simplexSpread = 1e-3;
//	optim.errorLimit = 1e-8;
//	optim.reevalBest = true;
//
//	optim.param.push_back(sx);
//	optim.param.push_back((sy + sz) / 2);
//	optim.Start();
//	while(optim.IsRunning()){
//		center.InitAngle(0);
//		center.SetBend(-1.2, 0.3, 0.3, BendLine::Epanechnikov);
//		center.SetBend(1.3, 0.75, 0.03, BendLine::Gauss);
//		center.Finish();
//	}

}

void LastModel::Paint(void) const
{
//	data.Paint();
//	hull.Paint();
//	symmetry.Paint();
	OpenGLMaterial::EnableColors();
	glColor3f(1, 1, 1);
	glNormal3f(1, 0, 0);
	loop.Paint();
	OpenGLMaterial yellow(1, 1, 0);
	yellow.UseColor(1.0);
	formfinder.Paint();
	cde.Paint();

	OpenGLMaterial::EnableColors();

//	glBegin(GL_LINES);
//	glColor3f(1, 0, 0);
//	glNormal3f(0, 0, 1);
//	glVertex3f(center.x, center.y, center.z);
//	glVertex3f(center.x + rot.x, center.y + rot.y, center.z + rot.z);
//	glColor3f(0, 1, 0);
//	glVertex3f(center.x, center.y, center.z);
//	glVertex3f(center.x + ort.x, center.y + ort.y, center.z + ort.z);
//
//	glEnd();

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
