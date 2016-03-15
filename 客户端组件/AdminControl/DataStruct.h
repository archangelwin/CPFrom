#ifndef SHEN
#define SHEN
template<class Type>
struct SColor
{
	Type r;
	Type g;
	Type b;
	SColor()
	{
		r=0;g=0;b=0;	
	}
	SColor(BYTE cr,BYTE cg,BYTE cb)
	{
		r=cr;
		g=cg;
		b=cb;	
	}
	//保存颜色信息
	void Set(COLORREF color)
	{
		r=GetRValue(color);
		g=GetGValue(color);
		b=GetBValue(color);
	}
};
#endif;