package vsdum.kex.japi.internal.block.model.element;

import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.NativeRenderMesh;

public class Face {

    public final int index;
    public String textureName;
    public int textureMeta;
    public final float startX, startY, startZ;
    public final float endX, endY, endZ;
    public float startU, startV;
    public float endU, endV;

    public Face(int index, String textureName, int textureMeta, float startX, float startY, float startZ, float endX, float endY, float endZ, float startU, float startV, float endU, float endV)
    {
        this.index = index;
        this.textureName = textureName;
        this.textureMeta = textureMeta;
        this.startX = startX;
        this.startY = startY;
        this.startZ = startZ;
        this.endX = endX;
        this.endY = endY;
        this.endZ = endZ;
        this.startU = startU;
        this.startV = startV;
        this.endU = endU;
        this.endV = endV;
    }

    public final Face copy()
    {
        return new Face(this.index, this.textureName, this.textureMeta, this.startX, this.startY, this.startZ, this.endX, this.endY, this.endZ, this.startU, this.startV, this.endU, this.endV);
    }

    public Face rotateTexture(int rightAngles)
    {
        for(int lap = 0; lap < rightAngles; lap++)
        {
            float temp = this.startU;
            this.startU = this.endU;
            this.endU = temp;
            if(lap % 2 == 0)
            {
                temp = this.startV;
                this.startV = this.endV;
                this.endV = temp;
            }
        }
        return this;
    }

    public void onLevelDisplayed()
    {
        float[] textureUVOffset = new float[4];
        NativeAPI.getAtlasTextureCoords(this.textureName, this.textureMeta, textureUVOffset);
        this.startU = textureUVOffset[0] + (textureUVOffset[2] - textureUVOffset[0]) * this.startU;
        this.startV = textureUVOffset[1] + (textureUVOffset[3] - textureUVOffset[1]) * this.startV;
        this.endU = textureUVOffset[0] + (textureUVOffset[2] - textureUVOffset[0]) * this.endU;
        this.endV = textureUVOffset[1] + (textureUVOffset[3] - textureUVOffset[1]) * this.endV;
    }

    public void build(NativeRenderMesh mesh)
    {
        switch(this.index)
        {
            case 0: // down
                mesh.setNormal(0, 1, 0);
                mesh.addVertex(this.endX, this.startY, this.startZ, this.endU, this.startV);
                mesh.addVertex(this.endX, this.startY, this.endZ, this.endU, this.endV);
                mesh.addVertex(this.startX, this.startY, this.endZ, this.startU, this.endV);
                mesh.addVertex(this.startX, this.startY, this.endZ, this.startU, this.endV);
                mesh.addVertex(this.startX, this.startY, this.startZ, this.startU, this.startV);
                mesh.addVertex(this.endX, this.startY, this.startZ, this.endU, this.startV);
                break;
            case 1: // up
                mesh.setNormal(0, -1, 0);
                mesh.addVertex(this.endX, this.endY, this.startZ, this.endU, this.endV);
                mesh.addVertex(this.endX, this.endY, this.endZ, this.endU, this.startV);
                mesh.addVertex(this.startX, this.endY, this.endZ, this.startU, this.startV);
                mesh.addVertex(this.startX, this.endY, this.endZ, this.startU, this.startV);
                mesh.addVertex(this.startX, this.endY, this.startZ, this.startU, this.endV);
                mesh.addVertex(this.endX, this.endY, this.startZ, this.endU, this.endV);
                break;
            case 2: // north
                mesh.setNormal(0, 0, 1);
                mesh.addVertex(this.startX, this.startY, this.endZ, this.endU, this.endV);
                mesh.addVertex(this.startX, this.endY, this.endZ, this.endU, this.startV);
                mesh.addVertex(this.endX, this.endY, this.endZ, this.startU, this.startV);
                mesh.addVertex(this.endX, this.endY, this.endZ, this.startU, this.startV);
                mesh.addVertex(this.endX, this.startY, this.endZ, this.startU, this.endV);
                mesh.addVertex(this.startX, this.startY, this.endZ, this.endU, this.endV);
                break;
            case 3: // south
                mesh.setNormal(0, 0, -1);
                mesh.addVertex(this.startX, this.startY, this.startZ, this.startU, this.endV);
                mesh.addVertex(this.startX, this.endY, this.startZ, this.startU, this.startV);
                mesh.addVertex(this.endX, this.endY, this.startZ, this.endU, this.startV);
                mesh.addVertex(this.endX, this.endY, this.startZ, this.endU, this.startV);
                mesh.addVertex(this.endX, this.startY, this.startZ, this.endU, this.endV);
                mesh.addVertex(this.startX, this.startY, this.startZ, this.startU, this.endV);
                break;
            case 4: // west
                mesh.setNormal(1, 0, 0);
                mesh.addVertex(this.endX, this.startY, this.startZ, this.startU, this.endV);
                mesh.addVertex(this.endX, this.endY, this.startZ, this.startU, this.startV);
                mesh.addVertex(this.endX, this.endY, this.endZ, this.endU, this.startV);
                mesh.addVertex(this.endX, this.endY, this.endZ, this.endU, this.startV);
                mesh.addVertex(this.endX, this.startY, this.endZ, this.endU, this.endV);
                mesh.addVertex(this.endX, this.startY, this.startZ, this.startU, this.endV);
                break;
            case 5: // east
                mesh.setNormal(-1, 0, 0);
                mesh.addVertex(this.startX, this.startY, this.startZ, this.endU, this.endV);
                mesh.addVertex(this.startX, this.endY, this.startZ, this.endU, this.startV);
                mesh.addVertex(this.startX, this.endY, this.endZ, this.startU, this.startV);
                mesh.addVertex(this.startX, this.endY, this.endZ, this.startU, this.startV);
                mesh.addVertex(this.startX, this.startY, this.endZ, this.startU, this.endV);
                mesh.addVertex(this.startX, this.startY, this.startZ, this.endU, this.endV);
                break;
        }
    }

}
