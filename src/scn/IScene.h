namespace scn
{
	class DrawReqInfo
	{
	};

	class IScene
	{
		public:
		~IScene();
		virtual void updateMain();
		virtual void updateUseGPU();
		virtual void updateDebug();
		virtual void draw(const scn::DrawReqInfo& info);
		virtual void isSceneEnd() const;
	};
}