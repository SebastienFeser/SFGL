#include "..\include\p2collider.h"

bool p2Collider::IsSensor()
{
	return false;
}

void * p2Collider::GetUserData()
{
	return nullptr;
}

void p2Collider::SetUserData(void* colliderData)
{
	userData = colliderData;
}
