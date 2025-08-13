#ifndef __STACK_VIEW_H__
#define __STACK_VIEW_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

/// <summary>
/// Stack 视图， 由 StackController 持有
/// </summary>
class StackView : public cocos2d::Node
{
public:
	CREATE_FUNC(StackView);

	/// <summary>
	/// 对 StackView 进行初始化
	/// </summary>
	/// <returns></returns>
	virtual bool init() override;

	using ButtonClickCallback = std::function<void()>;
	/// <summary>
	/// 外部按键点击事件绑定接口
	/// </summary>
	/// <param name="buttonClickCallback">无参无返回</param>
	void setButtonClickCallback(const ButtonClickCallback buttonClickCallback) { _buttonClickCallback = buttonClickCallback; }

private:
	/// <summary>
	/// 简单背景画面
	/// </summary>
	cocos2d::DrawNode* _backgroundCardTable;
	/// <summary>
	/// 回退按键
	/// </summary>
	cocos2d::ui::Button* _undoButton;

	void _onUndoButtonClick(cocos2d::Ref* sender);
	std::function<void()> _buttonClickCallback;
};


#endif