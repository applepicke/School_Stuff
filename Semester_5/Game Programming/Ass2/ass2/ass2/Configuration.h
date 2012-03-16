#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>

#define ROTATE_MODEL 0
#define ROTATE_LIGHT 1

class Configuration 
{
public:
	float x;
	float y;

	float xAngle;	
	float yAngle;
	float lightAngle;

	int rotateType;

	D3DLIGHTTYPE lightType;
	COLORREF lightColour;
	D3DSHADEMODE shadeMode;
	D3DFILLMODE fillMode;

	Configuration(){
		x = 0.0f;
		xAngle = 0.0f;
		y = 0.0f;
		yAngle = 0.0f;

		lightAngle = 0.0f;

		rotateType = ROTATE_MODEL;
		lightType = D3DLIGHT_DIRECTIONAL;
		lightColour = 0xFFFFFFFF;
		shadeMode = D3DSHADE_GOURAUD;
		fillMode = D3DFILL_SOLID;
	}
};