﻿
#ifndef __EFFEKSEER_INSTANCEGROUP_H__
#define __EFFEKSEER_INSTANCEGROUP_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "Effekseer.Base.h"
#include "Effekseer.EffectNodeTrack.h"
#include "Effekseer.IntrusiveList.h"
#include "SIMD/Effekseer.Mat43f.h"
#include "SIMD/Effekseer.Vec3f.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

/**
	@brief	インスタンスグループ
	@note
	インスタンスコンテナ内でさらにインスタンスをグループ化するクラス
*/
class InstanceGroup
{
	friend class InstanceContainer;
	friend class ManagerImplemented;

private:
	ManagerImplemented* m_manager;
	EffectNodeImplemented* m_effectNode;
	InstanceContainer* m_container;
	InstanceGlobal* m_global;
	int32_t m_time;

	Mat43f parentMatrix_;
	Mat43f parentRotation_;
	Vec3f parentTranslation_;
	Vec3f parentScale_;

	// インスタンスの実体
	IntrusiveList<Instance> m_instances;
	IntrusiveList<Instance> m_removingInstances;

	InstanceGroup(Manager* manager, EffectNode* effectNode, InstanceContainer* container, InstanceGlobal* global);

	~InstanceGroup();

public:
	/**
		@brief	描画に必要なパラメータ
	*/
	union {
		EffectNodeTrack::InstanceGroupValues track;
	} rendererValues;

	/**
		@brief	インスタンスの生成
	*/
	Instance* CreateInstance();

	Instance* GetFirst();

	int GetInstanceCount() const;

	void Update(bool shown);

	void SetBaseMatrix(const Mat43f& mat);

	void SetParentMatrix(const Mat43f& mat);

	void RemoveForcibly();

	void KillAllInstances();

	int32_t GetTime() const
	{
		return m_time;
	}

	/**
		@brief	グループを生成したインスタンスからの参照が残っているか?
	*/
	bool IsReferencedFromInstance;

	/**
		@brief	インスタンスから利用する連結リストの次のオブジェクトへのポインタ
	*/
	InstanceGroup* NextUsedByInstance;

	/**
		@brief	コンテナから利用する連結リストの次のオブジェクトへのポインタ
	*/
	InstanceGroup* NextUsedByContainer;

	InstanceGlobal* GetRootInstance() const
	{
		return m_global;
	}

	const Mat43f& GetParentMatrix() const
	{
		return parentMatrix_;
	}
	const Vec3f& GetParentTranslation() const
	{
		return parentTranslation_;
	}
	const Mat43f& GetParentRotation() const
	{
		return parentRotation_;
	}
	const Vec3f& GetParentScale() const
	{
		return parentScale_;
	}
};
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
} // namespace Effekseer
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif // __EFFEKSEER_INSTANCEGROUP_H__
