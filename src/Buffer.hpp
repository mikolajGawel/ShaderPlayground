#pragma once
class Buffer
{
	unsigned int m_ID;
	bool dynamic;
	int type;
	bool s_created = false;
public:
	Buffer(int type, bool dynamic);
	~Buffer();
	void storeData(void* data, size_t size);
	void bindBuffer();
};

