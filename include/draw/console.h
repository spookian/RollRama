struct 16_GXRenderModeObj
{
	unsigned long viTVMode;

	unsigned short fbWidth;
	unsigned short efbHeight;
	unsigned short xfbHeight;

	unsigned short viXOrigin;
	unsigned short viYOrigin;

	unsigned short viWidth;
	unsigned short viHeight;
	unsigned long xfbMode;

	unsigned char field_rendering;
	unsigned char aa;
	unsigned char sample_pattern[12][2];
	unsigned char vfilter[7];
}
// taken straight from the doldecomp github. you guys rock!

namespace nw4r::db
{
	namespace detail
	{
		class ConsoleHead
		{

		};
	}

	void DirectPrint_SetupFB(const 16_GXRenderModeObj* rmode);
	void Console_DrawDirect(const detail::ConsoleHead* console);
}