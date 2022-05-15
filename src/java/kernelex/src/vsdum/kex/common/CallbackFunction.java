package vsdum.kex.common;

import java.util.List;

public class CallbackFunction<T> {
    
    public final T function;
    public final int priority;

    public CallbackFunction(T function, int priority)
    {
        this.function = function;
        this.priority = priority;
    }

    public static <T> void addToList(CallbackFunction<T> func, List<CallbackFunction<T>> list)
    {
        for(int i = 0; i < list.size(); ++i)
        {
            if(list.get(i).priority < func.priority)
            {
                list.add(i, func);
                return;
            }
        }
        list.add(func);
    }

}
