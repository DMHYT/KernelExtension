package vsdum.kex.util;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.NativeItem;
import com.zhekasmirnov.innercore.utils.FileTools;

import android.graphics.Bitmap;

public class ItemAnimHelper {

    private static class AnimationContainer {
        private String textureName = "";
        private int meta = 0;
        private int timer = 0;
        private int frameIndex = 0;
    }

    private static final Map<Integer, AnimationContainer> animationTickingData = new HashMap<>();
    private static final Set<Runnable> animationTickers = new HashSet<>();
    
    public static void convertTexture(String sourcePath, String resultPath)
    {
        if(!FileTools.exists(resultPath + "_0.png"))
        {
            Bitmap anim = FileTools.readFileAsBitmap(sourcePath + ".png");
            if(anim.getHeight() % anim.getWidth() == 0)
            {
                for(int i = 0; i < anim.getHeight(); i++)
                {
                    Bitmap frame = Bitmap.createBitmap(anim.getWidth(), anim.getHeight(), Bitmap.Config.ARGB_8888);
                    for(int x = 0; x < anim.getWidth(); x++)
                    {
                        for(int y = 0; y < anim.getHeight(); y++)
                        {
                            frame.setPixel(x, y, anim.getPixel(x, y + anim.getWidth() * i));
                        }
                    }
                    FileTools.writeBitmap(String.format("%s_%d.png", new Object[]{ resultPath, Integer.valueOf(i) }), frame);
                }
            } else {
                Logger.debug("KEX-ItemAnimHelper", String.format("Invalid 'tall' texture on path %s. Texture's height must be a multiple of texture's width", new Object[]{ sourcePath + ".png" }));
            }
        } else {
            Logger.debug("KEX-ItemAnimHelper", String.format("Texture frame on path %s already exists, texture generation process cancelled!", new Object[]{ resultPath }));
        }
    }

    public static void makeCommonAnim(int id, String textureName, int ticks, int frames)
    {
        if(!animationTickingData.containsKey(id))
        {
            AnimationContainer container = new AnimationContainer();
            container.textureName = textureName;
            animationTickingData.put(id, container);
            animationTickers.add(() -> {
                if(container.timer + 1 == ticks)
                {
                    if(container.meta < frames - 1) ++container.meta;
                    else container.meta = 0;
                }
                if(container.timer < ticks) ++container.timer;
                else container.timer = 0;
            });
        } else {
            Logger.debug("KEX-ItemAnimHelper", String.format("An error occured calling 'ItemAnimHelper.makeCommonAnim' method. Another animation is already bound to item '%s'", new Object[]{ NativeItem.getNameForId(id, 0) }));
        }
    }

    public static void makeAdvancedAnim(int id, String textureName, int interval, int[] frames)
    {
        if(!animationTickingData.containsKey(id))
        {
            AnimationContainer container = new AnimationContainer();
            container.textureName = textureName;
            animationTickingData.put(id, container);
            animationTickers.add(() -> {
                if(container.timer + 1 == interval)
                {
                    if(container.frameIndex < frames.length) ++container.frameIndex;
                    else container.frameIndex = 0;
                    container.meta = frames[container.frameIndex];
                }
                if(container.timer < interval) container.timer++;
                else container.timer = 0;
            });
        } else {
            Logger.debug("KEX-ItemAnimHelper", String.format("An error occured calling 'ItemAnimHelper.makeAdvancedAnim' method. Another animation is already bound to item '%s'", new Object[]{ NativeItem.getNameForId(id, 0) }));
        }
    }

    public static void onLocalTick()
    {
        animationTickers.forEach(Runnable::run);
    }

    public static void onIconOverride(int id)
    {
        if(animationTickingData.containsKey(id))
        {
            AnimationContainer container = animationTickingData.get(id);
            NativeItem.overrideItemIcon(container.textureName, container.meta);
        }
    }

}
