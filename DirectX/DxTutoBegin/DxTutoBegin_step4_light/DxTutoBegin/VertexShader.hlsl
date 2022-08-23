
// cbuffer 상수버퍼 만들기 예약어

// 16byte 단위로 정렬해야 안전
cbuffer CBTransform
{
	matrix World;		// 전역변수 : 이 파일 전체에서 유효한 변수		4 * 4*4 = 64byte
	matrix View;		// 전역변수 : 이 파일 전체에서 유효한 변수
	matrix Projection;	// 전역변수 : 이 파일 전체에서 유효한 변수

	float4 LightDir;
	float4 LightColor;
};

struct VS_INPUT
{
	float4 Pos:POSITION; // <--주의 : 여기는 4로 맞춰야 한다. 3이면 작동 안함
	float3 Norm:NORMAL; // 법선데이터
};

//struct VS_OUTPUT
struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float3 Norm:NORMAL; // 법선데이터
	//float4 Color:COLOR0;
};

// 매개변수로 들어오는 것은 IA에서 전달받은 것이다
// 리턴 값은 Pixel Shader로 전달된다

// 정점 셰이더 : 정점 하나당 작동하는 프로그램
//float4 main( float4 pos : POSITION, float4 Color:COLOR ) : SV_POSITION // SystemValue 시맨틱
//VS_OUTPUT main(float4 pos : POSITION, float4 Color : COLOR)
PS_INPUT main(VS_INPUT i)
{
	PS_INPUT o = (PS_INPUT)0;

	//o.Pos = pos;

	// IA에서 넘겨받은 정점 위치데이터에
	// 월드, 뷰, 투영 변환을 적용한다
	o.Pos = mul(i.Pos, World);		// mul 셰이더 함수, 벡터와 행렬의 곱셈
	o.Pos = mul(o.Pos, View);
	o.Pos = mul(o.Pos, Projection);

	// 일단은 그냥 다음 단계(pixel shader)로 넘기는 것으로 테스트, 법선데이터
	// 그냥 로컬 좌표계의 법선데이터로 인지
	//o.Norm = i.Norm;

	// 월드변환을 적용하여 월드 좌표계의 법선데이터로 인지

	// 위치로 인지하고 있다 (x,y,z,1)
	//o.Norm = mul(float4(i.Norm, 1), World).xyz;

	// 벡터로 인지하고 있다 (x,y,z,0)
	o.Norm = mul(float4(i.Norm, 0), World).xyz;

	// 색상 정보는 그대로 다음 단계로 넘긴다
	//o.Color = i.Color;

	return o;
}