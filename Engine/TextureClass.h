////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.h
////////////////////////////////////////////////////////////////////////////////
#pragma once


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <stdio.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: TextureClass
////////////////////////////////////////////////////////////////////////////////
class TextureClass
{
private:
    struct TargaHeader
    {
        unsigned char data1[12];
        unsigned short width;
        unsigned short height;
        unsigned char bpp;
        unsigned char data2;
    };

public:
    TextureClass();
    TextureClass(const TextureClass&);
    ~TextureClass();

    bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const char*);
    void Shutdown();

    ID3D11ShaderResourceView* GetTexture();

    int GetWidth();
    int GetHeight();

private:
    bool LoadTarga32Bit(const char*);
    void CovertTo32Bit(unsigned char* input, unsigned char*& output, int width, int height);


private:
    unsigned char* m_targaData;
    ID3D11Texture2D* m_texture;
    ID3D11ShaderResourceView* m_textureView;
    int m_width, m_height;
};

