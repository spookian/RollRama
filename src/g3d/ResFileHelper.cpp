#include "g3d/ResFileRepository.h"
#include "g3d/Model.h"
#include "mem/Memory.h"

g3d::CharaModel* InitResModel(g3d::ResFileRepository& fileRepo, const char *res_path)
{
	g3d::ResFileAccessor mdlFile(fileRepo.get(res_path, false)); // for some reason it's not the full path
	g3d::ResModelContext mdlResCtx(mdlFile, "TopL");
	
	g3d::ModelBufferOption mdlOptions = g3d::ModelContext::DefaultModelBufferOption();
	
	mem::IAllocator* defAllocator = g3d::ModelContext::DefaultAllocator();
	hel::common::FixedString<32> string("MdlAnm");
	
	g3d::CharaModelContext mdlContext(mdlResCtx, mdlOptions, 4, 2, 2, *defAllocator, true, 0x200, string);
	// it's my estimate that it now requires around 80-90 deaths to fully crash the game if i never figure out how to clear the heap
	
	g3d::CharaModel *c = new g3d::CharaModel(mdlContext);
	return c;
}