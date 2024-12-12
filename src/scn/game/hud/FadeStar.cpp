#include "scn/game/hud/FadeStar.h"
#include "math/Math.h"
#include "common/Color.h"
#include "gfx/FullScreenDrawer.h"

#define FADE_TIME 120

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		const float fadeMax = (float)FADE_TIME;
		const float fadeMultiplier = 10.0f;
		
		FadeStar::FadeStar()
		{
			timer = 0;
			enable = true;
		}
		
		namespace 
		{
			const GlobalObject<Vector2, float> fadeStarMesh[8][3] = {
				{ // triangle 1
					{{ 0.0f, 0.5f}},
					{{ 0.17032f, 0.19179f }},
					{{ -0.17032f, 0.19179f }}
				},
				
				{ // triangle 2
					{{ -0.17032f, 0.19179f }},
					{{ 0.17032f, 0.19179f }},
					{{ 0.28054f, -0.1651f }}
				},
				
				{ // triangle 3
					{{ -0.17032f, 0.19179f }},
					{{ 0.28054f, -0.1651f }},
					{{ -0.28054f, -0.1651f }}
				},
				
				{ // triangle 4
					{{ -0.28054f, -0.1651f }},
					{{ 0.28054f, -0.1651f }},
					{{ 0.0f, -0.37862f }}
				},
				
				{ // triangle 5
					{{ 0.17032f, 0.19179f }},
					{{ 0.5f, 0.1f}},
					{{ 0.28054f, -0.1651f }}
				},
				
				{ // triangle 6
					{{ 0.28054f, -0.1651f }},
					{{ 0.28495f, -0.5f }},
					{{ 0.0f, -0.37862f }}
				},
				
				{ // triangle 7
					{{ -0.28054f, -0.1651f }},
					{{ 0.0f, -0.37862f }},
					{{ -0.28495f, -0.5f }}
				},
				
				{ // triangle 8
					{{ -0.17032f, 0.19179f }},
					{{ -0.28054f, -0.1651f }},
					{{ -0.5f, 0.1f}}
				}
			};	
			
			const GlobalObject<const Vector3, float> rectangle[4] = {
				{{-1.0, 1.0, 0.0}},
				{{-1.0, -1.0, 0.0}},
				{{1.0, -1.0, 0.0}},
				{{1.0, 1.0, 0.0}}
			};
		
			const GlobalObject<const Vector3, float> cameraOffset = { {0.0f, 0.0f, -50.0f} };
		
			void setupDrawMode()
			{
				hel::math::Matrix44 perspectiveMatrix = hel::math::Matrix44::CreateOrtho(1.0, -1.0, -1.0, 1.0, 0.0, 1.0);//hel::math::Matrix44::CreatePerspective(fov, aspectRatio, near, far);
				hel::math::Matrix34 viewMatrix;
				
				gfx::EasyRender3D::SetupGX(perspectiveMatrix, false);
				gfx::EasyRender3D::SetViewMtx(viewMatrix);
				
				GXSetZMode(0, 1, 0);
				GXSetBlendMode(GX_BM_NONE, GX_BL_SRCCLR, GX_BL_DSTCLR, GX_LO_NOOP);
				GXSetCullMode(0);
				return;
			}
			
			void drawFadeMesh(int timer)
			{
				float multiplier = (timer / fadeMax) * fadeMultiplier;
				Matrix34 lookAt;
				
				gfx::EasyRender3D::SetColor(hel::common::Color::BLACK);
				gfx::EasyRender3D::DrawQuadFill(lookAt, rectangle[0], rectangle[1], rectangle[2], rectangle[3]);
				gfx::EasyRender3D::SetColor(hel::common::Color::WHITE);
				for (int i = 0; i < 8; i++)
				{
					const Vector2 *vv0, *vv1, *vv2;
					vv0 = (const Vector2*)&fadeStarMesh[i][0], vv1 = (const Vector2*)&fadeStarMesh[i][1], vv2 = (const Vector2*)&fadeStarMesh[i][2];
					Vector3 v0(vv0->x, vv0->y, 0.0f);
					Vector3 v1(vv1->x, vv1->y, 0.0f);
					Vector3 v2(vv2->x, vv2->y, 0.0f);
					
					gfx::EasyRender3D::DrawQuadFill(lookAt, v0 * multiplier, v1 * multiplier, v2 * multiplier, v2 * multiplier);
				}
				return;
			}
		}
		
		void FadeStar::activate()
		{
			enable = true;
			timer = 0;
			return;
		}
		
		void FadeStar::updateAndDraw(g3d::Root& root)
		{
			if (timer == FADE_TIME) enable = false;
			if (enable)
			{
				gfx::FullScreenDrawer::Capture();
				setupDrawMode();
				gfx::EasyRender3D::SetColor(hel::common::Color::WHITE);
				drawFadeMesh(timer);
				
				GXSetBlendMode(GX_BM_LOGIC, GX_BL_SRCCLR, GX_BL_ONE, GX_LO_AND);
				gfx::FullScreenDrawer::Draw();
				timer++;
			}
		}
	}
}