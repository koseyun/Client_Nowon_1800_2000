#pragma once
#include "Creature.h"

// Ŭ���� ���
// class Ŭ���� �̸� : ��ӹ��� Ŭ���� �̸� (�θ�Ŭ����)

class Dog :
    public Creature
{
private:
    bool followEnable;

    //friend : friend class Ŭ������
    // �̶�� ����� Ŭ����Ÿ���� ��ü���� ���������ڿ� ������� ����� ���� �����ϵ��� ���ش�.
    // �ڵ� ���̴ϱ� �����ϸ� �Ⱦ����� ��������
    friend class Human;

public:
    int tailLength;

public:
    void Bite(Creature* creature);
    void IFourLeggedWalker();
};

