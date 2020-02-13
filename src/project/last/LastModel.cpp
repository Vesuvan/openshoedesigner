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
#include "../../math/KernelDensityEstimator.h"
#include "../../math/NelderMeadOptimizer.h"
#include "../../math/PCA.h"
#include "../../math/FourierTransform.h"
#include "../../math/MatlabFile.h"
#include "../../math/MatlabMatrix.h"
#include "../../math/ParameterLimits.h"

LastModel::LastModel()
{
//	center.XLinspace(0, 1, 101);
//	center.YInit(0);
//	center.Insert(0.3, -1.2, 0.3, BendLine::EpanechnikovKernel);
//	center.Insert(0.75, 1.3, 0.03, BendLine::GaussianKernel);
//	center.AngleToPos();

	sx = sy = sz = 0.01;

	mirrored = false;
	modified = true;

//	Polynom p = Polynom::ByValue(-1, 1, 0, 0, 1, 1);
//	std::cout << p << "\n";

//	PolyFilter pf;
//	pf.Init(0, 40);
//	pf.Export("/tmp/PF_0.mat");
//	pf.Init(1, 40);
//	pf.Export("/tmp/PF_1.mat");
//	pf.Init(2, 40);
//	pf.Export("/tmp/PF_2.mat");
//	pf.Init(3, 40);
//	pf.Export("/tmp/PF_3.mat");

//	KernelDensityEstimator kde0;
//	kde0.XLinspace(-5, 5, 301);
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::CauchyKernel);
//	kde0.Export("/tmp/CauchyKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::CosineKernel);
//	kde0.Export("/tmp/CosineKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::EpanechnikovKernel);
//	kde0.Export("/tmp/EpanechnikovKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::GaussianKernel);
//	kde0.Export("/tmp/GaussianKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::LogisticKernel);
//	kde0.Export("/tmp/LogisticKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::PicardKernel);
//	kde0.Export("/tmp/PicardKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::QuarticKernel);
//	kde0.Export("/tmp/QuarticKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::SigmoidKernel);
//	kde0.Export("/tmp/SigmoidKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::SilvermanKernel);
//	kde0.Export("/tmp/SilvermanKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::TriangularKernel);
//	kde0.Export("/tmp/TriangularKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::TricubeKernel);
//	kde0.Export("/tmp/TricubeKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::TriweightKernel);
//	kde0.Export("/tmp/TriweightKernel.mat");
//	kde0.YInit();
//	kde0.Insert(0, 1, 1, KernelDensityEstimator::UniformKernel);
//	kde0.Export("/tmp/UniformKernel.mat");

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
		hull.CalcNormals();
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
		hull.CopyFrom(stl.geometry);
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

bool LastModel::Vector3XLess(const Vector3 a, const Vector3 b)
{
	return a.x < b.x;
}

bool LastModel::AnalyseForm(void)
{
	MatlabFile mf("/tmp/test.mat");

	{
		// Find orientation of mesh

		PCA pca;
		pca.SetCenter(hull.GetCenter());
		for(size_t i = 0; i < hull.GetVertexCount(); ++i)
			pca.Add(hull.GetVertex(i));
		pca.Calculate();
		// Make coordinate system right handed
		if((pca.X * pca.Y).Dot(pca.Z) > 0) pca.Y = -pca.Y;
		// Remove orientation
		AffineTransformMatrix temp(pca.X, pca.Y, pca.Z, pca.center);
		temp.Invert();
		hull.ApplyTransformation(temp);
	}

	BoundingBox bb;
	for(size_t i = 0; i < hull.GetVertexCount(); ++i)
		bb.Insert(hull.GetVertex(i));
	AffineTransformMatrix bbc = bb.GetCoordinateSystem();

	{
		// Scan Shape for symmetry

		symmetry.Init(180);
		for(double cut = 0.2; cut < 0.81; cut += 0.2){
			Polygon3 section = hull.IntersectPlane(Vector3(1, 0, 0),
					bbc.GlobalX(cut));

			Vector3 rot = section.GetRotationalAxis();
			if(rot.x < 0) rot = -rot;

			coordsys.SetOrigin(section.GetCenter());
			coordsys.SetEx(Vector3(0, 1, 0));
			coordsys.SetEy(Vector3(0, 0, 1));
			coordsys.SetEz(Vector3(1, 0, 0));

			FourierTransform ft;
			ft.TSetSize(section.Size());
			for(size_t n = 0; n < section.Size(); ++n){
				ft.t[n] = atan2(coordsys.LocalY(section[n]),
						coordsys.LocalX(section[n]));
				ft.InRe[n] = (section[n] - coordsys.GetOrigin()).Abs();
				ft.InIm[n] = 0.0;
			}
			ft.TUnwrap();
			ft.TSetLoopLength(2 * M_PI);
			ft.TScale(1.0 / (2 * M_PI));
			ft.FLinspace(0, 30, 31);
			ft.Transform();
			ft.SingleSidedResult();
			symmetry.AddTransform(ft);
		}

		symmetry.Normalize();
		symmetry.FindPeaks(0.01);
		if(symmetry.ResultSize() == 0) return false;
		AffineTransformMatrix comp;
		comp *= AffineTransformMatrix::RotationAroundVector(Vector3(1, 0, 0),
		M_PI_2 - symmetry.ResultX(0));
		hull.ApplyTransformation(comp);
	}

	{
		// Find sole

		kde.XLinspace(0, 2 * M_PI, 360);
		kde.XSetCyclic(2 * M_PI);

		for(double cut = 0.2; cut < 0.81; cut += 0.2){
			Polygon3 section = hull.IntersectPlane(Vector3(1, 0, 0),
					bbc.GlobalX(cut));

			Vector3 rot = section.GetRotationalAxis();
			if(rot.x > 0) section.Reverse();

			const double Lmax = section.GetLength();
			for(size_t n = 0; n < section.Size(); ++n){
				const Vector3 temp = (section[(n + 1) % section.Size()]
						- section[n]);
				double a = atan2(temp.y, -temp.z);
				kde.Insert(a, temp.Abs() / Lmax, 0.2,
						KernelDensityEstimator::SilvermanKernel);
			}
		}

		kde.Normalize();

		kde.Attenuate(0, 0.75, 0.5, KernelDensityEstimator::CauchyKernel);
		kde.Attenuate(M_PI, 0.75, 0.5, KernelDensityEstimator::CauchyKernel);

		kde.FindPeaks(0.1);
		if(kde.ResultSize() == 0) return false;
		AffineTransformMatrix comp;
		comp *= AffineTransformMatrix::RotationAroundVector(Vector3(1, 0, 0),
				3 * M_PI_2 - kde.ResultX(0));
		hull.ApplyTransformation(comp);
	}

	// For Testing purposes change front and back.
//	{
//		hull.ApplyTransformation(
//				AffineTransformMatrix::RotationAroundVector(Vector3(0, 0, 1),
//				M_PI));
//		bb.Clear();
//		for(size_t i = 0; i < hull.GetVertexCount(); ++i)
//			bb.Insert(hull.GetVertex(i));
//	}

	{
		// Test for front/back reversal

//		loop.Clear();
		std::vector <double> ratio;
		for(double cut = 0.1; cut < 0.91; cut += 0.1){
			Polygon3 section = hull.IntersectPlane(Vector3(1, 0, 0),
					bbc.GlobalX(cut));
			BoundingBox temp;
			for(size_t n = 0; n < section.Size(); ++n)
				temp.Insert(section[n]);
			ratio.push_back(temp.GetSizeZ() / temp.GetSizeY());
//			loop += section.GetCenter();
		}
		PolyFilter pfr(2, ratio.size());
		Polynom pr = pfr.Filter(ratio);
		pr.ShiftX(1);
		pr.ScaleX(0.1);

//		test.Clear();
//		for(double r = 0; r <= 1; r += 0.01)
//			test += Vector3(bb.xmin + bb.GetSizeX() * r, 0.0, pr.Evaluate(r));

		pr.Derive();
		if(pr.Evaluate(0.5) > 0.0){
			// Reverse last
			std::cout << "Reverse last.\n";
			hull.ApplyTransformation(
					AffineTransformMatrix::RotationAroundVector(
							Vector3(0, 0, 1),
							M_PI));
			bb.Clear();
			for(size_t i = 0; i < hull.GetVertexCount(); ++i)
				bb.Insert(hull.GetVertex(i));
			bbc = bb.GetCoordinateSystem();
		}

//		double maxr;
//		if(pr.ExtremumPos(maxr)){
//			std::cout << "maxr = " << maxr << "\n";
//		}
//
//		std::vector <double> temp = loop.GetZVectorD();
//		PolyFilter pf(3, loop.Size());
//		Polynom pz = pf.Filter(temp);
//		pz.ShiftX(1);
//		pz.ScaleX(0.1);
//
//		loop.Clear();
//		for(double r = 0; r <= 1; r += 0.01)
//			loop += Vector3(bb.xmin + bb.GetSizeX() * r, 0.0, pz.Evaluate(r));
//
//		double pp;
//		double pn;
//		if(pz.ExtremumPos(pp) && pz.ExtremumNeg(pn)){
//			if(pp > pn && pp < 1.0 && pn > 0.0){
//				// Revert last
//				std::cout << "Rotate last by 180.\n";
//				hull.ApplyTransformation(
//						AffineTransformMatrix::RotationAroundVector(
//								Vector3(0, 0, 1),
//								M_PI));
//			}
//		}
	}

	bb.Clear();
	for(size_t i = 0; i < hull.GetVertexCount(); ++i)
		bb.Insert(hull.GetVertex(i));
	bbc = bb.GetCoordinateSystem();
//	return true;
	{
		// Scan for left/right

//		double ip = 0.5;
		loop.Clear();

//		kde.XLinspace(0, 1, 100);
//		kde.XSetLinear();
		for(double cut = 0.1; cut < 0.91; cut += 0.1){
			Polygon3 section = hull.IntersectPlane(Vector3(1, 0, 0),
					bbc.GlobalX(cut));
			loop += section.GetCenter();

//			BoundingBox bb2;
//			for(size_t n = 0; n < section.Size(); ++n)
//				bb2.Insert(section[n]);

//			kde.Insert(cut, bb2.GetSizeZ() / bb2.GetSizeY(), 0.3,
//					KernelDensityEstimator::TriweightKernel);
		}
//		kde.NormalizeByWeightSum();

		std::vector <double> temp = loop.GetYVectorD();
		PolyFilter pf(2, loop.Size());
		Polynom py = pf.Filter(temp);
		py.ShiftX(1);

		py.ScaleX(0.1);

//		test.Clear();
//		for(double r = 0; r <= 1; r += 0.01)
//			test += Vector3(bb.xmin + bb.GetSizeX() * r, py.Evaluate(r), 0.0);

		py.ScaleX(1.0 / bb.GetSizeX()); // Normale with lastlength
		py.ScaleY(1.0 / bb.GetSizeY()); // Normalize with lastwidth

//		std::cout << "py = " << py << ";\n";

		double chir = py[0];
//		if(py[0] > 1.0) std::cout << "Right last\n";
//		if(py[0] < -1.0) std::cout << "Left last\n";

//		pf.Export("/tmp/pf.mat");

//		if(pz.InflectionPoint(ip)) std::cout << "Inflection point: " << ip
//				<< "\n";

//		coordsys.SetCenter(Vector3(bb.xmin, 0, 0));
//		coordsys.SetEx(Vector3(bb.GetSizeX(), 0, 0));
//		coordsys.SetEy(Vector3(0, 0, 1));
//		coordsys.CalculateEz();

		kde.XLinspace(0, 2 * M_PI, 360);
		kde.XSetCyclic(2 * M_PI);

		loop = hull.IntersectPlane(Vector3(1, 0, 0), bbc.GlobalX(0.5));

		Vector3 rot = loop.GetRotationalAxis();
		if(rot.x > 0) loop.Reverse();

		const double Lmax = loop.GetLength();
		for(size_t n = 0; n < loop.Size(); ++n){
			const Vector3 temp = (loop[(n + 1) % loop.Size()] - loop[n]);
			double a = atan2(temp.y, -temp.z);
			kde.Insert(a, temp.Abs() / Lmax, 0.3,
					KernelDensityEstimator::SigmoidKernel);
		}

		kde.Normalize();

//		kde.Attenuate(0, 0.75, 0.5, KernelDensityEstimator::CauchyKernel);
//		kde.Attenuate(M_PI, 0.75, 0.5, KernelDensityEstimator::CauchyKernel);

		double minRight = 1e9;
		double minLeft = 1e9;
		for(size_t n = 0; n < kde.Size(); ++n){
			if(kde.X(n) > M_PI && kde.X(n) < 3 * M_PI_2 && kde.Y(n) < minRight) minRight =
					kde.Y(n);
			if(kde.X(n) < 2 * M_PI && kde.X(n) > 3 * M_PI_2
					&& kde.Y(n) < minLeft) minLeft = kde.Y(n);

		}

//		std::cout << "minLeft = " << minLeft << ";\n";
//		std::cout << "minRight = " << minRight << ";\n";

		chir += 4.0 * (minLeft - minRight) / (minLeft + minRight);

		if(chir < -0.5){
			AffineTransformMatrix temp;
			temp.ScaleGlobal(1.0, -1.0, 1.0);
			hull.ApplyTransformation(temp);

//			std::cout << "Flip sides left to right.\n";

			bb.Clear();
			for(size_t i = 0; i < hull.GetVertexCount(); ++i)
				bb.Insert(hull.GetVertex(i));
			bbc = bb.GetCoordinateSystem();
		}

//		std::cout << chir << " ";
//		if(chir > 0.0)
//			std::cout << " = Right last ";
//		else
//			std::cout << " = Left last ";
//		if(fabs(chir) < 0.5) std::cout << "(Insole recommended)";
//		std::cout << "\n";

	}

//	{
//		const double Lmax = shape2.GetLength();
//		for(size_t n = 0; n < shape2.Size(); ++n){
//			const Vector3 temp = (shape2[(n + 1) % shape2.Size()] - shape2[n]);
//			double a = atan2(temp.y, -temp.z);
//			cde.Add(CoreDensityEstimator::Epanechnikov, 0.5, a,
//					temp.Abs() / Lmax);
//		}
//	}

//	cde.Add(CoreDensityEstimator::Epanechnikov, 1, 1, 1);
//	cde.Add(CoreDensityEstimator::Epanechnikov, 0.5, 2.5, 1);
	{
		// Find the outline of the sole

//		loop = hull.IntersectPlane(Vector3(0, 1, 0), bbc.GlobalY(0, 0.5));

		const double param_soleangle = 35 * M_PI / 180;

		left.Clear();
		right.Clear();
		bottom.Clear();
		for(double cut = 0.05; cut < 0.95; cut += 0.025){
			Polygon3 section = hull.IntersectPlane(Vector3(1, 0, 0),
					bbc.GlobalX(cut));

			Vector3 r = section.GetRotationalAxis();
			if(r.x < 0) section.Reverse();

			const size_t N = section.Size();
			size_t Nmin = 0;
			for(size_t n = 0; n < N; ++n)
				if(section[n].z < section[Nmin].z) Nmin = n;

			for(size_t n = 0; n < N; ++n){
				const Vector3 n0 = section.Normal((Nmin + n) % N);
				const Vector3 n1 = section.Normal((Nmin + n + 1) % N);
				const double a0 = atan2(n0.y, -n0.z);
				const double a1 = atan2(n1.y, -n1.z);
				if(a0 < param_soleangle && a1 > param_soleangle){
					const double s = (param_soleangle - a0) / (a1 - a0);
					const Vector3 v0 = section[(Nmin + n) % N];
					const Vector3 v1 = section[(Nmin + n + 1) % N];
					left.InsertPoint((v1 - v0) * s + v0,
							((n1 - n0) * s + n0).Normal());
					break;
				}
			}

			for(size_t n = 0; n < N; ++n){
				const Vector3 n0 = section.Normal((Nmin + N - n) % N);
				const Vector3 n1 = section.Normal((Nmin + N - (n + 1)) % N);
				const double a0 = atan2(n0.y, -n0.z);
				const double a1 = atan2(n1.y, -n1.z);
				if(a0 > -param_soleangle && a1 < -param_soleangle){
					const double s = (-param_soleangle - a0) / (a1 - a0);
					const Vector3 v0 = section[(Nmin + N - n) % N];
					const Vector3 v1 = section[(Nmin + N - (n + 1)) % N];
					right.InsertPoint((v1 - v0) * s + v0,
							((n1 - n0) * s + n0).Normal());
					break;
				}
			}
		}

		for(size_t n = 0; n < right.Size(); ++n){
			const Vector3 temp = (right[n] + left[n]) / 2;
			bottom.InsertPoint(hull.IntersectArrow(temp, Vector3(0, 0, -1)));
		}

		coordsys.SetOrigin(Vector3(bb.xmin, (bb.ymax + bb.ymin) / 2, bb.zmin));
		coordsys.SetEx(Vector3(bb.xmax - bb.xmin, 0, 0));
		coordsys.SetEy(Vector3(0, 0, 1));
		coordsys.CalculateEz();

		PolyFilter pf;
		pf.Init(3, bottom.Size());
		Polynom pbo = pf.Filter(bottom.GetZVectorD());
		center.Clear();
		for(double n = 0; n < bottom.Size(); n += 0.4){
			center.PushBack(n/(double)bottom.Size(), pbo.Evaluate(n));
		}

//		ParameterLimits lim;
//		NelderMeadOptimizer optim;
//
//		optim.param.clear();
//
//		optim.param.push_back(0.3);
//		optim.param.push_back(-1.0);
//		optim.param.push_back(0.2);
//
//		lim.AddLimit(0, -0.5, 0.5);
//		lim.AddLimit(1, -5, -0.5);
//		lim.AddLimit(2, 0.1, 0.3);
//
//		optim.param.push_back(0.8);
//		optim.param.push_back(1.0);
//		optim.param.push_back(0.2);
//
//		lim.AddLimit(3, 0.5, 0.9);
//		lim.AddLimit(4, 0.5, 2);
//		lim.AddLimit(5, 0.1, 0.3);
//
//		optim.param.push_back(-20 * M_PI / 180);
//		lim.AddLimit(6, -20 * M_PI / 180, 20 * M_PI / 180);
//
//		optim.reevalBest = true;
//		optim.evalLimit = 100;
//
//		bottom.Export("/tmp/bot.mat");
//
//		Vector3 c = bottom[bottom.Size() / 2];
//
//		optim.Start();
//		while(optim.IsRunning()){
//
//			center.XLinspace(0, 1.4, 101);
//			center.YInit(0);
//			center.Insert(optim.param[0], optim.param[1], optim.param[2],
//					KernelDensityEstimator::GaussianKernel);
//			center.Insert(optim.param[3], optim.param[4], optim.param[5],
//					KernelDensityEstimator::GaussianKernel);
//
//			center.Export("/tmp/cent_0.mat");
//
//			center.Integrate();
//			double off1 = center.YatX(coordsys.LocalX(c));
//			center += optim.param[6] - off1;
//			center.YLimit(-1.4, 1.4);
//
//			center.Export("/tmp/cent_1.mat");
//
//			center.AngleToPos();
//			center.Export("/tmp/cent_2.mat");
//
//			double off2 = center.YatX(coordsys.LocalX(c));
//			center += coordsys.LocalY(c) - off2;
//
//			center.Export("/tmp/cent_3.mat");
//
//			double err = 0;
//			for(size_t n = 0; n < bottom.Size(); ++n){
//				const double x = coordsys.LocalX(bottom[n]);
//				const double y = center.YatX(x);
//				const double y_target = coordsys.LocalY(bottom[n]);
//				err += (y - y_target) * (y - y_target);
//			}
//			optim.SetError(err + lim.Evaluate(optim.param));
//		}
//
//		std::cout << "param = [";
//		for(size_t n = 0; n < optim.param.size(); ++n){
//			if(n > 0) std::cout << ", ";
//			std::cout << optim.param[n];
//		}
//		std::cout << "];\n";
//		std::cout << "res_err = " << optim.ResidualError() << ";\n";
//		std::cout << "eval_count = " << optim.EvaluationsDone() << ";\n";

//		coordsys.SetOrigin(Vector3());
//				coordsys.SetEx(Vector3(0, 1, 0));
//				coordsys.SetEy(Vector3(0, 0, 1));
//				coordsys.CalculateEz();

//			Polygon3 pmin;
//			for(size_t n = Nmin; n < (N + Nmin); ++n){
//				const size_t m = n % N;
//				pmin += loop[m];
//				if(m == Nmax) break;
//			}
//			Polygon3 pmax;
//			for(size_t n = Nmax; n < (N + Nmax); ++n){
//				const size_t m = n % N;
//				pmax += loop[m];
//				if(m == Nmin) break;
//			}
//
//			pmin.Resample(100);
//			pmax.Resample(100);
//			pmax.Reverse();
//
//			for(size_t n = 0; n < 100; ++n)
//				pmin[n] += pmax[n];
//			pmin /= 2.0;
//
//			loop = pmin;
//		loop.Resample(100);
//		Vector3 rot = loop.GetRotationalAxis();
//		if(rot.y < 0) loop.Reverse();
//
//		coordsys.SetCenter(loop.GetCenter());
//		coordsys.ResetRotationAndScale();
	}
//	formfinder.AddPolygon(loop, loop.GetCount() / 8);

//	std::vector <Vector3>::iterator min = std::min_element(formfinder.b.begin(),
//			formfinder.b.end(), Vector3XLess);
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

//	MatlabMatrix F("F", 12, formfinder.a.size());
//	for(size_t n = 0; n < formfinder.a.size(); ++n){
//		F.Insert(formfinder.a[n].x);
//		F.Insert(formfinder.b[n].x);
//		F.Insert(formfinder.c[n].x);
//		F.Insert(formfinder.d[n].x);
//		F.Insert(formfinder.a[n].y);
//		F.Insert(formfinder.b[n].y);
//		F.Insert(formfinder.c[n].y);
//		F.Insert(formfinder.d[n].y);
//		F.Insert(formfinder.a[n].z);
//		F.Insert(formfinder.b[n].z);
//		F.Insert(formfinder.c[n].z);
//		F.Insert(formfinder.d[n].z);
//	}
//	F.Transpose();
//	mf.WriteMatrix(F);

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

	return true;

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
	hull.Paint();

	OpenGLMaterial white(OpenGLMaterial::whiteplastic, 1.0);
	white.UseMaterial();

//	loop.Paint(true, 0.25);

	left.Paint(true);
	right.Paint(true);
	bottom.Paint(true);

	OpenGLMaterial green(OpenGLMaterial::whiterubber, 1.0);
	green.UseMaterial();

	test.Paint();

	OpenGLMaterial yellow(OpenGLMaterial::yellowplastic, 1.0);
	yellow.UseMaterial();

//	formfinder.Paint();

	glPushMatrix();
	coordsys.GLMultMatrix();
	center.Paint();

//	symmetry.Paint();
//	kde.Paint();
//	kde.PaintCircle(0.05);
//	kde.PaintCircle(0.1);
//	kde.PaintCircle(0.15);

	glPopMatrix();

	coordsys.Paint();

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
