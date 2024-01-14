#pragma once

#include "g3d/ResFileRepository.h"
#include "math/Matrix34.h"
#include "mem/Memory.h"
#include "common/FixedString.h"
#include "defines.h"

namespace g3d
{
	class CameraAccessor
	{
		void setViewMtx(const hel::math::Matrix34& mtx) const;
	};

	class RootContext
	{
		// get size of rootcontext
		SET_OBJECT_SIZE(20); // as seen in __ct__Q23g3d11RootContextFRQ23mem10IAllocatorUlUlUlUl
		
	public:
		RootContext(mem::IAllocator& heap, unsigned long unk0, unsigned long unk1, unsigned long num_lights, unsigned long unk3);
		/*
		* unk0 is normally 32
		* unk1 is normally 32
		* num_lights is normally 8
		* unk3 is normally 1
		*/
	};

	class Root
	{
		// get size of root
		SET_OBJECT_SIZE(0x50); // 520 - 400; seen in __ct__Q33scn5arena9RenderSetFRQ33scn5arena9Component
		
	public:
		Root(const RootContext& context);
		CameraAccessor& currentCamera() const;
		// note: 0x1c of root object is pointer to nw4r::g3d::scnroot object
		// scnroot contains a lightset object with various lights, that's your ticket in
	};
	
	class ResModelContext
	{
		SET_OBJECT_SIZE(48);
		
	public:
		ResModelContext(ResFileAccessor& mdl_file, const char* modelname);
	};

	class Model
	{
	public:
		void RegisterToRoot(const Root& root);
		void setModelRTMtx(const hel::math::Matrix34& mtx);
		void setModelScale(const hel::math::Vector3& scale);
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
		SET_OBJECT_SIZE(0x70);
		
	public:
		CharaModelContext(const ResModelContext& context, const ModelBufferOption& options, unsigned long unk, unsigned long unk1, unsigned long unk2, mem::IAllocator&, bool unk_b0, unsigned long unk3, const hel::common::FixedString<32>& string);
	}
	
	class CharaModel : public Model
	{
		SET_OBJECT_SIZE(356); //
		
	public:
		CharaModel(const CharaModelContext& context);
	};
}