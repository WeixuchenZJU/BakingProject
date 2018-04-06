#pragma once
class Filter
{
public:
	Filter(float r, float size);
	~Filter();
private:
	float m_radius;
	float m_size;
};

