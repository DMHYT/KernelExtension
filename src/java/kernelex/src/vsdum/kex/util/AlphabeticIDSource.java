package vsdum.kex.util;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.function.Consumer;

import android.support.annotation.Nullable;

public final class AlphabeticIDSource {

    private static final AlphabeticIDSource INSTANCE = new AlphabeticIDSource();

    public static final AlphabeticIDSource instance()
    {
        return INSTANCE;
    }

    private final Set<Scope> scopes = new HashSet<>();

    private AlphabeticIDSource() {}

    public final Scope createScope(String scopeKey, int firstID, @Nullable Consumer<ScopeData> callback)
    {
        Scope scope = new Scope(scopeKey, firstID, callback);
        this.scopes.add(scope);
        return scope;
    }

    public final void onModsLoaded()
    {
        this.scopes.forEach(scope -> {
            Optional.ofNullable(scope.callback)
                .ifPresent(callback -> callback.accept(scope.data()));
        });
    }

    public static class Scope {

        private final String key;
        private final int firstID;
        @Nullable private final Consumer<ScopeData> callback;
        private final Set<String> nameIDs = new HashSet<>();

        private Scope(String key, int firstID, @Nullable Consumer<ScopeData> callback)
        {
            this.key = key;
            this.firstID = firstID;
            this.callback = callback;
        }

        public boolean has(String nameID)
        {
            return this.nameIDs.contains(nameID);
        }

        public void add(String nameID)
        {
            if(this.has(nameID)) throw new IllegalArgumentException("Name ID " + nameID + " in ID scope " + this.key + " already exists!");
            this.nameIDs.add(nameID);
        }

        private final ScopeData data()
        {
            return new ScopeData(this.firstID, new ArrayList<>(this.nameIDs));
        }

    }

    public static class ScopeData {

        private final Map<String, Integer> nameToNumeric = new HashMap<>();
        private final Map<Integer, String> numericToName = new HashMap<>();

        private ScopeData(int firstID, List<String> nameIDs)
        {
            Collections.sort(nameIDs);
            int nextID = firstID;
            for(String nameID : nameIDs)
            {
                this.nameToNumeric.put(nameID, nextID);
                this.numericToName.put(nextID, nameID);
                nextID++;
            }
        }

        public boolean has(String nameID)
        {
            return this.nameToNumeric.containsKey(nameID);
        }

        public boolean has(int numericID)
        {
            return this.numericToName.containsKey(numericID);
        }

        public int getNumericID(String nameID)
        {
            return this.nameToNumeric.getOrDefault(nameID, 0);
        }

        @Nullable public String getNameID(int numericID)
        {
            return this.numericToName.get(numericID);
        }

    }

}
