#pragma once
#include <math.h>
#include <cfloat> // �۽Ƿ�(���� ���� ��)�� ���ؼ�

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

	// �Ű����� �ִ� ������
	SVector2D(float tX, float tY) : mX(tX), mY(tY)
	{

	}

	// ���������
	SVector2D(const SVector2D& tVector)
	{
		mX = tVector.mX;
		mY = tVector.mY;
	}
	// ������Ի�����
	/*void operator=(const SVector2D& tVector)
	{
		mX = tVector.mX;
		mY = tVector.mY;
	}*/

	// ���ͳ����� ����(����)
	const SVector2D operator+(const SVector2D& tVector2D) const
	{
		SVector2D tResult;
		tResult.mX = mX + tVector2D.mX;
		tResult.mY = mY + tVector2D.mY;

		return tResult;
	}

	const SVector2D operator-(const SVector2D& tVector2D) const
	{
		SVector2D tResult;
		tResult.mX = mX - tVector2D.mX;
		tResult.mY = mY - tVector2D.mY;

		return tResult;
	}

	// ����Ÿ�� �տ� const : ��ȯ�� read only
	// �Ű������� const : �Ű����� read only
	// 
	// ������ ��Į���
	SVector2D operator*(const float tScalar)
	{
		SVector2D tResult;
		tResult.mX = mX * tScalar;
		tResult.mY = mY * tScalar;

		return tResult;
	}

	// ������ ��Į���(���ǻ� / ��ȣ�� ������ �����ε��Ѵ�)
	SVector2D operator/(const float tScalar) const
	{
		SVector2D tResult;
		tResult.mX = mX / tScalar;
		tResult.mY = mY / tScalar;

		return tResult;
	}
	// �ݴ����
	const SVector2D operator-() const
	{
		return SVector2D(-mX, -mY);
	}

	SVector2D& operator+=(const SVector2D& tOther)
	{
		return *this = *this + tOther;
	}

	SVector2D& operator-=(const SVector2D& tOther)
	{
		return *this = *this - tOther;
	}

	SVector2D& operator*=(float tScalar)
	{
		return *this = *this * tScalar;
	}

	SVector2D& operator/=(float tScalar)
	{
		return *this = *this / tScalar;
	}

	// �񱳿�����
	bool operator==(const SVector2D& tOther) const
	{
		return (mX == tOther.mX) && (mY == tOther.mY);
	}

	bool operator!=(const SVector2D& tOther) const
	{
		return !(*this == tOther);
	}

	bool operator<(const SVector2D& tOther) const
	{
		if (mX != tOther.mX)
		{
			return mX < tOther.mX;
		}

		if (mY != tOther.mY)
		{
			return mY < tOther.mY;
		}

		return false;
	}

	// ���� Dot Product
	float Dot(const SVector2D& tOther) const
	{
		return (mX * tOther.mX) + (mY * tOther.mY);
	}

	// ���� Cross Product
	// å���� �̷��� �����̶�� ��������, ��Ȯ�� ����ϸ� �̰��� Ʋ�� ����̴�
	// ������ ��Į�� ��(2by2 ����� ��Ľ��� ���� ���� ���̴�) ������ �����ϰڴ�
	float Determinent(const SVector2D& tOther) const
	{
		return (mX * tOther.mX) - (mY * tOther.mY);
	}

	float Length() const
	{
		return sqrt(Dot(*this));
	}

	float Distance(const SVector2D& tOther) const
	{
		return (*this - tOther).Length();
	}

	// ������ ����ȭ : ũ�Ⱑ 1�� ���ͷ� �����
	SVector2D Normalize() const
	{
		const float tLength = Length();

		// ����ó��
		if (tLength < FLT_EPSILON)
		//if (tLength < __FLT_EPSILON__)
		{
			//return SVector2D::ZERO;
		}

		return *this / tLength; // ũ����� 1�� ��Į��� �Ͽ���
	}

	bool IsZero() const
	{
		return *this == SVector2D::ZERO;
	}

	static const SVector2D ZERO;
	static const SVector2D LEFT;
	static const SVector2D RIGHT;
	static const SVector2D DOWN;
	static const SVector2D UP;

};

