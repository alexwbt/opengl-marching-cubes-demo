#include "chunk.h"

#include "perlin_noise.h"

#include <time.h>
#include <iostream>

Chunk::Chunk() : mesh(generateVertices())
{}

float Chunk::inBound(glm::vec3 pos)
{
    return pos.x >= 0 && pos.x < size
        && pos.y >= 0 && pos.y < size
        && pos.z >= 0 && pos.z < size;
}

std::vector<Vertex> Chunk::generateVertices()
{
    // srand(time(NULL));

    PerlinNoise noise(time(NULL));

    float*** data = new float** [size];
    double scale = size * 0.075;
    for (int x = 0; x < size; x++)
    {
        data[x] = new float* [size];
        for (int y = 0; y < size; y++)
        {
            data[x][y] = new float[size];
            for (int z = 0; z < size; z++)
            {
                // random
                // data[x][y][z] = ((float)rand() / (float)RAND_MAX) * (max - min) + min;

                // sphere with noise
                data[x][y][z] = (float)noise.noise(x / scale, z / scale, y / scale) * (max - min) + min;
                glm::vec3 d = glm::vec3(x, y, z) - glm::vec3(size / 2);
                data[x][y][z] += 1 - (d.x * d.x + d.y * d.y + d.z * d.z) / pow(size * 0.5, 2);
                data[x][y][z] -= (d.x * d.x + d.y * d.y + d.z * d.z) / pow(size * 0.75, 2);

                // land with noise
                // data[x][y][z] = (float)noise.noise(x / scale, z / scale, y / scale) * (max - min) + min;
                // data[x][y][z] += 1 - y / (size * 0.5);
                // data[x][y][z] -= y / (size * 0.75);
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
                glm::vec3 cube[8] = {
                    glm::vec3(x, y, z),
                    glm::vec3(x + 1, y, z),
                    glm::vec3(x + 1, y, z + 1),
                    glm::vec3(x, y, z + 1),
                    glm::vec3(x, y + 1, z),
                    glm::vec3(x + 1, y + 1, z),
                    glm::vec3(x + 1, y + 1, z + 1),
                    glm::vec3(x, y + 1, z + 1)
                };

                int cubeIndex = 0;
                for (int i = 0; i < 8; i++)
                    if (inBound(cube[i]) && data[(int)cube[i].x][(int)cube[i].y][(int)cube[i].z] > surface)
                        cubeIndex |= (1 << i);

                if (cubeIndex != 0)
                {
                    int vertCount = 0;
                    for (int i = 0; i < 16; i++)
                    {
                        if (TRI[cubeIndex][i] == -1)
                            break;

                        glm::vec3 p1 = cube[CIAFE[TRI[cubeIndex][i]]];
                        glm::vec3 p2 = cube[CIBFE[TRI[cubeIndex][i]]];
                        float v1 = inBound(p1) ? data[(int)p1.x][(int)p1.y][(int)p1.z] : min;
                        float v2 = inBound(p2) ? data[(int)p2.x][(int)p2.y][(int)p2.z] : min;

                        glm::vec3 pos = p1 + (surface - v1) * (p2 - p1) / (v2 - v1);
                        // glm::vec3 pos = (p1 + p2) / 2.0f;
                        glm::vec3 color(pos.x / size, pos.y / size, pos.z / size);
                        vertices.push_back({ pos, glm::vec3(1.0f), color });

                        if (++vertCount == 3)
                        {
                            vertCount = 0;
                            size_t vertSize = vertices.size();
                            glm::vec3 vert1 = vertices[vertSize - 3].pos;
                            glm::vec3 vert2 = vertices[vertSize - 2].pos;
                            glm::vec3 vert3 = vertices[vertSize - 1].pos;

                            glm::vec3 U = vert2 - vert1;
                            glm::vec3 V = vert3 - vert1;

                            glm::vec3 normal(
                                U.y * U.z - U.z * V.y,
                                U.z * V.x - U.x * V.z,
                                U.x * V.y - U.y * V.x
                            );
                            vertices[vertSize - 3].normal = normal;
                            vertices[vertSize - 2].normal = normal;
                            vertices[vertSize - 1].normal = normal;
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
