#include "Primitives.hpp"

Plane::Plane()
{
	_data.positions.push_back(glm::vec3(-0.5f,-0.5f, 0));
	_data.positions.push_back(glm::vec3(0.5f,-0.5f, 0));
	_data.positions.push_back(glm::vec3(0.5f, 0.5f, 0));
	_data.positions.push_back(glm::vec3(-0.5f, 0.5f, 0));

	_data.normals.push_back(glm::vec3(0,0,1));
	_data.normals.push_back(glm::vec3(0,0,1));
	_data.normals.push_back(glm::vec3(0,0,1));
	_data.normals.push_back(glm::vec3(0,0,1));

	_data.indices.push_back(0);
	_data.indices.push_back(1);
	_data.indices.push_back(2);
	_data.indices.push_back(2);
	_data.indices.push_back(3);
	_data.indices.push_back(0);
}

Sphere::Sphere(int stacks, int slices)
{
	const float PI05 = pi * 0.5f;
	const float PI2 = pi * 2.0f;

	const float radius = 0.5f;

	// vertices
	for (int i = 0; i <= stacks; i++)
	{
		float v = static_cast<float>(i) / stacks;
		float phi = pi * v - PI05;
		for (int j = 0; j <= slices; j++)
		{
			float u = static_cast<float>(j) / slices;
			float theta = PI2 * u;

			auto& normal = _data.normals.emplace_back(glm::vec3(cos(phi) * cos(theta), -cos(phi) * sin(theta), sin(phi)));
			_data.positions.push_back(normal * radius);
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
				_data.indices.push_back(offset);
				_data.indices.push_back(offset + slices + 1);
				_data.indices.push_back(offset + 1);
			}
			if (i != stacks - 1)
			{
				_data.indices.push_back(offset + slices + 2);
				_data.indices.push_back(offset + 1);
				_data.indices.push_back(offset + slices + 1);
			}
		}
	}
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

	for (int i = 0; i < 6; i++)
	{
		int j = i * 24;
		_data.positions.push_back(glm::vec3(v[j + 0],  v[j + 1],  v[j + 2]));
		_data.positions.push_back(glm::vec3(v[j + 6],  v[j + 7],  v[j + 8]));
		_data.positions.push_back(glm::vec3(v[j + 12], v[j + 13], v[j + 14]));
		_data.positions.push_back(glm::vec3(v[j + 18], v[j + 19], v[j + 20]));

		_data.normals.push_back(glm::vec3(v[j + 3], v[j + 4], v[j + 5]));
		_data.normals.push_back(glm::vec3(v[j + 9], v[j + 10],v[j + 11]));
		_data.normals.push_back(glm::vec3(v[j + 15],v[j + 16],v[j + 17]));
		_data.normals.push_back(glm::vec3(v[j + 21],v[j + 22],v[j + 23]));

		_data.indices.push_back(i * 4 + 0);
		_data.indices.push_back(i * 4 + 1);
		_data.indices.push_back(i * 4 + 2);
		_data.indices.push_back(i * 4 + 2);
		_data.indices.push_back(i * 4 + 3);
		_data.indices.push_back(i * 4 + 0);
	}
}
