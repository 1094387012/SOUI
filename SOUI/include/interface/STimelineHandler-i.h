#pragma once

namespace SOUI
{

    /**
    * @struct     ITimelineHandler
    * @brief      ʱ���ᴦ��ӿ�
    * 
    * Describe    
    */
    struct ITimelineHandler
    {
        virtual void OnNextFrame()=0;
    };

}