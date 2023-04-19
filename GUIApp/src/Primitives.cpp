#include "Primitives.hpp"
#include "framework/engine.h"

Plane::Plane()
{
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;

	vertices.push_back({ glm::vec3(-0.5f,-0.5f, 0), glm::vec3(0,0,1), glm::vec2(0,0) });
	vertices.push_back({ glm::vec3(0.5f,-0.5f, 0), glm::vec3(0,0,1), glm::vec2(1,0) });
	vertices.push_back({ glm::vec3(0.5f, 0.5f, 0), glm::vec3(0,0,1), glm::vec2(1,1) });
	vertices.push_back({ glm::vec3(-0.5f, 0.5f, 0), glm::vec3(0,0,1), glm::vec2(0,1) });

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);

	getMesh()->set(vertices, indices);
}

Sphere::Sphere(int stacks, int slices)
{
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;

	const float PI = glm::pi<float>();
	const float PI05 = PI * 0.5f;
	const float PI2 = PI * 2.0f;

	const float radius = 0.5f;

	// vertices
	for (int i = 0; i <= stacks; i++)
	{
		float v = static_cast<float>(i) / stacks;
		float phi = PI * v - PI05;
		for (int j = 0; j <= slices; j++)
		{
			float u = static_cast<float>(j) / slices;
			float theta = PI2 * u;

			Vertex vertex;
			vertex.normal = glm::vec3(cos(phi) * cos(theta), -cos(phi) * sin(theta), sin(phi));
			vertex.position = vertex.normal * radius;
			vertex.tex_coords = glm::vec2(1.0f - u, 1.0f - v);
			vertices.push_back(vertex);
		}
	}

	// indices
	for (int i = 0; i < stacks; i++)
	{
		for (int j = 0; j < slices; j++)
		{
			int offset = (slices + 1) * i + j;
			if (i != 0)
			{
				indices.push_back(offset);
				indices.push_back(offset + slices + 1);
				indices.push_back(offset + 1);
			}
			if (i != stacks - 1)
			{
				indices.push_back(offset + slices + 2);
				indices.push_back(offset + 1);
				indices.push_back(offset + slices + 1);
			}
		}
	}

	getMesh()->set(vertices, indices);
}

Cube::Cube()
{
	// vertices and normals of a cube
	const float v[] = {
		// back face
		 0.5f, -0.5f, -0.5f,  0,  0, -1, // bottom-right
		-0.5f, -0.5f, -0.5f,  0,  0, -1, // bottom-left
		-0.5f,  0.5f, -0.5f,  0,  0, -1, // top-left
		 0.5f,  0.5f, -0.5f,  0,  0, -1, // top-right
		// front face
		-0.5f, -0.5f,  0.5f,  0,  0,  1, // bottom-left
		 0.5f, -0.5f,  0.5f,  0,  0,  1, // bottom-right
		 0.5f,  0.5f,  0.5f,  0,  0,  1, // top-right
		-0.5f,  0.5f,  0.5f,  0,  0,  1, // top-left
		// left face
		-0.5f, -0.5f,  0.5f, -1,  0,  0, // bottom-right
		-0.5f,  0.5f,  0.5f, -1,  0,  0, // top-right
		-0.5f,  0.5f, -0.5f, -1,  0,  0, // top-left
		-0.5f, -0.5f, -0.5f, -1,  0,  0, // bottom-left
		// right face
		 0.5f,  0.5f,  0.5f,  1,  0,  0, // top-left
		 0.5f, -0.5f,  0.5f,  1,  0,  0, // bottom-left
		 0.5f, -0.5f, -0.5f,  1,  0,  0, // bottom-right
		 0.5f,  0.5f, -0.5f,  1,  0,  0, // top-right
		// bottom face
		 0.5f, -0.5f,  0.5f,  0, -1,  0, // bottom-left
		-0.5f, -0.5f,  0.5f,  0, -1,  0, // bottom-right
		-0.5f, -0.5f, -0.5f,  0, -1,  0, // top-right
		 0.5f, -0.5f, -0.5f,  0, -1,  0, // top-left
		// top face
		-0.5f,  0.5f,  0.5f,  0,  1,  0, // bottom-left
		 0.5f,  0.5f,  0.5f,  0,  1,  0, // bottom-right
		 0.5f,  0.5f, -0.5f,  0,  1,  0, // top-right
		-0.5f,  0.5f, -0.5f,  0,  1,  0, // top-left
	};

	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;

	for (int i = 0; i < 6; i++)
	{
		int j = i * 24;
		vertices.push_back({ glm::vec3(v[j + 0],  v[j + 1],  v[j + 2]),  glm::vec3(v[j + 3], v[j + 4], v[j + 5]),  glm::vec2(0,0) });
		vertices.push_back({ glm::vec3(v[j + 6],  v[j + 7],  v[j + 8]),  glm::vec3(v[j + 9], v[j + 10],v[j + 11]), glm::vec2(1,0) });
		vertices.push_back({ glm::vec3(v[j + 12], v[j + 13], v[j + 14]), glm::vec3(v[j + 15],v[j + 16],v[j + 17]), glm::vec2(1,1) });
		vertices.push_back({ glm::vec3(v[j + 18], v[j + 19], v[j + 20]), glm::vec3(v[j + 21],v[j + 22],v[j + 23]), glm::vec2(0,1) });

		indices.push_back(i * 4 + 0);
		indices.push_back(i * 4 + 1);
		indices.push_back(i * 4 + 2);
		indices.push_back(i * 4 + 2);
		indices.push_back(i * 4 + 3);
		indices.push_back(i * 4 + 0);
	}

	getMesh()->set(vertices, indices);
}
