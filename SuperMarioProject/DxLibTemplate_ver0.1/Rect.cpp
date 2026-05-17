#include "Rect.h"

Rect::Rect()
{
	begin.Clear();
	size.Clear();
}

Rect::Rect(Float2 _leftTop, Float2 _size)
{
	begin = _leftTop;
	size = _size;

}
