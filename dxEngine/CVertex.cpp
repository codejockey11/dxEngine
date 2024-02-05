#include "CVertex.h"

CVertex::CVertex()
{
	memset(this, 0x00, sizeof(CVertex));
}

CVertex::~CVertex()
{
}

CVertex::CVertex(FLOAT p1, FLOAT p2, FLOAT p3)
{
	X = p1;
	Y = p2;
	Z = p3;
};

VOID CVertex::operator += (CONST CVertex& v)
{
	X += v.X;
	Y += v.Y;
	Z += v.Z;
};

VOID CVertex::operator -= (CONST CVertex& v)
{
	X -= v.X;
	Y -= v.Y;
	Z -= v.Z;
};

VOID CVertex::operator *= (FLOAT v)
{
	X *= v;
	Y *= v;
	Z *= v;
};

VOID CVertex::operator /= (FLOAT v)
{
	X /= v;
	Y /= v;
	Z /= v;
};

CVertex CVertex::operator + (CONST CVertex& v)
{
	CVertex t;

	t.X = X + v.X;
	t.Y = Y + v.Y;
	t.Z = Z + v.Z;

	return t;
};

CVertex CVertex::operator - (CONST CVertex& v)
{
	CVertex t;

	t.X = X - v.X;
	t.Y = Y - v.Y;
	t.Z = Z - v.Z;

	return t;
};

CVertex CVertex::operator * (FLOAT v)
{
	CVertex t;

	t.X = X * v;
	t.Y = Y * v;
	t.Z = Z * v;

	return t;
};

CVertex CVertex::operator / (FLOAT v)
{
	CVertex t;

	t.X = X / v;
	t.Y = Y / v;
	t.Z = Z / v;

	return t;
};

BOOL CVertex::operator == (CONST CVertex v)
{
	return (X == v.X) && (Y == v.Y) && (Z == v.Z);
};

BOOL CVertex::operator != (CONST CVertex v)
{
	return !((X == v.X) && (Y == v.Y) && (Z == v.Z));
};

FLOAT CVertex::Length()
{
	return (FLOAT)sqrtf((X * X) + (Y * Y) + (Z * Z));
}

VOID CVertex::Normalize()
{
	FLOAT d = CVertex::Length();

	X = X / d;
	Y = Y / d;
	Z = Z / d;
}

VOID CVertex::RadiusNormalize()
{
	FLOAT d = (FLOAT)fabs((DOUBLE)X) + (FLOAT)fabs((DOUBLE)Y) + (FLOAT)fabs((DOUBLE)Z);

	X = X / d;
	Y = Y / d;
	Z = Z / d;
}

FLOAT CVertex::Dot(CVertex v)
{
	return (X * v.X) + (Y * v.Y) + (Z * v.Z);
};

CVertex CVertex::Cross(CVertex v)
{
	CVertex t;

	t.X = (Y * v.Z) - (Z * v.Y);
	t.Y = (Z * v.X) - (X * v.Z);
	t.Z = (X * v.Y) - (Y * v.X);

	return t;
}

CVertex CVertex::CalculateNormal(CVertex* a, CVertex* b, CVertex* c)
{
	CVertex edge1 = *c - *b;
	CVertex edge2 = *c - *a;

	edge1.Normalize();

	edge2.Normalize();

	CVertex N1 = edge1.Cross(edge2);

	N1.Normalize();

	return N1;
}

CVertex CVertex::RotateAngleByAxis(const FLOAT AngleInRad, const CVertex ReferenceAxis)
{
	//
	//  Rotate 3D vector pvToRotate by angle AngleRad (in radian), along axis pvAxis,  
	//  using right handed space (positive rotation is counter-clockwize)
	//  This is using Rodrigues' rotation formula which is more efficient than 
	//  converting the axis and angle into a rotation matrix, and using the rotation 
	//  matrix to compute the rotated vector.
	//
	// Rotate vector V by Angle about direction vector W:
	//      Vrot = V*Cos(Angle) + (WxV)*Sin(Angle) + w*(w.v)*(1-Cos(Angle))
	//

	CVertex Out, Axis;

	Axis = ReferenceAxis;
	Axis.Normalize();
	Out = (*this) * ((FLOAT)(cos(AngleInRad))) +
		Axis.Cross(*this) * ((FLOAT)(sin(AngleInRad))) +
		Axis * (Axis.Dot(*this)) * (1 - ((FLOAT)(cos(AngleInRad))));

	return Out;
}

CVertexRGBA::CVertexRGBA()
{
	memset(this, 0x00, sizeof(CVertexRGBA));
}

CVertexRGBA::~CVertexRGBA()
{
}

CVertexT::CVertexT()
{
	memset(this, 0x00, sizeof(CVertexT));
}

CVertexT::~CVertexT()
{
}

CVertexNT::CVertexNT()
{
	memset(this, 0x00, sizeof(CVertexNT));
}

CVertexNT::~CVertexNT()
{
}

CVertex2d::CVertex2d()
{
	memset(this, 0x00, sizeof(CVertex2d));
}

CVertex2d::~CVertex2d()
{
}

CVertex2::CVertex2()
{
	memset(this, 0x00, sizeof(CVertex2));
}

CVertex2::CVertex2(FLOAT p1, FLOAT p2)
{
	X = p1;
	Y = p2;
}

CVertex2::~CVertex2()
{
}

VOID CVertex2::RadiusNormalize()
{
	FLOAT d = (FLOAT)fabs((DOUBLE)X) + (FLOAT)fabs((DOUBLE)Y);

	X = X / d;
	Y = Y / d;
}