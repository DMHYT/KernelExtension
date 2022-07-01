package vsdum.kex.util;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffColorFilter;
import vsdum.kex.util.textureworker.*;

public class TextureWorker {
    
    public static Bitmap changeBitmapColor(Bitmap source, int r, int g, int b)
    {
        Bitmap result = Bitmap.createBitmap(source.getWidth(), source.getHeight(), source.getConfig());
        Canvas canvas = new Canvas(result);
        Paint paint = new Paint();
        paint.setColorFilter(new PorterDuffColorFilter(Color.rgb(r, g, b), PorterDuff.Mode.MULTIPLY));
        canvas.drawBitmap(source, 0, 0, paint);
        return result;
    }

    public static OverlaidTextureBuilder createTextureWithOverlays()
    {
        return new OverlaidTextureBuilder();
    }

    public static PaintedTextureBuilder createPaintedTexture()
    {
        return new PaintedTextureBuilder();
    }

    public static GrayscaledTextureBuilder createGrayscaledTexture()
    {
        return new GrayscaledTextureBuilder();
    }

}
