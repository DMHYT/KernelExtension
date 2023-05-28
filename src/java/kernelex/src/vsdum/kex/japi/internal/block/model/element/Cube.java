package vsdum.kex.japi.internal.block.model.element;

import java.util.HashMap;
import java.util.Map;

import com.zhekasmirnov.innercore.api.NativeRenderMesh;
import com.zhekasmirnov.innercore.api.NativeICRender.CollisionEntry;

public class Cube {

    private static final Map<Float, Float> cachedScaleFactors = new HashMap<>();

    private static float getOrComputeScaleFactor(float rotationAngle)
    {
        if(!cachedScaleFactors.containsKey(rotationAngle))
            cachedScaleFactors.put(rotationAngle, 1.0f + 1.0f / (float) Math.cos(rotationAngle) - 1.0f);
        return cachedScaleFactors.get(rotationAngle);
    }

    public final Face[] faces = new Face[6];
    public final float startX, startY, startZ;
    public final float endX, endY, endZ;
    public byte rotationAxis = -1;
    public float rotationAngle = 0.0f;
    public float rotationOriginX = .5f;
    public float rotationOriginY = .5f;
    public float rotationOriginZ = .5f;
    public boolean rescale = false;

    public Cube(float startX, float startY, float startZ, float endX, float endY, float endZ)
    {
        this.startX = startX;
        this.startY = startY;
        this.startZ = startZ;
        this.endX = endX;
        this.endY = endY;
        this.endZ = endZ;
    }

    public final Cube copy()
    {
        Cube result = new Cube(this.startX, this.startY, this.startZ, this.endX, this.endY, this.endZ);
        result.rotationAxis = this.rotationAxis;
        result.rotationAngle = this.rotationAngle;
        result.rotationOriginX = this.rotationOriginX;
        result.rotationOriginY = this.rotationOriginY;
        result.rotationOriginZ = this.rotationOriginZ;
        result.rescale = this.rescale;
        for(int faceIndex = 0; faceIndex < 6; faceIndex++)
            if(this.faces[faceIndex] != null)
                result.faces[faceIndex] = this.faces[faceIndex].copy();
        return result;
    }

    public void onLevelDisplayed()
    {
        for(Face face : faces)
            if(face != null)
                face.onLevelDisplayed();
    }

    public void addToCollisionShape(CollisionEntry entry)
    {
        entry.addBox(this.startX, this.startY, this.startZ, this.endX, this.endY, this.endZ);
    }

    public void build(NativeRenderMesh mesh)
    {
        for(Face face : faces)
            if(face != null)
                face.build(mesh);
        mesh.rotate(
            this.rotationOriginX, this.rotationOriginY, this.rotationOriginZ,
            this.rotationAxis == 0 ? this.rotationAngle : 0.0f,
            this.rotationAxis == 1 ? this.rotationAngle : 0.0f,
            this.rotationAxis == 2 ? this.rotationAngle : 0.0f
        );
        if(this.rescale && this.rotationAxis != -1)
        {
            float scaleFactor = getOrComputeScaleFactor(this.rotationAngle);
            mesh.translate(
                this.rotationAxis != 0 ? -0.5f : 0.0f,
                this.rotationAxis != 1 ? -0.5f : 0.0f,
                this.rotationAxis != 2 ? -0.5f : 0.0f
            );
            mesh.scale(
                this.rotationAxis != 0 ? scaleFactor : 1.0f,
                this.rotationAxis != 1 ? scaleFactor : 1.0f,
                this.rotationAxis != 2 ? scaleFactor : 1.0f
            );
            mesh.translate(
                this.rotationAxis != 0 ? 0.5f : 0.0f,
                this.rotationAxis != 1 ? 0.5f : 0.0f,
                this.rotationAxis != 2 ? 0.5f : 0.0f
            );
        }
    }

    public Cube face(int index, String textureName, int textureMeta, float startU, float startV, float endU, float endV, int rightAngles)
    {
        this.faces[index] = new Face(
            index, textureName, textureMeta,
            this.startX, this.startY, this.startZ,
            this.endX, this.endY, this.endZ,
            startU, startV, endU, endV
        ).rotateTexture(rightAngles);
        return this;
    }

    public Cube rot(byte axis, float angle, float originX, float originY, float originZ, boolean rescale)
    {
        this.rotationAxis = axis;
        this.rotationAngle = (float) Math.toRadians(angle);
        this.rotationOriginX = originX;
        this.rotationOriginY = originY;
        this.rotationOriginX = originZ;
        this.rescale = rescale;
        return this;
    }

    public Cube uvLockX(int rightAngles)
    {
        if(this.faces[4] != null) this.faces[4].rotateTexture(rightAngles);
        if(this.faces[5] != null) this.faces[5].rotateTexture(rightAngles);
        return this;
    }

    public Cube uvLockY(int rightAngles)
    {
        if(this.faces[0] != null) this.faces[0].rotateTexture(rightAngles);
        if(this.faces[1] != null) this.faces[1].rotateTexture(rightAngles);
        return this;
    }

    public Cube uvLockZ(int rightAngles)
    {
        if(this.faces[2] != null) this.faces[2].rotateTexture(rightAngles);
        if(this.faces[3] != null) this.faces[3].rotateTexture(rightAngles);
        return this;
    }

}
