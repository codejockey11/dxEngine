#ifndef _CCAMERA
#define _CCAMERA

#include "standard.h"

#include "CVertex.h"

class CCamera
{
public:

	D3DXMATRIX view;

	D3DXVECTOR3	cup;
	D3DXVECTOR3	cposition;
	D3DXVECTOR3	clookAt;

	CVertex position;
	CVertex rotation;

	CVertex right;
	CVertex up;
	CVertex look;

	FLOAT yaw;
	FLOAT pitch;
	FLOAT roll;

	CCamera();

	~CCamera();

	VOID UpdateView();

	VOID UpdateRotation(FLOAT x, FLOAT y, FLOAT z);

	VOID Copy(CCamera* p);
};
#endif