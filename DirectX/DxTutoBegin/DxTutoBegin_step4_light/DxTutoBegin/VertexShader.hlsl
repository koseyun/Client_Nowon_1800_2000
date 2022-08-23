
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

struct VS_INPUT
{
	float4 Pos:POSITION; // <--���� : ����� 4�� ����� �Ѵ�. 3�̸� �۵� ����
	float3 Norm:NORMAL; // ����������
};

//struct VS_OUTPUT
struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float3 Norm:NORMAL; // ����������
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

	//o.Pos = pos;

	// IA���� �Ѱܹ��� ���� ��ġ�����Ϳ�
	// ����, ��, ���� ��ȯ�� �����Ѵ�
	o.Pos = mul(i.Pos, World);		// mul ���̴� �Լ�, ���Ϳ� ����� ����
	o.Pos = mul(o.Pos, View);
	o.Pos = mul(o.Pos, Projection);

	// �ϴ��� �׳� ���� �ܰ�(pixel shader)�� �ѱ�� ������ �׽�Ʈ, ����������
	// �׳� ���� ��ǥ���� ���������ͷ� ����
	//o.Norm = i.Norm;

	// ���庯ȯ�� �����Ͽ� ���� ��ǥ���� ���������ͷ� ����

	// ��ġ�� �����ϰ� �ִ� (x,y,z,1)
	//o.Norm = mul(float4(i.Norm, 1), World).xyz;

	// ���ͷ� �����ϰ� �ִ� (x,y,z,0)
	o.Norm = mul(float4(i.Norm, 0), World).xyz;

	// ���� ������ �״�� ���� �ܰ�� �ѱ��
	//o.Color = i.Color;

	return o;
}