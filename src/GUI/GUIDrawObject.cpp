﻿// MIT License
// Copyright (C) August 2016 Hotride

#include "GUIDrawObject.h"
#include "../CrossUO.h"
#include "../Point.h"
#include "../Managers/ColorManager.h"

CGUIDrawObject::CGUIDrawObject(
    GUMP_OBJECT_TYPE type, int serial, uint16_t graphic, uint16_t color, int x, int y)
    : CBaseGUI(type, serial, graphic, color, x, y)
{
}

CGUIDrawObject::~CGUIDrawObject()
{
}

CSize CGUIDrawObject::GetSize()
{
    DEBUG_TRACE_FUNCTION;
    CSize size;
    auto spr = g_Game.ExecuteGump(GetDrawGraphic());
    if (spr != nullptr)
    {
        size.Width = spr->Width;
        size.Height = spr->Height;
    }
    return size;
}

void CGUIDrawObject::SetShaderMode()
{
    DEBUG_TRACE_FUNCTION;
    if (Color != 0)
    {
        if (PartialHue)
        {
            glUniform1iARB(g_ShaderDrawMode, SDM_PARTIAL_HUE);
        }
        else
        {
            glUniform1iARB(g_ShaderDrawMode, SDM_COLORED);
        }
        g_ColorManager.SendColorsToShader(Color);
    }
    else
    {
        glUniform1iARB(g_ShaderDrawMode, SDM_NO_COLOR);
    }
}

void CGUIDrawObject::PrepareTextures()
{
    DEBUG_TRACE_FUNCTION;
    g_Game.ExecuteGump(Graphic);
}

void CGUIDrawObject::Draw(bool checktrans)
{
    DEBUG_TRACE_FUNCTION;
    auto spr = g_Game.ExecuteGump(GetDrawGraphic());
    if (spr != nullptr && spr->Texture)
    {
        SetShaderMode();
        spr->Texture->Draw(m_X, m_Y, checktrans);
    }
}

bool CGUIDrawObject::Select()
{
    DEBUG_TRACE_FUNCTION;
    auto spr = g_Game.ExecuteGump(Graphic);
    if (spr != nullptr)
    {
        return spr->Select(m_X, m_Y, !BoundingBoxCheck);
    }
    return false;
}
