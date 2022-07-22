#pragma once


#include <math.h>
#include <cfloat> //�۽Ƿ� �� ���ؼ�
using namespace std;


/*
	2D Vector

	������ ����(����)
	������ ��Į���

*/

//class SVector2D
struct SVector2D
{
	float mX = 0.0f;
	float mY = 0.0f;

	//������
	SVector2D() :
		mX(0.0f),
		mY(0.0f)
	{

	}
	//�Ű����� �ִ� ������
	SVector2D(float tX, float tY) :
		mX(tX),
		mY(tY)
	{

	}
	//���� ������
	SVector2D(const SVector2D& tVector2D)
	{
		mX = tVector2D.mX;
		mY = tVector2D.mY;
	}



	//������ �����ε�

	////���� ���� ������
	//void operator=(const SVector2D& tVector2D)
	//{
	//	mX = tVector2D.mX;
	//	mY = tVector2D.mY;
	//}
	////������ ����
	//SVector2D operator+(const SVector2D& tVector2D)
	//{
	//	SVector2D tResult;

	//	tResult.mX = mX + tVector2D.mX;
	//	tResult.mY = mY + tVector2D.mY;

	//	return tResult;
	//}
	//SVector2D operator-(const SVector2D& tVector2D)
	//{
	//	SVector2D tResult;

	//	tResult.mX = mX - tVector2D.mX;
	//	tResult.mY = mY - tVector2D.mY;

	//	return tResult;
	//}

	////������ ��Į���
	//SVector2D operator*(const float tScalar)
	//{
	//	SVector2D tResult;

	//	tResult.mX = mX * tScalar;
	//	tResult.mY = mY * tScalar;

	//	return tResult;
	//}
    
    // 
    //DOT PRODUCT ����
    float Dot(const SVector2D& tOther) const
    {
        return (mX * tOther.mX) + (mY * tOther.mY);
    }

    //CROSS PRODUCT ����
    //å���� �̷��� �����̶�� ��������,  ��Ȯ�� ����ϸ� �̰��� Ʋ�� ����̴�.
    //������ ��Į�� ��(2by2 ����� ��Ľ��� ���� ���� ���̴�) ������ �����ϰڴ�.
    float Determinent(const SVector2D& tOther) const
    {
        return (mX * tOther.mY) - (mY * tOther.mX);
    }

    float Length() const
    {
        return sqrt(Dot(*this));
        //for windows os
        //return std::sqrt(Dot(*this));
    }

    float Distance(const SVector2D& tOther) const
    {
        return (*this - tOther).Length();
    }


    SVector2D Normalize() const
    {
        const float tLength = Length();

        //for windows os
        if (tLength < FLT_EPSILON)
        //if (tLength < __FLT_EPSILON__)
        {
            return SVector2D::ZERO;
        }

        return *this / tLength;
    }

    bool IsZero() const
    {
        return *this == SVector2D::ZERO;
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

    const SVector2D operator+(const SVector2D& tOther) const
    {
        return SVector2D(mX + tOther.mX, mY + tOther.mY);
    }

    const SVector2D operator-(const SVector2D& tOther) const
    {
        return SVector2D(mX - tOther.mX, mY - tOther.mY);
    }

    const SVector2D operator*(float tScalar) const
    {
        return SVector2D(mX * tScalar, mY * tScalar);
    }
    const SVector2D operator/(float tScalar) const
    {
        return SVector2D(mX / tScalar, mY / tScalar);
    }

    const SVector2D operator-() const
    {
        return SVector2D(-mX, -mY);
    }

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


    static const SVector2D ZERO;
    static const SVector2D LEFT;
    static const SVector2D RIGHT;
    static const SVector2D DOWN;
    static const SVector2D UP;

};

