namespace g3d
{
	class CameraAccessor
	{
		void setViewMtx(const hel::math::Matrix34& mtx) const;
	};

	class RootContext
	{
		RootContext(mem::IAllocator& heap, unsigned long unk0, unsigned long unk1, unsigned long unk2, unsigned long unk3);
	};

	class Root
	{
		Root(const RootContext& context);

		CameraAccessor& currentCamera() const;
	};

	class Model
	{
		Model(); // wip definition

		void RegisterToRoot(const Root& root);
		void setModelRTMtx(const hel::math::Matrix34& mtx);
		void setModelScale(const hel::math::Vector3& scale);
	};
}