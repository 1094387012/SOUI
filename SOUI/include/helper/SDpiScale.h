#pragma once
namespace SOUI
{
	class SDpiScale
	{
	public:
		static int GetBuiltinScaleCount();

		static const int * GetBuiltinScales();

		/*��׼���Ŵ����, ѡ����Լ�ָ������Сһ�ŵı���*/
		static int NormalizeScale(int nScale);
	};


}
