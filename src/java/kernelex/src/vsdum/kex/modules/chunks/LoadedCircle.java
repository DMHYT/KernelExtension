package vsdum.kex.modules.chunks;

import java.util.Optional;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

import vsdum.kex.natives.Dimension;
import vsdum.kex.natives.TickingAreasManager;

public class LoadedCircle {
    
    private final Dimension dimension;
    private final String name;
    private Optional<Integer> x = Optional.empty();
    private Optional<Integer> z = Optional.empty();
    private int _radius = 0;
    private boolean loaded = false;

    public LoadedCircle(Dimension dimension)
    {
        this.dimension = dimension;
        this.name = this.dimension.getLevel()
            .getTickingAreasManager()
            .findUsableDefaultName(dimension);
        Logger.debug("KEX-ChunksModule", String.format("Loaded circle name was not specified, thus it was set to %s", new Object[]{ this.name }));
    }

    public LoadedCircle(Dimension dimension, String name)
    {
        this.dimension = dimension;
        this.name = name;
    }
    
    public LoadedCircle center(int x, int z)
    {
        this.x = Optional.of(x);
        this.z = Optional.of(z);
        return this;
    }

    public LoadedCircle radius(int r)
    {
        if(r <= 0) throw new IllegalArgumentException("Loaded circle radius cannot be less than 1");
        this._radius = r;
        return this;
    }

    public LoadedCircle load()
    {
        TickingAreasManager mgr = this.dimension.getLevel().getTickingAreasManager();
        if(!this.x.isPresent() || !this.z.isPresent()) throw new IllegalStateException("Loaded circle center coords were not specified");
        if(this._radius == 0) throw new IllegalStateException("Loaded circle radius was not specified");
        if(!this.loaded)
        {
            if(mgr.hasArea(this.name, this.dimension))
                throw new IllegalArgumentException(String.format("Ticking area with name %s already exists in dimension %d. You should use ChunksModule.areaExists in order not to get exceptions thrown.", new Object[]{ this.name, Integer.valueOf(this.dimension.getDimensionId()) }));
            mgr.addCircleArea(this.dimension, this.name, this.x.get().intValue(), this.z.get().intValue(), this._radius);
            this.loaded = true;
        }
        return this;
    }

    public LoadedCircle unload()
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
