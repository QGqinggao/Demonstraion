#ifndef __UNDO_MANAGER_H__
#define __UNDO_MANAGER_H__

#include "models/UndoModel.h"

/// <summary>
/// 撤销管理器
/// </summary>
class UndoManager
{

public:
	/// <summary>
	/// 将撤销步骤压入栈中
	/// </summary>
	/// <param name="step"></param>
	void pushStep(const UndoStep& step);
	/// <summary>
	/// 撤销上一次操作
	/// </summary>
	void undoLastStep();
	/// <summary>
	/// 是否可以撤销
	/// </summary>
	/// <returns></returns>
	bool canUndo() const;
	/// <summary>
	/// 清空撤销数据栈
	/// </summary>
	void clear();
	/// <summary>
	/// 外部撤销事件绑定接口
	/// </summary>
	/// <param name="callback"></param>
	void setUndoCallback(std::function<void(const UndoStep&)> callback) { _undoCallback = callback; }

private:
	std::shared_ptr<UndoModel> _undoModel = std::make_shared<UndoModel>();
	std::function<void(const UndoStep&)> _undoCallback;
};

#endif