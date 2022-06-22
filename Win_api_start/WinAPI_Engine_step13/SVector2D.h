#pragma once

struct SVector2D
{
	// 2����
	float mX = 0.0f;
	float mY = 0.01f;

	SVector2D(): mX(0.0f), mY(0.0f)
	{

	}
	~SVector2D()
	{

	}

	// �ŰԺ���
	SVector2D(float tX, float tY) : mX(tX), mY(tY)
	{

	}

	// ���������
	SVector2D(const SVector2D& tVector)
	{
		mX = tVector.mX;
		mY = tVector.mY;
	}

	// ���ͳ����� ����(����)
	SVector2D operator+(const SVector2D& tVector2D)
	{
		SVector2D tResult;
		tResult.mX = mX + tVector2D.mX;
		tResult.mY = mY + tVector2D.mY;

		return tResult;
	}

	SVector2D operator-(const SVector2D& tVector2D)
	{
		SVector2D tResult;
		tResult.mX = mX - tVector2D.mX;
		tResult.mY = mY - tVector2D.mY;

		return tResult;
	}

	// ������ ��Į���
	SVector2D operator*(const float tScalar)
	{
		SVector2D tResult;
		tResult.mX = mX * tScalar;
		tResult.mY = mY * tScalar;

		return tResult;
	}

};

