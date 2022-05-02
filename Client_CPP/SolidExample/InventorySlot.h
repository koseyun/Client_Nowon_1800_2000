#pragma once

#include "IPointerHandler.h"
#include "IPointerHandlerDown.h"
#include "IPointerHandlerUp.h"
#include "IPointerHandlerDragg.h"

class InventorySlot :
	public IPointerHandler
{
private:
	void Pick();
	void Dragging();
	void Drop();

	// mouse events
	void OnPointerDown();
	void OnPointerUp();
	void OnPointerClick();
	void OnPointerDrag();

};