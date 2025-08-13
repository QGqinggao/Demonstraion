#ifndef __PLAY_FIELD_VIEW_H__
#define __PLAY_FIELD_VIEW_H__

#include "cocos2d.h"

/// <summary>
/// PlayField 视图，由 PlayFieldController 持有
/// </summary>
class PlayFieldView : public cocos2d::Node
{
public:

	CREATE_FUNC(PlayFieldView);

	/// <summary>
	/// 对 PlayFieldView 进行初始化
	/// </summary>
	/// <returns>是否初始化成功</returns>
	virtual bool init() override;

private:

	/// <summary>
	/// 简单背景画面
	/// </summary>
	cocos2d::DrawNode* _backgroundCardTable;
};



#endif