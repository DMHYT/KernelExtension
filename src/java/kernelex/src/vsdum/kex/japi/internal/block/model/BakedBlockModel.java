package vsdum.kex.japi.internal.block.model;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Optional;
import java.util.Set;

import org.json.JSONArray;
import org.json.JSONObject;

import com.zhekasmirnov.innercore.api.NativeItemModel;
import com.zhekasmirnov.innercore.api.NativeRenderMesh;

import android.support.annotation.Nullable;
import android.util.Pair;
import vsdum.kex.japi.internal.block.model.element.*;
import vsdum.kex.util.mcmath.Vec3d;

import static vsdum.kex.japi.internal.block.model.BlockModelParser.deserializeCoordinates;

public final class BakedBlockModel {

    private boolean initialized = false;
    private int rotationX = 0;
    private int rotationY = 0;
    private boolean uvLock = false;

    public final Map<String, Pair<String, Integer>> textureVariables = new HashMap<>();
    public Pair<String, Integer> particleTexture = new Pair<>("missing_texture", 0);
    public final NativeRenderMesh mesh = NativeItemModel.getEmptyMeshFromPool();
    public final Set<Cube> elements = new HashSet<>();
    public Optional<ItemModelModifications> handModel = Optional.empty();
    public Optional<ItemModelModifications> guiModel = Optional.empty();
    public final NativeRenderMesh handMesh = NativeItemModel.getEmptyMeshFromPool();
    public final NativeRenderMesh guiMesh = NativeItemModel.getEmptyMeshFromPool();

    public final BakedBlockModel copy()
    {
        BakedBlockModel result = new BakedBlockModel();
        result.textureVariables.putAll(this.textureVariables);
        result.particleTexture = new Pair<>(this.particleTexture.first, this.particleTexture.second);
        this.elements.forEach(cube -> result.elements.add(cube.copy()));
        result.rotationX = this.rotationX;
        result.rotationY = this.rotationY;
        result.uvLock = this.uvLock;
        return result;
    }

    public BakedBlockModel rotate(int x, int y, boolean uvLock)
    {
        this.rotationX = x;
        this.rotationY = y;
        this.uvLock = uvLock;
        return this;
    }

    public void onLevelDisplayed()
    {
        if(this.initialized) return;
        this.elements.forEach(cube -> {
            if(this.uvLock)
            {
                if(this.rotationX != 0) cube.uvLockX(this.rotationX / 90);
                if(this.rotationY != 0) cube.uvLockY(this.rotationY / 90);
            }
            NativeRenderMesh tempMesh = NativeItemModel.getEmptyMeshFromPool();
            cube.onLevelDisplayed();
            cube.build(tempMesh);
            this.mesh.addMesh(tempMesh);
            NativeItemModel.releaseMesh(tempMesh);
        });
        this.mesh.rotate(.5f, .5f, .5f, (float) Math.toRadians(this.rotationX), (float) Math.toRadians(this.rotationY), .0f);
        if(this.handModel.isPresent())
        {
            this.handMesh.addMesh(this.mesh);
            this.handModel.get().apply(this.handMesh);
        }
        if(this.guiModel.isPresent())
        {
            this.guiMesh.addMesh(this.mesh);
            this.guiModel.get().apply(this.guiMesh);
        }
        this.initialized = true;
    }

    @Override protected void finalize()
    {
        try {
            super.finalize();
            NativeItemModel.releaseMesh(this.mesh);
            NativeItemModel.releaseMesh(this.handMesh);
            NativeItemModel.releaseMesh(this.guiMesh);
        } catch(Throwable ex) { ex.printStackTrace(); }
    }

    public static class ItemModelModifications {

        public final float rotationX;
        public final float rotationY;
        public final float rotationZ;
        public final float translationX;
        public final float translationY;
        public final float translationZ;
        public final float scaleX;
        public final float scaleY;
        public final float scaleZ;

        public ItemModelModifications(float rx, float ry, float rz, float tx, float ty, float tz, float sx, float sy, float sz)
        {
            this.rotationX = rx;
            this.rotationY = ry;
            this.rotationZ = rz;
            this.translationX = tx;
            this.translationY = ty;
            this.translationZ = tz;
            this.scaleX = sx;
            this.scaleY = sy;
            this.scaleZ = sz;
        }

        public final void apply(NativeRenderMesh mesh)
        {
            mesh.translate(-.5f, -.5f, -.5f);
            mesh.scale(this.scaleX, this.scaleY, this.scaleZ);
            mesh.translate(.5f, .5f, .5f);
            mesh.translate(this.translationX, this.translationY, this.translationZ);
            mesh.rotate(.5f, .5f, .5f, this.rotationX, this.rotationY, this.rotationZ);
        }

        @Nullable public static ItemModelModifications parse(@Nullable JSONObject json)
        {
            if(json == null) return null;
            Vec3d rotation = Optional.ofNullable(parseRotation(json.optJSONArray("rotation"))).orElse(Vec3d.ZERO);
            Vec3d translation = Optional.ofNullable(deserializeCoordinates(json.optJSONArray("translation"), -80D, 80D, true)).orElse(Vec3d.ZERO);
            Vec3d scale = Optional.ofNullable(deserializeCoordinates(json.optJSONArray("scale"), .001D, 4D, true)).orElse(new Vec3d(1D, 1D, 1D));
            return rotation == Vec3d.ZERO && translation == Vec3d.ZERO && scale == Vec3d.ZERO
                ? null : new ItemModelModifications((float) rotation.x, (float) rotation.y, (float) rotation.z, (float) translation.x, (float) translation.y, (float) translation.z, (float) scale.x, (float) scale.y, (float) scale.z);
        }

        @Nullable private static Vec3d parseRotation(@Nullable JSONArray arr)
        {
            if(arr == null || arr.length() != 3) return null;
            double[] angles = new double[3];
            for(int i = 0; i < 3; i++)
            {
                double angle = arr.optDouble(i);
                if(angle == Double.NaN) return null;
                angle %= 360D;
                angle = Math.toRadians(angle);
            }
            return new Vec3d(angles[0], angles[1], angles[2]);
        }

    }

}
