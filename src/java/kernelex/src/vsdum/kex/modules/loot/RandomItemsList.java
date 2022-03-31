package vsdum.kex.modules.loot;

import java.util.ArrayList;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.NativeItemInstanceExtra;

import vsdum.kex.common.INativeInterface;

public class RandomItemsList extends ArrayList<ItemStack> implements INativeInterface {

    private static native long nativeGet(long ptr, int index);
    private static native void nativeRefill(long ptr, Object[] stacks);

    private final long vectorPtr;
    private boolean wasChanged = false;

    public final long getPointer()
    {
        return this.vectorPtr;
    }

    public void markChanged()
    {
        if(!this.wasChanged) this.wasChanged = true;
    }

    public RandomItemsList(long pointer, int size)
    {
        super();
        this.vectorPtr = pointer;
        for(int i = 0; i < size; i++)
        {
            this.add(ItemStack.fromPtr(nativeGet(this.vectorPtr, i)));
        }
    }

    public void addItem(int id, int count, int data)
    {
        this.markChanged();
        this.add(new ItemStack(id, count, data));
    }

    public void addItem(int id, int count, int data, NativeItemInstanceExtra extra)
    {
        this.markChanged();
        this.add(new ItemStack(id, count, data));
    }

    @Override public ItemStack remove(int index)
    {
        this.markChanged();
        return super.remove(index);
    }

    public void modifyNative()
    {
        if(this.wasChanged)
        {
            Object[] arr = new Object[this.size()];
            for(int i = 0; i < this.size(); i++) arr[i] = this.get(i);
            nativeRefill(this.getPointer(), arr);
        }
    }

}
