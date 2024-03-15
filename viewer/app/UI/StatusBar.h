#pragma once

#include <Mesh/Operations/MeshWeightsParams.h>
#include <UI/UIPanel.h>
#include <Mesh/Selection.h>
#include <Tools/Tool.h>

#include <imgui.h>
#include <Mesh/Operations/MeshOperation.h>

class MeshOperationSystem;
class PolygonMesh;

struct StatusBarModel
{
	StatusBarModel() = default;
	StatusBarModel(const std::shared_ptr<ProjectData>& projectData,
		std::function<void (SelectionType)> selectionTypeChangedDelegate,
		std::function<void (uint32_t)> frameIndexChangedDelegate)
		: _projectData(projectData)
		, _selectionTypeChangedDelegate(std::move(selectionTypeChangedDelegate))
		, _frameIndexChangedDelegate(std::move(frameIndexChangedDelegate))
	{ }

	std::weak_ptr<ProjectData> _projectData;
	std::optional<MeshOperationError> _error;

	uint32_t _frameIndex = 0;
	bool _isDraggingSequencerHandle = false;

	std::function<void (SelectionType)> _selectionTypeChangedDelegate;
	std::function<void (uint32_t)> _frameIndexChangedDelegate;
	SelectionType _activeSelectionType = SelectionType::Vertex;
};

class StatusBar final : public UIPanel<std::shared_ptr<StatusBarModel>>
{
public:
	explicit StatusBar(const std::shared_ptr<MeshOperationSystem>& meshOperationSystem);

	void SetModel(const std::shared_ptr<StatusBarModel>& model) override;

	void Layout() override;

	[[nodiscard]] SelectionType GetActiveSelectionType() const
	{
		return _model->_activeSelectionType;
	}

	void SetError(std::optional<MeshOperationError> error)
	{
		_model->_error = std::move(error);
	}

private:
	void LayoutSelectionTool(const SelectionType selectionType,
		const char* label,
		const char* toolTip,
		const ImVec2& size) const;

private:
	std::weak_ptr<MeshOperationSystem> _meshOperationSystem;
};
