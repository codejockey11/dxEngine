#include "CBoundBox.h"

CBoundBox::CBoundBox()
{
	memset(this, 0x00, sizeof(CBoundBox));
}

CBoundBox::CBoundBox(CVertex* mn, CVertex* mx)
{
	memset(this, 0x00, sizeof(CBoundBox));

	min.X = mn->X;
	min.Y = mn->Y;
	min.Z = mn->Z;

	max.X = mx->X;
	max.Y = mx->Y;
	max.Z = mx->Z;
}

CBoundBox::CBoundBox(CBoundBox* b)
{
	min.X = b->min.X;
	min.Y = b->min.Y;
	min.Z = b->min.Z;

	max.X = b->max.X;
	max.Y = b->max.Y;
	max.Z = b->max.Z;
}

CBoundBox::~CBoundBox()
{
}

VOID CBoundBox::Copy(CBoundBox* b)
{
	min.X = b->min.X;
	min.Y = b->min.Y;
	min.Z = b->min.Z;

	max.X = b->max.X;
	max.Y = b->max.Y;
	max.Z = b->max.Z;
}

VOID CBoundBox::Update(CVertex* mn, CVertex* mx)
{
	min.X = mn->X;
	min.Y = mn->Y;
	min.Z = mn->Z;

	max.X = mx->X;
	max.Y = mx->Y;
	max.Z = mx->Z;
}

BYTE CBoundBox::CheckPointInBox(CVertex* p)
{
	if ((p->X > min.X) && (p->X < max.X))
	{
		if ((p->Y > min.Y) && (p->Y < max.Y))
		{
			return TRUE;
		}
	}

	return FALSE;
}