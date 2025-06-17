#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"


SpriteComponent::SpriteComponent(Actor* owner, int order) 
	: Component(owner)
	, m_DrawOrder(order)
{
}

SpriteComponent::~SpriteComponent() {

}

void SpriteComponent::SetTexture(const std::string& name) {
	m_Texture = m_Owner->GetGame()->GetTexture(name);
}

void SpriteComponent::Draw(class ApplicationClass* mApp) {
    if (!m_Texture) return;
    // Ottieni matrici:
	Matrix4 ownerTransform = m_Owner->GetWorldTransform();

    XMMATRIX view, proj;
    XMMATRIX world = XMMATRIX(ownerTransform.mat[0][0], ownerTransform.mat[0][1], ownerTransform.mat[0][2], ownerTransform.mat[0][3],
                              ownerTransform.mat[1][0], ownerTransform.mat[1][1], ownerTransform.mat[1][2], ownerTransform.mat[1][3],
                              ownerTransform.mat[2][0], ownerTransform.mat[2][1], ownerTransform.mat[2][2], ownerTransform.mat[2][3],
                              ownerTransform.mat[3][0], ownerTransform.mat[3][1], ownerTransform.mat[3][2], ownerTransform.mat[3][3]);
    mApp->GetCamera()->GetViewMatrix(view);
    mApp->GetD3D()->GetProjectionMatrix(proj);
    // Render quad con la texture di questo sprite:
    mApp->GetD3D()->GetDeviceContext();
    // Metti i vertex/index buffer:
    mApp->GetModel()->Render(mApp->GetD3D()->GetDeviceContext());
    // Imposta shader parameters e disegna:
    mApp->GetTextureShader()->Render(
        mApp->GetD3D()->GetDeviceContext(),
        mApp->GetModel()->GetIndexCount(),
        world, view, proj,
        m_Texture->GetTexture()
    );
}
