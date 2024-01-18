#pragma once

#include "g3d/ResFileRepository.h"
#include "math/Matrix34.h"
#include "math/Vector3.h"

#include "mem/Memory.h"
#include "common/FixedString.h"
#include "defines.h"

namespace g3d
{
	struct CameraAccessor
	{
		unsigned long unk;
		
		void setViewMtx(const hel::math::Matrix34& mtx) const;
	};

	class RootContext
	{
		// get size of rootcontext
		SET_OBJECT_SIZE(0x14); // as seen in __ct__Q23g3d11RootContextFRQ23mem10IAllocatorUlUlUlUl
		
	public:
		RootContext(mem::IAllocator& heap, unsigned long unk0, unsigned long maxNumChildren, unsigned long maxScnObj, unsigned long numLightSet);
		/*
		* unk0 is normally 32
		* maxNumChildren is normally 32
		* maxScnObj is normally 8
		* numLightSet is normally 1
		*/
	};

	class Root
	{
		// get size of root
		SET_OBJECT_SIZE(0x50); // 520 - 400; seen in __ct__Q33scn5arena9RenderSetFRQ33scn5arena9Component
		
	public:
		Root(const RootContext& context);
		CameraAccessor currentCamera() const;
		void sceneClear(); // i believe you either clear and refill the root object or you call a Root::sceneCalc* function
		void sceneDrawOpa() const;
		void sceneCalcOnDraw() const;
		// note: 0x1c of root object is pointer to nw4r::g3d::scnroot object
		// scnroot contains a lightset object with various lights, that's your ticket in
	};
	
	class ResModelContext
	{
		SET_OBJECT_SIZE(52);
		
	public:
		ResModelContext(const ResFileAccessor& mdl_file, const char* modelname);
	};
	
	struct ModelBufferOption
	{
		SET_OBJECT_SIZE(0x10);
		
	public:
		void addAnimMatColor();
		void addAnimTexPattern();
		void addAnimTexSRT();
		void addAnimVisible();
	};
	
	class ModelContext
	{
	public:
		static ModelBufferOption DefaultModelBufferOption();
		static mem::IAllocator* DefaultAllocator();
	};
	
	class CharaModelContext : public ModelContext
	{
		SET_OBJECT_SIZE(0x74);
		
	public:
		CharaModelContext(const ResModelContext& context, const ModelBufferOption& options, unsigned long maxNumChildren, unsigned long numView, unsigned long animSlotNum, mem::IAllocator& allocator, bool isCreateNodeLocalMtx, unsigned long animSlotWorkMemSize, const hel::common::FixedString<32>& heapNamePrefix);
		/*
		* maxNumChildren is usually 4
		* numView is usually 2
		* animSlotNum is usually 2
		* isCreateNodeLocalMtx is usually true from what i can tell
		* animSlotWorkMemSize is usually 0x2000
		* heapNamePrefix is usually "MdlAnm"
		*/
	};
	
	class CharaModel
	{
		SET_OBJECT_SIZE(356); //
		
	public:
		CharaModel(const CharaModelContext& context);
		
		void setModelRTMtx(const hel::math::Matrix34& mtx);
		void setModelScale(const hel::math::Vector3& scale);
		void registerToRoot(Root& root);
		void updateWorldMtx();
	};
}