
// cbuffer ������� ����� �����
// 16byte ������ �����ؾ� ����
cbuffer CBTransform
{
	matrix World;		// �������� : �� ���� ��ü���� ��ȿ�� ����
	matrix View;		// �������� : �� ���� ��ü���� ��ȿ�� ����
	matrix Projection;	// �������� : �� ���� ��ü���� ��ȿ�� ����
};

struct VS_OUTPUT
{
	float4 Pos:SV_POSITION;
	float4 Color:COLOR0;
};

// �Ű������� ������ ���� IA���� ���޹��� ���̴�
// ���� ���� Pixel Shader�� ���޵ȴ�

// ���� ���̴� : ���� �ϳ��� �۵��ϴ� ���α׷�
//float4 main( float4 pos : POSITION, float4 Color:COLOR ) : SV_POSITION // SystemValue �ø�ƽ
VS_OUTPUT main(float4 pos : POSITION, float4 Color : COLOR)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	//o.Pos = pos;

	// IA���� �Ѱܹ��� ���� ��ġ�����Ϳ�
	// ����, ��, ���� ��ȯ�� �����Ѵ�
	o.Pos = mul(pos, World);		// mul ���̴� �Լ�, ���Ϳ� ����� ����
	o.Pos = mul(o.Pos, View);
	o.Pos = mul(o.Pos, Projection);

	// ���� ������ �״�� ���� �ܰ�� �ѱ��
	o.Color = Color;

	return o;
}