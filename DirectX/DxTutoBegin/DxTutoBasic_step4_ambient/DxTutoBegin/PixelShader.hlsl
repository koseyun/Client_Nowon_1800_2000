/*struct VS_OUTPUT
{
	float4 Pos:SV_POSITION;
	float4 Color:COLOR0;
};*/

//Texture2D txDiffuse;
//SamplerState samLinear;

// ���� ��ȣ�� ��������� ������ �� �� �ִ�
// �������� ������ �ڵ����� �Ű��ش�
Texture2D txDiffuse:register(t0); // texture 0�� ����
SamplerState samLinear:register(s0); //sampler 0�� ����

// cbuffer ������� ����� �����
// 16byte ������ �����ؾ� ����
cbuffer CBTransform:register(b0) //<-- buffer 0�� ����
{
	matrix World;		// �������� : �� ���� ��ü���� ��ȿ�� ����		4 * 4*4 = 64byte
	matrix View;		// �������� : �� ���� ��ü���� ��ȿ�� ����
	matrix Projection;	// �������� : �� ���� ��ü���� ��ȿ�� ����

	float4 LightDir;
	float4 LightColor;
	float4 ambientColor;
};

struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float3 Norm:NORMAL; // ����������
	float2 Tex:TEXCOORD0;
	
	//float4 Color:COLOR0;
};

//float4 main():SV_TARGET
//float4 main(VS_OUTPUT i):SV_TARGET
float4 main(PS_INPUT i) :SV_TARGET
{
	// ���� ����
	float4 color = 0;

	// �ֺ���
	// �⺻ ������ �ֺ������� �ϴ� ����
	color = ambientColor;

	// ���ݻ籤
	// ���ݻ� ����
	float4 diffuseColor = 0;
	// ����(���� ����)
	float lightIntensity = 0;
	lightIntensity = saturate(dot(LightDir, i.Norm)); // ����Ʈ �����

	// ����(���ݻ� ����� ���� ����)�� 0���� ū ��쿡�� ����������� ����
	// (�ֳ��ϸ� 0�� ��츦 �ϸ� ������ ������ ������� -->0)
	if (lightIntensity > 0.0f)
	{
		diffuseColor = LightColor * lightIntensity; // ���ݻ� ���� ����

		color = color + diffuseColor;
	}

	// �ؽ��� ����
	float4 texColor = txDiffuse.Sample(samLinear, i.Tex);	

	// �ؽ��� ����� ����(�ֺ���, ���ݻ籤)������ ����			// �߿�!!
	//color = texColor * diffuseColor;
	color = texColor * color;
	color.a = 1;

	return color;
}