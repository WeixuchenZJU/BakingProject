#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UPWARD,
	DOWNWARD
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 100.0f;
const float SENSITIVTY = 0.01f;
const float ZOOM = 45.0f;

class Camera
{
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Direction;
	glm::vec3 Horizon;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	// Eular Angles
	double Yaw;
	double Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	Camera(glm::vec3 position, glm::vec3 direction=glm::vec3(0.0f,0.0f,-1.0f), float yaw = YAW, float pitch = PITCH):WorldUp(glm::vec3(0.0f,1.0f,0.0f)),MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM) {
		Position = position;
		Direction = direction;
		Horizon = glm::normalize(glm::cross(Direction, WorldUp));
		Up = glm::normalize(glm::cross(Horizon, Direction));
		Yaw = yaw;
		Pitch = pitch;
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Direction, Up);
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Direction * velocity;
		if (direction == BACKWARD)
			Position -= Direction* velocity;
		if (direction == LEFT)
			Position += Horizon * velocity;
		if (direction == RIGHT)
			Position -= Horizon* velocity;
		if (direction == UPWARD)
			Position -= Up * velocity;
		if (direction == DOWNWARD)
			Position += Up * velocity;
	}
//
//	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(double xoffset, double yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		updateCameraVectors();
	}
	void ProcessRightButtonPressed(float offset) {
		Position += Direction*offset*MouseSensitivity;
	}
//
private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Direction = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		Horizon = glm::normalize(glm::cross(Direction,WorldUp ));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Horizon, Direction));
	}
};
