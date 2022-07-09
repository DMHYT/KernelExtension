package vsdum.kex.modules.chunks;

import java.util.Optional;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

import vsdum.kex.natives.Dimension;
import vsdum.kex.natives.TickingAreasManager;

public class LoadedRectangle {
    
    private final Dimension dimension;
    private final String name;
    private Optional<Integer> x1 = Optional.empty();
    private Optional<Integer> z1 = Optional.empty();
    private Optional<Integer> x2 = Optional.empty();
    private Optional<Integer> z2 = Optional.empty();
    private boolean loaded = false;

    public LoadedRectangle(Dimension dimension)
    {
        this.dimension = dimension;
        this.name = this.dimension.getLevel()
            .getTickingAreasManager()
            .findUsableDefaultName(dimension);
        Logger.debug("KEX-ChunksModule", String.format("Loaded rectangle name was not specified, thus it was set to %s", new Object[]{ this.name }));
    }

    public LoadedRectangle(Dimension dimension, String name)
    {
        this.dimension = dimension;
        this.name = name;
    }

    public LoadedRectangle start(int x, int z)
    {
        this.x1 = Optional.of(x);
        this.z1 = Optional.of(z);
        return this;
    }

    public LoadedRectangle end(int x, int z)
    {
        this.x2 = Optional.of(x);
        this.z2 = Optional.of(z);
        return this;
    }

    public LoadedRectangle load()
    {
        TickingAreasManager mgr = this.dimension.getLevel().getTickingAreasManager();
        if(!this.x1.isPresent() || !this.z1.isPresent()) throw new IllegalStateException("Start coords for loaded rectangle were not specified");
        if(!this.x2.isPresent() || !this.z2.isPresent()) throw new IllegalStateException("End coords for loaded rectangle were not specified");
        if(!this.loaded)
        {
            if(mgr.hasArea(this.name, this.dimension))
                throw new IllegalArgumentException(String.format("Ticking area with name %s already exists in dimension %d. You should use ChunksModule.areaExists in order not to get exceptions thrown.", new Object[]{ this.name, Integer.valueOf(this.dimension.getDimensionId()) }));
            mgr.addRectangleArea(this.dimension, this.name, this.x1.get().intValue(), this.z1.get().intValue(), this.x2.get().intValue(), this.z2.get().intValue());
            this.loaded = true;
        }
        return this;
    }

    public LoadedRectangle unload()
    {
        if(this.loaded)
        {
            this.dimension.getLevel()
                .getTickingAreasManager()
                .removeAreaByName(this.dimension, this.name);
            this.loaded = false;
        }
        return this;
    }

    public boolean isLoaded()
    {
        return this.loaded;
    }

}
