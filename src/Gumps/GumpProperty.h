// MIT License
// Copyright (C) November 2017 Hotride

#pragma once

class CRenderObject;

#include "Gump.h"
#include "../Sprite.h"

class CGumpProperty : public CGump
{
    uint32_t Timer = 0;
    CGLTextTexture m_Texture_DONT;
    CSprite m_Sprite;

public:
    virtual void PrepareContent() override;
    virtual CRenderObject *Select() override { return nullptr; }

    CGumpProperty(const wstring &text);
    virtual ~CGumpProperty() = default;
};
