package vsdum.kex.util.textureworker;

import java.util.ArrayList;
import java.util.List;

import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.utils.FileTools;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.support.annotation.Nullable;
import vsdum.kex.util.TextureWorker;

public class OverlaidTextureBuilder {
    
    @Nullable private Bitmap _bitmap = null;
    private final List<Bitmap> overlays = new ArrayList<>();
    @Nullable private String _result = null;

    public OverlaidTextureBuilder bitmap(int width, int height)
    {
        return this.bitmap(width, height, Bitmap.Config.ARGB_8888);
    }

    public OverlaidTextureBuilder bitmap(int width, int height, Bitmap.Config config)
    {
        this._bitmap = Bitmap.createBitmap(width, height, config);
        return this;
    }

    public OverlaidTextureBuilder overlay(String path, String name)
    {
        return this.overlay(path, name, -1, -1, -1);
    }

    public OverlaidTextureBuilder overlay(String path, String name, int r, int g, int b)
    {
        Bitmap tex = FileTools.readFileAsBitmap(path + name + ".png");
        if(r >= 0 && g >= 0 && b >= 0) tex = TextureWorker.changeBitmapColor(tex, r, g, b);
        this.overlays.add(tex);
        return this;
    }

    public OverlaidTextureBuilder overlay(String path, String name, int r, int g, int b, int a)
    {
        Bitmap tex = FileTools.readFileAsBitmap(path + name + ".png");
        if(r >= 0 && g >= 0 && b >= 0 && a >= 0) tex = TextureWorker.changeBitmapColor(tex, r, g, b, a);
        this.overlays.add(tex);
        return this;
    }

    public OverlaidTextureBuilder overlay(Bitmap bitmap)
    {
        this.overlays.add(bitmap);
        return this;
    }

    public OverlaidTextureBuilder overlay(Bitmap bitmap, int r, int g, int b)
    {
        if(r >= 0 && g >= 0 && b >= 0) this.overlays.add(TextureWorker.changeBitmapColor(bitmap, r, g, b));
        return this;
    }

    public OverlaidTextureBuilder overlay(Bitmap bitmap, int r, int g, int b, int a)
    {
        if(r >= 0 && g >= 0 && b >= 0 && a >= 0) this.overlays.add(TextureWorker.changeBitmapColor(bitmap, r, g, b, a));
        return this;
    }

    public OverlaidTextureBuilder result(String path, String name)
    {
        this._result = path + name + ".png";
        return this;
    }

    @Nullable public Bitmap create()
    {
        if(FileTools.exists(this._result))
        {
            Logger.debug("KEX-TextureWorker", String.format("File on path %s already exists, texture generation process cancelled", this._result));
            return null;
        }
        if(this._bitmap == null) return null;
        Canvas canvas = new Canvas(this._bitmap);
        this.overlays.forEach(overlay -> canvas.drawBitmap(overlay, 0, 0, null));
        if(this._result != null) FileTools.writeBitmap(this._result, this._bitmap);
        return this._bitmap;
    }

}
