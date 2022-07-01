package vsdum.kex.util.textureworker;

import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.utils.FileTools;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.Paint;
import android.support.annotation.Nullable;

public class GrayscaledTextureBuilder {
    
    @Nullable private Bitmap _source = null;
    @Nullable private String _result = null;

    public GrayscaledTextureBuilder source(String path, String name)
    {
        this._source = FileTools.readFileAsBitmap(path + name + ".png");
        return this;
    }

    public GrayscaledTextureBuilder source(Bitmap src)
    {
        this._source = src;
        return this;
    }

    public GrayscaledTextureBuilder result(String path, String name)
    {
        this._result = path + name + ".png";
        return this;
    }

    @Nullable public Bitmap create()
    {
        if(FileTools.exists(this._result))
        {
            Logger.debug("KEX-TextureWorker", String.format("File on path %s already exists, texture generation process cancelled", new Object[]{ this._result }));
            return null;
        }
        if(this._source == null) return null;
        Bitmap result = Bitmap.createBitmap(this._source.getWidth(), this._source.getHeight(), this._source.getConfig());
        Canvas canvas = new Canvas(result);
        Paint paint = new Paint();
        ColorMatrix matrix = new ColorMatrix();
        matrix.setSaturation(0.0f);
        paint.setColorFilter(new ColorMatrixColorFilter(matrix));
        canvas.drawBitmap(this._source, 0, 0, paint);
        if(this._result != null) FileTools.writeBitmap(this._result, result);
        return result;
    }

}
