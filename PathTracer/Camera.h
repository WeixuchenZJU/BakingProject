#pragma once

#include "ray.h"

class Camera
{
public:
	Camera();
	~Camera();
	virtual Ray generateRay(glm::vec2 point) = 0;
	virtual float getTMin() const = 0;
	//��ʼ��ͶӰģʽ
	virtual void glInit(int w, int h) = 0;
	//�������λ��
	virtual void glPlaceCamera(void) = 0;
	//���������ƽ�����
	virtual void dollyCamera(float dist) = 0;
	//��ֱ���������ƽ�����
	virtual void truckCamera(float dx, float dy) = 0;
	//��ˮƽ�����ʹ�ֱ������ת���
	virtual void rotateCamera(float rx, float ry) = 0;

};
class PerspectiveCamera :
	public Camera
{
public:
	PerspectiveCamera(glm::vec3 center, glm::vec3 dir, glm::vec3 up, float angle);
	~PerspectiveCamera();
	virtual Ray generateRay(glm::vec2 point);
	virtual float getTMin() const;
	virtual void glInit(int w, int h);


	virtual void glPlaceCamera(void);
	virtual void dollyCamera(float dist);

	virtual void truckCamera(float dx, float dy);

	virtual void rotateCamera(float rx, float ry);
private:
	glm::vec3 m_center;
	glm::vec3 m_dir;
	glm::vec3 m_up;
	glm::vec3 m_hor;
	glm::vec3 m_pos;
	float m_angle;
	float m_lambda;
	float m_sensor_width;
	float m_sensor_height;
	float m_focallength;
};
