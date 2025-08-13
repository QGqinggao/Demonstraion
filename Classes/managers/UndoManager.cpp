#include "UndoManager.h"

void UndoManager::pushStep(const UndoStep& step)
{
	if (!_undoModel) return;
	_undoModel->steps.push_back(step);
}

bool UndoManager::canUndo() const
{
	return _undoModel && !_undoModel->steps.empty();
}

void UndoManager::undoLastStep()
{
	if (!UndoManager::canUndo()) return;
	UndoStep step = _undoModel->steps.back();
	_undoModel->steps.pop_back();

	if (_undoCallback) _undoCallback(step);
}

void UndoManager::clear()
{
	if (_undoModel) _undoModel->steps.clear();
}