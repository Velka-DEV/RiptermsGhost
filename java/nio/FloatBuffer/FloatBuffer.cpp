#include "FloatBuffer.h"

float FloatBuffer::get(int index)
{
	if (!instance) {
		std::cerr << "FloatBuffer instance is null." << std::endl;
		return 0.0f;
	}

	jclass floatBufferClass = env->GetObjectClass(instance);
	if (!floatBufferClass) {
		std::cerr << "Failed to get FloatBuffer class." << std::endl;
		return 0.0f;
	}

	jmethodID getMethodID = env->GetMethodID(floatBufferClass, "get", "(I)F");
	if (!getMethodID) {
		std::cerr << "Failed to get method ID for 'get'." << std::endl;
		return 0.0f;
	}

	jfloat result = env->CallFloatMethod(instance, getMethodID, index);
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->ExceptionClear();
		std::cerr << "Exception occurred while calling FloatBuffer::get." << std::endl;
		return 0.0f;
	}

	std::cout << "FloatBuffer::get(" << index << ") = " << result << std::endl;
	return result;
}

Ripterms::Maths::Matrix FloatBuffer::toMatrix(int lines, int columns)
{
	Ripterms::Maths::Matrix result(lines, columns);
	if (!instance)
	{
		std::cerr << "Failed to convert FloatBuffer to Matrix." << std::endl;
		return result;
	}
	
	int c = 0;
	for (int i = 0; i < lines; ++i)
	{
		for (int b = 0; b < columns; ++b)
		{
			result[i][b] = get(c);
			c++;
		}
	}
	return result;
}
