
// cbuffer ������� ����� �����

// 16byte ������ �����ؾ� ����
cbuffer CBTransform
{
	matrix World;		// �������� : �� ���� ��ü���� ��ȿ�� ����		4 * 4*4 = 64byte
	matrix View;		// �������� : �� ���� ��ü���� ��ȿ�� ����
	matrix Projection;	// �������� : �� ���� ��ü���� ��ȿ�� ����

	float4 LightDir;
	float4 LightColor;
};

/*struct VS_OUTPUT
{
	float4 Pos:SV_POSITION;
	float4 Color:COLOR0;
};*/

struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float3 Norm:NORMAL; // ����������
	//float4 Color:COLOR0;
};

// Vertex Shader�κ��� �����͸� ���޹޴´�
// ���������δ� ���� �ȼ������� ������

//float4 main() : SV_TARGET
//float4 main(VS_OUTPUT i) :SV_TARGET
float4 main(PS_INPUT i) :SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);

	// ���� vertex shading�ܰ迡�� ���޹��� ������ �������� �ȼ��� ĥ�Ѵ�
	//return i.Color;

	// ���̴� �ڵ忡�� ���󿬻��� �ڸ����� ���� �ͳ����� �����ϴ�
	// ��, ���ڸ����� ��� �ڸ����� ������ �����ϴ�
	//float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float4 color = 0;

	// �� ���Ϳ� �������͸� �̿��Ͽ� ������ ������
		
	// ���̴����� �����ϴ� �Լ�
	
	// float3 light = (0.0f, 0.0f, -1.0f);
	
	// ���� = ������ dot �������� <--[-1,1]
	// ��������(����) <-- [0,1]
	// �������� = ���� * ������� <-- ������ float, ��������� float4
	color = saturate(dot(LightDir, i.Norm)) * LightColor;

	color.a = 1;

	return color;
}