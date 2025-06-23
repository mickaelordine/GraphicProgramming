#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"



SpriteComponent::SpriteComponent(class Actor* owner, EnumDictionary::BufferType type, int order)
	: Component(owner)
	, m_DrawOrder(order)
	, m_Type(type)
{
    m_Owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() 
{
    m_Owner->GetGame()->RemoveSprite(this);
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

    switch (m_Type) 
    {
        case EnumDictionary::BufferType::Square:
            // Metti i vertex/index buffer:
            mApp->GetModelSquare()->Render(mApp->GetD3D()->GetDeviceContext());
            // Imposta shader parameters e disegna:
            mApp->GetTextureShader()->Render(
                mApp->GetD3D()->GetDeviceContext(),
                mApp->GetModelSquare()->GetIndexCount(),
                world, view, proj,
                m_Texture->GetTexture()
            );
            break;

		case EnumDictionary::BufferType::Rectangle:
            // Metti i vertex/index buffer:
            mApp->GetModelRect()->Render(mApp->GetD3D()->GetDeviceContext());
            // Imposta shader parameters e disegna:
            mApp->GetTextureShader()->Render(
                mApp->GetD3D()->GetDeviceContext(),
                mApp->GetModelRect()->GetIndexCount(),
                world, view, proj,
                m_Texture->GetTexture()
            );
            break;

        default:
			// Not supported type, return early
			return;
    }
    
}
