// cbuffer ������� ����� �����

// 16byte ������ �����ؾ� ����
cbuffer CBTransform:register(b0) //<-- buffer 0�� ����
{
	matrix World;		// �������� : �� ���� ��ü���� ��ȿ�� ����		4 * 4*4 = 64byte
	matrix View;		// �������� : �� ���� ��ü���� ��ȿ�� ����
	matrix Projection;	// �������� : �� ���� ��ü���� ��ȿ�� ����

	float4 LightDir;
	float4 LightColor;

	float4 ambientColor; // �ֺ���

	// ���ݻ�
	float3 cameraPosition;	// ī�޶��� ��ġ
	float specularPower;	// ���ݻ� ����(��ī�ο�)
	float4 specularColor;	// ���ݻ籤 ����
};

struct VS_INPUT
{
	float4 Pos:POSITION; // <--���� : ����� 4�� ����� �Ѵ�. 3�̸� �۵� ����
	float3 Norm:NORMAL; // ����������
	float2 Tex:TEXCOORD0;
};

//struct VS_OUTPUT
struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float3 Norm:NORMAL; // ����������
	float2 Tex:TEXCOORD0;
	
	//float4 Color:COLOR0;
};

// �Ű������� ������ ���� IA���� ���޹��� ���̴�
// ���� ���� Pixel Shader�� ���޵ȴ�

// ���� ���̴� : ���� �ϳ��� �۵��ϴ� ���α׷�
//float4 main( float4 pos : POSITION, float4 Color:COLOR ) : SV_POSITION // SystemValue �ø�ƽ
//VS_OUTPUT main(float4 pos : POSITION, float4 Color : COLOR)
PS_INPUT main(VS_INPUT i)
{
	PS_INPUT o = (PS_INPUT)0;
	
	// �� ��ü�� ���� �󿡼��� ��ġ
	// �ü����͸� ���ϱ� ���� �� ��ҷ� �� ��ü�� ��ġ �����Ͱ� �ʿ�
	float4 worldPosition;

	// IA���� �Ѱܹ��� ���� ��ġ�����Ϳ�
	// ����, ��, ���� ��ȯ�� �����Ѵ�
	o.Pos = mul(i.Pos, World);		// mul ���̴� �Լ�, ���Ϳ� ����� ����

	// ���� �󿡼��� ������ ��ġ�� ������ѳ��´�
	worldPosition = o.Pos;

	o.Pos = mul(o.Pos, View);
	o.Pos = mul(o.Pos, Projection);
	
	o.Norm = mul(float4(i.Norm, 0), World).xyz;
	o.Tex = i.Tex;

	return o;
}