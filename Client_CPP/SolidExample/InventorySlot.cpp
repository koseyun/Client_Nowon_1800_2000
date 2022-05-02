#include "InventorySlot.h"

void InventorySlot::OnPointerDown()
{
	Pick();
}

void InventorySlot::OnPointerUp()
{
	Drop();
}

void InventorySlot::OnPointerDrag()
{
	Dragging();
}
