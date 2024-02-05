#include "CCamera.h"

CCamera::CCamera()
{
	memset(this, 0x00, sizeof(CCamera));
}

CCamera::~CCamera()
{
}

VOID CCamera::UpdateRotation(FLOAT x, FLOAT y, FLOAT z)
{
	rotation.X += x;

	if (rotation.X < 0.0F)
	{
		rotation.X = 359.0F;
	}
	else if (rotation.X > 359.0F)
	{
		rotation.X = 0.0F;
	}

	rotation.Y += y;

	if (rotation.Y < 0.0F)
	{
		rotation.Y = 359.0F;
	}
	else if (rotation.Y > 359.0F)
	{
		rotation.Y = 0.0F;
	}

	rotation.Z += z;

	if (rotation.Z < 0.0F)
	{
		rotation.Z = 359.0F;
	}
	else if (rotation.Z > 359.0F)
	{
		rotation.Z = 0.0F;
	}
}

VOID CCamera::UpdateView()
{
	yaw = rotation.Y * PiDiv180;
	pitch = rotation.X * PiDiv180;
	roll = rotation.Z * PiDiv180;

	XMMATRIX xmMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);


	XMFLOAT3 xmlook;

	xmlook.x = 0.0F;
	xmlook.y = 0.0F;
	xmlook.z = 1.0F;

	FXMVECTOR fxmvlook = XMLoadFloat3(&xmlook);

	XMVECTOR xmvlook = XMVector3TransformCoord(fxmvlook, xmMatrix);

	XMFLOAT3 xmflook = XMFLOAT3(XMVectorGetX(xmvlook), XMVectorGetY(xmvlook), XMVectorGetZ(xmvlook));


	XMFLOAT3 xmfup;

	xmfup.x = 0.0F;
	xmfup.y = 1.0F;
	xmfup.z = 0.0F;

	FXMVECTOR fxmvup = XMLoadFloat3(&xmfup);

	XMVECTOR xmvup = XMVector3TransformCoord(fxmvup, xmMatrix);

	xmfup = XMFLOAT3(XMVectorGetX(xmvup), XMVectorGetY(xmvup), XMVectorGetZ(xmvup));


	XMFLOAT3 xmfposition = XMFLOAT3(position.X, position.Y, position.Z);
	XMVECTOR xmvposition = XMLoadFloat3(&xmfposition);

	xmflook.x = xmflook.x + xmfposition.x;
	xmflook.y = xmflook.y + xmfposition.y;
	xmflook.z = xmflook.z + xmfposition.z;

	xmvlook = XMLoadFloat3(&xmflook);


	XMMATRIX xmview = XMMatrixLookAtLH(xmvposition, xmvlook, xmvup);

	XMFLOAT4X4 xmfview;

	XMStoreFloat4x4(&xmfview, xmview);


	view = D3DXMATRIX((FLOAT*)& xmfview.m);



	right = CVertex(view._11, view._21, view._31);
	up = CVertex(view._12, view._22, view._32);
	look = CVertex(view._13, view._23, view._33);
}

VOID CCamera::Copy(CCamera* c)
{
	view = c->view;

	position = c->position;
	rotation = c->rotation;

	right = c->right;
	up = c->up;
	look = c->look;

	cup = c->cup;
	cposition = c->cposition;
	clookAt = c->clookAt;

	yaw = c->yaw;
	pitch = c->pitch;
	roll = c->roll;
}