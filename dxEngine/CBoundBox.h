#ifndef _CBOUNDBOX
#define _CBOUNDBOX

#include "standard.h"

#include "CVertex.h"

class CBoundBox
{
public:

	CVertex min;
	CVertex max;
	
	CBoundBox();

	CBoundBox(CBoundBox* b);

	CBoundBox(CVertex* mn, CVertex* mx);
	
	~CBoundBox();

	VOID Copy(CBoundBox* b);

	VOID Update(CVertex* mn, CVertex* mx);

	BYTE CheckPointInBox(CVertex* p);
};
#endif