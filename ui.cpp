#include "ui.h"

#include <assert.h>


namespace ui {

//---------------------------------------------------------------------------------
void draw_text(const draw_text_s& arg) {
    D2D1_SIZE_F renderTargetSize = arg.pRenderTarget->GetSize();
    D2D1::Matrix3x2F transform;

    transform = D2D1::Matrix3x2F::Scale(arg.scale, arg.scale)
        * D2D1::Matrix3x2F::Translation((renderTargetSize.width/2.0f) * (1.0f - arg.scale), (renderTargetSize.height / 2.0f) * (1.0f - arg.scale))
        * D2D1::Matrix3x2F::Translation((renderTargetSize.width * arg.x), (-renderTargetSize.height * arg.y));

    arg.pRenderTarget->SetTransform(transform);
    arg.pRenderTarget->DrawText(
        arg.text,
        arg.text_size - 1,
        arg.pTextFormat,
        D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
        arg.pBrush
    );
}

//---------------------------------------------------------------------------------
void draw_rectangle(const draw_rectangle_s& arg) {
    //TODO mdtmp Add scale + position
    D2D1_SIZE_F renderTargetSize = arg.pRenderTarget->GetSize();
    D2D1::Matrix3x2F transform;

    transform = D2D1::Matrix3x2F::Scale(0.5f, 0.5f)
        * D2D1::Matrix3x2F::Translation((renderTargetSize.width / 4), (renderTargetSize.height / 4))
        * D2D1::Matrix3x2F::Translation(0, (2 * renderTargetSize.height / 8));
    arg.pRenderTarget->SetTransform(transform);
    arg.pRenderTarget->DrawRectangle(
        D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
        arg.pBrush,
        4.0f // stroke width
    );
}

}