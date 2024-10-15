/*
 * Copyright 2024 Andreas Åkerberg.
 */

#include "TextRenderer.hpp"
#include "Font.hpp"
#include "game/core/Engine.hpp"

namespace JoD {
TextRenderer::TextRenderer() {
    TTF_Init();
    auto fontPath = std::string(SDL_GetBasePath()) + k_relativeFontsPath +
                    "awelier.otf";
    auto font20 = std::make_shared<Font>(fontPath, 20);
    auto font40 = std::make_shared<Font>(fontPath, 40);
    m_fonts.insert({FontSizes::_20, font20});
    m_fonts.insert({FontSizes::_40, font40});
}

void TextRenderer::RenderText(int id,
                              std::string_view text,
                              ColorF color,
                              bool centerAlign,
                              FontSizes fontSize,
                              std::string &out_uniqueNameID,
                              SizeF &out_size) const {
    auto font = m_fonts.at(fontSize)->GetFont();
    if (!font)
        return;
    auto sdlColor= color.ToSDLColor();
    auto outlineSDLColor= k_outlineColor.ToSDLColor();
    auto textOutlineSurface=
        TTF_RenderText_Blended(
            m_fonts.at(fontSize)->GetOutlineFont().get(),
            text.data(), outlineSDLColor);
    if (!textOutlineSurface)
        return;
    auto textSurface= TTF_RenderText_Blended(
        font.get(), text.data(),
        sdlColor);
    glEnable(GL_TEXTURE_2D);
    auto uniqueNameID= m_uniqueNameIDs.at(id);
    auto imageID= _<Engine>().GetImage(uniqueNameID.c_str());
    glBindTexture(GL_TEXTURE_2D, imageID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    auto w = textOutlineSurface->w;
    auto h = textOutlineSurface->h;
    auto image = SDL_CreateRGBSurface(
        SDL_SWSURFACE, w, h, 32, 0x000000FF,
        0x0000FF00, 0x00FF0000, 0xFF000000);
    auto canvasSize= GetCanvasSize();
    SDL_Rect textSourceRectangle;
    SDL_Rect textOutlineSourceRectangle;
    SDL_Rect textDestinationRectangle;
    SDL_Rect textOutlineDestinationRectangle;
    textSourceRectangle= SDL_Rect{0, 0, textSurface? textSurface->w : 0,
                                  textSurface? textSurface->h : 0};
    textOutlineSourceRectangle=
        SDL_Rect{0, 0, textOutlineSurface? textOutlineSurface->w : 0,
                 textOutlineSurface? textOutlineSurface->h : 0};
    textDestinationRectangle= textSourceRectangle;
    textDestinationRectangle.x += Font::k_fontOutlineWidth;
    textDestinationRectangle.w -= 2 * Font::k_fontOutlineWidth;
    textDestinationRectangle.y += Font::k_fontOutlineWidth;
    textDestinationRectangle.h -= 2 * Font::k_fontOutlineWidth;
    textOutlineDestinationRectangle= textOutlineSourceRectangle;
    textOutlineDestinationRectangle.y = 1;
    SDL_BlitSurface(
        textOutlineSurface, &textOutlineSourceRectangle, image,
        &textOutlineDestinationRectangle);
    SDL_BlitSurface(
        textSurface, &textSourceRectangle, image,
        &textDestinationRectangle);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, image->pixels);
    auto width = textSurface? static_cast<float>(textSurface->w) /
                 canvasSize.width : 0;
    auto height = textSurface? static_cast<float>(textSurface->h) /
                  canvasSize.height : 0;
    out_uniqueNameID = uniqueNameID;
    out_size = {width, height};
    SDL_FreeSurface(image);
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(textOutlineSurface);
}

RID TextRenderer::AllocateNewString() {
    static int s_idCounter = 0;
    auto id = s_idCounter++;
    auto uniqueName= "rendered_image" + std::to_string(id);
    _<Engine>().CreateBlankImage(uniqueName);
    m_uniqueNameIDs.insert({id, uniqueName});
    auto rid = _<Engine>().AllocateNewImage();
    m_rids.insert({id, rid});
    return static_cast<RID>(id);
}

void TextRenderer::DrawString(int id, std::string_view text, Point2F position,
                              ColorF color, bool centerAlign,
                              FontSizes fontSize) const {
    std::string uniqueNameID;
    SizeF size;
    RenderText(id, text, color, centerAlign, fontSize, uniqueNameID, size);
    auto canvasSize= GetCanvasSize();
    auto rectangle = BoxF{position.x, position.y, size.width,
                          size.height};
    int textW;
    int textH;
    TTF_SizeText(
        m_fonts.at(fontSize)->GetFont().get(), text.data(), &textW,
        &textH);
    // rect.h *= AspectRatio(_<GraphicsView>()->Window());
    rectangle.y -= static_cast<float>(textH) / canvasSize.height / 2.0f;
    if (centerAlign)
        rectangle.x -= static_cast<float>(textW) /
                       static_cast<float>(canvasSize.height) / 2.0f /
                       GetAspectRatio();
    auto scale {1.0f};
    rectangle.x += rectangle.width / 2.0f - rectangle.width / 2.0f * scale;
    rectangle.y += rectangle.height / 2.0f - rectangle.height / 2.0f * scale;
    rectangle.width *= scale;
    rectangle.height *= scale;
    auto rid = m_rids.at(id);
    _<Engine>().DrawImage(
        rid, uniqueNameID, rectangle,
        Colors::White, true);
}

SizeF TextRenderer::MeasureString(std::string_view text,
                                  FontSizes font_size) const {
    auto font = m_fonts.at(font_size)->GetFont();
    int text_w;
    int text_h;
    TTF_SizeText(font.get(), text.data(), &text_w, &text_h);
    auto canvas_size = GetCanvasSize();
    return {static_cast<float>(text_w) / canvas_size.width,
            static_cast<float>(text_h) / canvas_size.height};
}
}
