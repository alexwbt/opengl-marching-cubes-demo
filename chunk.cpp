#include "chunk.h"
#include <time.h>
#include <iostream>

Chunk::Chunk() : mesh(generateVertices())
{

}

float Chunk::inBound(int x, int y, int z)
{
    return x >= 0 && x < size && y >= 0 && y < size && z >= 0 && z < size;
}

std::vector<Vertex> Chunk::generateVertices()
{
    srand(time(NULL));
    float*** data = new float**[size];
    for (int x = 0; x < size; x++)
    {
        data[x] = new float*[size];
        for (int y = 0; y < size; y++)
        {
            data[x][y] = new float[size];
            for (int z = 0; z < size; z++)
            {
                data[x][y][z] = (float)rand() / (float)RAND_MAX;
                std::cout << data[x][y][z] << std::endl;
                // chunkData[x, y, z] = (float)Random.Range(0, 100) / 100.0f;
                // chunkData[x, y, z] = key.y * SIZE + y > Chunk.SIZE * 1.5 ? 0 : 1;

                // Vector3 pos = (Vector3)key * (float)SIZE + new Vector3(x, y, z);
                // chunkData[x, y, z] = -pos.y + Mathf.PerlinNoise(pos.x / SIZE, pos.z / SIZE) * SIZE * 2;// + pos.y % 3;

                //Vector3 pos = (key * SIZE + new Vector3(x, y, z)) - new Vector3(SIZE, SIZE, SIZE) * 5f / 2f;
                //chunkData[x, y, z] = pos.y < SIZE * 2.5 ? 1 - Mathf.Sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z) / (SIZE * 5 - 2) : 0;

                // chunkData[x, y, z] = manager.noise.Density(0, pos);
            }
        }
    }

    std::vector<Vertex> vertices;
    for (int x = -1; x < size; x++)
    {
        for (int y = -1; y < size; y++)
        {
            for (int z = -1; z < size; z++)
            {
                int cube[8][3] = {
                    { x, y, z },
                    { x + 1, y, z },
                    { x + 1, y, z + 1 },
                    { x, y, z + 1 },
                    { x, y + 1, z },
                    { x + 1, y + 1, z },
                    { x + 1, y + 1, z + 1 },
                    { x, y + 1, z + 1}
                };

                int cubeIndex = 0;
                for (int i = 0; i < 8; i++)
                    if (inBound(cube[i][0], cube[i][1], cube[i][2]) ? data[cube[i][0]][cube[i][1]][cube[i][2]] : 0 > surface)
                        cubeIndex |= 1 << i;

                if (cubeIndex != 0)
                {
                    // int vertCount = 0;
                    for (int i = 0; i < 16; i++)
                    {
                        if (TRI[cubeIndex][i] != -1)
                        {
                            // vertCount++;
                            int a = CIAFE[TRI[cubeIndex][i]];
                            int b = CIBFE[TRI[cubeIndex][i]];

                            glm::vec3 p1((float)cube[a][0], (float)cube[a][1], (float)cube[a][2]);
                            glm::vec3 p2((float)cube[b][0], (float)cube[b][1], (float)cube[b][2]);
                            float v1 = inBound(cube[a][0], cube[a][1], cube[a][2]) ? data[cube[a][0]][cube[a][1]][cube[a][2]] : 0;
                            float v2 = inBound(cube[b][0], cube[b][1], cube[b][2]) ? data[cube[b][0]][cube[b][1]][cube[b][2]] : 0;
                            
                            glm::vec3 pos = p1 + (surface - v1) * (p2 - p1) / (v2 - v1);
                            std::cout << pos.x << ' ' << pos.y << ' ' << pos.z << ' ' << p1.x << std::endl;
                            // glm::vec3 pos = (p1 + p2) * 0.5f;
                            glm::vec3 color(pos.x / size, pos.y / size, pos.z / size);
                            vertices.push_back({ pos, glm::vec3(1), color });

                            // if (vertCount == 3)
                            // {
                            //     vertCount = 0;
                            //     size_t vertSize = vertices.size();
                            //     glm::vec3 v1 = vertices[vertSize - 3].pos;
                            //     glm::vec3 v2 = vertices[vertSize - 2].pos;
                            //     glm::vec3 v3 = vertices[vertSize - 1].pos;
                            // 
                            //     glm::vec3 U = v2 - v1;
                            //     glm::vec3 V = v3 - v1;
                            // 
                            //     glm::vec3 normal(
                            //         U.y * U.z - U.z * V.y,
                            //         U.z * V.x - U.x * V.z,
                            //         U.x * V.y - U.y * V.x
                            //     );
                            //     vertices[vertSize - 3].normal = normal;
                            //     vertices[vertSize - 2].normal = normal;
                            //     vertices[vertSize - 1].normal = normal;
                            // }
                        }
                    }
                }
            }
        }
    }

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
            delete[] data[x][y];
        delete[] data[x];
    }
    delete[] data;

    return vertices;
}

void Chunk::render()
{
    mesh.render();
}
