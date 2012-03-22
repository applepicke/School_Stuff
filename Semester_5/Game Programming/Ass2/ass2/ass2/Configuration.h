/**********************************************************************
Filename:		Configuration.h
Version: 		1.0                                         
Author:			William Collins                                             
Student No:  	040652633                                           
Course Name/Number: Game Programming CST8237                                 
Lab Sect: 		310                                                      
Assignment #:	2
Assignment name:Assignment 2	
Due Date:		March 23, 2012                                           
Submission Date:March 23, 2012
Professor:		Andrew Tyler                                           
Purpose: 		The configuration structure that determines certain settings
				in the x-viewer.
*********************************************************************/
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>

#define ROTATE_MODEL 0
#define ROTATE_LIGHT 1

class Configuration 
{
public:
	float x; //The x value of the mouse position on drag
	float y; //The y value of the mouse position on drag

	float xAngle; //The calculated angle to rotate on x axis
	float yAngle; //The calculated angle to rotate on y axis
	float lightAngle; //The calculated angle to rotate the light

	int rotateType; //What is being rotated
	float z;

	D3DLIGHTTYPE lightType; //Type of light for the scene
	COLORREF lightColour; //Colour of light being rendered in the scene
	D3DSHADEMODE shadeMode; //The shade mode of the object in the scene
	D3DFILLMODE fillMode; //The fill mode of the object in the scene

	Configuration(){
		x = 0.0f;
		xAngle = 0.0f;
		y = 0.0f;
		yAngle = 0.0f;

		lightAngle = 0.0f;
		z = -30.0f;
		rotateType = ROTATE_MODEL;
		lightType = D3DLIGHT_DIRECTIONAL;
		lightColour = 0xFFFFFFFF;
		shadeMode = D3DSHADE_GOURAUD;
		fillMode = D3DFILL_SOLID;
	}
};