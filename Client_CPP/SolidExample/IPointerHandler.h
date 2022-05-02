#pragma once

class IPointerHandler
{
public:
	virtual void OnPointerDown();
	virtual void OnPointerUp();
	virtual void OnPointerClick();
	virtual void OnPointerDrag();
};

