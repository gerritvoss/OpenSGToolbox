#include "OSGGraphics2D.h"


OSG_BEGIN_NAMESPACE

void Graphics2D::preDraw()
{
	_light = glIsEnabled(GL_LIGHTING);

	glGetIntegerv(GL_POLYGON_MODE, _fill);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	_depth = glIsEnabled(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);

	_colmat = glIsEnabled(GL_COLOR_MATERIAL);
	glDisable(GL_COLOR_MATERIAL);

	glDisable(GL_TEXTURE_2D);
}

void Graphics2D::postDraw()
{
	if(_depth == GL_TRUE)
	{
		glEnable(GL_DEPTH_TEST);
	}
	if(_light == GL_TRUE)
	{
		glEnable(GL_LIGHTING);
	}
	if(_colmat == GL_TRUE)
	{
		glEnable(GL_COLOR_MATERIAL);
	}
	glPolygonMode(GL_FRONT, _fill[0]);
	glPolygonMode(GL_BACK , _fill[1]);
}

void Graphics2D::drawRect(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color4f& Color) const
{
	if(Color.alpha() < 1.0)
	{
		//Setup the Blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	glBegin(GL_QUADS);
	   glColor4fv(Color.getValuesRGBA());
	   glVertex2sv(TopLeft.getValues());
	   glVertex2s(BottomRight.x(), TopLeft.y());
	   glVertex2sv(BottomRight.getValues());
	   glVertex2s(TopLeft.x(), BottomRight.y());
	glEnd();
	
	if(Color.alpha() < 1.0)
	{
		glDisable(GL_BLEND);
	}
}

OSG_END_NAMESPACE
