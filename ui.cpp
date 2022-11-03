#include "ui.h"


namespace ui {

void draw_text(const draw_text_s& arg) {

    D2D1_SIZE_F renderTargetSize = arg.pRenderTarget->GetSize();
    D2D1::Matrix3x2F transform;

    //--------------------  After a scale of .5, we need to offset by .25 of window size to come back to middle. (x/2)
    transform = D2D1::Matrix3x2F::Scale(0.5f, 0.5f)
        * D2D1::Matrix3x2F::Translation((renderTargetSize.width / 4), (renderTargetSize.height / 4));

    arg.pRenderTarget->SetTransform(transform);
    arg.pRenderTarget->DrawText(
        arg.text,
        arg.text_size - 1,
        arg.pTextFormat,
        D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
        arg.pBrush
    );
}

}