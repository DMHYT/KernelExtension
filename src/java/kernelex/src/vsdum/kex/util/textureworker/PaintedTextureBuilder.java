package vsdum.kex.util.textureworker;

import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.utils.FileTools;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.support.annotation.Nullable;
import vsdum.kex.util.TextureWorker;

public class PaintedTextureBuilder {
    
    @Nullable private Bitmap _bitmap = null;
    @Nullable private Bitmap _source = null;
    @Nullable private String _result = null;
    private int r = -1;
    private int g = -1;
    private int b = -1;

    public PaintedTextureBuilder bitmap(int width, int height)
    {
        return this.bitmap(width, height, Bitmap.Config.ARGB_8888);
    }

    public PaintedTextureBuilder bitmap(int width, int height, Bitmap.Config config)
    {
        this._bitmap = Bitmap.createBitmap(width, height, config);
        return this;
    }

    public PaintedTextureBuilder source(String path, String name)
    {
        this._source = FileTools.readFileAsBitmap(path + name + ".png");
        return this;
    }

    public PaintedTextureBuilder source(Bitmap src)
    {
        this._source = src;
        return this;
    }

    public PaintedTextureBuilder color(int r, int g, int b)
    {
        this.r = r;
        this.g = g;
        this.b = b;
        return this;
    }

    public PaintedTextureBuilder result(String path, String name)
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
        if(this._bitmap == null) this._bitmap = Bitmap.createBitmap(this._source.getWidth(), this._source.getHeight(), this._source.getConfig());
        Canvas canvas = new Canvas(this._bitmap);
        canvas.drawBitmap(TextureWorker.changeBitmapColor(this._source, this.r, this.g, this.b), 0, 0, null);
        if(this._result != null) FileTools.writeBitmap(this._result, this._bitmap);
        return this._bitmap;
    }

}
