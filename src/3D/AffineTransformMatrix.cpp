///////////////////////////////////////////////////////////////////////////////
// Name               : AffineTransformMatrix.cpp
// Purpose            : A class to store a 3D affine transform matrix and provide operations upon.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 22.07.2009
// Copyright          : (C) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "AffineTransformMatrix.h"

#include <math.h>
#include <wx/tokenzr.h>
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfAffineTransformMatrix);

AffineTransformMatrix::AffineTransformMatrix()
{
	SetIdentity();
	linkScaling = true;
}

/*!\brief Copies a matrix by inserting a given matrix into \a a.
 *  \param b The matrix to copy.
 */
void AffineTransformMatrix::Set(AffineTransformMatrix const& b)
{
	if(this == &b) return;
	for(unsigned int i = 0; i < 16; i++)
		a[i] = b.a[i];
	TakeMatrixApart();
}

AffineTransformMatrix& AffineTransformMatrix::operator=(
		const AffineTransformMatrix& b)
{
	if(this == &b) return *this;
	for(unsigned int i = 0; i < 16; i++)
		this->a[i] = b.a[i];
	// this->TakeMatrixApart();
	return *this;
}

//! Resets the matrix to the identity matrix.
void AffineTransformMatrix::SetIdentity()
{
	rx = ry = rz = 0.0;
	tx = ty = tz = 0.0;
	sx = sy = sz = 1.0;
	for(unsigned int i = 0; i < 16; i++)
		a[i] = 0;
	a[0] = 1.0;
	a[5] = 1.0;
	a[10] = 1.0;
	a[15] = 1.0;
}

//! Returns the center point of the matrix.
Vector3 AffineTransformMatrix::GetCenter(void) const
{
	Vector3 temp;
	temp.x = a[12];
	temp.y = a[13];
	temp.z = a[14];
	return temp;
}

//! Generate a string containing the matrix.
wxString AffineTransformMatrix::ToString()
{
	TakeMatrixApart();
	wxString temp;
	temp += wxString::Format(_T("%f#%f#%f#"), tx, ty, tz);
	temp += wxString::Format(_T("%f#%f#%f#"), rx, ry, rz);
	temp += wxString::Format(_T("%f#%f#%f"), sx, sy, sz);
	return temp;
}

//! Setup the matrix from a string.
void AffineTransformMatrix::FromString(wxString const& string)
{
	wxStringTokenizer tkz(string, wxT("#"));
	while(tkz.HasMoreTokens()){
		wxString token = tkz.GetNextToken();
		switch(tkz.CountTokens()){
		case 8:
			token.ToDouble(&tx);
			break;
		case 7:
			token.ToDouble(&ty);
			break;
		case 6:
			token.ToDouble(&tz);
			break;
		case 5:
			token.ToDouble(&rx);
			break;
		case 4:
			token.ToDouble(&ry);
			break;
		case 3:
			token.ToDouble(&rz);
			break;
		case 2:
			token.ToDouble(&sx);
			break;
		case 1:
			token.ToDouble(&sy);
			break;
		case 0:
			token.ToDouble(&sz);
			break;
		}
	}
	PutMatrixTogether();
}

void AffineTransformMatrix::ToStream(wxTextOutputStream& stream)
{
	for(unsigned int n = 0; n < 16; n++){
		if(n > 0) stream << _T(" ");
		stream.WriteDouble(a[n]);
	}
}

void AffineTransformMatrix::FromStream(wxTextInputStream& stream)
{
	for(unsigned int n = 0; n < 16; n++)
		a[n] = stream.ReadDouble();
	TakeMatrixApart();
}

//! Calculate rx,ry,rz,tx,ty,tz and sx,sy,sz from the matrix.
void AffineTransformMatrix::TakeMatrixApart(void)
{
	double b[16];

	tx = a[12];
	ty = a[13];
	tz = a[14];

	sx = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	sy = sqrt(a[4] * a[4] + a[5] * a[5] + a[6] * a[6]);
	sz = sqrt(a[8] * a[8] + a[9] * a[9] + a[10] * a[10]);

	if(sx > 0.0){
		b[0] = a[0] / sx;
		b[1] = a[1] / sx;
		b[2] = a[2] / sx;
	}else{
		b[0] = 0.0;
		b[1] = 0.0;
		b[2] = 0.0;
	}
	if(sy > 0.0){
		b[4] = a[4] / sy;
		b[5] = a[5] / sy;
		b[6] = a[6] / sy;
	}else{
		b[4] = 0.0;
		b[5] = 0.0;
		b[6] = 0.0;
	}
	if(sz > 0.0){
		b[8] = a[8] / sz;
		b[9] = a[9] / sz;
		b[10] = a[10] / sz;
	}else{
		b[8] = 0.0;
		b[9] = 0.0;
		b[10] = 0.0;
	}

	//FIXME: I think this if(...) is wrong, because b[0] can be 0.
	if(b[0] != 0.0 || b[1] != 0.0){
		rz = atan2(b[1], b[0]);
	}else{
		rz = 0.0;
	}
	double coz = cos(rz);
	double siz = sin(rz);

	if(b[0] != 0.0 || b[1] != 0.0 || b[2] != 0.0){
		ry = atan2(-b[2], sqrt(b[0] * b[0] + b[1] * b[1]));
	}else{
		ry = 0.0;
	}
	double coy = cos(ry);
	double siy = sin(ry);

	b[0] = b[5] * coy * siz - b[6] * siy + b[4] * coy * coz;
	b[1] = -b[4] * siz + b[5] * coz;
	b[2] = b[5] * siy * siz + b[4] * coz * siy + b[6] * coy;

	if(b[1] != 0.0 || b[2] != 0.0){
		rx = atan2(b[2], b[1]);
	}else{
		rx = 0.0;
	}
}

//! Calculate the matrix from rx,ry,rz,tx,ty,tz and sx,sy,sz.
void AffineTransformMatrix::PutMatrixTogether(void)
{
	const double cox = cos(rx);
	const double six = sin(rx);
	const double coy = cos(ry);
	const double siy = sin(ry);
	const double coz = cos(rz);
	const double siz = sin(rz);

	//Matrix calculated with Axiom:
	// Rx := matrix[[1,0,0],[0,cox,-six],[0,six,cox]]
	// Ry := matrix[[coy,0,siy],[0,1,0],[-siy,0,coy]]
	// Rz := matrix[[coz,-siz,0],[siz,coz,0],[0,0,1]]
	// S := matrix[[sx,0,0],[0,sy,0],[0,0,sz]]
	// Rz*Ry*Rx*S

	a[0] = coy * coz * sx;
	a[1] = coy * siz * sx;
	a[2] = -siy * sx;
	a[3] = 0.0;
	a[4] = (-cox * siz + coz * six * siy) * sy;
	a[5] = (six * siy * siz + cox * coz) * sy;
	a[6] = coy * six * sy;
	a[7] = 0.0;
	a[8] = (six * siz + cox * coz * siy) * sz;
	a[9] = (cox * siy * siz - coz * six) * sz;
	a[10] = cox * coy * sz;
	a[11] = 0.0;
	a[12] = tx;
	a[13] = ty;
	a[14] = tz;
	a[15] = 1.0;
}

/*! \brief Inverts the matrix.
 *
 * The transform used in here is optimized for matrices with 0,0,0,1 in the last row.
 * It would not give the correct results for other matrices,
 *
 * \return Inverted matrix.
 */
const AffineTransformMatrix AffineTransformMatrix::Inverse() const
{
	//Axiom code:
	// )set fortran optlevel 2
	// )set output fortran on
	// R:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]])
	// inverse(R)

	const double T11 = (a[0] * a[5] + (-a[1] * a[4])) * a[10]
			+ ((-a[0] * a[6]) + a[2] * a[4]) * a[9]
			+ (a[1] * a[6] + (-a[2] * a[5])) * a[8];
	// T11 is the determinant of the matrix. This can not
	// not be zero for a correct transformation matrix.
	wxASSERT(T11!=0);

	double T12 = a[4] * a[9];
	double T13 = a[5] * a[8];
	double T14 = a[4] * a[10];
	double T15 = a[6] * a[8];
	double T16 = a[5] * a[10];
	double T17 = a[6] * a[9];
	double T18 = a[0] * a[9];
	double T19 = a[1] * a[8];
	double T21 = a[0] * a[10];
	double T22 = a[2] * a[8];
	double T24 = a[1] * a[10];
	double T25 = a[2] * a[9];
	double T27 = a[1] * a[6] + (-a[2] * a[5]);
	double T28 = (-a[0] * a[6]) + a[2] * a[4];
	double T29 = a[0] * a[5] + (-a[1] * a[4]);
	double T30 = a[0] * a[5];
	double T31 = a[1] * a[4];
	double T32 = a[0] * a[6];
	double T33 = a[2] * a[4];
	double T34 = a[1] * a[6];
	double T35 = a[2] * a[5];

	AffineTransformMatrix b;

	b.a[0] = (T16 - T17) / T11;
	b.a[4] = (-T14 + T15) / T11;
	b.a[8] = (T12 - T13) / T11;
	b.a[12] =
			((-T12 + T13) * a[14] + (T14 - T15) * a[13] + (-T16 + T17) * a[12])
					/ T11;
	b.a[1] = (-T24 + T25) / T11;
	b.a[5] = (T21 - T22) / T11;
	b.a[9] = (-T18 + T19) / T11;
	b.a[13] =
			((T18 - T19) * a[14] + (-T21 + T22) * a[13] + (-T25 + T24) * a[12])
					/ T11;
	b.a[2] = T27 / T11;
	b.a[6] = T28 / T11;
	b.a[10] = T29 / T11;
	b.a[14] =
			((-T30 + T31) * a[14] + (T32 - T33) * a[13] + (-T34 + T35) * a[12])
					/ T11;
	b.a[3] = 0;
	b.a[7] = 0;
	b.a[11] = 0;
	b.a[15] = 1;
	return b;
}

//! Overloaded operator to allow correct multiplication of two matrices.
AffineTransformMatrix& AffineTransformMatrix::operator*=(
		const AffineTransformMatrix& b)
{
	//Generated with this code:
	//php -r'for($i=0;$i<4;$i++){for($j=0;$j<4;$j++){printf("this->a[%u]=",$i*4+$j);for($k=0;$k<4;$k++){printf("c[%u]*b.a[%u]%s",$k*4+$j,$i*4+$k,($k==3)?";\r\n":"+");}}}'

	// The php code generates all combinations.
	// The axiom code optimizes it a little more, because b.a[3], b.a[7] and b.a[11] are
	// zero and b.a[15] is one.

	// Axiom:
	// this:=matrix([[c[0],c[4],c[8],c[12]],[c[1],c[5],c[9],c[13]],[c[2],c[6],c[10],c[14]],[0,0,0,1]]);
	// b:=matrix([[ba[0],ba[4],ba[8],ba[12]],[ba[1],ba[5],ba[9],ba[13]],[ba[2],ba[6],ba[10],ba[14]],[0,0,0,1]]);

	double c[16];
	for(unsigned int i = 0; i < 16; i++)
		c[i] = this->a[i];

	this->a[0] = c[0] * b.a[0] + c[4] * b.a[1] + c[8] * b.a[2];
	this->a[1] = c[1] * b.a[0] + c[5] * b.a[1] + c[9] * b.a[2];
	this->a[2] = c[2] * b.a[0] + c[6] * b.a[1] + c[10] * b.a[2];
	this->a[3] = 0;

	this->a[4] = c[0] * b.a[4] + c[4] * b.a[5] + c[8] * b.a[6];
	this->a[5] = c[1] * b.a[4] + c[5] * b.a[5] + c[9] * b.a[6];
	this->a[6] = c[2] * b.a[4] + c[6] * b.a[5] + c[10] * b.a[6];
	this->a[7] = 0;

	this->a[8] = c[0] * b.a[8] + c[4] * b.a[9] + c[8] * b.a[10];
	this->a[9] = c[1] * b.a[8] + c[5] * b.a[9] + c[9] * b.a[10];
	this->a[10] = c[2] * b.a[8] + c[6] * b.a[9] + c[10] * b.a[10];
	this->a[11] = 0;

	this->a[12] = c[0] * b.a[12] + c[4] * b.a[13] + c[8] * b.a[14] + c[12];
	this->a[13] = c[1] * b.a[12] + c[5] * b.a[13] + c[9] * b.a[14] + c[13];
	this->a[14] = c[2] * b.a[12] + c[6] * b.a[13] + c[10] * b.a[14] + c[14];
	this->a[15] = 1;

	return *this;
}

//! Overloaded operator to allow correct multiplication of two matrices.
const AffineTransformMatrix AffineTransformMatrix::operator*(
		const AffineTransformMatrix& b) const
{
	AffineTransformMatrix c = *this;
	c *= b;
	return c;
}

/*!\brief  Overloaded operator to allow correct division of two matrices.
 *
 * The division is done by inverting the second matrix and the multiplying both.
 */
AffineTransformMatrix& AffineTransformMatrix::operator/=(
		const AffineTransformMatrix& b)
{
	(*this) = (*this) * (b.Inverse());
	return *this;
}

//! Overloaded operator to allow correct division of two matrices.
const AffineTransformMatrix AffineTransformMatrix::operator/(
		const AffineTransformMatrix& b) const
{
	AffineTransformMatrix c = *this;
	c /= b;
	return c;
}

//! Apply the transformation matrix on a given vector.
Vector3 AffineTransformMatrix::Transform(Vector3 const& v) const
{
	//Axiom code:
	// R:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]])
	// V:=matrix([[x],[y],[z],[1]])
	// R*V

	Vector3 temp;
	temp.x = a[0] * v.x + a[4] * v.y + a[8] * v.z + a[12];
	temp.y = a[1] * v.x + a[5] * v.y + a[9] * v.z + a[13];
	temp.z = a[2] * v.x + a[6] * v.y + a[10] * v.z + a[14];
	return temp;
}

//! Apply the transformation matrix on a given vector without shifting the vector.
Vector3 AffineTransformMatrix::TransformNoShift(Vector3 const& v) const
{
	//Axiom code:
	// R:=matrix([[a[0],a[4],a[8],0],[a[1],a[5],a[9],0],[a[2],a[6],a[10],0],[0,0,0,1]])
	// V:=matrix([[x],[y],[z],[1]])
	// R*V

	Vector3 temp;
	temp.x = a[0] * v.x + a[4] * v.y + a[8] * v.z;
	temp.y = a[1] * v.x + a[5] * v.y + a[9] * v.z;
	temp.z = a[2] * v.x + a[6] * v.y + a[10] * v.z;
	return temp;
}

//! Function returning an identity matrix.
AffineTransformMatrix AffineTransformMatrix::Identity()
{
	AffineTransformMatrix a;
	return a;
}

//! Translate matrix in the global coordinate system.
void AffineTransformMatrix::TranslateGlobal(double const& x, double const& y,
		double const& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// T:=matrix([[1,0,0,x],[0,1,0,y],[0,0,1,z],[0,0,0,1]]);
	// T*this
	a[12] += x;
	a[13] += y;
	a[14] += z;
}

//! Translate matrix in the local, rotated coordinate system.
void AffineTransformMatrix::TranslateLocal(double const& x, double const& y,
		double const& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// T:=matrix([[1,0,0,x],[0,1,0,y],[0,0,1,z],[0,0,0,1]]);
	// this*T
	a[12] += x * a[0] + y * a[4] + z * a[8];
	a[13] += x * a[1] + y * a[5] + z * a[9];
	a[14] += x * a[2] + y * a[6] + z * a[10];
}

//! Scale matrix in the global coordinate system.
void AffineTransformMatrix::ScaleGlobal(double const& x, double const& y,
		double const& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// S:=matrix([[x,0,0,0],[0,y,0,0],[0,0,z,0],[0,0,0,1]]);
	// S*this

	a[0] *= x;
	a[1] *= y;
	a[2] *= z;
	a[4] *= x;
	a[5] *= y;
	a[6] *= z;
	a[8] *= x;
	a[9] *= y;
	a[10] *= z;
	a[12] *= x;
	a[13] *= y;
	a[14] *= z;
}

//! Scale matrix in the local coordinate system.
void AffineTransformMatrix::ScaleLocal(const double& x, const double& y,
		const double& z)
{
	// Axiom code:
	// this:=matrix([[a[0],a[4],a[8],a[12]],[a[1],a[5],a[9],a[13]],[a[2],a[6],a[10],a[14]],[0,0,0,1]]);
	// S:=matrix([[x,0,0,0],[0,y,0,0],[0,0,z,0],[0,0,0,1]]);
	// this*S

	a[0] *= x;
	a[1] *= x;
	a[2] *= x;
	a[4] *= y;
	a[5] *= y;
	a[6] *= y;
	a[8] *= z;
	a[9] *= z;
	a[10] *= z;
}

/*!\brief Rotation around a given vector.
 *
 * Generates a rotation matrix around a given vector.
 * \param vector Axis of rotation.
 * \param phi Angle of rotation.
 * \return Rotation matrix.
 */
AffineTransformMatrix AffineTransformMatrix::RotateAroundVector(
		Vector3 const& vector, double const& phi)
{
	const double c = cos(phi);
	const double s = sin(phi);
	const double t = 1 - c;

	Vector3 v(vector);
	v.Normalize();

	AffineTransformMatrix a;

	a.a[0] = t * v.x * v.x + c;
	a.a[1] = t * v.x * v.y + s * v.z;
	a.a[2] = t * v.x * v.z - s * v.y;

	a.a[4] = t * v.x * v.y - s * v.z;
	a.a[5] = t * v.y * v.y + c;
	a.a[6] = t * v.y * v.z + s * v.x;

	a.a[8] = t * v.x * v.z + s * v.y;
	a.a[9] = t * v.y * v.z - s * v.x;
	a.a[10] = t * v.z * v.z + c;

	return a;
}

/*! \brief Rotation by mouse.
 *
 * This function is only a drop in until the RotateByTrackball function works.
 *
 * \param x Movement of mouse in x direction (=xnew-xold).
 * \param y Movement of mouse in y direction (=ynew-yold).
 * \param scale Scaling of the movement.
 * \return Rotation matrix.
 */
AffineTransformMatrix AffineTransformMatrix::RotateXY(int const& x,
		int const& y, double const& scale)
{

	const double dx = (double) x / scale;
	const double dy = (double) y / scale;

	const double dist = sqrt(dx * dx + dy * dy);

	AffineTransformMatrix a;

	if(dist > 0.001){
		const double ang = -atan2(dy, dx);

		const double coy = cos(dist / 100);
		const double siy = sin(dist / 100);
		const double coz = cos(ang);
		const double siz = sin(ang);

		a.a[0] = coz * coz * coy + siz * siz;
		a.a[1] = coz * siz * coy - coz * siz;
		a.a[2] = -coz * siy;
		a.a[4] = siz * coz * coy - coz * siz;
		a.a[5] = siz * siz * coy + coz * coz;
		a.a[6] = -siz * siy;
		a.a[8] = coz * siy;
		a.a[9] = siz * siy;
		a.a[10] = coy;
	}
	return a;
}

//! Rotation by the Z,Y,X rule.
AffineTransformMatrix AffineTransformMatrix::RotateXYZ(double const& x,
		double const& y, double const& z)
{
	AffineTransformMatrix a;

	//Axiom code:
	// Rx := matrix[[1,0,0,0],[0,cox,-six,0],[0,six,cox,0],[0,0,0,1]]
	// Ry := matrix[[coy,0,siy,0],[0,1,0,0],[-siy,0,coy,0],[0,0,0,1]]
	// Rz := matrix[[coz,-siz,0,0],[siz,coz,0,0],[0,0,1,0],[0,0,0,1]]
	// Rz*Ry*Rx

	const double six = sin(x);
	const double siy = sin(y);
	const double siz = sin(z);
	const double cox = cos(x);
	const double coy = cos(y);
	const double coz = cos(z);

	a.a[0] = coy * coz;
	a.a[1] = coy * siz;
	a.a[2] = -siy;

	a.a[4] = -cox * siz + coz * six * siy;
	a.a[5] = six * siy * siz + cox * coz;
	a.a[6] = coy * six;

	a.a[8] = six * siz + cox * coz * siy;
	a.a[9] = cox * siy * siz - coz * six;
	a.a[10] = cox * coy;

	return a;
}

/*!\brief An interwoven rotation.
 *
 * Generates a rotation matrix around x,y,z.
 * In this case the rotations are interwoven:
 *
 * Every rotation (around x, around y and around z) is done
 * in infinitesimal small steps. On step around x, one step around y, ...
 *
 * This results in a rotation as expected from a 6 DOF controller.
 */
AffineTransformMatrix AffineTransformMatrix::RotateInterwoven(double const& x,
		double const& y, double const& z)
{
	const double alpha = sqrt(x * x + y * y + z * z);
	if(alpha == 0) return AffineTransformMatrix::Identity();
	const Vector3 R(x / alpha, y / alpha, z / alpha);
	return AffineTransformMatrix::RotateAroundVector(R, alpha);
}

/*!\brief Rotate around a virtual trackball.
 *
 * @param x1 Old x-mouse position on screen
 * @param y1 Old y-mouse position on screen
 * @param x2 New x-mouse position on screen
 * @param y2 New y-mouse position on screen
 * @param r Radius of a sphere in screen units.
 * @return Rotational Matrix
 */
AffineTransformMatrix AffineTransformMatrix::RotateTrackball(const double& x1,
		const double& y1, const double& x2, const double& y2, const double& r)
{
	Vector3 r1(x1, y1, 0);
	r1 /= r;
	const double d1 = r1.Abs2();
	if(d1 >= 1.0){
		r1 /= sqrt(d1);
	}else{
		r1.z = sqrt(1 - d1);
	}
	Vector3 r2(x2, y2, 0);
	r2 /= r;
	const double d2 = r2.Abs2();
	if(d2 >= 1.0){
		r2 /= sqrt(d2);
	}else{
		r2.z = sqrt(1 - d2);
	}
	const Vector3 A = r1 * r2;
	const double alpha = asin(A.Abs());
	return AffineTransformMatrix::RotateAroundVector(A, alpha);
}
