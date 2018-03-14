#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
Camera::Camera()
{
	
}


Camera::~Camera()
{
}

PerspectiveCamera::PerspectiveCamera(glm::vec3 center, glm::vec3 dir, glm::vec3 up, float angle)
{
	this->m_center = center;
	dir=glm::normalize(dir);
	up = glm::normalize(up);
	this->m_dir = dir;

	this->m_hor = glm::cross(dir, up);
	this->m_hor=glm::normalize(this->m_hor);

	this->m_up = glm::cross(this->m_hor, dir);
	this->m_up=glm::normalize(this->m_up);
	//cout << "Up vec:" << this->m_up << endl;
	//cout << "Hor vec:" << this->m_hor << endl;
	this->m_angle = angle;
	//printf("tan45=%.2f,%.2f,%.2f\n", tan(45.0f), tan(glm::radians(45.0f)), tan(3.1415926f / 2));	
	
	m_sensor_width = 0.025f;
	m_sensor_height = 0.025f;
	m_focallength = 0.035f;

	//由于透视摄像机产生视锥，因此相机的中心点center作为视锥的顶点，我们还需要一个虚拟的成像平面，将pos作为成像平面的中心
	this->m_pos = this->m_center +m_focallength * this->m_dir;


}
PerspectiveCamera::~PerspectiveCamera()
{
}
Ray PerspectiveCamera::generateRay(glm::vec2 point) {

	float ratio = 1.0f/*height * 1.0 / width*/;//成像平面的宽高比
									   //虚拟成像平面的左下角位置
									   //Vec3f min = this->m_pos - this->m_up*0.25  - this->m_hor*0.5;
	glm::vec3 min = this->m_pos - 0.5f*this->m_up*m_sensor_height - 0.5f*this->m_hor*m_sensor_width;
	//用户输入的像素点，归一化到0，1区间
	float s, t;
	t = point.x;
	s = point.y;
	//Vec3f org = min + t*this->m_hor + s*0.5*this->m_up;
	glm::vec3 org = min + t * m_sensor_width* this->m_hor + s * m_sensor_height*this->m_up;
	glm::vec3 dire = org - this->m_center;
	org = this->m_center;
	dire=glm::normalize(dire);
	return Ray(org, dire);
}
float PerspectiveCamera::getTMin() const {
	return 0;
}
void PerspectiveCamera::glInit(int w, int h)

{

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//gluPerspective(m_angle*180.0 / 3.14159265358979323846, (float)w / float(h), 0.5, 1000.0);
}


// ====================================================================

// Place a perspective camera within an OpenGL scene

// ====================================================================


void PerspectiveCamera::glPlaceCamera(void)

{

	/*gluLookAt(m_center.x(), m_center.y(), m_center.z(),

		m_center.x() + m_dir.x(), m_center.y() + m_dir.y(), m_center.z() + m_dir.z(),

		m_up.x(), m_up.y(), m_up.z());*/
}


void PerspectiveCamera::dollyCamera(float dist)
{
	m_center += m_dir * dist;


	// ===========================================
	// ASSIGNMENT 3: Fix any other affected values
	// ===========================================
	this->m_pos = this->m_center + m_lambda * this->m_dir;


}

void PerspectiveCamera::truckCamera(float dx, float dy)
{
	glm::vec3 horizontal;
	horizontal = glm::cross(m_dir, m_up);
	horizontal = glm::normalize(horizontal);

	glm::vec3 screenUp;
	screenUp = glm::cross(horizontal, m_dir);
	screenUp = glm::normalize(screenUp);
	m_center += horizontal * dx + screenUp * dy;
	m_hor = horizontal;

	// ===========================================

	// ASSIGNMENT 3: Fix any other affected values

	// ===========================================
	this->m_pos = this->m_center + m_lambda * this->m_dir;


}


// ====================================================================

// rotateCamera: Rotate around the m_up and horizontal vectors

// ====================================================================


void PerspectiveCamera::rotateCamera(float rx, float ry)
{
	glm::vec3 horizontal;
	horizontal = glm::cross(m_dir, m_up);
	horizontal = glm::normalize(horizontal);


	//// Don't let the model flip m_upside-down (There is a singularity

	//// at the poles when 'm_up' and 'm_dir' are aligned)
	//float tiltAngle = acos(glm::dot(m_up,m_dir));
	//if (tiltAngle - ry > 3.13)

	//	ry = tiltAngle - 3.13;
	//else if (tiltAngle - ry < 0.01)
	//	ry = tiltAngle - 0.01;

	//Matrix rotMat = Matrix::MakeAxisRotation(m_up, rx);

	//rotMat *= Matrix::MakeAxisRotation(m_hor, ry);

	//rotMat.Transform(m_center);
	//rotMat.TransformDirection(m_dir);

	//m_dir.Normalize();

	//// ===========================================
	//// ASSIGNMENT 3: Fix any other affected values
	//// ===========================================
	//rotMat.TransformDirection(m_hor);

	//rotMat.TransformDirection(m_up);
	//this->m_pos = this->m_center + m_lambda * this->m_dir;

}


// ====================================================================


// ====================================================================

