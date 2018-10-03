#pragma once

struct Transform
{
	glm::vec3 position;
	glm::vec3 scale = glm::vec3(1.0f);
	glm::quat rotation;
	glm::mat4 matrix;
	void UpdateMatrix()
	{
		matrix = glm::mat4();
		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, glm::angle(rotation), glm::axis(rotation));
		matrix = glm::scale(matrix, scale);
	}
	void UpdateMatrix(glm::mat4 &matrix)
	{
		matrix = glm::translate(matrix, position);
		//matrix = glm::rotate(matrix, glm::angle(rotation), glm::axis(rotation));
		//matrix = glm::scale(matrix, scale);
	}
	glm::mat4 GetMatrix()
	{
		UpdateMatrix();
		return matrix;
	}
	glm::mat4 GetRotation()
	{
		glm::mat4 outMatrix;
		outMatrix = glm::scale(outMatrix, scale);
		outMatrix = glm::rotate(outMatrix, glm::angle(-rotation), glm::axis(rotation));
		
		return outMatrix;
	}
	glm::mat4 LocalToGlobal(glm::mat4 &matrix)
	{
		//matrix = glm::scale(matrix, scale);
		matrix = glm::rotate(matrix, glm::angle(rotation), glm::axis(rotation));
		//matrix = glm::translate(matrix, position);
		
		
		return matrix;
	}
	glm::mat4 GetMatrixInv()
	{
		matrix = glm::mat4();
		//matrix = glm::translate(matrix, position);
		//matrix = glm::scale(matrix, scale);
		matrix = glm::rotate(matrix, glm::angle(rotation), glm::axis(rotation));
		//matrix = glm::translate(matrix, position);
		//
		return matrix;
	}
	glm::vec3 GetEulerAngles()
	{
		return glm::eulerAngles(rotation);
	}
	void Rotate(glm::vec3 eulerAngles)
	{
		//rotate accepts euler angles and builds a quaternion to match
		rotation = glm::quat(eulerAngles);
	}
	void RotateRelative(glm::vec3 eulerAngles)
	{
		rotation = glm::quat(eulerAngles + glm::eulerAngles(rotation));
	}
};