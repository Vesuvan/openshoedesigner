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

#include "../foot/FootMeasurements.h"
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
#include "../../math/Kernel.h"

#include <cctype>
#include <cmath>
#include <iostream>
#include <ostream>
#include <algorithm>

#include "../../3D/Bender.h"
#include "../../3D/OpenGL.h"
#include "../../3D/OpenGLText.h"
#include "../../3D/TransformationMixer.h"
#include "../../3D/TransformationMixerVector.h"
#include "../../math/MEstimator.h"
#include "../Insole.h"

LastModel::LastModel()
{
//	center.XLinspace(0, 1, 101);
//	center.YInit(0);
//	center.Insert(0.3, -1.2, 0.3, BendLine::EpanechnikovKernel);
//	center.Insert(0.75, 1.3, 0.03, BendLine::GaussianKernel);
//	center.AngleToPos();

	resized.paintTriangles = false;
	resized.paintVertices = true;

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

void LastModel::Modify(bool modified)
{
	this->modified = modified;
}
bool LastModel::IsModified(void) const
{
	return modified;
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
		raw.CopyFrom(geometry);
		raw.CalcNormals();
		if(raw.IsClosed()){
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
		raw.CopyFrom(stl.geometry);
		if(raw.IsClosed()){
			std::cout << "Fully closed hull loaded." << "\n";
		}else{
			std::cout << "Hull has open edges." << "\n";
		}
		raw.CalcNormals();
		AnalyseForm();
		return true;
	}
	if(extension.compare("obj") == 0){
		if(raw.LoadObj(filename)){
			AnalyseForm();
			return true;
		}
	}
	return false;
}

void LastModel::UpdateForm(const Insole & insole,
		const FootMeasurements & measurements)
{
	resized = raw;
//	resized.smooth = true;

	Polygon3 lastPlane = planeXZ;
	Polygon3 lastLeft = bottomleft;
	Polygon3 lastRight = bottomright;
	Polygon3 insoleCenter = insole.inside;
	for(size_t n = 0; n < insoleCenter.Size(); ++n)
		insoleCenter[n].y = 0.0;
	Polygon3 lastCenter;
	for(size_t n = idxHeelPoint; n <= idxToePoint; ++n)
		lastCenter.InsertPoint(lastPlane[n]);

	Polynom centerHeight;
	{
		const double L0 = lastCenter.GetLength();
//			const double v0 =
//					(lastPlane[idxHeelPoint] - lastPlane[idxZero]).Abs() / 2;
//			const double v1 = (lastPlane[idxWaistBottom]
//					- lastPlane[idxWaistTop]).Abs() / 2;
//			const double v2 = (lastPlane[idxLittleToeBottom]
//					- lastPlane[idxLittleToeTop]).Abs() / 2;
//			const double v3 = (lastPlane[idxBigToeBottom]
//					- lastPlane[idxBigToeTop]).Abs() / 2;
//			centerHeight = Polynom::ByBezier(v0, v1, v2, v3);
		centerHeight = Polynom::ByBezier(L0 / 5, L0 / 5, L0 / 10, L0 / 10);
	}

	{
		// Resize last to fit the length of the insole.
		const double scale = insoleCenter.GetLength() / lastCenter.GetLength();
		AffineTransformMatrix m;
		m.ScaleGlobal(scale, scale, scale);
		m *= AffineTransformMatrix::RotationXYZ(0, heela, 0);

		// Move heelpoint to insole
		Vector3 shift = insoleCenter[0] - m(lastCenter[0]);
		m.TranslateGlobal(shift.x, shift.y, shift.z);

		resized.Transform(m);
		lastLeft.Transform(m);
		lastRight.Transform(m);
		lastPlane.Transform(m);
		lastCenter.Transform(m);
	}

	{
		// Adjust last angles

		Polynom pDistance = Polynom::ByValue(0, 0, 1, insoleCenter.GetLength());

		Bender b;

		Vector3 c0 = (lastPlane[idxHeelPoint] + lastPlane[idxTop]) / 2;
		b.from0.SetOrigin(c0);
		b.from0.SetEz((lastPlane[idxTop] - lastPlane[idxHeelCenter]).Normal());
		b.from0.SetEy(Vector3(0, 1, 0));
		b.from0.CalculateEx();

		Vector3 c1 = (lastPlane[idxWaistBottom] + lastPlane[idxWaistTop]) / 2;
		b.from1.SetOrigin(c1);
		b.from1.SetEz(
				(lastPlane[idxWaistTop] - lastPlane[idxWaistBottom]).Normal());
		b.from1.SetEy(Vector3(0, 1, 0));
		b.from1.CalculateEx();

		auto I0 = insoleCenter.At(0.05);
		auto I1 = insoleCenter.At(0.4);
		auto A0 = lastCenter.At(0.05);
		auto A1 = lastCenter.At(0.4);

		double I0a = atan2(I0.d.z, I0.d.x);
		double I1a = atan2(I1.d.z, I1.d.x);
		double A0a = atan2(A0.d.z, A0.d.x);
		double A1a = atan2(A1.d.z, A1.d.x);

		double da0 = A0a - I0a;
		double da = (A1a - A0a) - (I1a - I0a);

		AffineTransformMatrix d = b.from1 / b.from0;

		b.to0 = b.from0;
		b.to0 = b.to0 * AffineTransformMatrix::RotationXYZ(0, da0, 0);

//		d = AffineTransformMatrix::RotationXYZ(0, da0 / 2, 0) * d
//				* AffineTransformMatrix::RotationXYZ(0, da0 / 2, 0);
		b.to1 = b.to0 * d;
//		b.to1 = b.to1 * AffineTransformMatrix::RotationXYZ(0, da0, 0);
		b.Calculate();
//		resized.Transform(b);
//		lastLeft.ApplyTransformation(b);
//		lastRight.ApplyTransformation(b);
//		lastPlane.ApplyTransformation(b);
//		lastCenter.ApplyTransformation(b);
	}

	{
		// Align last along the center of the insole
		const double L0 = lastCenter.GetLength();
		const size_t N = 9;
		centerHeight = Polynom::ByBezier(L0 / 5, L0 / 10, L0 / 10, L0 / 10);
		centerHeight.ScaleX(N + 2);
		centerHeight.ShiftX(-1);
		Polynom pDistance = Polynom::ByValue(-1, 0, N + 1,
				insoleCenter.GetLength());
//		std::cout<< centerHeight << "\n";
		for(size_t n = 0; n < N; ++n){
			const double L0 = pDistance(n);
			const double L1 = pDistance(n + 1);
			auto I0 = insoleCenter.At(L0);
			auto I1 = insoleCenter.At(L1);
			auto A0 = lastCenter.At(L0);
			auto A1 = lastCenter.At(L1);
			const double h0 = 0; //centerHeight(n);
			const double h1 = 0; //centerHeight(n + 1);

			Bender b;
			b.from0.SetEx(A0.d);
			b.from0.SetEy(Vector3(0, 1, 0));
			b.from0.CalculateEz();
			b.from0.SetOrigin(A0.p + b.from0.GetEz() * h0);
			b.from1.SetEx(A1.d);
			b.from1.SetEy(Vector3(0, 1, 0));
			b.from1.CalculateEz();
			b.from1.SetOrigin(A1.p + b.from0.GetEz() * h1);
			b.to0.SetEx(I0.d);
			b.to0.SetEy(Vector3(0, 1, 0));
			b.to0.CalculateEz();
			b.to0.SetOrigin(I0.p);
			b.to1.SetEx(I1.d);
			b.to1.SetEy(Vector3(0, 1, 0));
			b.to1.CalculateEz();
			b.to1.SetOrigin(I1.p);
			b.Calculate();

//			resized.Transform(b);
//			lastLeft.ApplyTransformation(b);
//			lastRight.ApplyTransformation(b);
//			lastPlane.ApplyTransformation(b);
//			lastCenter.ApplyTransformation(b);

		}

	}

	{
		// Align centerlines

		TransformationMixer m;
		const size_t N = 20;
		Polynom pDistance = Polynom::ByValue(0, -0.5, N - 1, 0.5);
		pDistance.ScaleY(0.95);
		pDistance.ShiftY(0.5);
		pDistance.ScaleY(insoleCenter.GetLength());
		Polynom dDistance = pDistance.Derivative();
		const double width = dDistance(0);

		for(size_t n = 0; n < N; ++n){
			const double L0 = pDistance(n);
			auto I0 = insoleCenter.At(L0);
			auto A0 = lastCenter.At(L0);

			Vector3 translate = I0.p - A0.p;
			AffineTransformMatrix tr;
			tr.TranslateGlobal(translate.x, translate.y, translate.z);
//			m.AddPlane(A0.p, A0.d, Kernel::Scale(Kernel::Cauchy, width/10), tr);
			m.AddCylinder(A0.p, Vector3(0, 1, 0),
					Kernel::Scale(Kernel::Cauchy, width / 5), tr);
		}
		resized.Transform(m);
		lastLeft.ApplyTransformation(m);
		lastRight.ApplyTransformation(m);
		lastPlane.ApplyTransformation(m);
		lastCenter.ApplyTransformation(m);
	}

	{
		// Scale width of the last

		TransformationMixer m;
		const size_t N = 6;
		Polynom pDistance = Polynom::ByValue(0, -0.5, N - 1, 0.5);
		pDistance.ScaleY(0.95);
		pDistance.ShiftY(0.5);
		pDistance.ScaleY(insoleCenter.GetLength());
		Polynom dDistance = pDistance.Derivative();
		const double width = dDistance(0);

		Polygon3 sideCenter = lastLeft;
		for(size_t n = 0; n < sideCenter.Size(); ++n)
			sideCenter[n] += lastRight[n];
		sideCenter /= 2;

		for(size_t n = 0; n < N; ++n){
			const double L0 = pDistance(n);

			auto I0 = insoleCenter.At(L0);
			size_t idx = I0.idx;
			if(I0.rel > 0.5) ++idx;
			Vector3 insoleR = insole.inside[idx];
			Vector3 insoleL = insole.outside[idx];

			auto A0 = lastCenter.At(L0);
			size_t lastIdx = sideCenter.ClosestPoint(A0.p);

			Vector3 lastR = lastRight[lastIdx];
			Vector3 lastL = lastLeft[lastIdx];

			AffineTransformMatrix tr;
			const double sc = (insoleR.y - insoleL.y) / (lastR.y - lastL.y);
			tr.ScaleGlobal(1, sc, 1);
			tr.TranslateGlobal(0, (insoleR.y - lastR.y * sc), 0);

//						m.AddPlane(A0.p, A0.d, Kernel::Scale(Kernel::Cauchy, width/10), tr);
			m.AddCylinder(A0.p, Vector3(0, 1, 0),
					Kernel::Scale(Kernel::Cauchy, width / 3), tr);
		}
		resized.Transform(m);
		lastLeft.ApplyTransformation(m);
		lastRight.ApplyTransformation(m);
		lastPlane.ApplyTransformation(m);
		lastCenter.ApplyTransformation(m);

	}

	{
		// Scale girth of the last
		TransformationMixer m;

		const double width = insoleCenter.GetLength() / 20;

		{
			Vector3 n = (lastPlane[idxTop] - lastPlane[idxHeelPoint]).Normal();
			Vector3 n2(-n.z, 0, n.x);
			Polygon3 resizedHeelGirth = resized.IntersectPlane(n2,
					n2.Dot(lastPlane[idxHeelPoint]));

			const double a = atan2(n.z, n.x);
			const Vector3 origin = lastPlane[idxHeelPoint];
			AffineTransformMatrix tr;
			const double scale = measurements.heelGirth.value
					/ resizedHeelGirth.GetLength();
			tr.ScaleGlobal(scale, 1, 1);

			tr = AffineTransformMatrix::RotationXYZ(0, -a, 0) * tr
					* AffineTransformMatrix::RotationXYZ(0, a, 0);

			tr.TranslateGlobal(-origin.x, -origin.y, -origin.z);
			tr.TranslateLocal(origin.x, origin.y, origin.z);

			m.AddPlane(origin, n2, Kernel::Scale(Kernel::Cauchy, width), tr);
		}
		{
			Vector3 n =
					(lastPlane[idxWaistTop] - lastPlane[idxWaistBottom]).Normal();
			Vector3 n2(-n.z, 0, n.x);
			Polygon3 resizedWaistGirth = resized.IntersectPlane(n2,
					n2.Dot(lastPlane[idxWaistBottom]));

			const double a = atan2(n.z, n.x);
			const Vector3 origin = lastPlane[idxWaistBottom];
			AffineTransformMatrix tr;
			const double scale = measurements.waistGirth.value
					/ resizedWaistGirth.GetLength();
			tr.ScaleGlobal(scale, 1, 1);

			tr = AffineTransformMatrix::RotationXYZ(0, -a, 0) * tr
					* AffineTransformMatrix::RotationXYZ(0, a, 0);

			tr.TranslateGlobal(-origin.x, -origin.y, -origin.z);
			tr.TranslateLocal(origin.x, origin.y, origin.z);

			m.AddPlane(origin, n2, Kernel::Scale(Kernel::Cauchy, width), tr);

		}
		{
			Vector3 n = (lastPlane[idxLittleToeTop]
					- lastPlane[idxLittleToeBottom]).Normal();
			Vector3 n2(-n.z, 0, n.x);
			Polygon3 resizedLittleToeGirth = resized.IntersectPlane(n2,
					n2.Dot(lastPlane[idxLittleToeBottom]));

			const double a = atan2(n.z, n.x);
			const Vector3 origin = lastPlane[idxLittleToeBottom];
			AffineTransformMatrix tr;
			const double scale = measurements.littleToeGirth.value
					/ resizedLittleToeGirth.GetLength();
			tr.ScaleGlobal(scale, 1, 1);

			tr = AffineTransformMatrix::RotationXYZ(0, -a, 0) * tr
					* AffineTransformMatrix::RotationXYZ(0, a, 0);

			tr.TranslateGlobal(-origin.x, -origin.y, -origin.z);
			tr.TranslateLocal(origin.x, origin.y, origin.z);

			m.AddPlane(origin, n2, Kernel::Scale(Kernel::Cauchy, width), tr);

		}
		{
			Vector3 n =
					(lastPlane[idxBigToeTop] - lastPlane[idxBigToeBottom]).Normal();
			Vector3 n2(-n.z, 0, n.x);
			Polygon3 resizedBigToeGirth = resized.IntersectPlane(n2,
					n2.Dot(lastPlane[idxBigToeBottom]));

			const double a = atan2(n.z, n.x);
			const Vector3 origin = lastPlane[idxBigToeBottom];
			AffineTransformMatrix tr;
			const double scale = measurements.bigToeGirth.value
					/ resizedBigToeGirth.GetLength();
			tr.ScaleGlobal(scale, 1, 1);

			tr = AffineTransformMatrix::RotationXYZ(0, -a, 0) * tr
					* AffineTransformMatrix::RotationXYZ(0, a, 0);

			tr.TranslateGlobal(-origin.x, -origin.y, -origin.z);
			tr.TranslateLocal(origin.x, origin.y, origin.z);

			m.AddPlane(origin, n2, Kernel::Scale(Kernel::Cauchy, width), tr);
		}

		resized.Transform(m);
		lastLeft.ApplyTransformation(m);
		lastRight.ApplyTransformation(m);
		lastPlane.ApplyTransformation(m);
		lastCenter.ApplyTransformation(m);
	}

	{
		// Align centerlines (again)

		TransformationMixer m;
		const size_t N = 20;
		Polynom pDistance = Polynom::ByValue(0, -0.5, N - 1, 0.5);
		pDistance.ScaleY(0.95);
		pDistance.ShiftY(0.5);
		pDistance.ScaleY(insoleCenter.GetLength());
		Polynom dDistance = pDistance.Derivative();
		const double width = dDistance(0);
		const double scale = insoleCenter.GetLength() / lastCenter.GetLength();

		for(size_t n = 0; n < N; ++n){
			const double L0 = pDistance(n);
			auto I0 = insoleCenter.At(L0);
			auto A0 = lastCenter.At(L0 / scale);

			Vector3 translate = I0.p - A0.p;
			AffineTransformMatrix tr;
			tr.TranslateGlobal(translate.x, translate.y, translate.z);
			//			m.AddPlane(A0.p, A0.d, Kernel::Scale(Kernel::Cauchy, width/10), tr);
			m.AddCylinder(A0.p, Vector3(0, 1, 0),
					Kernel::Scale(Kernel::Cauchy, width / 5), tr);
		}
		resized.Transform(m);
		lastLeft.ApplyTransformation(m);
		lastRight.ApplyTransformation(m);
		lastPlane.ApplyTransformation(m);
		lastCenter.ApplyTransformation(m);
	}

//	TransformationMixerVector mixervector;
//	TransformationMixer mixer;
//	resized.Transform(mixervector);
	return;
	/*
	 BoundingBox bb;
	 for(size_t i = 0; i < hull.GetVertexCount(); ++i)
	 bb.Insert(hull.GetVertex(i));
	 AffineTransformMatrix bbc = bb.GetCoordinateSystem();

	 scalevalues.resize(3, 0.001);

	 NelderMeadOptimizer optim;
	 optim.param.push_back(scalevalues[0]);
	 optim.param.push_back(scalevalues[1]);
	 optim.param.push_back(scalevalues[2]);

	 ParameterLimits limits;
	 limits.AddLimit(0, 0.001, 100, 1, 1000);
	 limits.AddLimit(1, 0.001, 100, 1, 1000);
	 limits.AddLimit(2, 0.001, 100, 1, 1000);

	 optim.simplexSpread = 1e-3;
	 optim.errorLimit = 1e-8;
	 optim.reevalBest = true;
	 optim.Start();
	 while(optim.IsRunning()){
	 Polynom s = Polynom::ByDerivative(0, optim.param[1], 0, 1,
	 optim.param[2], 0);
	 const double sx = optim.param[0];
	 for(size_t n = 0; n < resized.Size(); ++n){
	 Vector3 temp = hull[n];
	 const double x = bbc.LocalX(temp);
	 const double syz = s.Evaluate(x);
	 resized[n].Set(temp.x * sx, temp.y * syz, temp.z * syz);
	 }
	 double err = limits.Evaluate(optim.param);

	 err += pow((center.GetLength() * sx) - measurements.footLength.value,
	 2.0);

	 AffineTransformMatrix bbc2 = bbc;
	 bbc2.ScaleGlobal(sx, s[0.5], s[0.5]);

	 Polygon3 section = resized.IntersectPlane(Vector3(1, 0, 0),
	 bbc2.GlobalX(0.75));
	 Polygon3 section2 = resized.IntersectPlane(Vector3(1, 0, 0),
	 bbc2.GlobalX(0.5));
	 Polygon3 section3 = resized.IntersectPlane(Vector3(1, 0, -0.5),
	 bbc2.GlobalX(0.4));

	 err += pow((section.GetLength() - measurements.ballGirth.value), 2.0);
	 err += pow((section2.GetLength() - measurements.waistGirth.value), 2.0);
	 err += pow((section3.GetLength() - measurements.instepGirth.value),
	 2.0);
	 loop = section2;
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

	 std::cout << "ballGirth: " << measurements.ballGirth.value << " <== "
	 << section.GetLength() << "\n";
	 std::cout << "waistGirth: " << measurements.waistGirth.value << " <== "
	 << section2.GetLength() << "\n";
	 std::cout << "instepGirth: " << measurements.instepGirth.value
	 << " <== " << section3.GetLength() << "\n";

	 optim.SetError(err);
	 }

	 std::cout << "Min. Err: " << optim.ResidualError() << "\n";
	 //	std::cout << data.dx * data.sections.size() << " m\n";
	 //	std::cout << data.sections[37].GetLength() << " m\n";
	 */

	TransformationMixer tm;

	const Vector3 bendpoint(1.2, 0, -0.2);

	AffineTransformMatrix rot;
	rot = AffineTransformMatrix::RotationAroundVector( {0, 1, 0},
			-45.0 * M_PI / 180.0);
	rot.TranslateLocal(-1.2, 0, 0.2);
	rot.TranslateGlobal(1.2, 0, -0.2);

	tg.Set(Vector3(-2, -1, -1), Vector3(3, 1, 1));
	tg.SetCellSize(0.1);

	tm.AddPlane( {1.2 + 0.5, 0, -0.2}, {1, 0, 0},
			Kernel::Shift(Kernel::Scale(Kernel::Integrated::Cosine, 0.5), 0.0));
//	tm[0].TranslateLocal(0, 0, -1);
	tm[0] = rot;

	double angle = 45.0 / 180.0 * M_PI;
	auto unitBend = [angle](const Vector3 & v)-> Vector3{
		if(v.x <= 0.0)return v;
		const double fp = tan(fmin(v.x,1.0)*angle/2.0)*angle;
		const double sc = (fp+fmax(v.x-1.0,0.0))/(v.x-fp);
		const double co = cos(angle*fmin(v.x,1.0));
		const double si = sin(angle*fmin(v.x,1.0));
		const Vector3 d((v.x-fp)*sc,v.y,v.z);
		const Vector3 r(co*d.x-si*d.z,d.y,co*d.z+si*d.x);
		return Vector3((r.x+fp),r.y,r.z);
	};

//	for(size_t n = 0; n < resized.Size(); ++n)
//		resized[n] = unitBend(raw[n] - bendpoint) + bendpoint;
//	for(auto & p : tg.p)
//		p = unitBend(p - bendpoint) + bendpoint;

	{
		Bender b;
		b.from0.TranslateGlobal(1, 0, 0);

		b.from1.TranslateGlobal(1, 0, 0);
//	b.from1 *= AffineTransformMatrix::RotationXYZ(0, -M_PI / 6, 0);
		b.from1.TranslateLocal(1, 0, 0);
//	b.from1 *= AffineTransformMatrix::RotationXYZ(0, -M_PI / 6, 0);

		b.to0.TranslateGlobal(1, 0, 0);

		b.to1.TranslateLocal(1, 0, 0);
		b.to1 *= AffineTransformMatrix::RotationXYZ(0, M_PI / 10, 0);
		b.to1.TranslateLocal(1, 0, 0);
		b.to1 *= AffineTransformMatrix::RotationXYZ(0, M_PI / 10, 0);

		b.Calculate();

//	tg.p[0] = b(tg.p[16000]);

//		for(auto & p : tg.p)
//			p = b(p);
	}
	{
		Bender b;
		b.from0.TranslateGlobal(1, 0, 0);

		b.from1.TranslateGlobal(1, 0, 0);
		b.from1 *= AffineTransformMatrix::RotationXYZ(0, M_PI / 10, 0);
		b.from1.TranslateLocal(1, 0, 0);
		b.from1 *= AffineTransformMatrix::RotationXYZ(0, M_PI / 10, 0);

		b.to0.TranslateGlobal(1, 0, 0);

		b.to1.TranslateLocal(1, 0, 0);
		//	b.to1 *= AffineTransformMatrix::RotationXYZ(0, M_PI / 10, 0);
		b.to1.TranslateLocal(1, 0, 0);
		//	b.to1 *= AffineTransformMatrix::RotationXYZ(0, M_PI / 10, 0);

		b.Calculate();

		Transform(b);
	}

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

void LastModel::PaintMarker(const size_t idx, const OpenGLText &font,
		const std::string & text) const
{
	if(idx >= planeXZ.Size()) return;
	Vector3 normal =
			(planeXZ[(idx + 1) % planeXZ.Size()] - planeXZ[idx]).Normal();
	normal = Vector3(normal.z, 0, -normal.x);
	const Vector3 pos = planeXZ[idx];
	const Vector3 pos2 = pos + normal * 0.5;
	glBegin(GL_LINES);
	glVertex3f(pos.x, pos.y, pos.z);
	glVertex3f(pos2.x, pos2.y, pos2.z);
	glEnd();
	glPushMatrix();
	glTranslatef(pos2.x, pos2.y, pos2.z);
	glScalef(0.1, 0.1, 0.1);
	font.Paint(text);
	glPopMatrix();

}

void LastModel::PaintAnalysis(void) const
{

	OpenGLMaterial white(OpenGLMaterial::Preset::WhitePlastic, 1.0);
	white.UseMaterial();

//	loop.Paint(true, 0.25);

	bottomleft.Paint(true);
	bottomright.Paint(true);
//	bottom.Paint(true);
//	top.Paint(true);
//	center.Paint(true);

	OpenGLMaterial green(OpenGLMaterial::Preset::GreenRubber, 1.0);
	green.UseMaterial();

	planeXZ.Paint();

	HeelGirth.Paint();
	WaistGirth.Paint();
	LittleToeGirth.Paint();
	BigToeGirth.Paint();

	OpenGLText font;

	glNormal3f(0, -1, 0);

//	PaintMarker(0, font, "0");
	PaintMarker(idxZero, font, "Back");
	PaintMarker(idxHeel, font, "Heel");
	PaintMarker(idxHeelPoint, font, "HeelPoint");
	PaintMarker(idxHeelCenter, font, "HeelCenter");
	PaintMarker(idxWaistBottom, font, "Waist");
	PaintMarker(idxLittleToeBottom, font, "LittleToeBottom");
	PaintMarker(idxBigToeBottom, font, "BigToeBottom");
	PaintMarker(idxToeCenter, font, "ToeCenter");
	PaintMarker(idxToeTip, font, "ToeTip");
	PaintMarker(idxBigToeTop, font, "BigToeTop");
	PaintMarker(idxLittleToeTop, font, "LittleToeTop");
	PaintMarker(idxWaistTop, font, "WaistTop");
	PaintMarker(idxTop, font, "Front");

	OpenGLMaterial yellow(OpenGLMaterial::Preset::YellowPlastic, 1.0);
	yellow.UseMaterial();

//	formfinder.Paint();
	glDisable(GL_CULL_FACE);
	{
		Vector3 heelp = planeXZ[idxHeelCenter];
		Vector3 temp = heelp - Vector3(cos(heela), 0, sin(heela)) * 2.0;
		glBegin(GL_TRIANGLES);
		glVertex3f(heelp.x, heelp.y, heelp.z);
		glVertex3f(temp.x, temp.y, temp.z);
		glVertex3f(temp.x, temp.y, heelp.z);
		glEnd();
	}

	{
		Vector3 toep = planeXZ[idxToeCenter];
		Vector3 temp = toep + Vector3(cos(toea), 0, sin(toea)) * 2.0;
		glBegin(GL_TRIANGLES);
		glVertex3f(toep.x, toep.y, toep.z);
		glVertex3f(temp.x, temp.y, toep.z);
		glVertex3f(temp.x, temp.y, temp.z);
		glEnd();
	}
	glEnable(GL_CULL_FACE);

	glPushMatrix();
//	coordsys.GLMultMatrix();

	glRotatef(90, 0, 1, 0);

//	symmetry.Paint();
//	kde.Paint();

//	DependentVector::PaintCircle(0.125);
//	DependentVector::PaintCircle(0.25);
//	DependentVector::PaintCircle(0.5);

	glPopMatrix();

	OpenGLMaterial(OpenGLMaterial::Preset::YellowRubber).UseColor(1.0);
	glPushMatrix();

	coordsys.GLMultMatrix();
	glRotatef(90, 1, 0, 0);
//	angleXZ.Paint();

	glTranslatef(0, 0, 0.001);
	OpenGLMaterial(OpenGLMaterial::Preset::GreenPlastic).UseColor(1.0);
	debugA.Paint();

	glTranslatef(0, 0, 0.001);
	OpenGLMaterial(OpenGLMaterial::Preset::cFuchsia).UseColor(1.0);
	debugB.Paint();

	glTranslatef(0, 0, 0.001);
	OpenGLMaterial(OpenGLMaterial::Preset::Obsidian).UseColor(1.0);
	debugC.Paint();

	glRotatef(90, 0, 0, 1);

	glTranslatef(0, 0, 0.001);
	OpenGLMaterial(OpenGLMaterial::Preset::CyanPlastic).UseColor(1.0);
	debug0.Paint();

	glTranslatef(0, 0, 0.001);
	OpenGLMaterial(OpenGLMaterial::Preset::RedPlastic).UseColor(1.0);
	debug1.Paint();

	glTranslatef(0, 0, 0.001);
	OpenGLMaterial(OpenGLMaterial::Preset::Copper).UseColor(1.0);
	debug2.Paint();

	glPopMatrix();
	OpenGLMaterial::EnableColors();
	coordsys.Paint();

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

//	tg.PaintLines();

	OpenGLMaterial(OpenGLMaterial::Preset::cGray).UseMaterial(0.5);
	raw.Paint();
//	rawBB.Paint();
}

void LastModel::Paint(void) const
{
	resized.Paint();
}

DependentVector LastModel::OrthogonalPoint(const Vector3 & p) const
{
	const size_t N = planeXZ.Size();
	DependentVector temp;
	temp.XLinspace(0, 1, N);
	for(size_t n = 0; n < N; ++n){
		const Vector3 d = (planeXZ[(n + 1) % N] - planeXZ[n]).Normal();
		const Vector3 c = (planeXZ[n] - p).Normal();
		temp.Y(n) = d.Dot(c);
	}
	return temp;
}

size_t LastModel::FindTopPoint(size_t idxBottom, size_t idxStart,
		size_t idxEnd) const
{
	auto orth = OrthogonalPoint(planeXZ[idxBottom]);
	for(size_t n = 0; n < orth.Size(); ++n)
		orth.X(n) = angleXZ.X(n);
	size_t idx = orth.IatY(0, DependentVector::Direction::first_risingabove,
			idxStart, idxEnd);
	if(idx > idxEnd){
		return idxEnd;
	}else{
		return idx;
	}
}

double LastModel::RelValAt(const DependentVector& est, double x)
{
	auto vmin = est.Min();
	auto vmax = est.Max();
	double v = est.YatX(x);
	return (v - vmax.y) / (vmin.y - vmax.y);
}

void LastModel::Transform(std::function <Vector3(Vector3)> func)
{
	for(auto & p : tg.p)
		p = func(p);

	for(size_t n = 0; n < resized.Size(); ++n)
		resized[n] = func(raw[n]);

}

void LastModel::Mirror(void)
{
	AffineTransformMatrix m;
	m.ScaleGlobal(1, -1, 1);
	for(size_t n = 0; n < resized.Size(); ++n)
		resized[n] = m(resized[n]);
	resized.FlipNormals();
}

bool LastModel::Vector3XLess(const Vector3 a, const Vector3 b)
{
	return a.x < b.x;
}

void LastModel::UpdateRawBoundingBox(void)
{
	rawBB.Clear();
	for(size_t i = 0; i < raw.GetVertexCount(); ++i)
		rawBB.Insert(raw.GetVertex(i));
}

void LastModel::ReorientPCA(void)
{ // Find orientation of mesh

	PCA pca;
	pca.SetCenter(raw.GetCenter());
	for(size_t i = 0; i < raw.GetVertexCount(); ++i)
		pca.Add(raw.GetVertex(i));
	pca.Calculate();
// Make coordinate system right handed
	if((pca.X * pca.Y).Dot(pca.Z) > 0) pca.Y = -pca.Y;
// Remove orientation
	AffineTransformMatrix temp(pca.X, pca.Y, pca.Z, pca.center);
	temp.Invert();
	raw.Transform(temp);
	UpdateRawBoundingBox();
}

bool LastModel::ReorientSymmetry(void)
{
// Scan Shape for symmetry
	{
//		AffineTransformMatrix comp;
//		comp *= AffineTransformMatrix::RotationAroundVector(Vector3(1, 0, 0),
//				1.0);
//		raw.Transform(comp);
//		UpdateRawBoundingBox();
	}

	AffineTransformMatrix bbc = rawBB.GetCoordinateSystem();
	symmetry.Init(180);
	for(double cut = 0.2; cut < 0.81; cut += 0.2){
		Polygon3 section = raw.IntersectPlane(Vector3(1, 0, 0),
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
	auto results = symmetry.FindPeaks(0.01);
	if(results.empty()) return false;
	AffineTransformMatrix comp;
	comp *= AffineTransformMatrix::RotationAroundVector(Vector3(1, 0, 0),
	M_PI_2 - results[0].x);
//	std::cout << "Peak at " << results[0].x * 180.0 / M_PI << "degrees.\n";
//	std::cout << "Rotate by: " << (M_PI_2 - results[0].x) * 180.0 / M_PI
//			<< " degrees.\n";

	raw.Transform(comp);
	UpdateRawBoundingBox();
	return true;
}

bool LastModel::ReorientSole(void)
{
// Find sole
	kde.Clear();
	kde.XLinspace(0, 2 * M_PI, 360);
	kde.XSetCyclic(2 * M_PI);

	AffineTransformMatrix bbc = rawBB.GetCoordinateSystem();
	for(double cut = 0.2; cut < 0.81; cut += 0.2){
		Polygon3 section = raw.IntersectPlane(Vector3(1, 0, 0),
				bbc.GlobalX(cut));

		Vector3 rot = section.GetRotationalAxis();
		if(rot.x > 0) section.Reverse();

		const double Lmax = section.GetLength();
		for(size_t n = 0; n < section.Size(); ++n){
			const Vector3 temp =
					(section[(n + 1) % section.Size()] - section[n]);
			double a = atan2(temp.y, -temp.z);
			kde.Insert(a, Kernel::Silverman, temp.Abs() / Lmax, 0.2);
		}
	}

	kde.Normalize();

	kde.Attenuate(0, Kernel::Cauchy, 0.75, 0.5);
	kde.Attenuate(M_PI, Kernel::Cauchy, 0.75, 0.5);

	auto results = kde.FindPeaks(0.1);
	if(results.empty()) return false;
	AffineTransformMatrix comp;
	comp *= AffineTransformMatrix::RotationAroundVector(Vector3(1, 0, 0),
			3 * M_PI_2 - results[0].x);
	raw.Transform(comp);
	UpdateRawBoundingBox();
	return true;
}

void LastModel::ReorientFrontBack(void)
{ // Test for front/back reversal

//		loop.Clear();
	std::vector <double> ratio;
	AffineTransformMatrix bbc = rawBB.GetCoordinateSystem();
	for(double cut = 0.1; cut < 0.91; cut += 0.1){
		Polygon3 section = raw.IntersectPlane(Vector3(1, 0, 0),
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
	if(pr(0.5) > 0.0){
		// Reverse last
//		std::cout << "Reverse last.\n";
		raw.Transform(
				AffineTransformMatrix::RotationAroundVector(Vector3(0, 0, 1),
				M_PI));
		UpdateRawBoundingBox();
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
//				hull.Transform(
//						AffineTransformMatrix::RotationAroundVector(
//								Vector3(0, 0, 1),
//								M_PI));
//			}
//		}
}

void LastModel::ReorientLeftRight(void)
{

// Scan for left/right

//		double ip = 0.5;
	loop.Clear();

//		kde.XLinspace(0, 1, 100);
//		kde.XSetLinear();
	AffineTransformMatrix bbc = rawBB.GetCoordinateSystem();
	for(double cut = 0.1; cut < 0.91; cut += 0.1){
		Polygon3 section = raw.IntersectPlane(Vector3(1, 0, 0),
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

	py.ScaleX(1.0 / rawBB.GetSizeX()); // Normale with lastlength
	py.ScaleY(1.0 / rawBB.GetSizeY()); // Normalize with lastwidth

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
	kde.Clear();
	kde.XLinspace(0, 2 * M_PI, 360);
	kde.XSetCyclic(2 * M_PI);

	loop = raw.IntersectPlane(Vector3(1, 0, 0), bbc.GlobalX(0.5));

	Vector3 rot = loop.GetRotationalAxis();
	if(rot.x > 0) loop.Reverse();

	const double Lmax = loop.GetLength();
	for(size_t n = 0; n < loop.Size(); ++n){
		const Vector3 temp = (loop[(n + 1) % loop.Size()] - loop[n]);
		double a = atan2(temp.y, -temp.z);
		kde.Insert(a, Kernel::Sigmoid, temp.Abs() / Lmax, 0.3);
	}

	kde.Normalize();

//		kde.Attenuate(0, 0.75, 0.5, KernelDensityEstimator::CauchyKernel);
//		kde.Attenuate(M_PI, 0.75, 0.5, KernelDensityEstimator::CauchyKernel);

	double minRight = 1e9;
	double minLeft = 1e9;
	for(size_t n = 0; n < kde.Size(); ++n){
		if(kde.X(n) > M_PI && kde.X(n) < 3 * M_PI_2 && kde.Y(n) < minRight) minRight =
				kde.Y(n);
		if(kde.X(n) < 2 * M_PI && kde.X(n) > 3 * M_PI_2 && kde.Y(n) < minLeft) minLeft =
				kde.Y(n);

	}

//		std::cout << "minLeft = " << minLeft << ";\n";
//		std::cout << "minRight = " << minRight << ";\n";

	chir += 4.0 * (minLeft - minRight) / (minLeft + minRight);

	if(chir < -0.5){
		AffineTransformMatrix temp;
		temp.ScaleGlobal(1.0, -1.0, 1.0);
		raw.Transform(temp);

		//			std::cout << "Flip sides left to right.\n";

		UpdateRawBoundingBox();
	}

//		std::cout << chir << " ";
//		if(chir > 0.0)
//			std::cout << " = Right last ";
//		else
//			std::cout << " = Left last ";
//		if(fabs(chir) < 0.5) std::cout << "(Insole recommended)";
//		std::cout << "\n";

}

void LastModel::FindAndReorientCenterplane(void)
{
	const double param_soleangle = 25.0 * M_PI / 180.0;

	AffineTransformMatrix bbc = rawBB.GetCoordinateSystem();
	Polygon3 section = raw.IntersectPlane(Vector3(1, 0, 0), bbc.GlobalX(0.2));
	{
		Vector3 r = section.GetRotationalAxis();
		if(r.x < 0) section.Reverse();
	}
	const size_t N = section.Size();
	size_t Nmin = 0;
	for(size_t n = 0; n < N; ++n)
		if(section[n].z < section[Nmin].z) Nmin = n;

	size_t p0 = 0;
	size_t p1 = 0;
	for(size_t n = Nmin; n < Nmin + N; ++n){
		const Vector3 n0 = section.Normal(n % N);
		const Vector3 n1 = section.Normal((n + 1) % N);
		const double a0 = atan2(n0.y, n0.z);
		const double a1 = atan2(n1.y, n1.z);
		if(a0 > param_soleangle && a1 <= param_soleangle) p0 = n;
		if(a0 >= -param_soleangle && a1 < -param_soleangle){
			p1 = n + 1;
			break;
		}
	}
	Vector3 c = (section[p0 % N] + section[p1 % N]) / 2.0;

//	loop.Clear();
//	loop.InsertPoint(section[p0 % N], section.Normal(p0 % N));
//	loop.InsertPoint(section[p1 % N], section.Normal(p1 % N));

	planeXZ = raw.IntersectPlane(Vector3(0, 1, 0), c.y);
	{
		// Reverse the loop to run in a positive direction in the x-z coordinate system.
		// (Left-handed coordinate system)
		Vector3 r = planeXZ.GetRotationalAxis();
		if(r.y > 0) planeXZ.Reverse();
	}

	{
		kde.Clear();
		kde.XLinspace(0, 2 * M_PI, 360);
		kde.XSetCyclic(2 * M_PI);
		for(size_t n = 0; n < planeXZ.Size(); ++n){
			const Vector3 temp =
					(planeXZ[(n + 1) % planeXZ.Size()] - planeXZ[n]);
			const double a = atan2(-temp.x, temp.z);
			const double hx = bbc.LocalX(planeXZ[n]);
			const double hz = bbc.LocalZ(planeXZ[n]);
			double g = Kernel::Integrated::Cosine(-5.0 * (hx - 0.5));
			g *= Kernel::Integrated::Cosine(5.0 * (hz - 0.5));
			kde.Insert(a, Kernel::Sigmoid, temp.Abs() * g, 0.2);
		}
		kde.Normalize();
		auto results = kde.FindPeaks();
		double topangle = results[0].x;

		AffineTransformMatrix temp = AffineTransformMatrix::RotationXYZ(0,
				topangle - M_PI_2, 0);
		raw.Transform(temp);

		planeXZ.Transform(temp);
		UpdateRawBoundingBox();
		bbc = rawBB.GetCoordinateSystem();
		planeXZ.RotateOrigin(bbc.Transform(Vector3(0, 0.5, 3)));
	}

// Calculate the angles on the the shape
	{
		planeXZ.Filter(11);
		const size_t N = planeXZ.Size();
		angleXZ.Clear();
		const double Lmax = 1;		//planeXZ.GetLength();
		double L = 0.0;
		for(size_t n = 0; n < N; ++n){
			Vector3 temp = (planeXZ[(n + 1) % N] - planeXZ[n]);
			const double h = atan2(temp.z, temp.x);
			angleXZ.PushBack((double) L / (double) Lmax, h);
			L += temp.Abs();
		}
		if(angleXZ[0] > 0.0) angleXZ[0] -= 2 * M_PI;
		angleXZ.Unwrap(M_PI);
	}
}

bool LastModel::FindMarker(void)
{
	auto toRad = [](double x){return x*M_PI/180.0;};
	auto toDeg = [](double x){return x*180.0/M_PI;};

	const size_t N = planeXZ.Size();

// Temporary markerpoints for the top of the last
	{
		idxZero = angleXZ.IatY(toRad(-160),
				DependentVector::Direction::first_risingabove);
		if(idxZero >= N) idxZero = 0;
		idxTop = angleXZ.IatY(toRad(160),
				DependentVector::Direction::last_risingabove);
	}

// Temporary markerpoints for toes and heel
	{
		idxHeel = angleXZ.IatY(toRad(-90),
				DependentVector::Direction::first_risingabove);
		idxHeelPoint = angleXZ.IatY(toRad(-70),
				DependentVector::Direction::first_risingabove);
		idxToeTip = angleXZ.IatY(toRad(+90),
				DependentVector::Direction::first_risingabove);
		if(idxHeelPoint > angleXZ.Size()) return false;
		if(idxToeTip > angleXZ.Size()) return false;
	}

// Estimate the angles for the heel and ball area of the sole
	{
		MEstimator estheel;
		estheel.XLinspace(toRad(-90), toRad(90), 301);
		estheel.EstimateY(angleXZ, MEstimator::AndrewWave(), 0.03, idxHeelPoint,
				idxToeTip,
				Kernel::SubMul(Kernel::Integrated::Triangular, 0.35 * 2.0 - 1.0,
						-5));
		estheel.Normalize();
		auto valleyheel = estheel.FindValleys();
		if(valleyheel.empty()) return false;
		heela = valleyheel[0].x;
		if(valleyheel.size() >= 1 && RelValAt(estheel, valleyheel[1].x) > 0.8){
			std::cout << "No clear heel area.\n";
		}
	}

	{
		MEstimator esttoes;
		esttoes.XLinspace(toRad(-90), toRad(90), 301);
		esttoes.EstimateY(angleXZ, MEstimator::AndrewWave(), 0.03, idxHeelPoint,
				idxToeTip,
				Kernel::SubMul(Kernel::Integrated::Triangular, 0.65 * 2.0 - 1.0,
						5));
		esttoes.Normalize();
		auto valleytoe = esttoes.FindValleys();
		if(valleytoe.empty()) return false;
		toea = valleytoe[0].x;
		if(valleytoe.size() >= 1 && RelValAt(esttoes, valleytoe[1].x) > 0.8){
			std::cout << "No clear toe area.\n";
		}
	}

// Recalculate toe & heel and support points.
	{
		idxHeelPoint = angleXZ.IatY(heela - param_soleangle,
				DependentVector::Direction::first_risingabove);
		idxToeTip = angleXZ.IatY(toea + toRad(90),
				DependentVector::Direction::first_risingabove);
		idxToePoint = angleXZ.IatY(toea + param_soleangle,
				DependentVector::Direction::first_risingabove);

		const double xheel = angleXZ.X(idxHeelPoint);
		const double xtoes = angleXZ.X(idxToeTip);
		idxHeelCenter = angleXZ.IatX(xheel + (xtoes - xheel) / 6);
		idxWaistBottom = angleXZ.IatX(xheel + (xtoes - xheel) * 0.4);
		idxLittleToeBottom = angleXZ.IatX(xheel + (xtoes - xheel) * 0.62);
		idxBigToeBottom = angleXZ.IatX(xheel + (xtoes - xheel) * 0.62);
		const double xball = angleXZ.X(idxBigToeBottom);
		idxToeCenter = angleXZ.IatX(xball + (xtoes - xball) * 0.5);
		idxHeel = angleXZ.IatY(heela - toRad(90),
				DependentVector::Direction::last_risingabove, 0, idxHeelCenter);
	}

// Mark left and right outside lines
	FindOutline();

// Find the ball measurement angle
	{
		const Vector3 p = planeXZ[idxLittleToeBottom];
		Vector3 a, b;
		double da = DBL_MAX;
		double db = DBL_MAX;
		for(size_t n = 0; n < bottomleft.Size(); ++n){
			const double d = (bottomleft[n] - p).Abs2();
			if(d < da){
				da = d;
				a = bottomleft[n];
			}
		}
		for(size_t n = 0; n < bottomright.Size(); ++n){
			const double d = (bottomright[n] - p).Abs2();
			if(d < da){
				da = d;
				b = bottomright[n];
			}
		}
		const double w = (a - b).Abs();
		const double d = w * sin(toRad(10));
		const double xBigToe = angleXZ.X(idxLittleToeBottom) + d;
		idxBigToeBottom = angleXZ.IatX(xBigToe);
	}

// Recalculate heel point
	{
		const double xfront = angleXZ.X(idxTop);
		const double xend = angleXZ.X(idxZero) + 1.0;
		size_t idxTopMiddle = angleXZ.IatX((xend + xfront) / 2.0);
		auto orth = OrthogonalPoint(planeXZ[idxTopMiddle]);
		size_t temp = orth.IatY(0.0,
				DependentVector::Direction::last_risingabove, idxHeelPoint,
				idxBigToeBottom);
		if(temp < idxHeelCenter) idxHeelCenter = temp;
	}

// Place the marker on top of the last
// The markers are place so that a measurement tape wrapped around
// the last would be shortest.
	{
		size_t idx0 = angleXZ.IatY(toea + toRad(135),
				DependentVector::Direction::first_risingabove);
		idxBigToeTop = FindTopPoint(idxBigToeBottom, idx0, idxTop);
		idxLittleToeTop = FindTopPoint(idxLittleToeBottom, idx0, idxTop);
		idxWaistTop = FindTopPoint(idxWaistBottom, idxBigToeTop, idxTop);
		idxTop = FindTopPoint(idxHeelPoint, idxBigToeTop, idxTop);
	}

//	bool hasBallArea = true;
//	{
//		MEstimator est;
//		est.EstimateX(angleXZ, MEstimator::AndrewWave(), 0.03, toea,
//				idxBigToeBottom, idxToeTip);
//		est.Normalize();
////		debugB = est;
////		std::cout << "y0 = " << est.Y(idxBallBottom) << "\n";
//		const double v0 = est.XatY(0.5,
//				DependentVector::Direction::first_fallingbelow);
//		const double v1 = est.XatY(0.5,
//				DependentVector::Direction::last_risingabove);
//		const double v = (v0 + v1) / 2.0;
//		idxToeCenter = angleXZ.IatX(v);
//		hasBallArea = (est.Y(idxBigToeBottom) > 0.5);
//		debugA = est;
//	}

// Estimate the position of the foot arch
//	bool hasArchArea = false;
//	{
//		auto valleys = angleXZ.FindValleys(M_PI, idxHeelCenter, idxToeCenter);
//
//		const double xheel = angleXZ.X(idxHeelCenter);
//		const double xtoes = angleXZ.X(idxToeCenter);
//		idxLittleToeBottom = angleXZ.IatX((xheel + xtoes) / 2.0);
//		if(valleys.empty()){
//			std::cout << "Very round last without arch. (MBT last?)\n";
//		}else{
//			if(valleys[0].y > heela - toRad(2)){
//				std::cout << "The last has a very flat arch (only "
//						<< toDeg(heela - valleys[0].y) << " deg).\n";
//			}else{
//				hasArchArea = true;
//				idxLittleToeBottom = valleys[0].idx;
//				const double ymiddle = (heela + valleys[0].y) / 2.0;
//				{
//					const double ydelta = heela - valleys[0].y;
//					std::cout << "Arch bow: " << toDeg(ydelta) << " deg\n";
//				}
//				idxWaistBottom = angleXZ.IatY(ymiddle,
//						DependentVector::Direction::first_fallingbelow,
//						idxHeelCenter, idxLittleToeBottom);
//			}
//
//			if(valleys[0].y > toea - toRad(2)){
//				std::cout << "The last has a very flat toe bend (only "
//						<< toDeg(toea - valleys[0].y) << " deg).\n";
//			}else{
//				const double ymiddle = (toea + valleys[0].y) / 2.0;
//							{
//								const double ydelta = heela - valleys[0].y;
//								std::cout << "Arch bow: " << toDeg(ydelta) << " deg\n";
//							}
//				idxBigToeBottom = angleXZ.IatY(ymiddle,
//						DependentVector::Direction::first_risingabove,
//						idxLittleToeBottom, idxToeTip);
//			}
//
//		}
//	}
//	if(!hasBallArea){
//		const double x0 = test.X(idxBallBottom);
//		const double x1 = test.X(idxToeCenter);
//		markerindex[7] = test.IatX((x0 + x1) / 2.0);
//	}

// Estimate the ball area
//	{
//		MEstimator est;
//		est.XLinspace(toRad(-90), toRad(90), 301);
//		est.EstimateY(test, MEstimator::AndrewWave(), 0.03, idxInstepBottom,
//				idxToeTip);
//
//		const auto vmax = est.Max();
//		const auto vmin = est.Min();
//		auto valleys = est.FindValleys();
//
//		if(valleys.size() == 0) return false;
//		if(valleys.size() == 1
//				|| valleys[1].y > (vmin.y + (vmax.y - vmin.y) * 0.8)){
//			toea = valleys[0].x;
//			std::cout << "No clear ball area in last.\n";
//		}else{
//			if(valleys[0].idx > valleys[1].idx) std::swap(valleys[0],
//					valleys[1]);
//
//			toea = valleys[1].x;
//			auto min
//		}
//		debug2 = est;
//	}
// Estimate angle and position of heel-area
//	{
//		MEstimator est;
//		est.XLinspace(toRad(-90), toRad(90), 301);
//		est.EstimateY(test, MEstimator::AndrewWave(), 0.03, idxHeelPoint,
//				idxInstepBottom);
//		auto valleys = est.FindValleys();
//		if(valleys.empty()) return false;
//		heela = valleys[0].x;
//
//		est.EstimateX(test, MEstimator::AndrewWave(), 0.05, heela,
//				idxHeelPoint, idxInstepBottom);
//		const double mean = est.Mean();
//		double v0 = est.XatY(mean,
//				DependentVector::Direction::first_fallingbelow);
//		double v1 = est.XatY(mean,
//				DependentVector::Direction::last_risingabove);
//		double v = (v0 + v1) / 2.0;
//		idxHeelCenter = test.IatX(v);
//
//		debug0 = est;
//	}
//
//	{
//		MEstimator est;
//		est.XLinspace(toRad(-90), toRad(90), 301);
//		est.EstimateY(test, MEstimator::AndrewWave(), 0.03, idxWaistBottom,
//				idxToeTip);
//		auto valleys = est.FindValleys();
//		if(valleys.empty()) return false;
//		toea = valleys[0].x;
//
//		est.EstimateX(test, MEstimator::AndrewWave(), 0.05, toea,
//				idxWaistBottom, idxToeTip);
//		const double mean = est.Mean();
//		double v0 = est.XatY(mean,
//				DependentVector::Direction::first_fallingbelow);
//		double v1 = est.XatY(mean,
//				DependentVector::Direction::last_risingabove);
//		double v = (v0 + v1) / 2.0;
//		idxToeCenter = test.IatX(v);

//		debug1 = est;
//	}

//	// Temorary place Markers at the top of the last
//	{
//		const double A0 = test.X(idxHeelPoint) - test.X(idxToeTip);
//		const double A1 = test.X(idxHeelCenter) - test.X(idxToeTip);
//		const double A2 = test.X(idxWaistBottom) - test.X(idxToeTip);
//		const double A3 = test.X(idxBallBottom) - test.X(idxToeTip);
//		const double B0 = test.X(idxTop) - test.X(idxToeTip);
//		const double B1 = A1 / A0 * B0 + test.X(idxToeTip);
//		const double B2 = A2 / A0 * B0 + test.X(idxToeTip);
//		const double B3 = A3 / A0 * B0 + test.X(idxToeTip);
//		idxInstepTop = test.IatX(B1);
//		idxWaistTop = test.IatX(B2);
//		idxBallTop = test.IatX(B3);
//	}

//	debug2.XLinspace(toRad(-90), toRad(90), 301);
//	auto e = MEstimator::AndrewWave();
//	for(size_t n = 0; n < debug2.Size(); ++n)
//		debug2.Y(n) = e.Rho(debug2.X(n) / 0.05);

// Statistics for magic numbers
//	{
//		const double A0 = test.X(idxToeTip) - test.X(idxHeelPoint);
//		for(size_t n = 3; n < 9; ++n){
//			const double A1 = test.X(markerindex[n]) - test.X(idxHeelPoint);
//			std::cout << (char) ('@' + n) << " - " << 100 * A1 / A0 << "%\n";
//		}
//	}
// Extramarkers for heel and toeangle

//	est.XLinspace(-M_PI, M_PI, 301);
//	auto f = MEstimator::AndrewWave();
//	est.EstimateY(test, f, 0.01);
//	est /= est.Area();
//	est *= 2;
//	est.XLinspace(0, 1, 301);

// Rescale test for displaying.
//	angleXZ /= M_PI;
	return true;
}

void LastModel::MarkMeasurements(void)
{
	{
		Vector3 n = (planeXZ[idxTop] - planeXZ[idxHeelPoint]).Normal();
		Vector3 n2(-n.z, 0, n.x);
		HeelGirth = raw.IntersectPlane(n2, n2.Dot(planeXZ[idxHeelPoint]));
	}
	{
		Vector3 n = (planeXZ[idxWaistTop] - planeXZ[idxWaistBottom]).Normal();
		Vector3 n2(-n.z, 0, n.x);
		WaistGirth = raw.IntersectPlane(n2, n2.Dot(planeXZ[idxWaistBottom]));
	}
	{
		Vector3 n =
				(planeXZ[idxLittleToeTop] - planeXZ[idxLittleToeBottom]).Normal();
		Vector3 n2(-n.z, 0, n.x);
		LittleToeGirth = raw.IntersectPlane(n2,
				n2.Dot(planeXZ[idxLittleToeBottom]));
	}
	{
		Vector3 n = (planeXZ[idxBigToeTop] - planeXZ[idxBigToeBottom]).Normal();
		Vector3 n2(-n.z, 0, n.x);
		BigToeGirth = raw.IntersectPlane(n2, n2.Dot(planeXZ[idxBigToeBottom]));
	}
}

void LastModel::FindOutline(void)
{
// Find the outline of the sole

//		loop = hull.IntersectPlane(Vector3(0, 1, 0), bbc.GlobalY(0, 0.5));

	const size_t Ncut = 50;

	const Polynom rotation = Polynom::ByValue(0, heela, Ncut - 1, toea);
	const Polynom cutAt = Polynom::ByValue(0, 0.05, Ncut - 1, 0.95);

	const Vector3 xHeel = planeXZ[idxHeel];
	const Vector3 xToe = planeXZ[idxToeTip];

	bottomleft.Clear();
	bottomright.Clear();

//	AffineTransformMatrix bbc = rawBB.GetCoordinateSystem();

	for(size_t n = 0; n < Ncut; ++n){
		const double a = rotation(n);
		const Vector3 normal(cos(a), 0, sin(a));
		const Vector3 pos = xHeel + (xToe - xHeel) * cutAt(n);
		Polygon3 section = raw.IntersectPlane(normal, normal.Dot(pos));

		Vector3 r = section.GetRotationalAxis();
		if(r.x < 0) section.Reverse();

//		if(n == 25) loop = section;

		const size_t N = section.Size();
		size_t Nmin = 0;
		for(size_t n = 0; n < N; ++n)
			if(section[n].z < section[Nmin].z) Nmin = n;

		for(size_t n = 0; n < N; ++n){
			const Vector3 n0 = section.Normal((Nmin + n) % N);
			const Vector3 n1 = section.Normal((Nmin + n + 1) % N);
			const double a0 = atan2(n0.y, -n0.z);
			const double a1 = atan2(n1.y, -n1.z);
			if(a0 < param_soleangle && a1 >= param_soleangle){
				const double s = (param_soleangle - a0) / (a1 - a0);
				const Vector3 v0 = section[(Nmin + n) % N];
				const Vector3 v1 = section[(Nmin + n + 1) % N];
				bottomleft.InsertPoint((v1 - v0) * s + v0,
						((n1 - n0) * s + n0).Normal());
				break;
			}
		}

		for(size_t n = 0; n < N; ++n){
			const Vector3 n0 = section.Normal((Nmin + N - n) % N);
			const Vector3 n1 = section.Normal((Nmin + N - (n + 1)) % N);
			const double a0 = atan2(n0.y, -n0.z);
			const double a1 = atan2(n1.y, -n1.z);
			if(a0 > -param_soleangle && a1 <= -param_soleangle){
				const double s = (-param_soleangle - a0) / (a1 - a0);
				const Vector3 v0 = section[(Nmin + N - n) % N];
				const Vector3 v1 = section[(Nmin + N - (n + 1)) % N];
				bottomright.InsertPoint((v1 - v0) * s + v0,
						((n1 - n0) * s + n0).Normal());
				break;
			}
		}
	}

	bottom.Clear();
	top.Clear();
	for(size_t n = 0; n < bottomright.Size(); ++n){
		const Vector3 temp = (bottomright[n] + bottomleft[n]) / 2;
		bottom.InsertPoint(raw.IntersectArrow(temp, Vector3(0, 0, -1)));
		top.InsertPoint(raw.IntersectArrow(temp, Vector3(0, 0, 1)));
	}
//	planeXZ.Clear();
//	for(size_t n = 0; n < bottomright.Size(); ++n){
//		planeXZ.InsertPoint((top[n] + bottom[n] * 2.0) / 3.0);
//	}
//	{
//		const size_t iEnd = center.Size() - 1;
//		Vector3 temp = raw.IntersectArrow(center[0], center[0] - center[3]);
//		center[0] = temp;
//		temp = raw.IntersectArrow(center[iEnd],
//				center[iEnd] - center[iEnd - 3]);
//		center[iEnd] = temp;
//	}
}

bool LastModel::AnalyseForm(void)
{
	std::cout << "*** Analysing last ***\n";
	ReorientPCA();
	if(!ReorientSymmetry()) return false;
	if(!ReorientSole()) return false;
	ReorientFrontBack();
	ReorientLeftRight();
	FindAndReorientCenterplane();

	if(!FindMarker()) return false;

	MarkMeasurements();

//	kde.Clear();
//	kde.XLinspace(0, 2 * M_PI, 360);
//	kde.XSetCyclic(2 * M_PI);
//	for(size_t n = 0; n < center.Size(); ++n){
//		const Vector3 temp = (center[(n + 1) % center.Size()] - center[n]);
//		const double a = atan2(-temp.x, temp.z);
//		kde.Insert(a, Kernel::Picard, temp.Abs(), 0.3);
//	}
//	kde.Attenuate(M_PI_2, Kernel::Tricube, 1.0, M_PI);
//	kde.Attenuate(M_PI_2, Kernel::Uniform, 1.0, 1.6);
//
//	kde.Normalize();
//	auto results = kde.FindPeaks();

//	FindOutline();

// For Testing purposes change front and back.
//	{
//		hull.ApplyTransformation(
//				AffineTransformMatrix::RotationAroundVector(Vector3(0, 0, 1),
//				M_PI));
//		bb.Clear();
//		for(size_t i = 0; i < hull.GetVertexCount(); ++i)
//			bb.Insert(hull.GetVertex(i));
//	}

	MatlabFile mf("/tmp/test.mat");

//	return true;

//	{
//		const double Lmax = shape2.GetLength();
//		for(size_t n = 0; n < shape2.Size(); ++n){
//			const Vector3 temp = (shape2[(n + 1) % shape2.Size()] - shape2[n]);
//			double a = atan2(temp.y, -temp.z);
//			cde.Add(CoreDensityEstimator::Epanechnikov, 0.5, a,
//					temp.Abs() / Lmax);
//		}
//	}

	coordsys = rawBB.GetCoordinateSystem();

//	cde.Add(CoreDensityEstimator::Epanechnikov, 1, 1, 1);
//	cde.Add(CoreDensityEstimator::Epanechnikov, 0.5, 2.5, 1);
	{
//		coordsys.SetOrigin(
//				Vector3(rawBB.xmin, (rawBB.ymax + rawBB.ymin) / 2, rawBB.zmin));
//		coordsys.SetEx(Vector3(rawBB.xmax - rawBB.xmin, 0, 0));
//		coordsys.SetEy(Vector3(0, 0, 1));
//		coordsys.CalculateEz();

//		PolyFilter pf;
//		pf.Init(3, bottom.Size());
//		Polynom pbo = pf.Filter(bottom.GetZVectorD());
//		center.Clear();
//		for(double n = 0; n < bottom.Size(); n += 0.4){
//			center.PushBack(n/(double)bottom.Size(), pbo.Evaluate(n));
//		}

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

	std::cout << "*** Analysis done ***\n";
	return true;

}

